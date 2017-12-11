#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import patches
from matplotlib.pyplot import axvline, axhline
from collections import defaultdict


def zplane(z, p, filename=None):
    """Plot the complex z-plane given zeros and poles.
    """

    # get a figure/plot
    ax = plt.subplot(2, 2, 1)
    # TODO: should just inherit whatever subplot it's called in?

    # Add unit circle and zero axes
    unit_circle = patches.Circle((0,0), radius=1, fill=False,
                                 color='black', ls='solid', alpha=0.1)
    ax.add_patch(unit_circle)
    axvline(0, color='0.7')
    axhline(0, color='0.7')

    # Plot the poles and set marker properties
    poles = plt.plot(p.real, p.imag, 'x', markersize=9, alpha=0.5)

    # Plot the zeros and set marker properties
    zeros = plt.plot(z.real, z.imag,  'o', markersize=9,
             color='none', alpha=0.5,
             markeredgecolor=poles[0].get_color(), # same color as poles
             )

    # Scale axes to fit
    r = 1.5 * np.amax(np.concatenate((abs(z), abs(p), [1])))
    plt.axis('scaled')
    plt.axis([-r, r, -r, r])
#    ticks = [-1, -.5, .5, 1]
#    plt.xticks(ticks)
#    plt.yticks(ticks)

    """
    If there are multiple poles or zeros at the same point, put a
    superscript next to them.
    TODO: can this be made to self-update when zoomed?
    """
    # Finding duplicates by same pixel coordinates (hacky for now):
    poles_xy = ax.transData.transform(np.vstack(poles[0].get_data()).T)
    zeros_xy = ax.transData.transform(np.vstack(zeros[0].get_data()).T)

    # dict keys should be ints for matching, but coords should be floats for
    # keeping location of text accurate while zooming
    d = defaultdict(int)
    coords = defaultdict(tuple)
    for xy in poles_xy:
        key = tuple(np.rint(xy).astype('int'))
        d[key] += 1
        coords[key] = xy
    for key, value in d.iteritems():
        if value > 1:
            x, y = ax.transData.inverted().transform(coords[key])
            plt.text(x, y,
                        r' ${}^{' + str(value) + '}$',
                        fontsize=13,
                        )

    d = defaultdict(int)
    coords = defaultdict(tuple)
    for xy in zeros_xy:
        key = tuple(np.rint(xy).astype('int'))
        d[key] += 1
        coords[key] = xy
    for key, value in d.iteritems():
        if value > 1:
            x, y = ax.transData.inverted().transform(coords[key])
            plt.text(x, y,
                        r' ${}^{' + str(value) + '}$',
                        fontsize=13,
                        )

    if filename is None:
        plt.show()
    else:
        plt.savefig(filename)
        print 'Pole-zero plot saved to ' + str(filename)

#
# Copyright (c) 2011 Christopher Felton
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# The following is derived from the slides presented by
# Alexander Kain for CS506/606 "Special Topics: Speech Signal Processing"
# CSLU / OHSU, Spring Term 2011.

import numpy as np
import matplotlib.pyplot as plt
from  matplotlib import patches
from matplotlib.figure import Figure
from matplotlib import rcParams
import scipy.signal
import math

def zplane(b,a,filename=None):
    """Plot the complex z-plane given a transfer function.
    """

    # get a figure/plot
    ax = plt.subplot(111)

    # create the unit circle
    uc = patches.Circle((0,0), radius=1, fill=False,
                        color='black', ls='dashed')
    ax.add_patch(uc)

    # The coefficients are less than 1, normalize the coeficients
    if np.max(b) > 1:
        kn = np.max(b)
        b = b/float(kn)
    else:
        kn = 1

    if np.max(a) > 1:
        kd = np.max(a)
        a = a/float(kd)
    else:
        kd = 1

    # Get the poles and zeros
    p = np.roots(a)
    z = np.roots(b)
    k = kn/float(kd)

    # Plot the zeros and set marker properties
    t1 = plt.plot(z.real, z.imag, 'go', ms=10)
    plt.setp( t1, markersize=10.0, markeredgewidth=1.0,
              markeredgecolor='k', markerfacecolor='g')

    # Plot the poles and set marker properties
    t2 = plt.plot(p.real, p.imag, 'rx', ms=10)
    plt.setp( t2, markersize=12.0, markeredgewidth=3.0,
              markeredgecolor='r', markerfacecolor='r')

    ax.spines['left'].set_position('center')
    ax.spines['bottom'].set_position('center')
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)


    # set the ticks
    r = 1.5; plt.axis('scaled'); plt.axis([-r, r, -r, r])
    ticks = [-1, -.5, .5, 1]; plt.xticks(ticks); plt.yticks(ticks)

    if filename is None:
        plt.show()
    else:
        plt.savefig(filename)


    return z, p, k


if __name__ == "__main__":

    b, a = scipy.signal.butter(2, [0.06, 0.7], 'bandpass')

    zplane(b,a)
    #zplane(b,a, '../latex/imgs/ZPlane.png')

    # Get the poles and zeros
    z, p, k = scipy.signal.tf2zpk(b, a)

    # Display zeros, poles and gain
    print str(len(z)) + " zeros: " + str(z)
    print str(len(p)) + " poles: " + str(p)
    print "gain: " + str(k)

    # Impulse response
    index = np.arange(0,20)
    u = 1.0*(index==0)
    y = scipy.signal.lfilter(b, a, u)
    plt.stem(index,y)
    plt.title('Impulse response')
    plt.grid(True, color='0.9', linestyle='-', which='both', axis='both')
    plt.show()

    # Frequency response
    w, h = scipy.signal.freqz(b, a)
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
