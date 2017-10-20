#ifndef READDATA_H
#define READDATA_H

#define MAXIMUM 500

typedef struct LinkRep *WordList;
typedef struct Node *vLink;

typedef struct Node {
	char   *word;
	vLink next;
}Node;

//Graph Representation
typedef struct LinkRep {
    int   nV;         // #vertices
    vLink connections[MAXIMUM]; // array of lists
} LinkRep;

// operations on graphs
WordList  newWordList();
void addLink(WordList, int, char *);
vLink insertVList(vLink, char *);
void printURL(WordList, int);
int inVList(WordList , int, char *);
void sortList(WordList, char **, int);

void getURLCollection(char **, char **, int);
int findNumberURL();

#endif
