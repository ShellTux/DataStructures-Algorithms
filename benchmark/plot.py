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

import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import sys

def usage(program_name: str):
    print(f'Usage: {program_name} <show | save>')
    sys.exit(1)

if len(sys.argv) != 2:
    usage(sys.argv[0])

SHOW_GRAPHS: bool = sys.argv[1] == 'show'

base_dir = os.path.dirname(os.path.realpath(__file__))

data = pd.read_csv(f'{base_dir}/binTree-benchmark.csv', delimiter=';')

features: list[str] = list(data.columns)[2:]

GROUP1: str = 'Structure'
GROUP2: str = 'Group'

structures = data[GROUP1].unique()
groups = data[GROUP2].unique()

means = {}

for feature in features:
    means[feature] = {}
    for group in groups:
        means[feature][group] = data[data[GROUP2] == group][feature].values

print(means)

def plot_grouped_bar(
        group1: str,
        group2: str,
        feature: str,
        *,
        image_filepath: str = ''
        ):
    if any([len(arg) == 0 for arg in (group1, group2, feature)]):
        return

    _, ax = plt.subplots()

    X = np.arange(len(structures))
    WIDTH = 0.25
    MULTIPLIER = 0

    for group, measurement in means[feature].items():
        offset = WIDTH * MULTIPLIER
        rects = ax.bar(X + offset, measurement, WIDTH, label=group)
        ax.bar_label(rects, padding=3)
        MULTIPLIER += 1

    ax.set_ylabel(feature)
    ax.set_title(f'{feature} by {group1} and {group2}')
    ax.set_xticks(X + WIDTH, structures)
    ax.legend(loc='upper left', bbox_to_anchor=(1, 1), title=GROUP2)

    if len(image_filepath) != 0:
        plt.savefig(image_filepath)

for feature in features:
    plot_grouped_bar(
            GROUP1,
            GROUP2,
            feature,
            image_filepath=f'{base_dir}/{feature}.png'
            )

if SHOW_GRAPHS:
    plt.show()
