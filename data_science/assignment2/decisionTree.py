import pandas as pd
import math
import sys

class Tree():
    def __init__(self, _data, is_leaf):
        self.data = _data
        self.children = dict()
        self.is_leaf = is_leaf
        self.crt = None

    # build decision tree
    def buildTree(self, _data):
        global setCnt
        self.data = _data
        attrs = _data.columns.tolist()
        setCnt = _data.shape[0]
        del attrs[-1]

        p_info = 0  # information gain of parent node
        p_crossTable = make_crossTable(_data.iloc[:, len(_data.columns)-1], _data.iloc[:, len(_data.columns)-1])
        for i in range(len(p_crossTable)):
            p_info += sum(-p/setCnt * math.log(p/setCnt, 2) for p in p_crossTable.iloc[i, :-1] if p)
        
        # if the parent's gain is 0, the current node has a label node as a child
        if p_info==0:
            self.is_leaf = 1
            label = _data.iloc[0, -1]
            self.children = label
            return

        # select the attribute that will be the classification criterion
        Max = -1
        selected_attr = 0
        for i in range(len(_data.columns)-1):
            c_info = entropy(make_crossTable(_data.iloc[:, i], _data.iloc[:,len(_data.columns)-1]))
            gain = p_info - c_info
            if Max < gain:
                Max = gain
                selected_attr = i
        
        self.crt = attrs[selected_attr]
        values = _data.iloc[:, selected_attr].unique() # set of selected attribute values     

        # create a new dataframe for each selected attribute values
        # and delete selected attribute column
        for i in range(len(values)):
            nd = _data[_data[attrs[selected_attr]] == values[i]]
            nd = nd.drop([attrs[selected_attr]], axis = 1)
            self.children[values[i]] = Tree(nd, 0)
            self.children[values[i]].buildTree(nd)

    # search the decision tree to determine the class label for each test set
    def classify(self, _data):
        for i in range(len(_data)):
            err = 0
            case = _data.iloc[i, :]
            next = self
            while next.crt != None:
                if not (case[next.crt] in next.children.keys()):
                    maj = next.data.iloc[:, -1].value_counts(sort=True).idxmax(axis=0)
                    test.iloc[i, -1] = maj
                    err = 1
                    break
                next = next.children[case[next.crt]]
            if not err:
                next = next.children
                test.iloc[i, -1] = next

# create cross table based on class label for each attribute
def make_crossTable(fac, label):
    table = pd.crosstab(fac, label)
    table['total'] = table.iloc[:, :len(labels)].sum(axis=1)
    return table

# calculate entropy
def entropy(crossTable):
    global setCnt
    ent = 0
    for i in range(len(crossTable)):
        total = crossTable.iloc[i, -1]
        info = sum(-p/total * math.log(p/total, 2) for p in crossTable.iloc[i, :-1] if p)
        prob = total/ setCnt * info
        ent = ent + prob
    return ent

if __name__ == '__main__':
    train_file = sys.argv[1]
    test_file = sys.argv[2]
    result_file = sys.argv[3]
    
    setCnt = 0

    train = pd.read_csv(train_file, sep='\t')
    labels = train.iloc[1:,len(train.columns)-1].unique() # set of class label values
    decisionTree = Tree(train, 0)
    
    decisionTree.buildTree(train)

    test = pd.read_csv(test_file, sep='\t')
    test[train.columns[-1]] = 'none'

    decisionTree.classify(test)

    test.to_csv(result_file, index=False, sep='\t')