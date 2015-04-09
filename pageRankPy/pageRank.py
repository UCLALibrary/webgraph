# Copyright (c) 2010 Pedro Matiello <pmatiello@gmail.com>
#                    Juarez Bochi <jbochi@gmail.com>
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:

# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

import csv, operator
import networkx as nx


"""
PageRank algoritm

@sort: pagerank
"""

def pagerank(graph, damping_factor=0.85, max_iterations=100, min_delta=0.00001):
    """
    Compute and return the PageRank in an directed graph.    
    
    @type  graph: digraph
    @param graph: Digraph.
    
    @type  damping_factor: number
    @param damping_factor: PageRank dumping factor.
    
    @type  max_iterations: number 
    @param max_iterations: Maximum number of iterations.
    
    @type  min_delta: number
    @param min_delta: Smallest variation required to have a new iteration.
    
    @rtype:  Dict
    @return: Dict containing all the nodes PageRank.
    """
    
    nodes = graph.nodes()
    graph_size = len(nodes)
    if graph_size == 0:
        return {}
    min_value = (1.0-damping_factor)/graph_size #value for nodes without inbound links
    
    # itialize the page rank dict with 1/N for all nodes
    pagerank = dict.fromkeys(nodes, 1.0/graph_size)
        
    for i in range(max_iterations):
        diff = 0 #total difference compared to last iteraction
        # computes each node PageRank based on inbound links
        for node in nodes:
            rank = min_value
            for referring_page in graph.neighbors(node):
                rank += damping_factor * pagerank[referring_page] / graph.degree(referring_page)
                
            diff += abs(pagerank[node] - rank)
            pagerank[node] = rank
        
        #stop if PageRank has converged
        if diff < min_delta:
            break
    
    return pagerank


if __name__ == '__main__':

    domains={}
    edges=[]
    G=nx.DiGraph()

    #compute indegree
    with open('data/example_index','r') as f:
        reader=csv.reader(f,delimiter='\t')
        for domain,id in reader:
            domains[id]=domain
            G.add_node(id)


    with open('data/example_arcs','r') as f:
        reader=csv.reader(f,delimiter='\t')
        for origin,target in reader:
            t=(origin,target)
            edges.append(t)

            
 
    G.add_edges_from(edges)
    graph = pagerank(G)


    #sort by values
    sorted_nodes = sorted(graph.items(), key=operator.itemgetter(1))
    #reverse node list
    sorted_nodes.reverse()

    i=1
    for x in sorted_nodes:
            print "%s: %s" % (domains[x[0]] , i)
            i+=1
            
