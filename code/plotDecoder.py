import matplotlib.pyplot as plt
import numpy as np

savePlots = 0
showPlots = 1

data = np.genfromtxt("noisy.data",delimiter="\n")
raw = np.genfromtxt("am11.dat",delimiter="\n")
filtered = np.genfromtxt("filtered.data",delimiter="\n")
N = int(len(data)/2)
N2 = int(N/2)

real = np.zeros(N+1)
imag = np.zeros(N+1)

real[:N2] = data[N::2]
real[N2:] = data[:N+1:2]
imag[:N2] = data[N+1::2]
imag[N2:] = data[1:N+2:2]


S = (real**2+imag**2)**2
F = np.arange(N2+1)
peaks = np.where(S[N2:]>1000000000000)[0]
BW = peaks[-1]-peaks[0]

print("bandwidth = %i"%BW)
print("max peak = %i"%peaks[1])
print(peaks)

plt.figure("FFT")
plt.plot(F,S[N2:],'.-')
plt.xlabel("Frequency [Hz]")
plt.xlim((750,1300))
plt.savefig("../figs/FFTnoisy.pdf")

plt.figure("Input signal")
plt.plot(np.arange(8192)/8192,raw)
plt.xlabel("Time [s]")
plt.xlim((0,0.1))
plt.savefig("../figs/noisySignal.pdf")

plt.figure("filtered")
plt.plot(np.arange(8192)/8192,filtered)
plt.xlabel("Time [s]")
plt.xlim((0,0.1))
plt.savefig("../figs/filteredSignal.pdf")
plt.show()
