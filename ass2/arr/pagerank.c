#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pagerank.h"
#include "graph.h"
#include "readData.h"

#define MAXIMUM 500

void PageRankW(char **finalURL, float d, float diffPR, int maxIterations){

    float a;
    char str[MAXIMUM];
    int numberURL = findNumberURL(), j = 0;

    //Create list of URL
    char *URL[numberURL], *URLLink[numberURL];
    getURLCollection(URL, URLLink, numberURL);

    //Create Graph
    Graph graph = newGraph(numberURL);

    //Scan each text file
    for(int i = 0; i < numberURL; i++){
        char *currentURL = URLLink[i];
        FILE *url;
        url = fopen(currentURL, "r");
        while(fscanf(url, "%s", &str)){
            for(int a = 0; a < numberURL; a++){
                if(strcmp(str, URL[a]) == 0) addEdge(graph, URL[i], str);
            }
            if(strcmp(str,"Section-2") == 0) break;
        }
    }

    //Find + Calculate indegree and outdegree
    float *Win[numberURL], *Wout[numberURL];
    for(int a = 0; a < numberURL; a++){
        Win[a] = (float *)malloc(numberURL * sizeof(float));
        Wout[a] = (float *)malloc(numberURL * sizeof(float));
    }

    int indegree[numberURL], outdegree[numberURL];
    float inScore = 0, outScore = 0;

        //Find InDegree + OutDegree
    for(int a = 0; a < numberURL; a++){
        int in = 0,out = 0;
        for(int b = 0; b < numberURL; b++){
            if(isConnected(graph, URL[a], URL[b]) == 1) out+=1;
            if(isConnected(graph, URL[b], URL[a]) == 1) in+=1;
        }
        indegree[a] = in;
        outdegree[a] = out;
    }

        //Find InScore + OutScore
    for(int a = 0; a < numberURL; a++){
        inScore = 0;
        outScore = 0;
        for(int b = 0; b < numberURL; b++){
            if(isConnected(graph, URL[a], URL[b]) == 1){
                inScore+=indegree[b];

                if(outdegree[b] != 0){
                    outScore+=outdegree[b];
                } else{
                    outScore+= 0.5;
                }
            }
        }

            //Find Win + Wout
        for(int b = 0; b < numberURL; b++){
            if(isConnected(graph, URL[a], URL[b]) == 1){
                Win[a][b] = 1.0 * indegree[b]/inScore;

                if(outdegree[b] != 0){
                    Wout[a][b] = outdegree[b]/outScore;
                } else{
                    Wout[a][b] = 0.5/outScore;
                }
            }
            else{
                Win[a][b] = 0;
                Wout[a][b] = 0;
            }
        }
    }

    //Page Rank Algorithm
    float *pageRank[numberURL];
    float diff = diffPR;
    int iteration = 0;

    //Initial Stage
    for(int a = 0; a < numberURL; a++){
        pageRank[a] = (float *)malloc(maxIterations * sizeof(float));
        pageRank[a][0] = 1.0/numberURL;
    }

    while ((iteration < maxIterations) && (diff >= diffPR)){
        iteration++;
        float N = numberURL, sigma;

        for(int a = 0; a < numberURL; a++){
            sigma = 0;
            for(int b = 0; b < numberURL; b++){
                if((isConnected(graph, URL[b], URL[a]) != 0)&&(b!=a)) sigma += pageRank[b][iteration-1] * Win[b][a] * Wout[b][a];
            }
            pageRank[a][iteration] = ((1-d)/N) + (d * sigma);
        }

        diff = 0;
        for(int c = 0; c < numberURL; c++){
            float result = pageRank[c][iteration] - pageRank[c][iteration-1];
            if (result < 0) result = 0 - result;
            diff += result;
        }
    }

    //Sorting Page Rank (Bubble Sort)
    float finalPageRank[numberURL];
    for(int a = 0; a < numberURL; a++) finalPageRank[a] = pageRank[a][iteration];
    int SORTED = 1;
    do{
        SORTED = 1;
        for(int a = 0; a < numberURL - 1; a++){
            if(finalPageRank[a] < finalPageRank[a+1]){
                float temp = finalPageRank[a];
                char tempName[MAXIMUM];
                int temp2 = outdegree[a];

                strcpy(tempName, URL[a]);
                finalPageRank[a] = finalPageRank[a+1];
                strcpy(URL[a],URL[a+1]);
                outdegree[a] = outdegree[a+1];

                finalPageRank[a+1] = temp;
                strcpy(URL[a+1],tempName);
                outdegree[a+1] = temp2;
                SORTED = 0;
            }
        }
    }while(SORTED == 0);

    for(int a = 0; a < numberURL; a++){
      finalURL[a] = URL[a];
    }

    return;
}


