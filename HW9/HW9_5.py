import matplotlib.pyplot as plt # for plotting
import numpy as np # for sine function
import csv

t = [] # column 0
data1 = [] # column 1

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

print(np.size(data1)) # size of data

Fs = 10000 # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

data_sample_rate = np.size(t)/t[-1] # determine sample rate of data
print(data_sample_rate)

data_MAF = []
for i in range(np.size(t)):
    j=0
    z=0
    X=250  # number of data points averaged
    while j < X:
        z = z + data1[i-j]
        j+=1
    avg = z/X
    data_MAF.append(avg)


y = data_MAF # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y2 = np.fft.fft(y)/n # fft computing and normalization
Y2 = Y2[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,data1,'k',t,data_MAF,'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k',frq,abs(Y2),'r') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
ax1.set_title(str(X) + ' data points averaged')
plt.show()
