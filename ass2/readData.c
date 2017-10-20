#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "readData.h"
//#include "pagerank.h"




//get all the urls from collection.txt return the number of urls
int GetCollection(){

    FILE *f = fopen("collection.txt","r");
    int count = 0;
    char temp[MAXV];
    while(fscanf(f, "%s",temp) == 1) {
        count++;
    }
    fclose(f);
    return count++;
}

//get all the urls from collection.txt and write in char **urls
char **readCollection(int nUrls) {
    char **urls = malloc(nUrls * sizeof(char*));
    FILE *f = fopen("collection.txt","r");
    char temp[MAXV];
    int i = 0;
    while (fscanf(f, "%s", temp)==1) {
        urls[i] = strdup(temp);
        i++;
    }
    fclose(f);
    return urls;
}


//write all the vertexs and their edges into the graph
void GetnewGraph(Graph g,char **urls, int nUrls){

        //loop thought and write in each url
        int i; 
        for(i = 0; i < nUrls; i++) {
            // write in a url
            g->vertex[i] = urls[i];
        }
 
        //loop thought and read each url file
    
        for(i = 0; i < nUrls; i++) {
            // set filename
            char name[MAXV]; 
            sprintf(name, "%s.txt", g->vertex[i]);
            //printf("TXT:%s\n",name);


            //file open
            FILE *f = fopen(name,"r");
            //git rid of first line
            fscanf(f, "#start Section-1"); 
         
            char temp[MAXV];
            while(fscanf(f, "%s", temp) == 1) {
                if (strcmp(temp,"#end") == 0) {
                    break;
                }
                if (!addEdge(g,g->vertex[i],temp)){
                    perror("unable to add edge");
                }
            }
            fclose(f);
        }


}











