# -*- coding:utf-8 -*-

import pandas as pd

data = pd.read_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_person.csv", header=None)
A = list(data.iloc[:, 0])
B = list(data.iloc[:, 1])
C = list(data.iloc[:, 2])

print("file read finish!")
singleA = list(set(A))
singleB = list(set(B))
AB = list(singleA)
#print(AB)
# for b in B:
#     if b not in AB:
#         AB.append(b)
AB.extend(singleB)
print("AB is finish!")
AB.sort()
print("%d sort is finish!" % len(AB))


dic = dict(zip(AB, list(range(len(AB)))))
#print(dic)
middle = pd.DataFrame.from_dict(dic, orient='index')
#print(dic)
middle.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\map.csv", header=False)

outdata = []
for i in range(len(A)):
    a = dic.get(A[i])
    b = dic.get(B[i])
    outdata.append([a, b, C[i]])
    if i % 10000 == 0:
        print("%d data is finish" % i)

dic = dict(zip(list(range(len(outdata))), outdata))
out = pd.DataFrame.from_dict(dic, orient='index')
#print(outdata)
#print(dic)
#print(out)
out.to_csv(r"D:\Documents\WeChat Files\zhangcy_0511\Files\x_persond_to_i.csv", header=False, index=False)
#print(out)