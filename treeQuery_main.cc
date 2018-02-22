  #include "global.h"
#include "proto.h"
#include "pruned_landmark_labeling.h"
#include <unordered_set>
using namespace std;




//2018
int main (int argc, char **argv){

    char *in_fname = argv[1];
    char *qfname = argv[2];
    string option(argv[4]);

	double timeDiff = 0.0;
	double pTime1 = 0, pTime2 = 0;//time for establishing prophet graph.
	struct timeval start_before_load,start, time1, time2, time3, time4, startQuery, endQuery;
	gettimeofday(&start_before_load,NULL);

	PrunedLandmarkLabeling<> pll;
	vector<pair<int, int>> edge_list;

	graph_t G = load_graph(in_fname, edge_list);//loading the graph.


	cout << "# nodes: " << G.n << ".  # edges: " << G.neighbors.size()/2 << endl;
	gettimeofday(&start,NULL);
	Query_tree testQTree = readfromfile(qfname);



	gettimeofday(&time1, NULL);
	//query the pattern

    QueryResultTrees qResult;
    if (option == "0") qResult = AStar_Prophet_Tree_v2(G,testQTree,pTime2); //pTime is only useful if the weight depends on recency.
    if (option == "1") qResult = Bruteforce(G,testQTree,pTime2);
    if (option == "2") qResult = Backbone_query(G,testQTree,pTime2);

    gettimeofday(&time2, NULL);

	timeDiff = (time2.tv_sec + double(time2.tv_usec)/1000000) - (time1.tv_sec + double(time1.tv_usec)/1000000);

    if(qResult.trees.size()>0){
        for (int i=0; i<qResult.trees.size(); i++){
                cout  <<i<<" th lightest tree has weight: "<< qResult.trees[i].wgt << "\t" << qResult.mem << "\t" <<qResult.numTrees << "\t" << qResult.totalTrees << "\t" <<"time--"<<timeDiff<<endl;
        }
    }

	else{
        cout << -1 << "\t" << qResult.mem << "\t" << qResult.totalTrees << endl;
        return 0; //terminate when there is no instances: do not count those queries.
		}
	cout << "#################################################"<< endl;


	string outputFile(argv[3]);
	string tmpstr = outputFile +".result.txt";
	ofstream ofs0 (tmpstr.c_str(), std::ofstream::out);//creating output stream.
	print2FileTree(qResult, timeDiff, ofs0) ;

	ofs0.flush();


	ofs0.close();


    return 0;
}



