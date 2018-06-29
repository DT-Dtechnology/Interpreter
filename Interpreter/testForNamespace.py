a = 1
def g():
    print(a)

def f(a = 2):
    g()

a = 3
f()
