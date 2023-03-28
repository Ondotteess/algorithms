import random

def shell_sort(arr):
    n = len(arr)
    gap = 1
    while gap <= n // 3:
        gap = gap * 3 + 1

    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap = (gap - 1) // 3
    return arr

rand_arr = [random.randint(-9999, 9999) for _ in range(1000)]
rand_arr_2 = [x for x in rand_arr]

rand_arr = shell_sort(rand_arr)
rand_arr_2.sort()

print(rand_arr == rand_arr_2)
