# -*- coding:utf-8 -*-
"""
输入文件的格式为三列
将文件中 A B 两列的长字符串转为数字，减少运行时占用的内存
"""
import pandas as pd
from datetime import datetime


def str_to_i(file_name):
    """
    将文件中前两列的数据去重、合并、排序
    将排好序的顺序和值保存为字典，存到文件中
    将原文件中的长字符串转为字典中对应的数字
    """
    data = pd.read_csv(file_name, header=None)
    print("file read finish!")

    a = list(data.iloc[:, 0])
    b = list(data.iloc[:, 1])
    c = list(data.iloc[:, 2])

    single_a = list(set(a))
    single_b = list(set(b))

    # ab 保存了文件第一列，第二列的所有字符串
    ab = list(single_a)
    ab.extend(single_b)
    ab.sort()
    # print("AB is finish!")

    dic = dict(zip(ab, list(range(len(ab)))))

    middle = pd.DataFrame.from_dict(dic, orient='index')
    # print(middle)
    middle.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\map_2.csv", header=False)

    # 使用解析列表进行程序优化，时间为 for 一半
    start = datetime.now()
    out_a = [dic.get(x) for x in a]
    out_b = [dic.get(y) for y in b]
    out_data = list(zip(out_a, out_b, c))
    end = datetime.now()
    print("解析列表用时：", end-start)

    # # 最开始使用 for 循环
    # out_data = []
    # dic = dict(zip(ab, list(range(len(ab)))))
    # start = datetime.now()
    # for i in range(len(a)):
    #     first = dic.get(a[i])
    #     second = dic.get(b[i])
    #     out_data.append([first, second, c[i]])
    # end = datetime.now()
    # print("for循环用时：", end-start)

    dic = dict(zip(list(range(len(out_data))), out_data))
    out = pd.DataFrame.from_dict(dic, orient='index')

    # print(out_data)
    # print(out)
    out.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_to_i.csv", header=False, index=False)


str_to_i(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_person_1.csv")
