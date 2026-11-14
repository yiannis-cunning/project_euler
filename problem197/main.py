import math



magicnum = 30.403243784

def run():
    print(2**magicnum)
    print(2**magicnum /2**30)
    print(2**(magicnum - 30))


def f(x):
    a = 2**(magicnum - x**2)
    b = math.floor(a)
    c = b*10**-9
    return c


def main():

    u = -1
    n = 1000

    for i in range(n):
        print(f"U_{i} = {u}")
        u = f(u)

main()

