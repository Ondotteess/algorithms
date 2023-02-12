def karatsuba(x, y):
    """
    >>> karatsuba(-12345,12345)
    -152399025
    >>> karatsuba(-1111111, 6346723)
    -7051913739253
    >>> karatsuba(-6136126, 0)
    0
    >>> karatsuba(918274, 326346)
    299675046804
    """
    if abs(x) < 10 or abs(y) < 10:
        return x * y
    m = max(len(str(x)), len(str(y))) // 2
    x_high, x_low = divmod(x, 10**m)
    y_high, y_low = divmod(y, 10**m)
    a = karatsuba(x_low, y_low)
    b = karatsuba((x_low + x_high), (y_low + y_high))
    c = karatsuba(x_high, y_high)
    return (c * 10**(2 * m)) + ((b - c - a) * 10**m) + a

a = int(input('first: '))
b = int(input('second: '))
print(karatsuba(a, b))
