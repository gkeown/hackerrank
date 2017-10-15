# https://www.hackerrank.com/challenges/string-validators/problem
if __name__ == '__main__':
    s = input("Enter a string: ")
    alnum = False
    alpha = False
    digit = False
    lower = False
    upper = False

    for i in s:
        if i.isalnum():
            alnum = True
        if i.isalpha():
            alpha = True
        if i.isdigit():
            digit = True
        if i.islower():
            lower = True
        if i.isupper():
            upper = True

    print(alnum)
    print(alpha)
    print(digit)
    print(lower)
    print(upper)
