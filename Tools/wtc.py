# -*- coding:utf-8 -*-


import pandas as pd
from pandas import DataFrame
dataA = pd.read_csv(r"D:\用户目录\我的文档\WeChat Files\zhangcy_0511\FileStorage\File\2019-05\mpl1\A.csv", header=None)
dataB = pd.read_csv(r"D:\用户目录\我的文档\WeChat Files\zhangcy_0511\FileStorage\File\2019-05\mpl1\B.csv", header=None)

dropB = []

begin = 0
end = dataA.index.size
j = 0
for i in range(dataB.index.size):
    listB = dataB.loc[i]
    for j in range(begin, end):
        listA = dataA.loc[j]
        if listB[0] < listA[0]:
            if j != 0:
                begin = j-1
            break
        elif listB[0] > listA[0]:
            continue
        elif listB[0] == listA[0]:
            if listB[1] == listA[1]:
                a = int(listA[2])
                b = int(listB[2])
                listA[2] = str(a+b)

                dropB.append(i)
                begin = j
                break
            else:
                continue
        else:
            print("出错误了")
    if j == end:
        j = j-1
        if dataA.loc[j][0] < listB[0]:
            break


dataC = dataB.drop(dropB)


dataD = dataA.append(dataC, ignore_index=True)
dataD = dataD.sort_values(by=[0])
dataD.to_csv(r"D:\用户目录\我的文档\WeChat Files\zhangcy_0511\FileStorage\File\2019-05\mpl1\out.csv", index=False, header=False)
print(dataD)


#print(dataA[0])

