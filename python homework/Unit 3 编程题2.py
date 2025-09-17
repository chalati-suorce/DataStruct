''' 
有如下元组，name=("jack","jason"," 小明"," 小李","George")。
1、计算元组的长度。
2、获取元组的第二个元素。
3、是否可以修改元组的第二个元素的值。
4、遍历元组所有元素的值并输出。
'''
# ...existing code...

# 创建元组
name = ("jack", "jason", " 小明", " 小李", "George")

# 1. 计算元组的长度
length = len(name)
print("1. 元组的长度为:", length)

# 2. 获取元组的第二个元素
second_element = name[1]
print("2. 第二个元素是:", second_element)

# 3. 测试是否可以修改元组的第二个元素
print("3. 元组是不可变的，不能修改其中的元素")
# 如果尝试修改会引发错误: name[1] = "Tom"  # TypeError: 'tuple' object does not support item assignment

# 4. 遍历元组所有元素
print("4. 遍历元组所有元素:")
for item in name:
    print(item)