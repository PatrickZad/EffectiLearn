import numpy as np
import math
def normalWinFunc(vector):
    l=vector**2
    return math.exp(np.sum(l)/(-2))/(2*math.pi)**0.5
def cubeWinFunc(vector):
    result=1;
    for i in np.abs(vector):
        if i>0.5:
            result=0;
            break
    return result
def expWinFunc(vector):
    return math.exp(-np.linalg.norm(vector))
def parzenEstimate(sampleSet,width,winFunc=normalWinFunc):
    n,d=sampleSet.shape()
    v=(width/n**0.5)**d
    def probability(sample):
        s=0
        for i in range(0,n):
            s+=winFunc((sample-sampleSet[i])/width)/v
        return s/n
    return probability
