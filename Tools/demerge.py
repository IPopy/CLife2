# -*- coding:utf-8 -*-

import pandas as pd
import numpy as np
from datetime import datetime
data = pd.read_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_to_i.csv", header=None)

middle = np.array(data)
data = middle.tolist()


print("data.size = %d" % len(data))

sum = 0
i = 0
begin = datetime.now()
while len(data)!=0:
    i += 1
    temp = []
    listA = []
    listB = []

    listA.append(data[0][0])
    listB.append(data[0][1])

    j = 0
    # 将第一行的 a 和 b 作为起始点，寻找所有的能访问的点
    start = datetime.now()
    for x in data:
        j += 1
        if j % 50000 == 0:
            end = datetime.now()
            print(end - start)
            print("%d is finish!——use:" % j, end - start)
        if x[0] in listA:
            if x[1] not in listB:
                listB.append(x[1])
                continue
            else:
                continue
        elif x[1] in listB:
            if x[0] not in listA:
                listA.append(x[0])
                continue
            else:
                continue


    end = datetime.now()
    print(end-start)
    print("%d is find!———— %d" % (i, len(listA)+len(listB)))

    ii = 0
    # 删除所有找到的点所在的行，并存储 temp 中
    for x in data:
        if x[0] in listA or x[1] in listB:
            temp.append(x)
            data.remove(x)
            ii += 1
            if ii % 10000 == 0:
                jj = ii*10000
                print("del %d row data!" % jj)

    # 将 temp 写入文件
    dic = dict(zip(list(range(len(temp))), temp))
    out = pd.DataFrame.from_dict(dic, orient='index')
    out.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_mg_%d.csv" % i, header=False, index=False)
    sum += len(temp)

    print("%d is finish!" % i)
print("sum = %d" % sum)
finish = datetime.now()
print(finish-begin)





