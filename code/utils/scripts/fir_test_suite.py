import numpy as np
import matplotlib.pyplot as plt
import subprocess
import os
import shutil

FIG_DIR = "../../../docs/figures"
os.makedirs(FIG_DIR, exist_ok=True)

# ---------------- CONFIG ---------------- #
FS = 48000
DURATION = 2.0
N = int(FS * DURATION)
OUT_DIR = "out"
FILTER_BIN = "./fir_filter_utn"
COEFF_FILE = "coef_bandpass_hamming_5k.txt"

os.makedirs(OUT_DIR, exist_ok=True)

# ---------------------------------------- #

def run_filter(input_file, tag):
    cmd = [
        FILTER_BIN,
        f"-fc={COEFF_FILE}",
        input_file
    ]

    print("\nRunning:", " ".join(cmd))
    subprocess.run(cmd)

    # Renombrar salida
    src = os.path.join(OUT_DIR, "outputFixed.pcm")
    dst = os.path.join(OUT_DIR, f"output_{tag}.pcm")

    if os.path.exists(src):
        shutil.move(src, dst)
    else:
        print("ERROR: no se generó outputFixed.pcm")

    return dst


def write_pcm(signal, filename):
    signal = np.clip(signal, -1, 1)
    signal_q31 = (signal * (2**31 - 1)).astype(np.int32)
    signal_q31.tofile(filename)


def read_pcm(file):
    data = np.fromfile(file, dtype=np.int32)
    return data / (2**31 - 1)


# ---------------- TEST 1: IMPULSO ---------------- #
def test_impulse():
    x = np.zeros(N)
    x[0] = 1.0

    file = os.path.join(OUT_DIR, "input_impulse.pcm")
    write_pcm(x, file)

    return run_filter(file, "impulse")


# ---------------- TEST 2: MULTITONO ---------------- #
def test_multitone():
    t = np.arange(N) / FS

    f1 = 200      # fuera
    f2 = 2500     # dentro
    f3 = 22000     # fuera

    x = 0.3*np.sin(2*np.pi*f1*t) + \
        0.4*np.sin(2*np.pi*f2*t) + \
        0.3*np.sin(2*np.pi*f3*t)

    file = os.path.join(OUT_DIR, "input_multitone.pcm")
    write_pcm(x, file)

    return run_filter(file, "multitone")


# ---------------- TEST 3: CHIRP ---------------- #
def test_chirp():
    t = np.arange(N) / FS

    f0 = 20
    f1 = 20000

    k = (f1 - f0) / DURATION
    x = np.sin(2*np.pi*(f0*t + 0.5*k*t**2))

    file = os.path.join(OUT_DIR, "input_chirp.pcm")
    write_pcm(x, file)

    return run_filter(file, "chirp")


# ---------------- TEST 4: RUIDO ---------------- #
def test_noise():
    x = np.random.normal(0, 0.3, N)

    file = os.path.join(OUT_DIR, "input_noise.pcm")
    write_pcm(x, file)

    return run_filter(file, "noise")


# ---------------- FFT ---------------- #
def plot_fft(signal, title):
    NFFT = 8192
    y = signal[:NFFT]

    window = np.hanning(len(y))
    y = y * window

    Y = np.fft.fft(y, NFFT)
    freqs = np.fft.fftfreq(NFFT, 1/FS)

    half = NFFT // 2
    Y = Y[:half]
    freqs = freqs[:half]

    mag = 20 * np.log10(np.abs(Y) / np.max(np.abs(Y)) + 1e-12)

    plt.plot(freqs, mag, label=title)


# ---------------- PLOTEO EN EL TIEMPO ---------------- #

def plot_time_signal(x, y, title, filename):
    T_SHOW = 2  # 2s (zoom útil)
    N_SHOW = int(FS * T_SHOW)

    t = np.arange(N_SHOW) / FS

    plt.figure(figsize=(8,5))

    plt.plot(t, x[:N_SHOW], label="Entrada")
    plt.plot(t, y[:N_SHOW], label="Salida")

    gain = np.max(np.abs(y)) / (np.max(np.abs(x)) + 1e-12)
    gain_db = 20 * np.log10(gain + 1e-12)

    plt.title(f"{title}\nGanancia ≈ {gain_db:.2f} dB")
    plt.xlabel("Tiempo [s]")
    plt.ylabel("Amplitud")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, filename), dpi=300)
    plt.close()

