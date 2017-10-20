// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);

// addon things
typedef struct GraphRep {
	int   nV;
	char  **vertex;
	int   **edges;
} GraphRep;
static int vertexID(char *str, char **names, int N);
int addVertex(char *, char **, int);
#endif
