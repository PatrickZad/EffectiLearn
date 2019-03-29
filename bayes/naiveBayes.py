import numpy as np
import pandas as pd
from nonParameterEstimation import knearest
def naiveBayes(sampleData,lableArray):
    '''
    朴素贝叶斯分类器，暂认为数值型的属性都是连续型，字符型的都是离散型
    args:
        sampleSet:DataFrame
        lableArray:DataFrame
    '''
    lableset=set(lableArray)
    #类先验概率,Serise对象
    lableProb=pd.Serise([(len([i for i in lableArray and i==lable])+1)/\
        (len(lableArray)+len(lableset)) for lable in lableset],index=lableset)#拉普拉斯平滑    
    #类条件概率
    
def continuous(attrArray,lableArray):
    '''
    return:条件样本概率密度，Series对象，索引是类别标签
    '''
    lableSet=set(lableArray)
    attrSet=set(attrArray)
    lableDict={}
    for lable in lableSet:
        lableDict.setdefault(lable,[])
    #条件样本集合，dict对象
    for i in range(len(attrArray)):
        lableDict[lableArray[i]].append(attrArray[i])
    densityList=[knearest.knearestEstimate([samp for samp in lableDict[lable]]) for lable in lableSet]
    return pd.Series(densityList,index=lableSet)

def discrete(attrArray,lableArray): 
    '''
    return:条件样本概率的DataFrame，行索引是属性值类别，列索引是标签类别
    '''
    lableSet=set(lableArray)
    attrSet=set(attrArray)
    lableDict={}
    for lable in lableSet:
        lableDict.setdefault(lable,[])
    #条件样本集合，dict对象
    seriselist=[] 
    for i in range(len(attrArray)):
        lableDict[lableArray[i]].append(attrArray[i])
    for lable in lableSet:
        serise=pd.Series([(len([samp for samp in lableDict[lable] and samp==attr])+1)/\
            (len(lableDict[lable])+len(attrSet)) for attr in attrSet],index=attrSet)#拉普拉斯平滑
        seriselist.append(serise)
    for i in range(len(seriselist)):
        lableDict[lableDict.keys()[i]]=seriselist[i]
    return pd.DataFrame(lableDict)

if __name__=='__main__':
    import requests
    import os
    if 'iris.data' not in os.listdir():
        r=requests.get('https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data')
        with open('./iris.data','w') as f:
            f.write(r.text)
    df=pd.read_csv('./iris.data',names=\
        ['sepalL','sepalW','petalL','petalW','class'])
    print(df)