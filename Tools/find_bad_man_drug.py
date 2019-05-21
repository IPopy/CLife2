# -*- coding:utf-8 -*-
"""
从原始数据的文件中找出 bad_man 文件中所有数据对应的药物
"""
import pandas as pd
import numpy as np


def find_bad_man_drug(origin_file_name, bad_man_file_name, out_file_name):
    data = pd.read_csv(origin_file_name, header=None)
    bad_man = pd.read_csv(bad_man_file_name, header=None)

    man = list(data.iloc[:, 0])
    drug = list(data.iloc[:, 1])
    data = np.array(data).tolist()

    no_dup_man = man.duplicated()
    for i in range(10):
        if bad_man[i][0] in no_dup_man:
            bad_man = list(bad_man.iloc[:, 0])
        elif bad_man[i][1] in no_dup_man:
            bad_man = list(bad_man.iloc[:, 1])
        else:
            print("请检查输入文件是否正确！\n，未能够在 %s 中找到 %s 的前十条数据" % (origin_file_name, bad_man_file_name))

    no_dup_drug = [x[1] for x in data if x[0] in bad_man].duplicated()

    dic = dict(zip(list(range(len(no_dup_drug))), no_dup_drug))
    out = pd.DataFrame.from_dict(dic, orient='index')
    out.to_csv(out_file_name, header=False, index=False)


origin_file = r"C:\filename.csv"
bad_man_file= r"C:\filename.csv"
out_file = r"C:\filename.csv"
find_bad_man_drug(origin_file, bad_man_file, out_file)



