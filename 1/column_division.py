def column_division(dividend, divisor):
    if not divisor:
        raise ZeroDivisionError
    quotient = ''
    remainder = 0
    for digit in str(dividend):
        remainder = remainder * 10 + int(digit)
        if remainder >= divisor:
            num = 0
            while remainder >= divisor:
                remainder -= divisor
                num += 1
            quotient += str(num)
    return quotient, remainder

dividend = int(input("dividend: "))
divisor = int(input("divisor: "))
quotient, remainder = column_division(dividend, divisor)
print("quotient:", quotient)
print("remainder:", remainder)
