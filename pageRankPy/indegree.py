import csv
import operator

nodes={}
domains={}

#compute indegree
with open('data/example_arcs','r') as f:
    reader=csv.reader(f,delimiter='\t')
    for origin,target in reader:
    	if target in nodes:
    		nodes[target]+=1
    	else:
        	nodes[target]=1

#sort by values
sorted_nodes = sorted(nodes.items(), key=operator.itemgetter(1))
#reverse node list
sorted_nodes.reverse()

#id -> domain name
with open('data/example_index','r') as f:
    reader=csv.reader(f,delimiter='\t')
    for domain,id in reader:
    	if id not in domains:
    		domains[id]=domain


#output
for x in sorted_nodes:
		print "%s: %s" % (domains[x[0]] , x[1])