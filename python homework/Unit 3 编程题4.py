''' 
设计一个字典用来存放商品的信息和价格，例如，
“面粉：2.5元”“大米：3.0元”“白菜：0.99元”，
可以添加、删除、修改商品的价格。
'''
# ...existing code...

# 创建商品字典
goods = {
    "面粉": 2.5,
    "大米": 3.0,
    "白菜": 0.99
}

def show_goods():
    """显示所有商品信息"""
    print("\n当前商品列表：")
    for item, price in goods.items():
        print(f"{item}：{price}元")

def add_goods():
    """添加商品"""
    name = input("请输入商品名称：")
    try:
        price = float(input("请输入商品价格："))
        goods[name] = price
        print(f"成功添加商品：{name}，价格：{price}元")
    except ValueError:
        print("价格输入错误，请输入数字")

def delete_goods():
    """删除商品"""
    name = input("请输入要删除的商品名称：")
    if name in goods:
        del goods[name]
        print(f"成功删除商品：{name}")
    else:
        print("商品不存在")

def modify_price():
    """修改商品价格"""
    name = input("请输入要修改的商品名称：")
    if name in goods:
        try:
            new_price = float(input("请输入新的价格："))
            goods[name] = new_price
            print(f"成功修改{name}的价格为：{new_price}元")
        except ValueError:
            print("价格输入错误，请输入数字")
    else:
        print("商品不存在")

# 主程序循环
while True:
    print("\n=== 商品管理系统 ===")
    print("1. 显示所有商品")
    print("2. 添加商品")
    print("3. 删除商品")
    print("4. 修改商品价格")
    print("0. 退出程序")
    
    choice = input("请选择操作（0-4）：")
    
    if choice == '1':
        show_goods()
    elif choice == '2':
        add_goods()
    elif choice == '3':
        delete_goods()
    elif choice == '4':
        modify_price()
    elif choice == '0':
        print("程序已退出")
        break
    else:
        print("输入无效，请重新选择")