def func(year):
    if (year%4==0 and year %100!=0) or (year%400==0):
        return f"{year}是闰年"
    else:
        return f"{year}是平年"
    
year=int(input("请输入年份："))
print(func(year))