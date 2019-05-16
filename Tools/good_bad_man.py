# -*- coding:utf-8 -*-

import pandas as pd
import numpy as np

# data 保存了 名字和对应的数字
data = pd.read_csv(r"D:Documents\map.csv", header=None)


dic = dict(zip(data.iloc[:, 0], data.iloc[:, 1]))


train_id = pd.read_csv(r"D:Documents\train_id.tsv")
train_id = list(train_id.iloc[:, 0])


id_result = {}

for x in train_id:
    id_result[x[:-2]] = x[-1]

name = list(id_result.keys())


out = {}
for x in name:
    out[dic.get(x)] = id_result.get(x, -1)

ll = list(out.values())
print("-1 的个数：%d" % ll.count(-1))
out = pd.DataFrame.from_dict(out, orient='index')

out.to_csv("good_bad_man.csv", header=False)


