import matplotlib.pyplot as plt
import os
import pandas as pd

base_dir = os.path.dirname(os.path.realpath(__file__))

data = pd.read_csv(f'{base_dir}/binTree-benchmark.csv', delimiter=';')

header_info: list[str] = list(data.columns)
first_column = data.iloc[:, 0]

for column in data.columns[1:]:
    plt.figure()
    bar_plot = plt.bar(first_column, data[column])
    plt.xlabel(header_info[0])
    plt.ylabel(column)
    title = f'Graph of {header_info[0]} vs {column}'
    plt.title(title)

    for bar in bar_plot:
        plt.text(
                bar.get_x() + bar.get_width() / 2,
                bar.get_height(),
                round(bar.get_height(), 2),
                ha='center',
                va='bottom'
                )

    plt.savefig(f'{base_dir}/{title}.png')

plt.show()
