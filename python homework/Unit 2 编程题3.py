def func(n):
    for x in range(n//2+1):
        y=(n-2*x)//4
        if x*2+y*4==n and y>0:
            return f"至多有{x+y}只动物"
    for y in range(n//4+1):
        x=(n-4*y)//2
        if x*2+y*4==n and x>0:
            return f"至少有{x+y}只动物"
    return "无解"
n=int(input("脚的总数量为"))
print(func(n))