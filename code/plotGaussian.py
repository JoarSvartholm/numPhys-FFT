import matplotlib.pyplot as plt
import numpy as np

noSamp = 1024
dt = 1.0/noSamp
sigma = 16*dt
data = np.genfromtxt("gaussian.data",delimiter=" ")
raw = np.genfromtxt("raw.data",delimiter=" ")
print(len(data))

real = np.zeros(noSamp+1)
imag = np.zeros(noSamp+1)
areal = np.zeros(noSamp+1)
aimag = np.zeros(noSamp+1)

real[:512] = data[noSamp::2]
real[513:] = data[0:noSamp:2]
imag[:512] = data[noSamp+1::2]
imag[513:] = data[1:noSamp+1:2]
F = np.arange(-int(noSamp/2),int(noSamp/2)+1)
real *= np.real(np.exp(-np.pi*1j*F))
imag *= np.imag(np.exp(-np.pi*1j*F))
areal = np.real(np.exp(-0.25*(2*np.pi*sigma*F)**2))
aimag = np.imag(np.exp(-0.25*(2*np.pi*sigma*F)**2))


#normalization
areal = areal/np.max(np.abs(areal))
real = real/np.max(np.abs(real))

print(np.max(np.abs(areal-real)))
print(np.max(np.abs(aimag-imag)))
#print((imag))
plt.figure("FFT comparison")
plt.plot(F,imag,'*',label='Imaginary part')
plt.plot(F,real,'*',label='Real part')
plt.plot(F,areal,".",label='Analytic Real part')
plt.plot(F,aimag,".",label='Analytic Imaginary part')
plt.legend()
plt.xlabel('frequency')
plt.savefig('../figs/FFTgauss.pdf')
plt.show()

plt.figure("raw")
plt.plot(range(-int(noSamp/2),int(noSamp/2)),raw,'.',label='Signal')
plt.legend()
plt.xlabel('time [t]')
plt.ylabel('Signal')
plt.savefig('../figs/gaussianSignal.pdf')
