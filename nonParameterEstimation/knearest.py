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

if __name__=='__main__':
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    from matplotlib.ticker import LinearLocator, FormatStrFormatter
    def samplePoint(mean,cov,x0,x1):
        x=np.mat([x0,x1])
        mean=np.mat(mean)
        cov=np.mat(cov)
        p=len(mean)
        y=(2*math.pi)**(p/(-2))
        y=y*(np.linalg.det(cov))**(-0.5)
        t=(x-mean)*np.linalg.inv(cov)*(x-mean).T
        y=y*np.e**(-0.5*t[0,0])
        return [x0,x1,y]
    sampleset=np.random.multivariate_normal(mean=[0,0],cov=[[1,0],[0,1]],size=1024)
    densityfunc=knearestEstimate(sampleset,4)
    estipoints=[]
    samppoints=[]
    for i in range(0,64):
        estipoints.append([sampleset[i,0],sampleset[i,1],densityfunc(sampleset[i])])
        samppoints.append(samplePoint([0,0],[[1,0],[0,1]],sampleset[i,0],sampleset[i,1]))
    fig=plt.figure()
    ax=fig.gca(projection='3d')
    ax.scatter([x[0] for x in samppoints],[x[1] for x in samppoints],[x[2] for x in samppoints])
    ax.scatter([x[0] for x in estipoints],[x[1] for x in estipoints],[x[2] for x in estipoints])
    plt.savefig('./nonParameterEstimation/knearest.png')
    plt.show()
