''' 
假设队列的值是：[1,22,34,27,3,8,69,100,3,48,95,]。
1、查找元素3所在的索引。
2、反向查找元素3所在的索引。
3、查找所有大于或小于50的元素。
4、从元素38开始查找元素3所在的索引。
5、把索引为7的元素的值修改为66。
'''
list = [1, 22, 34, 27, 3, 58, 69, 100, 3, 48, 95, 20]

print("(1) 元素3第一次出现的索引:", list.index(3))
print("(2) 元素3最后一次出现的索引:", len(list) - 1 - list[::-1].index(3))

greater_than_50 = [x for x in list if x > 50]
less_than_50 = [x for x in list if x < 50]

print("(3) 大于50的元素:", greater_than_50)
print("    小于50的元素:", less_than_50)

try:
    start_index = list.index(38)
    result = list.index(3, start_index)
    print("(4) 从38开始查找3的索引:", result)
except ValueError:
    print("(4) 未找到元素38或其后没有元素3")

list[7] = 66
print("(5) 修改后的列表:", list)