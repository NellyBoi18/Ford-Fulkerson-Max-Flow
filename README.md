# Ford-Fulkerson Max Flow
Implements the Ford-Fulkerson method for finding the maximum flow in graphs with only integer edge capacities in C. The algorithm is efficient and takes O(mF) time, where m is the number of edges in the graph and F is the value of the maximum flow in the graph. 

# Input
Read from standard input, the input will start with a positive integer, giving the number of instances that follow. For each instance, there will be two positive integers, indicating the number of nodes n = |V| in the graph and the number of edges |E| in the graph. Following this, there will be |E| additional lines describing the edges. Each edge line consists of a number indicating the source node, a number indicating the destination node, and a capacity. The nodes are not listed separetly, but are nubmered {1, ... , n}

# Output
For each instance, the program outputs the maximum flow.

# Sample
**Input:**\
2\
3 2\
2 3 4\
1 2 5\
6 9\
1 2 9\
1 3 4\
2 4 1\
2 5 6\
3 4 4\
3 5 5\
4 6 8\
5 6 5\
5 6 3

**Output:**\
4\
11

The sample input has two instances. The first instance has 3 nodes and 2 edges, followed by 2 additional lines describing the edges (source destination capacity). The second instance has 6 nodes and 9 edges, followed by 9 additional lines describing the edges (source destination capacity)