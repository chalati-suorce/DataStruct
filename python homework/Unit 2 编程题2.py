'''
题目：根据三角形三条边的长度判断能否可以构成一个三角形。
'''
def func(a,b,c):
    if a+b>c and a+c>b and b+c>a:
        return f"{a},{b},{c}能构成三角形"
    else:
        return f"{a},{b},{c}不能构成三角形"
a=int(input("请输入第一条边长："))
b=int(input("请输入第二条边长："))
c=int(input("请输入第三条边长："))
print(func(a,b,c))