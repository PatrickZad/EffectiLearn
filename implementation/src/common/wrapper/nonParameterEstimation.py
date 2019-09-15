import numpy as np
import math
def knearestEstimate(sampleSet,k):
    '''
    K近邻非参数估计方法
    Args:
        sampleSet:样本向量的集合
        k:用于计算近邻数Kn的常数
    Returns:
        估计的概率密度函数
    '''
    n,d=np.shape(sampleSet)
    m=(k*n**0.5)
    def probability(sample):
        '''
        K近邻非参数估计得到的概率密度函数
        Args:
            sampleSet:概率密度待估计的样本向量
        Returns:
            估计的概率密度
        '''
        dist=[]
        for p in sampleSet-sample:
            dist.append((np.sum(p**2))**0.5)
        np.sort(np.array(dist))
        r=dist[int(m)]
        v=math.pi**(d/2)*r**d/math.gamma(d/2+1)
        return m/n/v
    return probability
def normalWinFunc(vector):
    '''
    使用标准正态分布的Parzen窗函数
    Args:
        vector:窗函数的输入向量
    Returns:
        窗函数的数值运算结果
    '''
    l=vector**2
    return math.exp(np.sum(l)/(-2))/(2*math.pi)**0.5
def cubeWinFunc(vector):
    '''
    方窗Parzen窗函数
    Args:
        vector:窗函数的输入向量
    Returns:
        窗函数的数值运算结果
    '''
    result=1;
    for i in np.abs(vector):
        if i>0.5:
            result=0;
            break
    return result
def expWinFunc(vector):
    '''
    指数窗Parzen窗函数
    Args:
        vector:窗函数的输入向量
    Returns:
        窗函数的数值运算结果
    '''
    return math.exp(-np.linalg.norm(vector))
def parzenEstimate(sampleSet,w,winFunc=normalWinFunc):
    '''
    Parzen窗非参数估计方法
    Args:
        sampleSet:样本向量的集合
        width:用于计算窗宽hn的常数
        winFunc:Parzen窗估计所使用的窗函数，内置方窗cubeWinFunc,标准正态窗normalWinFunc,指数窗expWinFunc,可以使用自定义窗函数
    Returns:
        估计的概率密度函数
    '''
    n,d=sampleSet.shape
    width=w/n**0.5
    v=width**d
    def probability(sample):
        '''
        Parzen窗非参数估计得到的概率密度函数
        Args:
            sampleSet:概率密度待估计的样本向量
        Returns:
            估计的概率密度
        '''
        s=0
        for i in range(0,n):
            s+=winFunc((sample-sampleSet[i])/width)/v
        return s/n
    return probability