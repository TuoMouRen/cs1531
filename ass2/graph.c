// graph.c ... Graph of strings (adjacency matrix)
// Written by John Shepherd, September 2015
// Form lab08
// Cited in the Shuyu Zong's ass2 (Graph ADT)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
//#include "pagerank.h"

#define strEQ(g,t) (strcmp((g),(t)) == 0)


// duplicate things that complete in graph.h 


// Function signatures

Graph newGraph();
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
static int vertexID(char *, char **, int);
int addVertex(char *, char **, int);

// newGraph()
// - create an initially empty Graph
// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV;
	new->vertex = malloc(nV*sizeof(char *));
	assert(new->vertex != NULL);
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	    }
	return new;
}

// disposeGraph(Graph)
// - clean up memory associated with Graph
void disposeGraph(Graph g)
{
	if (g == NULL) return;
	int i;
	for (i = 0; i < g->nV; i++) {
		free(g->vertex[i]);
	}
	for (i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
}

// addEdge(Graph,Src,Dest)
// - add an edge from Src to Dest
// - returns 1 if edge successfully added
// - returns 0 if unable to add edge
//   (usually because nV exceeds maxV)
int addEdge(Graph g, char *src, char *dest)
{
	assert(g != NULL);
	int v = vertexID(src,g->vertex,g->nV);
	int w = vertexID(dest,g->vertex,g->nV);

	g->edges[v][w] = 1;
	return 1;
}

// isConnected(Graph,Src,Dest)
// - check whether there is an edge from Src->Dest
int isConnected(Graph g, char *src, char *dest)
{
	assert(g != NULL);
	int v = vertexID(src,g->vertex,g->nV);
	int w = vertexID(dest,g->vertex,g->nV);
	if (v < 0 || w < 0)
		return 0;
	else
		return g->edges[v][w];
}

// nVertices(Graph)
// - return # vertices currently in Graph
int nVertices(Graph g)
{
	assert(g != NULL);
	return (g->nV);
}



// showGraph(Graph)
// - display Graph
void showGraph(Graph g, int mode)
{
	assert(g != NULL);
	if (g->nV == 0)
		printf("Graph is empty\n");
	else {
		printf("Graph has %d vertices:\n",g->nV);
		int i, j;
		if (mode == 1) {
			for (i = 0; i < g->nV; i++) {
				for (j = 0; j < g->nV; j++)
					printf("%d",g->edges[i][j]);
				putchar('\n');
			}
		}
		else if (mode == 2){
			for (i = 0; i < g->nV; i++) {
				printf("Vertex: %s\n", g->vertex[i]);
				printf("connects to\n");
				for (j = 0; j < g->nV; j++) {
					if (g->edges[i][j])
						printf("   %s\n",g->vertex[j]);
				}
			}
		}
	}
}

// Helper functions


// vertexID(Str,Names,N)
// - searches for Str in array of Names[N]
// - returns index of Str if found, -1 if not
static int vertexID(char *str, char **names, int N)
{
	int i;
	for (i = 0; i < N; i++)
		if (strEQ(str,names[i])) return i;
	return -1;
}

// addVertex(Str,Names,N)
// - add Str at end of Names
int addVertex(char *str, char **names, int N)
{
	names[N] = strdup(str);
	return N;
}
