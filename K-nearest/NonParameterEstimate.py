import numpy as np
import math
def knearestEstimate(sampleset,k):
    n,d=np.shape(sampleset)
    m=(k/n**0.5)%1
    def probability(sample):
        dist=[]
        for p in sampleset-sample:
            dist.append((np.sum(p**2))**0.5)
        dist=np.sort(np.array(dist))
        r=dist[m-1]
        v=math.pi**(d/2)*r**d/math.gamma(d/2+1)
        return m/n/v

