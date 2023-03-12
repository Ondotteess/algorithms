import subprocess
import math

def get_average(data: list):
    return round(sum(data) / len(data), 5)

def get_deviation(arr):
    n = len(arr)
    mean = sum(arr) / n
    variance = sum((x - mean) ** 2 for x in arr) / n
    std_deviation = math.sqrt(variance)
    return round(std_deviation, 5)

def get_geometric_mean(data: list):
    prod = 1
    for el in data:
        prod *= el
    return round(pow(prod, 1/len(data)), 5)


def format_table(benchmarks, algos, results):
    table = []
    for i in range(len(benchmarks)+1):
        if i == 0:
            table.append(['Benchmark'] + algos)
        else:
            table.append([benchmarks[i-1]] + results[i-1])

    max_lengths = [max(map(len, list(map(str, [table[i][j] for i in range(len(table))])))) for j in range(len(algos)+1)]

    for i in range(len(table)):
        print('|', end='')
        for j in range(len(table[0])):
            print(f' {table[i][j]:<{max_lengths[j]}} |', end='')

        if i == 0:
            print('\n|' + '-' * (sum(max_lengths) + len(algos) * (len(table[0])) - 1) + '|')
        else:
            print()


size = 3
while True:
    matrix_size = f'{size}'.encode()
    benchmark_list = [[], [], []]

    for _ in range(5):
        mult, rec, strass = subprocess.run(["pypy",  "matrix_multiply.py"], input=matrix_size ,stdout=subprocess.PIPE).stdout.decode("utf-8").split(' ')
        benchmark_list[0].append(float(mult))
        benchmark_list[1].append(float(rec))
        benchmark_list[2].append(float(strass.strip('\r\n')))
    print(get_average(benchmark_list[0]) > get_average(benchmark_list[2]))

    if get_average(benchmark_list[0]) < get_average(benchmark_list[2]):
        print(size)
        size += 1
        continue
    else:
        print(size)
        format_table(['Average', 'Deviation', 'Geometric mean'],
                     ['Classic', '8 Recursions', 'Strassen'],
                     [[get_average(benchmark_list[0]), get_average(benchmark_list[1]), get_average(benchmark_list[2])],
                      [get_deviation(benchmark_list[0]), get_deviation(benchmark_list[1]),
                       get_deviation(benchmark_list[2])],
                      [get_geometric_mean(benchmark_list[0]), get_geometric_mean(benchmark_list[1]),
                       get_geometric_mean(benchmark_list[2])]])
        break
