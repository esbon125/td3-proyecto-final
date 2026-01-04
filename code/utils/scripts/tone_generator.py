#!/usr/bin/env python
import numpy as np

# Parámetros
fs = 48000          # Sample rate (Hz)
f = 10              # Frecuencia senoidal (Hz)
f2= 5000
duration = 1.0      # Duración (segundos)
amplitude = 0.85     # Amplitud relativa (0.0 a 1.0)
amplitude2= 0.15

# Eje temporal
t = np.arange(0, duration, 1/fs)

# Señal senoidal
signal = amplitude * np.sin(2 * np.pi * f * t)
signal_multitone = (amplitude *np.sin(2 * np.pi * f * t)) + (amplitude2 * np.sin(2 * np.pi * f2 * t))

# Escalado a int32 (PCM 32 bits con signo)
pcm32 = np.int32(signal * (2**31 - 1))
pcm32_multitone = np.int32(signal_multitone * (2**31 - 1))

# Guardar archivo PCM crudo (little-endian)
pcm32.tofile("../bin_files/sine_10hz_32bit.pcm")
pcm32_multitone.tofile("../bin_files/sine_10hz_and_100hz_32bit.pcm")

print("Archivo generado: sine_10hz_32bit.pcm")
print("Archivo generado: sine_10hz_and_100hz_32bit.pcm")

print(f"Muestras: {len(pcm32)}")
