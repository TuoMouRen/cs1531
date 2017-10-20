#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "readData.h"
#include "searchPagerank.h"
#include "pagerank.h"
#include "invertedIndex.h"

#define MAXIMUM 500

int main(int argc, char *argv[]){

    if (argc == 1) return 1;

    int a = 1;
    char **words = malloc(sizeof(char) * (argc - 1));
    while(a != argc){
      words[a-1] = strdup(argv[a]);
      a++;
    };

    PageRankW(0.85, 0.00001, 1000);
    invertedIndex();
    findResult(words, argc - 1);

    for(int a = 1; a != argc; a++){
      free(words[a-1]);
    }
    free(words);

    return 0;
}

void findResult(char **words, int argc){

  FILE *inputFile;
  char **urlList = malloc(0);
  char str[100];
  int urlCount = 0;

  inputFile = fopen("pagerankList.txt", "r");
  while(fscanf(inputFile, "%s", str) != EOF){

    for(int a = 0; str[a]; a++){
        if((str[a] == ',')||(str[a] == '?')||(str[a] == '.')||(str[a] == ';')){
            str[a] = '\0';
        }
    }

    if(str[0] != '0' && str[0] != '1' && str[0] != '2' && str[0] != '3' && str[0] != '4' && str[0] != '5' && str[0] != '6' && str[0] != '7' && str[0] != '8' && str[0] != '9'){
      urlList = realloc(urlList, (urlCount + 1) * (strlen(str) + 10));
      urlList[urlCount] = strdup(str);
      urlCount++;
    }
  }

  int wordCount[urlCount];

  for(int a = 0; a < urlCount; a++) wordCount[a] = 0;


  for(int i = 0; i < argc; i++){
    char *currentWord = words[i];
    int FOUND = 0;


    inputFile = fopen("invertedIndex.txt", "r");

    while((FOUND == 0) && (fscanf(inputFile, "%s", str) != EOF)){
      int a = strlen(str);
      if(strcmp(currentWord,str) == 0){
        do{
          FOUND = 1;
          fscanf(inputFile, "%s", str);
          for(int j = 0; j < urlCount; j++){
            if(strcmp(urlList[j],str) == 0){
              wordCount[j] += 1;
              FOUND = 0;
            }
          }
        }while(FOUND == 0);
      }
    }
  }

  int finalCount = 0;
  char **finalURL = malloc(0);

  for(int a = 0; a < urlCount; a++){
      if(wordCount[a] == argc){
        finalURL = realloc(finalURL, MAXIMUM * (finalCount + 1));
        finalURL[finalCount] = strdup(urlList[a]);
        finalCount++;
      }
  }

  for(int a = 0; a < finalCount; a++){
    printf("%s\n", finalURL[a]);
    //free(finalURL[a]);
    //free(urlList[a]);
  }
  free(urlList);
  free(finalURL);
}
