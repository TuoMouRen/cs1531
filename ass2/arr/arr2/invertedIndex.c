#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "readData.h"
#include "invertedIndex.h"
#include "searchPagerank.h"

//Get Word List Graph
void invertedIndex(){

    int numberURL = 0, wordCount = 0, NEWWORD;
    char str[100];
    WordList wordCountList = newWordList();

    //Word List
    char **wordList = (char **)malloc(sizeof(char *) * MAXIMUM);
    for(int a = 0; a < MAXIMUM; a++){
        wordList[a] = (char *)malloc(MAXIMUM * sizeof(char));
    }

    //Get URL
    FILE *collection;
    collection = fopen("collection.txt", "r");
    while(fscanf(collection, "%s", str) != EOF) numberURL++;
    fclose(collection);

    //Create list of URL
    char **URL = malloc(sizeof(char) * 100 * numberURL);
    char **URLLink = malloc(sizeof(char) * 100 * numberURL);
    getURLCollection(URL, URLLink, numberURL);

    //Scan each file
    for(int i = 0; i < numberURL; i++){
        FILE *url;
        char *currentURL = URLLink[i];
        url = fopen(currentURL, "r");

        //Skip Section 1
        fscanf(url, "%s", &str);
        while(strcmp(str, "Section-2") != 0) fscanf(url, "%s", &str);

        //Scan text in each text
        while(fscanf(url, "%s", &str) != EOF && (strcmp("#end",str) != 0)){
            for(int a = 0; str[a]; a++){
                str[a] = tolower(str[a]);
                if((str[a] == ',')||(str[a] == '?')||(str[a] == '.')||(str[a] == ';')){
                    str[a] = '\0';
                }
            }

            //Find if it's a duplicated word
            NEWWORD = 1;
            for(int m = 0; m < wordCount && NEWWORD == 1; m++){
                if(strcmp(wordList[m],str) == 0){
                  if (inVList(wordCountList, m, URL[i]) == 0){
                    addLink(wordCountList, m, URL[i]);
                  }
                  NEWWORD = 0;
                }
            }

            //New Word
            if (NEWWORD == 1){
                addLink(wordCountList, wordCount, URL[i]);
                wordList[wordCount] = strdup(str);
                wordCount++;
            }
        }
    }

    //Finalise wordCount
    sortList(wordCountList, wordList, wordCount);

    //Print Result
    FILE *textFile;
  	textFile = fopen("invertedIndex.txt", "w");
    for(int a = 0; a < wordCount; a++){
      fprintf(textFile, "%s ", wordList[a]);
      vLink current = wordCountList->connections[a];
    	while(current != NULL){
        fprintf(textFile, "%s ", current->word);
    		current = current->next;
    	}
      fprintf(textFile, "\n");
    }
    fclose(textFile);

    free(wordList);
    free(URL);
    free(URLLink);
}
