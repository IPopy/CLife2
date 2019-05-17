# -*- coding:utf-8 -*-
"""
这个数据文件为 tsv 文件？虽然不知道是什么，但是还是读了出来
我才复用的可能性很小
整理还是算了吧~~~
author: zcy
"""
import pandas as pd

# data 保存了 名字和对应的数字
data = pd.read_csv(r"D:Documents\map.csv", header=None)


dic = dict(zip(data.iloc[:, 0], data.iloc[:, 1]))


train_id = pd.read_csv(r"D:Documents\train_id.tsv")
train_id = list(train_id.iloc[:, 0])


id_result = {}

# id_result = {x[:-2]: x[-1] for x in train_id}
for x in train_id:
    id_result[x[:-2]] = x[-1]

name = list(id_result.keys())


out = {}
# out = {dic.get(x): id_result.get(x, -1) for x in name}
for x in name:
    out[dic.get(x)] = id_result.get(x, -1)

ll = list(out.values())
print("-1 的个数：%d" % ll.count(-1))
out = pd.DataFrame.from_dict(out, orient='index')

out.to_csv("good_bad_man.csv", header=False)


