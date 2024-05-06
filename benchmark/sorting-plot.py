 # Project                                      ___       _______  _______
 #                                             /   \     |   ____||       \
 #                                            /  ^  \    |  |__   |  .--.  |
 #                                           /  /_\  \   |   __|  |  |  |  |
 #                                          /  _____  \  |  |____ |  '--'  |
 #                                         /__/     \__\ |_______||_______/
 #
 # Author: Luís Góis
 #
 # This software is licensed as described in the file LICENSE, which
 # you should have received as part of this distribution.
 #
 # You may opt to use, copy, modify, merge, publish, distribute and/or sell
 # copies of the Software, and permit persons to whom the Software is
 # furnished to do so, under the terms of the LICENSE file.
 #
 # This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 # KIND, either express or implied.
 #
 #

from matplotlib.figure import Figure
from numpy.typing import NDArray
import itertools
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import math

base_dir = os.path.dirname(os.path.realpath(__file__))

dataFrame = pd.read_csv(f'{base_dir}/sorting-benchmark.csv', delimiter=';')

algorithms: NDArray[np.object_] = np.unique(dataFrame['Algorithm'])
datasets: NDArray[np.object_] = np.unique(dataFrame['Dataset'].to_numpy(dtype = str))

ALGORITHM_ROW = 0
DATASET_ROW   = 1

X_LABEL = 'Array Size'
Y_LABEL = 'Time (ms)'

MAX_ARRAY_SIZE = math.ceil(math.ceil(max(dataFrame[X_LABEL]) / 10) * 10 * 1.01)
MAX_TIME_MILISECONDS = math.ceil(math.ceil(max(dataFrame[Y_LABEL]) / 10) * 10 * 1.01)

def graph(
        figure: Figure,
        axis,
        *,
        output_file: str = '',
        show_plots: bool = True,
        limit: bool = True,
        ratio: bool = True
        ):
    for row, col in itertools.product(range(2), range(3)):
        algorithm = algorithms[col]
        dataset = datasets[col]

        subplot = axis[row, col]

        def plot(subplot, xValues, yValues, title: str):
            subplot.plot(xValues if ratio else xValues.astype(str), yValues, marker='o')
            subplot.set_title(title)
            subplot.set_xlabel(X_LABEL)
            subplot.set_ylabel(Y_LABEL)
            if limit:
                subplot.set_xlim(0, MAX_ARRAY_SIZE)
                subplot.set_ylim(0, MAX_TIME_MILISECONDS)

        if row == ALGORITHM_ROW:
            insertion_data = dataFrame[dataFrame['Algorithm'] == algorithm]

            for dataset in datasets:
                subset = insertion_data[insertion_data['Dataset'] == dataset]
                xValues = subset[X_LABEL]
                yValues = subset.groupby([X_LABEL])[Y_LABEL].mean()
                plot(subplot, xValues, yValues, algorithm)
            subplot.legend(datasets)
        elif row == DATASET_ROW:
            insertion_data = dataFrame[dataFrame['Dataset'] == dataset]

            for algorithm in algorithms:
                subset = insertion_data[insertion_data['Algorithm'] == algorithm]
                xValues = subset['Array Size']
                yValues = subset.groupby(['Array Size'])['Time (ms)'].mean()
                plot(subplot, xValues, yValues, dataset)
            subplot.legend(algorithms)

    if show_plots:
        figure.show()

    if len(output_file) != 0:
        figure.savefig(f'{base_dir}/{output_file}')

for ratio, limit in itertools.product((True, False), (True, False)):
    output_file = 'sorting-benchmark'
    output_file += '-ratio' if ratio else '-no-ratio'
    output_file += '-limit' if limit else '-no-limit'
    output_file += '.png'
    fig, axis = plt.subplots(2, 3, figsize=(18, 10))
    graph(fig, axis, output_file=output_file, limit=limit, ratio=ratio)

plt.show()
