#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "readData.h"
#include "pagerank.h"
#include "graph.h"
#include "searchPagerank.h"

//New Word List
WordList newWordList(){
    WordList g = malloc(sizeof(struct LinkRep));
    assert(g != NULL);
    g->nV = MAXIMUM;
    for (int i = 0; i < g->nV; i++) g->connections[i] = NULL;
    return g;
}

void addLink(WordList w, int num, char *link){
		assert(w != NULL);
		w->connections[num] = insertVList(w->connections[num], link);
    return;
}

 vLink insertVList(vLink w, char *link){
   vLink newV = malloc(sizeof(struct Node));
	 newV->word = strdup(link);
	 newV->next = NULL;
	 if(w == NULL){
		 w  = newV;
	 }
	 else{
		 vLink end = w;
		 while(end->next != NULL)  end = end->next;
		 end->next = newV;
	 }

   return w;
}

int inVList(WordList w, int num1, char *link){
	vLink V = w->connections[num1];

	while(V != NULL){
			if(strcmp(link, V->word) == 0)	return 1;
			V = V->next;
	}

	return 0;
}

void sortList(WordList w, char **wordList, int wordCount){
	int SORTED = 1;
	do{
		SORTED = 1;
		int a = 0;
		while(a != wordCount - 1){
			char *word1 = wordList[a];
			char *word2 = wordList[a+1];

			if(strcmp(word1,word2) > 0){
				char *temp1 = strdup(word1);
				vLink temp2 = w->connections[a];

				strcpy(word1, word2);
				w->connections[a] = w->connections[a+1];

				strcpy(word2, temp1);
				w->connections[a+1] = temp2;
				SORTED = 0;
			}
			a++;
		}
	} while(SORTED == 0);
	return;
}


void getURLCollection(char **URL, char **URLLink, int numberURL){
    FILE *collection;
    collection = fopen("collection.txt", "r");
    char name[MAXIMUM];
    int j = 0;

    while(fscanf(collection, "%s", name) != EOF){
        URL[j] = strdup(name);
        URLLink[j] = strdup(name);
        URLLink[j] = strcat(URLLink[j], ".txt");
        j++;
    }

    return;
}

int findNumberURL(){
	int numberURL = 0;
	char str[MAXIMUM];

	FILE *collection;
	collection = fopen("collection.txt", "r");
	while(fscanf(collection, "%s", str) != EOF) numberURL++;
	fclose(collection);

	return numberURL;
}
