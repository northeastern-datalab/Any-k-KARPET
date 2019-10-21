
# Any-k-KARPET 

  

Many problems in areas as diverse as recommendation systems, social network analysis, semantic search, and distributed root cause analysis can be modeled as pattern search on labeled graphs (also called heterogeneous information networks or HINs).  Given a large graph and a query pattern with node and edge label constraints, a fundamental challenge is to find the top-k matches according to a ranking function over edge and node weights. For users, it is difficult to select value k. 
We therefore propose the novel notion of an any-k ranking algorithm: for a given time budget, return as many of the top-ranked results as possible. Then, given additional time, produce the next lower-ranked results quickly as well. It can be stopped anytime, but may have to continue until all results are returned. This project focuses on acyclic patterns over arbitrary labeled graphs. We are interested in practical algorithms that effectively exploit (1) properties of heterogeneous networks, in particular selective constraints on labels, and (2) that the users often explore only a fraction of the top-ranked results. Our solution, KARPET, carefully integrates aggressive pruning that leverages the acyclic nature of the query, and incremental guided search.  

  
For more information, please read our paper at https://arxiv.org/abs/1802.06060.

  

## Getting Started 

  

These instructions will get you a copy of the project up and running on your local machine. 

  

### Prerequisites 

  

You should have g++ 4.8 or above installed, and access to a bash command line terminal. 

  

### Installing 

  

After git clone, run "make clean" in the project directory to clean object files. Then run "make" to compile. This will create an executable "karpet" in the same directory. 

  

## Running the algorithms 

Run the following command in the same directory: 

 ./karpet datafile queryfile outputfile option 

 

(1) datafile. The format of the datafile follows the description at:  
http://jiongqianliang.com/PRO-HEAPS/
 

(2) queryfile. An example query file is 9 lines each file for a binary tree query. Below is an example queryfile explained: 

 

3 2 3 3 13809 6 193478 

1 2 6 

4 13809 3 3 2 193478 6 6 2 

5 13809 3 193478 6 2 

2 0 2 

2 13809 193478 

1 4 

1 2 

5 0 1 0 2 0   

  

line 1 starts with number 3, meaning that there are 3 mappings to left child, the rest being pairs of parent, left child. 

line 2 starts with number 1, meaning that there is 1 mapping to right child, the rest being parent, right child. 

line 3 records redundant verification mapping from node to parents in the similar format. It should be in consistent with the above two lines. 

line 4 denotes a post-order of all nodes, starting from a count on how many nodes. 

line 5 denotes which indexes in the above post-order list are indexes to terminal nodes in increasing order, starting with a count on list length. 

line 6 denotes such terminal nodes starting with count. Should be consistent with line 4 and 5. 

line 7 denotes which indexes in the post-order list are to junction nodes(nodes with both left child and right child), in increasing order starting with count.  

line 8 denotes such junction nodes starting with count. Should be consistent with line 4 and 7. 

line 9 denotes the type of each node in the post-order nodes list, stating with a count. 

 

(3) outfile. It is the file that the output will be written into. 

 

(4) option. Option 0 is KARPET, option 1 is Unguided baseline, option 2 is Backbone baseline.  

 

### How to interpret the output 

The output will contain a total running time of this query in second, followed by an integer k, then k float number of top-k matching instances.  

 

For example 

0.00325704 5 38.4477 39.0524 39.1529 39.9535 40.3926 

 

Is a result that contains 5 matching instances, the running time of the query (after loading data) is 0.00325704 s,  the top 5 matching instances have weight 38.4477 39.0524 39.1529 39.9535 40.3926 respectively. 

   
### Acknowledgement

Thanks to Jiongqian Albert Liang for providing bfm.cc, bfs.cc, dfm.cc, dfs.cc, dijkstra.cc.

