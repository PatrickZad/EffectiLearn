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
def parzenEstimate(sampleSet,width,winFunc=cubeWinFunc):
    n,d=sampleSet.shape
    width=width/n**0.5
    v=width**d
    def probability(sample):
        s=0
        for i in range(0,n):
            s+=winFunc((sample-sampleSet[i])/width)/v
        return s/n
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
    densityfunc=parzenEstimate(sampleset,4)
    estipoints=[]
    samppoints=[]
    for i in range(0,64):
        estipoints.append([sampleset[i,0],sampleset[i,1],densityfunc(sampleset[i])])
        samppoints.append(samplePoint([0,0],[[1,0],[0,1]],sampleset[i,0],sampleset[i,1]))
    fig=plt.figure()
    ax=fig.gca(projection='3d')
    ax.scatter([x[0] for x in samppoints],[x[1] for x in samppoints],[x[2] for x in samppoints])
    ax.scatter([x[0] for x in estipoints],[x[1] for x in estipoints],[x[2] for x in estipoints])
    plt.savefig('./parzen.png')
    plt.show()
