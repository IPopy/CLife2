# -*- coding:utf-8 -*-

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

#plt.rcParams['figure.figsize'] = (19.2, 10.8)
#plt.rcParams['figure.dpi'] = 400
data = pd.read_csv("data.csv", header=None)


y = list(data.iloc[:, 1])
radis = list(data.iloc[:, 2])

x = list(data.iloc[:, 0])
ylabel = list(y)


plt.scatter(x, y, s=radis)
#plt.xticks(x)
plt.show()