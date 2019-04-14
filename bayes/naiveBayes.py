import numpy as np
import pandas as pd
import sys
import os
sys.path.append(os.getcwd())
class NaiveBayesClassifier():
    '''
    朴素贝叶斯分类器，暂认为数值型的属性都是连续型，字符型的都是离散型
    '''
    def __init__(self,data,lable):
        '''
        完成模型训练
        args:
            data:样本的各属性组成的二维数组
            lable:样本的指定标签
        return:
            none
        '''
        self.__lableset=set(lable)
        self.__samparray=data
        self.__lablearray=lable
        self.__attrset=[]
        row,column=np.shape(data)
        #类先验概率
        self.__lableProb=pd.Serise([(len([i for i in self.__lablearray and i==lable])+1)/\
            (len(self.__lablearray)+len(self.__lableset)) for lable in self.__lableset],\
                index=self.__lableset)#拉普拉斯平滑         
        #类条件属性概率
        for i in range(column):
            self.__attrset.append(Attr(data[:,i],self.__lablearray,self.__lableset))

    def naiveBayesClassify(self,samp):
        '''
        对给定样本进行分类
        args:
            samp:一个样本点，array-like
        return:
            分类结果，classification result
        '''
        sampLable=None
        lableMaxProb=0
        for lable in self.__lableset:
            lableCd=1
            for i in range(len(samp)):
                lableCd*=self.__attrset[i].cdProb(samp[i],lable)#独立性假设
            if lableCd*self.__lableProb[lable]>lableMaxProb:
                sampLable=lable
        return sampLable

    class Attr():
        '''
        完成处理单个属性的操作
        '''
        def __init__(self,attrarray,lablearray,lableset=None):
            '''
            判断属性是否连续，计算全部的类条件概率
            args:
                attrarray:给定属性的所有样本值
                lablearray:全部样本的类别标签
                lableset:类别标签的set
            return:
                none
            '''
            self.__attrarray=attrarray
            self.__lablearray=lablearray
            if lableset is not None:
                self.__lableset=lableset
            else:
                self.__lableset=set(lablearray)
            if attrarray.dtype is 'object':
                self.__classCdProb=self.__discreteCdProb(attrarray)
                self.__isDiscrete=True
            else:
                self.__classCdProb=self.__continuousCdProb(attrarray)
                self.__isDiscrete=False
        def cdProb(self,value,lable):
            '''
            对给定的属性值返回其在指定类条件下的概率
            args:
                value:给定的属性值
                lable:给定的类别标签
            return:

            '''
            if self.__isDiscrete:
                return self.__classCdProb[value,lable]
            else:
                return self.__classCdProb[lable](value)
        def __continuousCdProb(self):
            import nonParameterEstimation.knearest
            '''
            计算单个连续属性的类条件概率
            args:
                none
            return:
                连续属性的条件样本概率密度，Series对象，索引是类别标签
            '''
            lableDict={}
            for lable in self.__lableset:
                lableDict.setdefault(lable,[])
            #条件样本集合，dict对象
            for i in range(len(self.__attrarray)):
                lableDict[self.__lablearray[i]].append(self.__attrarray[i])
            densityList=[knearest.knearestEstimate([samp for samp in lableDict[lable]]) for lable in self.__lableset]
            return pd.Series(densityList,index=self.__lableset)

        def __discreteCdProb(self): 
            '''
            计算单个离散属性的类条件概率
            args:
                none
            return:
                离散属性的条件样本概率的DataFrame，行索引是属性值类别，列索引是标签类别
            '''
            attrSet=set(self.__attrarray)
            lableDict={}
            for lable in self.__lableset:
                lableDict.setdefault(lable,[])
            #条件样本集合，dict对象
            seriselist=[] 
            for i in range(len(self.__attrarray)):
                lableDict[self.__lablearray[i]].append(self.__attrarray[i])
            for lable in self.__lableset:
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