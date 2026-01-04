#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import os

# --- Configuration for the PCM file ---

pcm_file_path = "../bin_files/sine_10hz_32bit.pcm" 
pcm_file_path_multitone = "../bin_files/sine_10hz_and_100hz_32bit.pcm"  
pcm_file_path_output = "../bin_files/outputFixed.pcm"  
# Define the data type. Common PCM formats are:
# 'h' for 16-bit signed integer (short)
# 'b' for 8-bit signed integer
# 'i' for 32-bit signed integer (int)
dtype_format = 'i' 

# Optional: You can specify the sampling rate to have time on the x-axis.
# Example: 44100 Hz (CD quality)
sampling_rate = 48000 
# ----------------------------------------

# Read the raw PCM data into a NumPy array using memory mapping
try:
    data = np.memmap(pcm_file_path, dtype=dtype_format, mode='r')
    print(f"Successfully read data with shape: {data.shape}")
except FileNotFoundError:
    print(f"Error: The file '{pcm_file_path}' was not found.")
    exit()
except ValueError as e:
    print(f"Error reading file. Check your 'dtype_format' setting. Details: {e}")
    exit()

try:
    data_multitone = np.memmap(pcm_file_path_multitone, dtype=dtype_format, mode='r')
    print(f"Successfully read data with shape: {data_multitone.shape}")
except FileNotFoundError:
    print(f"Error: The file '{pcm_file_path_multitone}' was not found.")
    exit()
except ValueError as e:
    print(f"Error reading file. Check your 'dtype_format' setting. Details: {e}")
    exit()

try:
    data_output = np.memmap(pcm_file_path_output, dtype=dtype_format, mode='r')
    print(f"Successfully read data with shape: {data_output.shape}")
except FileNotFoundError:
    print(f"Error: The file '{pcm_file_path_multitone}' was not found.")
    exit()
except ValueError as e:
    print(f"Error reading file. Check your 'dtype_format' setting. Details: {e}")
    exit()



# Create time values (optional, but recommended for proper representation)
time = np.arange(len(data)) / sampling_rate

# Create a figure and a set of subplots (1 row, 2 columns)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4))

# Plot the data
ax1.plot(time, data/(2**31-1)) # Use plt.plot(time, data) to plot against time in seconds
ax1.set_title(f"Forma de onda PCM ({os.path.basename(pcm_file_path)})")
ax1.set_xlabel("Sample Number" if sampling_rate is None else "Time (seconds)")
ax1.set_ylabel("Amplitude")
ax1.grid(True)

ax2.plot(time, data_multitone/(2**31-1))
ax2.set_title(f"Forma de onda PCM ({os.path.basename(pcm_file_path_multitone)})")
ax2.set_xlabel("Sample Number" if sampling_rate is None else "Time (seconds)")
ax2.set_ylabel("Amplitude")
ax2.grid(True)

# Add a title for the entire figure and adjust layout
fig.suptitle('Entrada Monotono vs Entrada multitono')
plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Adjust layout to prevent title overlap

plt.figure()
plt.plot(time, data_output/(2**31-1))
plt.title(f"Forma de onda PCM Salida ({os.path.basename(pcm_file_path_output)})")
plt.xlabel("Sample Number" if sampling_rate is None else "Time (seconds)")
plt.ylabel("Amplitude")
plt.grid(True)


plt.show()


