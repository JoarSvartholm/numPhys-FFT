import matplotlib.pyplot as plt
import numpy as np

savePlots = 0
showPlots = 1

data = np.genfromtxt("amdata.data",delimiter=" ")
raw = np.genfromtxt("amraw.data",delimiter=" ")
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

print(np.where(S[N2:] >1000000)[0])

#Plotting
plt.figure()
plt.plot(range(N),raw,'.',label='signal')
if showPlots:
    plt.show()
if savePlots:
    plt.savefig('../figs/amsignal.pdf')

plt.figure()
plt.plot(F,S[N2:],'.-',label='fourier transform')
plt.xlim((0,80))
plt.xlabel('frequency [$f$]')
plt.ylabel('Amplitude $S(f)=|U(f)|^2$')
plt.legend()
if showPlots:
    plt.show()
if savePlots:
    plt.savefig('../figs/FFTam.pdf')
