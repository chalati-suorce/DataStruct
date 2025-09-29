#编写程序，根据输入的三科成绩，计算并打印平均值和总分。
#要求：使用三种格式化字符串方式输出结果。
#说明输入为math=130，eng=101,chi=126  输出为
#print(“average score is{},sum score is{}”.format(…))
def avg(a,b,c):
    return (a+b+c)/3

def sum(a,b,c):
    return a+b+c

math=int(input("请输入数学成绩："))
eng=int(input("请输入英语成绩："))
chi=int(input("请输入语文成绩："))

print("均值为：",avg(math,eng,chi))
print("总分为",sum(math,eng,chi))

