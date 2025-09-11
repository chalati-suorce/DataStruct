def 冒泡排序(arr):
    n = len(arr)
    # 遍历所有数组元素
    for i in range(n):
        # 最后i个元素已经是排好序的了
        for j in range(0, n-i-1):
            # 如果当前元素大于下一个元素，则交换它们
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
arr_input = input("请输入5个整数，用空格分隔：")
arr = list(map(int, arr_input.split()))
if len(arr) != 5:
    print("输入的整数数量不是5个，请重新输入。")
else:
    sorted_arr = 冒泡排序(arr)
    print("排序后的数组:", sorted_arr)

