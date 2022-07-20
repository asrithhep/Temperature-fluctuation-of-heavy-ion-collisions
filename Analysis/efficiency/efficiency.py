import numpy as np
import matplotlib.pyplot as plt
import pywt
import math
import random



def wavelet(items):
    mean = 0.10649405999999999 #np.mean(item)    
    data=[]
    for i in items:
        data.append(abs(float(i)-mean))


    A1,A2,A3,A4,A5,A6= pywt.wavedec(items,'db2',4)
    '''

    th6=2.5*np.std(A6);
    th5=2.8*np.std(A5);
    th4=2.8*np.std(A4);
    th3=2.8*np.std(A3);
    th2=2.8*np.std(A2);
    '''
    th=100
    #th1=0.007231178851969548
    th1=2.5*np.std(A1);
    th6= 0.0017410719645134455
    th5= 0.0033598009124183753
    th4= 0.0014806283066986488
    th3= 0.002385945177408299
    th2= 0.004647258596840243
    
    B =pywt.threshold(A1,100, 'soft')
    B1_=pywt.threshold(A1,th1, 'soft')
    B2_=pywt.threshold(A2, th, 'soft')
    B3_=pywt.threshold(A3, th, 'soft')
    B4_=pywt.threshold(A4, th, 'soft')
    B5_=pywt.threshold(A5, th, 'soft')
    B6_=pywt.threshold(A6, th, 'soft')
    B1=pywt.threshold(A1, th1, 'soft')
    B2=pywt.threshold(A2, th2, 'soft')
    B3=pywt.threshold(A3, th3, 'soft')
    B4=pywt.threshold(A4, th4, 'soft')
    B5=pywt.threshold(A5, th5, 'soft')
    B6=pywt.threshold(A6, th6, 'soft')


    coef=B1,B2,B3,B4,B5,B6
    coef1=B,B2,B3,B4,B5,B6
    coef2=B1_,B2_,B3_,B4_,B5_,B6_
    
    value= pywt.waverec(coef,'db2',4)
    output=np.where(value<0, 0, value) 
    value1= pywt.waverec(coef1,'db2',4)
    output1=np.where(value1<0, 0, value1)
    value2= pywt.waverec(coef2,'db2',4)
    output2=np.where(value2<0, 0, value2) 

    return (output, output1, output2)

 
   
def efficiency(i,j):
    random.seed((10*j)+i) 
    randomlist = random.sample(range(0, 100), i)
    my_file = open('temperature.txt')
    all_the_lines = my_file.readlines()
    items = []

    for h in all_the_lines:
        items. append(abs(float(h)))
    for m in randomlist:
        items[m]= .1150;
    output,output1,output2=wavelet(items)
    
    y=[]
    z=[]
    T=[]

    for i in range(100):
        if output1[i]> 0.0001:
           z.append(i)

    for i in range(100):
        if output[i]< (output2[i]-.000091):
           y.append(i)

    k=0
    if i < 60 :
        for n in z:
            if items[n]==.1150 :
               k=k+1

    if i >= 60 :
        for m in y:
            if items[m]==.1150 :
               k=k+1
        
    efficiency= k*100/i
    print (i,efficiency)
    #print (items)
    return (efficiency)

EFF=[]
n=1   
for i in range(1,101):
    eff=0
    for j in range(n):
        eff_=efficiency(i,j)
        eff=eff+eff_
    EFF.append(eff/n)
        
with open('eff1.txt', 'w') as f:
    for item in EFF:
        f.write("%s\n" % item)  
       
#print(EFF)
