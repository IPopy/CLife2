# -*- coding:utf-8 -*-
"""
这个工具是用来处理原始数据的
将一个数据集，拆分为多个完全连通图
但是结果仍然是多个数据集，而不是被处理后的图
要想得到图，还需要运行其他的程序
"""
import pandas as pd
import numpy as np
from datetime import datetime


def demerge_map(file_name):
    data = pd.read_csv(file_name, header=None)
    data = np.array(data).tolist()

    print("data.size = %d" % len(data))

    i = 0

    begin = datetime.now()
    while len(data):
        i += 1
        list_a = []
        list_b = []

        list_a.append(data[0][0])
        list_b.append(data[0][1])

        j = 0

        start = datetime.now()
        # 将第一行的 a 和 b 作为起始点，寻找所有的能访问的点，分别放在 list_a 和 list_b 中
        for x in data:
            j += 1
            if j % 50000 == 0:
                end = datetime.now()
                print("%d is finish!——use:" % j, end - start)
            if x[0] in list_a:
                if x[1] not in list_b:
                    list_b.append(x[1])
                    continue
                else:
                    continue
            elif x[1] in list_b:
                if x[0] not in list_a:
                    list_a.append(x[0])
                    continue
                else:
                    continue

        end = datetime.now()
        print("寻找连通点的时间：", end-start)
        print("%d is find!———— %d" % (i, len(list_a) + len(list_b)))

        ii = 0

        start = datetime.now()

        # 将 list_a 和 list_b 中所有的点所在行，存储在 temp 中
        temp = [x for x in data if x[0] in list_a or x[1] in list_b]
        # 从原数据中删除已在 temp 中的行
        for x in temp:
            data.remove(x)
        # 下面那行语句的时间复杂度太高
        # data = [x for x in data if x not in temp]

        end = datetime.now()
        print("第 %d 次拆分用时：" % i, end-start)

        # 将 temp 写入文件
        dic = dict(zip(list(range(len(temp))), temp))
        out = pd.DataFrame.from_dict(dic, orient='index')
        out.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_mg_%d.csv" % i, header=False, index=False)

    finish = datetime.now()
    print("程序总时长：", finish-begin)


demerge_map(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_to_i.csv")



