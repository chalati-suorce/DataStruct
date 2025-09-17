'''
题目：用python语言判断某一年是闰年还是平年，
例如，2000年是闰年，2014年是平年。
'''
def func(year):
    if (year%4==0 and year %100!=0) or (year%400==0):
        return f"{year}是闰年"
    else:
        return f"{year}是平年"
    
year=int(input("请输入年份："))
print(func(year))