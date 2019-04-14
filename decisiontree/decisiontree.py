class DecisionTree():
    def __init__(self, data, lable,selection='GainRatio'):
        pass
    def dtreeClassify(self):
        pass
    def treeGenerate(self):
        pass
    def __infoGain(self):
        '''
        information gain 
        '''
        pass
    def __gainRation(self):
        '''
        information ratio
        '''
        pass
    def __giniIndex(self):
        '''
        Gini index
        '''
        pass
    class Node():
        def __init__(self,attrindex):
            self.kids=[]
            self.attrindex=attrindex
            pass
        def addKid(self,kidnode):
            self.kids.append(kidnode)