# -*- coding:utf-8 -*-
"""
将两个 CSV 文件合并成一个文件
两个文件都必须是按照第一列排好序的
"""

import pandas as pd
from pandas import DataFrame


def merge_csv(file_name_1, file_name_2):

    data_a = pd.read_csv(file_name_1, header=None)
    data_b = pd.read_csv(file_name_2, header=None)

    drop_b = []

    begin = 0
    end = data_a.index.size
    j = 0
    # 遍历 B，将其中数据插入 A
    for i in range(data_b.index.size):
        list_b = data_b.loc[i]
        for j in range(begin, end):
            list_a = data_a.loc[j]
            if list_b[0] < list_a[0]:
                if j != 0:
                    begin = j-1
                break
            elif list_b[0] > list_a[0]:
                continue
            elif list_b[0] == list_a[0]:
                if list_b[1] == list_a[1]:
                    # b 和 a 的前两列都得相等，则第三列的值相加
                    a = int(list_a[2])
                    b = int(list_b[2])
                    list_a[2] = str(a+b)

                    drop_b.append(i)
                    begin = j
                    break
                else:
                    continue
            else:
                print("出错误了")
        if j == end:
            j = j-1
            if data_a.loc[j][0] < list_b[0]:
                break

    data_c = data_b.drop(drop_b)

    data_d = data_a.append(data_c, ignore_index=True)
    data_d = data_d.sort_values(by=[0])
    data_d.to_csv("out.csv", index=False, header=False)
    print(data_d)


    #print(dataA[0])

