import numpy as np
class DecisionTree():
    def __init__(self, data,lablecolumn=-1,selection='GainRatio'):
        if lablecolumn < 0:
            lablecolumn=len(data.columns)+lablecolumn
        self.__treeRoot=Node()#没有分支到 root 节点的分支条件，分支条件都保存在子结点
        self.__samparray=data
        self.__lablearray=data.iloc[:,lablecolumn].vlaues
        self.__selection=selection
        self.__treeGenerate(self.__treeRoot,data,[i for i in range(len(data.columns)) if i != lablecolumn])
    def dtreeClassify(self,samp):
        pass
    def __treeGenerate(self,node,data,attrarray,lablecolumn=-1):
        '''
        判断node是否为叶节点
        若不是则为其增加子结点，子结点的分支条件也进行判断
        attrarray保存各属性在data.columns中的索引
        '''
        diff=False#剩余数据的lable是否全相同
        lablearray=data.iloc[:,lablecolumn].values
        for lable in lablearray:
            if lable != lablearray[0]:
                diff=True
                break
        if diff :
            same=True#same 为 False 时产生子结点 
            if len(attrarray)!=0:
                for attr in attrarray:
                    for sample in data:
                        if sample[attr] != data[0][attr]:
                            same=False    
                            break
                    if not same:
                        break
            if same :
                uniqueLable=np.unique(lablearray)
                lableAmountDict={lable : 0 for lable in uniqueLable}
                for i in range(len(data)):
                    lableAmountDict[lablearray[i]]+=1
                amount=0
                lable=None
                for k,v in lableAmountDict.items():
                    if v>amount:
                        lable=k
                        amount=v
                node.setLeaf(lable)
            else :
                if self.__selection is 'GainRatio':
                    bestAttr=self.__gainRatio(data,lablearray,attrarray)
                if self.__selection is 'infoGain':
                    bestAttr=self.__infoGain(data,lablearray,attrarray)
                if self.__selection is 'giniIndex':
                    bestAttr=self.__giniIndex(data,lablearray,attrarray)
                attrVals=np.unique(self.__samparray.iloc[:,bestAttr].values)
                if data[bestAttr].dtype is 'object':
                    for val in attrVals:
                        kidNode=Node(bestAttr,True,val)
                        node.addKid(kidNode)
                        dataval=data[data[str(data.columns[bestAttr])]==val]
                        if len(dataval) == 0:
                            uniqueLable=np.unique(lablearray)
                            lableAmountDict={lable : 0 for lable in uniqueLable}
                            for i in range(len(data)):
                                lableAmountDict[lablearray[i]]+=1
                            amount=0
                            lable=None
                            for k,v in lableAmountDict.items():
                                if v>amount:
                                    lable=k
                                    amount=v
                            kidNode.setLeaf(lable)
                        else:
                            i=0
                            for j in attrarray:
                                if attrarray[j]==bestAttr:
                                    i=j
                                    break
                            newAttrarray=attrarray.copy().pop(i)
                            self.__treeGenerate(kidNode,dataval,newAttrarray)
        else:
            node.setLeaf(lablearray[0])
    def __infoGain(self,data,lablearray,attrarray):
        '''
        information gain 
        '''
        pass
    def __gainRatio(self,data,lablearray,attrarray):
        '''
        information ratio
        '''
        pass
    def __giniIndex(self,data,lablearray,attrarray):
        '''
        Gini index
        '''
        pass
    class Node():
        def __init__(self):
            '''
            根节点初始化
            '''
            self.kids=[]
            self.__isLeaf=False
        def __init__(self,attrindex,isDiscrete,value,isLarger=None):
            self.kids=[]
            self.attrindex=attrindex
            self.__isLeaf=False
            self.__isDiscrete=isDiscrete
            self.__value=value
            if not isDiscrete:
                self.__isLarger=isLarger
        def addKid(self,kidnode):
            self.kids.append(kidnode)
        def setLeaf(self,lable):
            self.__isLeaf=True
            self.__lable=lable
        def isThis(self,sample):
            result=False
            if self.__isDiscrete:
                if sample[attrindex]==self.__value:
                    result=True
            else:
                if self.__isLarger:
                    if sample[attrindex]>self.__value:
                        result=True
                else:
                    if sample[attrindex]<self.__value:
                        result=True