def plot_time_signal_zoom(x, y, title, filename):
    T_SHOW = 0.01  # 10ms (zoom útil)
    N_SHOW = int(FS * T_SHOW)

    t = np.arange(N_SHOW) / FS

    plt.figure(figsize=(8,5))

    plt.plot(t, x[:N_SHOW], label="Entrada")
    plt.plot(t, y[:N_SHOW], label="Salida")

    gain = np.max(np.abs(y)) / (np.max(np.abs(x)) + 1e-12)
    gain_db = 20 * np.log10(gain + 1e-12)

    plt.title(f"{title}\nGanancia ≈ {gain_db:.2f} dB")
    plt.xlabel("Tiempo [s]")
    plt.ylabel("Amplitud")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, filename), dpi=300)
    plt.close()

# ---------------- RESULTS ---------------- #

def plot_results(results):
    # -------- IMPULSO -------- #
    x_imp = read_pcm(os.path.join(OUT_DIR, "input_impulse.pcm"))
    y_imp = read_pcm(results["impulse"])

    t = np.arange(200) / FS

    plt.figure(figsize=(8, 5))

    plt.subplot(2,1,1)
    plt.stem(t, x_imp[:200])
    plt.title("Impulso de entrada")
    plt.xlabel("Tiempo [s]")
    plt.ylabel("Amplitud")
    plt.grid(True)

    plt.subplot(2,1,2)
    plt.stem(t, y_imp[:200])
    plt.title("Respuesta al impulso")
    plt.xlabel("Tiempo [s]")
    plt.ylabel("Amplitud")
    plt.grid(True)

    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "impulse_response.png"), dpi=300)
    plt.close()

    # -------- FFT RESPUESTA AL IMPULSO -------- #
    plt.figure(figsize=(8,5))
    plot_fft(y_imp, "Respuesta al impulso")
    plt.title("FFT - Respuesta al impulso (H(f))")
    plt.xlabel("Frecuencia [Hz]")
    plt.ylabel("Magnitud [dB]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "fft_impulse_response.png"), dpi=300)
    plt.close()

    # -------- FFT MULTITONO -------- #
    plt.figure(figsize=(8,5))
    plot_fft(read_pcm(results["multitone"]), "Multitono")
    plt.title("FFT - Señal multitono filtrada")
    plt.xlabel("Frecuencia [Hz]")
    plt.ylabel("Magnitud [dB]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "fft_multitone.png"), dpi=300)
    plt.close()

    # -------- FFT CHIRP -------- #
    plt.figure(figsize=(8,5))
    plot_fft(read_pcm(results["chirp"]), "Chirp")
    plt.title("FFT - Barrido en frecuencia filtrado")
    plt.xlabel("Frecuencia [Hz]")
    plt.ylabel("Magnitud [dB]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "fft_chirp.png"), dpi=300)
    plt.close()

    # -------- FFT RUIDO -------- #
    plt.figure(figsize=(8,5))
    plot_fft(read_pcm(results["noise"]), "Ruido")
    plt.title("FFT - Ruido gaussiano filtrado")
    plt.xlabel("Frecuencia [Hz]")
    plt.ylabel("Magnitud [dB]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "fft_noise.png"), dpi=300)
    plt.close()

    x_multi = read_pcm(os.path.join(OUT_DIR, "input_multitone.pcm"))
    y_multi = read_pcm(results["multitone"])

    plot_time_signal_zoom(
        x_multi,
        y_multi,
        "Señal multitono (entrada vs salida)",
        "time_multitone.png"
    )

    x_chirp = read_pcm(os.path.join(OUT_DIR, "input_chirp.pcm"))
    y_chirp = read_pcm(results["chirp"])

    plot_time_signal(
        x_chirp,
        y_chirp,
        "Barrido en frecuencia (entrada vs salida)",
        "time_chirp.png"
    )

    x_noise = read_pcm(os.path.join(OUT_DIR, "input_noise.pcm"))
    y_noise = read_pcm(results["noise"])

    plot_time_signal_zoom(
        x_noise,
        y_noise,
        "Ruido gaussiano (entrada vs salida)",
        "time_noise.png"
    )

    print(f"\nPlots guardados en: {FIG_DIR}")



# ---------------- MAIN ---------------- #
if __name__ == "__main__":
    results = {}

    print("\n=== TEST 1: IMPULSO ===")
    results["impulse"] = test_impulse()

    print("\n=== TEST 2: MULTITONO ===")
    results["multitone"] = test_multitone()

    print("\n=== TEST 3: CHIRP ===")
    results["chirp"] = test_chirp()

    print("\n=== TEST 4: RUIDO ===")
    results["noise"] = test_noise()

    print("\n=== GENERANDO PLOTS ===")
    plot_results(results)
