#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "readData.h"
#include "graph.h"



//count how many inlinks
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

//count how many outlinks
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



//Weighted outlinks:
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

//Weighted inlinks:
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


/////////////////////////////////////////////////////////////////////
//some functions above used to calculate Pagerank below            //
/////////////////////////////////////////////////////////////////////





//Page Rank Algorithm
void calculatePagerank(Graph g, double d, double diffPR, int maxIterations, double *pageR){
    //printf("%f\n",pageR[1][0]);
    //printf("%f\n\n",d);

    double diff = diffPR;
    int iteration = 0;


    double *lastpageR = malloc(g->nV * sizeof(double));
    //pageR to save pageR by the order of the index of the g->vertex[]..
    while (iteration < maxIterations && diff >= diffPR) {
        int i = 0;
        for (i=0; i<g->nV; i++) {
            lastpageR[i] = pageR[i];
        }
        iteration++;
        for (i = 0; i<g->nV; i++) {
            pageR[i] = 0;
            int j= 0;
            double count = 0.0;
            //sum of the PR(pj,t)*Win*Wout where Pj are outlinks from Pi
            for (j=0;j<g->nV;j++) {
                if (g->edges[j][i]!= 0 && j!=i) {
                    count += lastpageR[j] * Win(g,j,i) * Wout(g,j,i);
                    printf("%f",count);
                }
            }

            pageR[i] = ((1 - d)/g->nV) + (d*count);
        }
        int ii = 0;
        for (ii = 0; ii < g->nV; ii++) {
            diff += fabs(pageR[i] - lastpageR[i]);
        }
    }
    return ;
}







int main(int argc, char* argv[]) {

//get number of usrls
    int nUrls = GetCollection();
//get urls
    char **urls = readCollection(nUrls);
//get empty Graph
    Graph g = newGraph(nUrls);
//write in all connections about urls (vertex[] edges[][] )
    GetnewGraph(g,urls,nUrls);
 

//get args from stdin
    double d, diffPR;
    int maxIterations;
    sscanf(argv[1], "%lf", &d);
    sscanf(argv[2], "%lf", &diffPR);
    sscanf(argv[3], "%d", &maxIterations);

    printf("%f\n",d);
    printf("%f\n",diffPR);
    printf("%d\n",maxIterations);

    double *pageR = malloc(g->nV * sizeof(double));
    int i = 0;
// For each url in the PR(pi;0)=1/N
    for(i = 0; i < g->nV; i++){
        pageR[i] = 1.0/g->nV;
    }
    calculatePagerank(g, d, diffPR, maxIterations, pageR);




    for (i=0; i<g->nV; i++) {
        printf("%f\n",pageR[i]);
    }






/*
  Page* pages = malloc(num_urls * sizeof(Page));

  int i;
  for(i=0;i<num_urls;i++)
  {
    pages[i].name = urls[i];
    pages[i].outlinks = calculateOutlinks(num_urls, m, i);
    pages[i].pagerank = pageranks[i];
  }

  qsort(pages, num_urls, sizeof(Page), comparePages);

  FILE *f = fopen("pagerankList.txt", "w");
  for(i=0;i<num_urls;i++)
  {
    fprintf(f, "%s, %d, %.8lf\n", pages[i].name, pages[i].outlinks, pages[i].pagerank);
  }
*/
  return 0;
}
