import numpy as np
import matplotlib.pyplot as plt
import pywt
import math
import random
my_file = open('temperature.txt')
all_the_lines = my_file.readlines()
items = []
item = []
for i in all_the_lines:
    items. append(abs(float(i)))
    item.append(abs(float(i)))
    
mean = 0.1067682  
data=[]
for i in items:
    data.append(abs(float(i)-mean))



A1,A2,A3,A4,A5,A6= pywt.wavedec(data,'db2',4)
'''
th6=2.8*np.std(A6);
th5=2.8*np.std(A5);
th4=2.8*np.std(A4);
th3=2.8*np.std(A3);
th2=2.8*np.std(A2);
'''
th1=5*np.std(A1);
th6= 0.000391326203281245
th5= 0.000291271678801671
th4= 0.00023864691364537883
th3= 0.0003235506912425535
th2= 0.00038401221783652284
th1= 100

B1=pywt.threshold(A1, th1, 'soft')
B2=pywt.threshold(A2, th2, 'soft')
B3=pywt.threshold(A3, th3, 'soft')
B4=pywt.threshold(A4, th4, 'soft')
B5=pywt.threshold(A5, th5, 'soft')
B6=pywt.threshold(A6, th6, 'soft')


coef =B1,B2,B3,B4,B5,B6
value= pywt.waverec(coef,'db2',4)

output=np.where(value<0, 0, value) 


x=[]
for i in range(100):
    x.append(i)



plt.plot(x, output)
plt.show()

y=[]
for i in range(100):
    if output[i]> 0.000065:
       y.append(i)
T=[]
for i in range(100):
    if i not in y:
       T.append(0.0)
    else:
       T.append(data[i])
print(y)

with open('temperature_fluctuation.txt', 'w') as f:
    for item in T:
        f.write("%s\n" % item)
