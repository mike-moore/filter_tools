#!/usr/bin/python
import numpy as np
import math
import scipy.fftpack
import scipy.signal
import csv
import matplotlib.pyplot as plt
from ZPlane import zplane

class ChupacabraAnalysis(object):

    def __init__(self, file_name):
        self.chup_data_file = file_name
        self.sampling_rate = 500.0
        if self.chup_data_file == '':
            print 'Must set your data file first. Use setChupDataFile(\'path/to/file.csv\')'
            print 'Exiting...'
            return
        self.velocity_data = []
        self.velocity_cmds = []
        data_file = csv.DictReader(open(self.chup_data_file))
        for row in data_file:
            self.velocity_data.append(float(row['Sensed Velocity (rpm)']))
            self.velocity_cmds.append(float(row['Velocity Cmd (rpm)']))
        self.b = []
        self.a = []

    def plotFilterDetails(self):
        zplane(self.b, self.a)
        # Display zeros, poles and gain
        z, p, k = scipy.signal.tf2zpk(self.b, self.a)
        print str(len(z)) + " zeros: " + str(z)
        print str(len(p)) + " poles: " + str(p)
        print "gain: " + str(k)

        # Impulse response
        index = np.arange(0,30)
        u = 1.0*(index==0)
        y = scipy.signal.lfilter(self.b, self.a, u)
        plt.stem(index,y)
        plt.title('Impulse response')
        plt.grid(True, color='0.9', linestyle='-', which='both', axis='both')
        plt.show()

        # Frequency response
        w, h = scipy.signal.freqz(self.b, self.a)
        plt.plot(w/math.pi, 20*scipy.log10(abs(h)))
        plt.xscale('log')
        plt.title('Frequency response')
        plt.xlabel('Normalized frequency')
        plt.ylabel('Amplitude [dB]')
        plt.grid(True, color = '0.7', linestyle='-', which='major')
        plt.grid(True, color = '0.9', linestyle='-', which='minor')
        plt.show()

        # Phase
        plt.plot(w/math.pi, 180/math.pi * np.unwrap(np.angle(h)))
        plt.xscale('log')
        plt.xlabel('Normalized frequency')
        plt.ylabel('Phase [degrees]')
        plt.grid(True, color = '0.7', linestyle='-', which='major')
        plt.grid(True, color = '0.9', linestyle='-', which='minor')
        plt.show()

    def butterLowpass(self, cutoff_freq, fs, order=5):
        nyq = 0.5 * fs
        normal_cutoff = cutoff_freq / nyq
        self.b, self.a = scipy.signal.butter(order, normal_cutoff, btype='low', analog=False)

    def butterLowpassFilter(self, data, cutoff_freq, order=5):
        self.butterLowpass(cutoff_freq, self.sampling_rate, order=order)
        y = scipy.signal.lfilter(self.b, self.a, data)
        return y

    def plotFft(self, theSignal, plotTitle):
        FFT = abs(scipy.fft(theSignal))
        freqs = scipy.fftpack.fftfreq(len(theSignal), 1.0/self.sampling_rate)
        plt.subplot(211)
        plt.ylabel('Signal Magnitude')
        plt.xlabel('Sample #')
        plt.title(plotTitle)
        plt.plot(theSignal)
        plt.subplot(212)
        plt.plot(freqs,20*scipy.log10(FFT),'x')
        plt.ylabel('Signal Magnitude (dB)')
        plt.xlabel('Frequency (Hz)')

    def velocityAnalysis(self, filtered_velocity):
        fig, (ax1, ax2) = plt.subplots(2, sharex=True)
        ax1.set_title('Noisy Velocity')
        ax1.set_ylabel('Sensed Velocity (rpm)')
        ax1.plot(self.velocity_data, color='b', linestyle='-', label='Sensed')
        ax1.plot(self.velocity_cmds, color='r', linestyle='--', label='Cmd')
        ax1.grid()
        ax2.set_title('Filtered Velocity')
        ax2.set_ylabel('Filtered Velocity (rpm)')
        ax2.plot(filtered_velocity, color='b', linestyle='-', label='Filtered')
        ax2.plot(self.velocity_cmds, color='r', linestyle='--', label='Cmd')
        ax2.grid()
        plt.legend()
        plt.show()
        self.plotFft(self.velocity_data, 'Noisy Velocity FFT')
        self.plotFft(filtered_velocity, 'Filtered Velocity FFT')

if __name__ == '__main__':
    file_name = './data/MotorControlTestStandVelocityControl_500Hz.csv'
    analyzer = ChupacabraAnalysis(file_name)
    filtered_velocity = analyzer.butterLowpassFilter(analyzer.velocity_data, 1.0, order=2)
    analyzer.velocityAnalysis(filtered_velocity)
    analyzer.plotFilterDetails()
    print "B coefficients : " + str(analyzer.b)
    print "A coefficients : " + str(analyzer.a)
    plt.show()


