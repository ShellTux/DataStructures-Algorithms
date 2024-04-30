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

max_time_ms = math.ceil(math.ceil(max(dataFrame['Time (ms)']) / 10) * 10 * 1.01)

fig, axs = plt.subplots(2, 3, figsize=(18, 10))

ALGORITHM_ROW = 0
DATASET_ROW   = 1

for row, col in itertools.product(range(2), range(3)):
    algorithm = algorithms[col]
    dataset = datasets[col]

    subplot = axs[row, col]
    xLabel = 'Array Size'
    yLabel = 'Time (ms)'

    def plot(xLabel: str, xValues, yLabel: str, yValues, title: str):
        subplot.plot(xValues, yValues, marker='o')
        subplot.set_title(title)
        subplot.set_xlabel(xLabel)
        subplot.set_ylabel(yLabel)
        subplot.set_ylim(0, max_time_ms)

    if row == ALGORITHM_ROW:
        insertion_data = dataFrame[dataFrame['Algorithm'] == algorithm]

        for dataset in datasets:
            subset = insertion_data[insertion_data['Dataset'] == dataset]
            xValues = subset[xLabel].astype(str)
            yValues = subset.groupby(['Array Size'])['Time (ms)'].mean()
            plot(xLabel, xValues, yLabel, yValues, algorithm)
        subplot.legend(datasets)
    elif row == DATASET_ROW:
        insertion_data = dataFrame[dataFrame['Dataset'] == dataset]

        for algorithm in algorithms:
            subset = insertion_data[insertion_data['Algorithm'] == algorithm]
            xValues = subset['Array Size'].astype(str)
            yValues = subset.groupby(['Array Size'])['Time (ms)'].mean()
            plot(xLabel, xValues, yLabel, yValues, dataset)
        subplot.legend(algorithms)

plt.show()
plt.savefig(f'{base_dir}/sorting-benchmark.png')
