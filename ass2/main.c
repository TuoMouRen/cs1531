#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "readData.h"
//#include "pagerank.h"
#include "graph.h"




int countinlink(Graph g, int in){
    int inlinks = 0;
    int i = 0;
	for (i = 0; i < g->nV; i++) {
		if (g->edges[i][in]){
			inlinks++;
		}
	}
    return inlinks;
}


int countoutlink(Graph g, int out){
    int outlinks = 0;
    int j = 0;
	for (j = 0; j < g->nV; j++) {
		if (g->edges[out][j]){
			outlinks++;
	    }
	}
    return outlinks;
}



//Wout:
double Wout(Graph g, int from, int to) {
    double count = 0.0;
    int i = 0;
    for(i = 0; i < g->nV; i++) {
        if (g->edges[from][i] == 1 && i!=to) {
          count += countoutlink(g, i);
        }
    }
    //printf("%f",count);
    return countoutlink(g,from)/count;
}

//Win:
double Win(Graph g, int from, int to){
    double count = 0.0;
    int i = 0;
    for (i = 0; i < g->nV; i++) {
        if (g->edges[from][i] == 1 && i!=to) {
          count += countinlink(g, i);
        }
    }
    return countinlink(g,from)/count;
}





int main(void){



int nUrls = GetCollection();
//printf("%d\n",nUrls);


char **urls = readCollection(nUrls);
int i;
//for(i = 0; i < nUrls; i++) {
//    printf("%s\n",urls[i]);

//}

Graph g = newGraph(nUrls);
showGraph(g,1);
GetnewGraph(g,urls,nUrls);
/*
            int inlinks = 0;
            int in = 3;
			for (i = 0; i < g->nV; i++) {
					if (g->edges[i][in]){
						inlinks++;
				}
			}

        printf("%d\n",inlinks);

            int outlinks = 0;
			int out = 3;
            int j=0;
				for (j = 0; j < g->nV; j++) {
					if (g->edges[out][j]){
						outlinks++;
				}
			}
        printf("%d\n",outlinks);
*/
showGraph(g,1);



double b = Wout(g,0,2);

        printf("%f\n",b);
b = Win(g,0,2);
        printf("%f\n",b);
   



return 0;
}














