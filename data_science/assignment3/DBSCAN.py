import sys
import numpy as np
from math import sqrt

class Point:
    def __init__(self, id, x, y):
        self.id = id
        self.x = x
        self.y = y
        self.label = None

class DBSCAN:
    def __init__(self, data, Eps, MinPts):
        self.data = data
        self.Eps = Eps
        self.MinPts = MinPts

    def dist(self, p1, p2):
        return sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)

    def get_neighbors(self, x):
        neighbors = [p for p in self.data if self.dist(x, p) <= self.Eps]
        return neighbors

    def clustering(self):
        cluster_num = -1
        clusters = []

        for point in self.data:
            if point.label is None:
                neighbors = self.get_neighbors(point)
                if (len(neighbors) >= self.MinPts):
                    cluster_num += 1
                    point.label = cluster_num
                    clusters.append([])
                    clusters[-1].append(point)

                    pts = set(neighbors)

                    while pts:
                        pt = pts.pop()
                        if pt.label is None:
                            pt.label = cluster_num
                            clusters[-1].append(pt)
                            neighbors = self.get_neighbors(pt)

                            if len(neighbors) >= self.MinPts:
                                pts.update(neighbors)
                    
                    print("cluster_num %d, points = %d" % (cluster_num, len(clusters[-1])))
        
        return clusters

if __name__ == "__main__":
    input_file = sys.argv[1]
    n = int(sys.argv[2])
    Eps = int(sys.argv[3])
    MinPts = int(sys.argv[4])

    data = list(map(lambda i: Point(i[0], i[1], i[2]), (np.loadtxt(input_file).tolist())))
    clusters = DBSCAN(data, Eps, MinPts).clustering()
    clusters.sort(key = len, reverse = True)
    if len(clusters) > n:
        print("remove %d clusters" % (len(clusters) - n))
        clusters = clusters[:n]

    cnt = 0
    for cluster in clusters:
        cluster.sort(key=lambda p: p.id)
        output_file = open("input%d_cluster_%d.txt" % (int(input_file[-5]), cnt), 'w')
        for point in cluster:
            output_file.write(str(int(point.id)) + '\n')
        cnt += 1
        output_file.close()