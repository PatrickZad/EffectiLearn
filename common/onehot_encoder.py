import pandas as pd
import numpy as np
def onehot_encode(attrArray):
    '''
    输入一列离散属性，返回独热编码的一组属性列
    Args:
        array-like
    Returns:
        dataframe
    '''
    attrset=set(attrArray)
    attrdict={attr:np.zeros(len(attrArray)) for attr in attrset}
    for i in range(len(attrArray)):
        attrdict[samp][i]=1
    return pd.DataFrame({attr:pd.Series(attrdict[dict]) for attr in attrset})