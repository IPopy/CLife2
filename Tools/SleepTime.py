# -*- coding:utf-8 -*-

import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import xlrd
from pprint import pprint
from datetime import datetime


mpl.rcParams['font.sans-serif'] = ['SimHei']
mpl.rcParams['font.family']='sans-serif'

# file = r"C:\Users\Administrator.USER-20190305YI\Desktop\博客\sleeptime.xlsx"
# data = xlrd.open_workbook(filename=file)
#
# ws = data.sheet_by_name('week1')
#
# dataset = []
#
# for r in range(ws.nrows):
#     col = []
#     for c in range(ws.ncols):
#         cell = ws.cell(r, c)
#         if cell.ctype == xlrd.XL_CELL_DATE:
#             #data_value = xlrd.xldate_as_tuple(cell.value, book.datemode)
#             print(datetime(cell.value))
#         col.append(ws.cell(r, c).value)
#
#     dataset.append(col)
sleep_time = []
wakeup_time = []



class ShowSleepTime():
    sleep_time = []
    wakeup_time = []

    date = []
    def sleep_time_talbe(self):
        table = {'5.13': ['23:55', '06:40'],
                 '5.14': ['00:40', '08:30'],
                 '5.15': ['23:00', '06:20'],
                 '5.16': ['23:45', '06:20'],
                 '5.17': ['23:50', '06:35'],
                 '5.18': ['00:00', '06:15'],
                 '5.19': ['02:00', '12:00']
                 }

        self.date = list(table.keys())

        for value in table.values():
            self.sleep_time.append(value[0])
            self.wakeup_time.append(value[1])



    def time_to_num(self, time):
        hour = []
        minute = []
        for t in time:
            hour.append(int(t[:2]))
            minute.append(int(t[3:]))

        return hour, minute



s = ShowSleepTime()
s.sleep_time_talbe()


def plot_time():
    x = range(7)
    y1 = []
    y2 = []
    h1, m1 = s.time_to_num(s.sleep_time)
    h1 = [i if i < 20 else i-24 for i in h1]
    m1 = [i/60 for i in m1]

    h2, m2 = s.time_to_num(s.wakeup_time)
    m2 = [i / 60 for i in m2]

    for t in range(7):
        y1.append(h1[t] + m1[t])
        y2.append(h2[t] + m2[t])

    plt.plot(y1, label="睡觉时间")
    plt.plot(y2, label="起床时间")

    plt.axhline(-0.5, color='r', linestyle='--', alpha=0.4)
    plt.axhline(6.5, color='r', linestyle='--', alpha=0.4)

    plt.yticks(range(-2, 10), ['22:00', '23:00', '00:00', '01:00', '02:00', '03:00', '04:00', '05:00', '06:00', '07:00', '08:00', '09:00'])
    plt.xticks(range(7), s.date, rotation=20)



    plt.xlabel("日期")
    plt.ylabel("时间")
    plt.title("第四周")

    plt.legend()

    plt.savefig(r"..\image\第零周.jpg")
    plt.show()


plot_time()