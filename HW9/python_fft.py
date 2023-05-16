import matplotlib.pyplot as plt
import numpy as np

dt = 1.0/1024.0 # 10kHz
t = np.arange(0.0, 1.0, dt) # 10s
# a constant plus 100Hz and 1000Hz
s = np.sin(2*np.pi*2*t) + np.sin(2*np.pi*100*t) + np.sin(2*np.pi*250*t)

Fs = 1024 # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization

print(Y)
Y = Y[range(int(n/2))]


#fig, (ax1, ax2) = plt.subplots(2, 1)
#ax1.plot(t,y,'b')
#ax1.set_xlabel('Time')
#ax1.set_ylabel('Amplitude')
#ax2.loglog(frq,abs(Y),'b') # plotting the fft
#ax2.set_xlabel('Freq (Hz)')
#ax2.set_ylabel('|Y(freq)|')
#plt.show()