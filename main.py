#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import random
import numpy as np


def get_window_width_from_input(values_count):
    window_width_power = int(raw_input('Enter the window width (power of 2, between 1 and 16): '))

    if window_width_power not in range(1, 16):
        print 'Window width power of 2 must be integer between 1 and 16, "{}" given.'.format(window_width_power)
        print 'Exiting.'

        sys.exit(1)

    window_width = pow(2, window_width_power)

    print 'Window width: {}'.format(window_width)

    if values_count < window_width:
        print 'Window width must not be larger than values count!'
        print 'Exiting.'

        sys.exit(1)

    return window_width


def read_data(filename):
    values = open(filename, 'r').read().split()

    for i, value in enumerate(values):
        values[i] = float(value)

    return values


def get_windows(values, width):
    count = 2 * (len(values) - width) / width + 1

    print 'Number of windows: {}'.format(count)

    results = {}

    for i in xrange(0, count):
        results[i] = {}

        for j in xrange(0, width):
            results[i][j] = values[j + i * width / 2]

    return results


def fft(values):
    """A vectorized, non-recursive version of the Cooley-Tukey FFT"""
    values = np.asarray(values, dtype=float)
    values_count = values.shape[0]

    if np.log2(values_count) % 1 > 0:
        raise ValueError('values count must be a power of 2, "{}" given.'.format(values_count))

    # N_min here is equivalent to the stopping condition above,
    # and should be a power of 2
    n_min = min(values_count, 32)

    # Perform an O[N^2] DFT on all length-N_min sub-problems at once
    n = np.arange(n_min)
    k = n[:, None]
    m = np.exp(-2j * np.pi * n * k / n_min)
    arr = np.dot(m, values.reshape((n_min, -1)))

    # build-up each level of the recursive calculation all at once
    while arr.shape[0] < values_count:
        arr_even = arr[:, :arr.shape[1] / 2]
        arr_odd = arr[:, arr.shape[1] / 2:]
        factor = np.exp(-1j * np.pi * np.arange(arr.shape[0]) / arr.shape[0])[:, None]
        arr = np.vstack([arr_even + factor * arr_odd, arr_even - factor * arr_odd])

    return arr.ravel()


def main():
    # data = read_data('./data/CHIRP2.txt')
    # data = np.random.random(pow(2, 16))
    data = []
    for data_key in range(0, pow(2, 2)):
        data.append(round(random.uniform(-1.0, 1.0), 8))

    print 'Values count: {}'.format(len(data))

    window_width = get_window_width_from_input(len(data))

    windows = get_windows(data, window_width)

    result = {}

    for window_key, window in windows.iteritems():
        result[window_key] = fft(window.values())
        # result[window_key] = np.fft.fft(window.values())

    # print result

    print 'FFT done!'

if __name__ == '__main__':
    main()
