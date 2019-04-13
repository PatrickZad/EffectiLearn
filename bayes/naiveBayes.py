import numpy as np
import pandas as pd
import sys
import os
sys.path.append(os.getcwd())
class NaiveBayesClassifier():
    def __init__(self,data,lable):
        self.__lableset=set(lable)
        self.__samparray=data
        self.__lablearray=lable

    def naiveBayes(self):
        '''
        朴素贝叶斯分类器，暂认为数值型的属性都是连续型，字符型的都是离散型
        args:
            sampleSet:DataFrame
            lableArray:DataFrame
        returns:
            classifier:function
        '''
        #类先验概率,Serise对象
        lableProb=pd.Serise([(len([i for i in self.__lablearray and i==lable])+1)/\
            (len(self.__lablearray)+len(self.__lableset)) for lable in self.__lableset],\
                index=self.__lableset)#拉普拉斯平滑    
        #类条件概率
        row,column=np.shape(self.__samparray)

    
    def __continuous(self,attrArray):
        import nonParameterEstimation.knearest
        '''
        return:连续属性的条件样本概率密度，Series对象，索引是类别标签
        '''
        attrSet=set(attrArray)
        lableDict={}
        for lable in self.__lableset:
            lableDict.setdefault(lable,[])
        #条件样本集合，dict对象
        for i in range(len(attrArray)):
            lableDict[self.__lablearray[i]].append(attrArray[i])
        densityList=[knearest.knearestEstimate([samp for samp in lableDict[lable]]) for lable in self.__lableset]
        return pd.Series(densityList,index=self.__lableset)

    def __discrete(self,attrArray): 
        '''
        return:离散属性的条件样本概率的DataFrame，行索引是属性值类别，列索引是标签类别
        '''
        if lableSet is None:
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
    '''
    print(sys.path)
    sys.path.append(os.getcwd())
    print(sys.path)
    samparray=np.array([[1,'aa',3,'cc'],[2,'bb',4,'dd']])
    c1=samparray[:,0]
    c2=samparray[:,1]
    '''
    if 'iris.data' not in os.listdir():
        r=requests.get('https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data')
        with open('./iris.data','w') as f:
            f.write(r.text)
    df=pd.read_csv('./iris.data',names=\
        ['sepalL','sepalW','petalL','petalW','class'])
    #print(df)
    samp0=df.iloc[:,:-2]
    samp1=df.iloc[:,-1]
    samp2=samp0.iloc[:,0]
    print('float' in str(samp2.dtype))
    print(samp1.dtype)
    print('samp dtype')