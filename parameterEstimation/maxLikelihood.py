import sympy
import numpy as np
def mle(sampleSet,densityExp,*vars):
    '''
    对符号表达式描述的含参概率密度函数的参数做极大似然估计，
    对随机向量的密度函数参数估计转换为多变量运算
    args:
        sampleSet:array-like 样本集合，每个样本都是一个向量
        densityExp:含参的概率密度函数符号表达式
        *vars:样本向量各分量在densityExp中的符号表示
    return:
        参数估计值的集合
    '''
    lfunc=np.prod([densityExp.subs([(var,sampd) for var in vars \
        for sampd in sample]) for sample in sampleSet])
    params=lfunc.free_symbols
    loglfunc=sympy.expand_log(sympy.log(lfunc))
    solve=sympy.solve([sympy.diff(loglfunc,param) for param in params],*param)
    return solve

if __name__=="__main__":
    x,y=sympy.symbols('x y');
    exp=x+y-x**y
    e1=exp.subs(x,1)
    param=e1.free_symbols
    e1=exp.subs(x,2)
    e1=exp.subs(x,3)