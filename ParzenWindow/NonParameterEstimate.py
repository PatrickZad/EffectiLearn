import numpy as np
import pandas as pd
def normalWinFunc(vector):
    l=vector**2
    s=0
    for num in l:
        s+=num
    
    pass
def cubeWinFunc(vector):
    pass
def expWinFunc(vector):
    pass
def parzenEstimate(sampleSet,width,winFunc='normal'):
    n,d=sampleSet.shape()
    v=width**d
    if winFunc is 'normal':
        winFunc=normalWinFunc
    elif winFunc is 'cube':
        winFunc=cubeWinFunc
    elif winFunc is 'exp':
        winFunc=expWinFunc
    else:
        pass
    def probability(sample):
        s=0
        for i in range(0,n):
            s+=winFunc((sample-sampleSet[i])/width)/v
        return s/n
    return probability
