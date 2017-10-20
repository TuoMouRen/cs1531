//search words as cmdline arg
//find pages with one or more search terms
//find pages in decending order of number of search term
//each group of page , decending order of weighted Pagerank
//output all if < 30


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "pagerank.h"
#include "readData.h"
#include "searchPagerank.h"

//mian

int main(int argc,char *argv[]){

    //all variabbles needed
    int nWords = 0;
    int nUrls = 0;
    char **words = NULL;
    char **urls = NULL;
    char temp[3000];
    char newline[3000];
    int i;


    if (argc < 2) {
        fprintf(stderr, "There is no input...\n");
        exit(1);
    }

    for(i=0; i<argc-1;i++){
        FILE *p = fopen("invertedIndex.txt","r");
        starderliseinput(argv[i+1]);

        words = realloc(words,10000);
        words[nWords] = malloc(10000);
        //assume there max 10000 words
        strcpy(words[nWords++],argv[i+1]);

        //when words in input is found, store it's url
        while(fscanf(p, "%99s", temp) == 1){
          if(strcmp(words[i],temp)==0){
              while(fscanf(p,"%99s%99[ \t\n]", temp, newline) == 2){
                urls = realloc(urls,10000);
                urls[nUrls] = malloc(10000);
                strcpy(urls[nUrls++],temp);
                  if(strchr(newline,'\n')){
                    break;
                  }
              }
          }
        }
        fclose(p);
      }

      //find the number int each url
      getFreq(urls,nUrls);
      free(words);
      free(urls);

      return 0;
}


void starderliseinput(char *c){
  int i;
  char *temp;
  char *flag;

  for(i = 0;i < strlen(c);i++){
    c[i] = tolower(c[i]);
  }

  temp = flag = c;
  while(*flag){
    *temp = *flag++;
    if((*temp != '.' && *temp != ',' && *temp != ';' && *temp != ' ')){
      temp++;
    }
  }
  *temp = '\0';
}

void getFreq(char **temp , int len){
  int i,j,m;
  int counter  = 0;
  int feq[len];
  char **url = malloc(sizeof(char)*10000);
  int *freq  =malloc(sizeof(char)*10000);

  //initial feq array
  for(i = 0;i<len;i++){
    feq[i] = -1;
  }

  for(i = 0;i<len;i++){
    m = 1;
    for(j = i+1;j<len;j++){
      if(strcmp(temp[i],temp[j])==0){
        m++;
        feq[j] = 0;
      }
    }
    if(feq[i]!=0){
      feq[i] = m;
    }
  }

  //
  for(i = 0;i<len;i++){
    if(feq[i]!=0){
      url[counter] = temp[i];
      freq[counter] = feq[i];
      counter++;
    }
  }

  sortfeq(url,freq,counter);
  printresult(url,freq,counter);

  free(freq);
  free(url);
}


void sortfeq(char **temp, int *feq, int len){
  int i, j ,flag;
  char *arr;

  for(i = 0;i < len; i++){
    for(j = j+1;j<len;j++){
      if(feq[i]<feq[j]){
        flag = feq[i];
        feq[i] = feq[j];
        feq[j] = flag;

        arr = temp[i];
        temp[i] = temp[j];
        temp[j] = arr;
      }
    }
  }
}

void printresult(char **temp, int *feq, int len){
  int max, i, j ,k;
  int counter1 = 0;
  int counter2 = 0;
  int frequency  = getfeq(feq,len);
  char **flag = NULL;
  int start  = 0;
  char **new  = NULL;

  for(i = 0; i<frequency;i++){
    counter1 = 0;
    max = getMax(feq,len);
    for(j = start;j<len;j++){
      if(feq[j] != max){
        start = j;
        break;
      }

      flag = realloc(flag,10000);
      flag[counter1] = malloc(10000);
      strcpy(flag[counter1++],temp[j]);
      feq[j] = -1;
    }

    sortpageRank(flag,counter1);

    for(k = 0;k<counter1;k++){
      new = realloc(new,10000);
      new[counter2] = malloc(10000);
      strcpy(new[counter2++],flag[k]);
    }
  }

  if(counter2 < 30){
      for(i=0;i<counter2;i++){
        printf("%s\n",new[i]);
      }
  }
  else{
    for(i=0;i<30;i++){
      printf("%s\n",new[i]);
    }
  }
}

int getMax(int *feq,int len){
  int max = feq[0];
  int i;

  for(i = 1;i<len;i++){
    if(feq[i] > max){
      max = feq[i];
    }
  }

  return max;
}

int getfeq(int *feq,int length){
  int distinct = 1;
	int isDistinct;
	int i, j;

	for(i=1 ; i<length; i++){
		isDistinct = 1;
		for(j=0; isDistinct && j<i; j++){
			if(feq[i] == feq[j]){
				isDistinct = 0;
			}
		}
		if(isDistinct){
			distinct++;
		}
	}

	return distinct;
}


void sortpageRank(char **arr, int length){
	int i, j;
	char string[3000];
	char newLine[3000];
	double *prValues = malloc(sizeof(double)*10000);
	int prCount = 0;
	double temp;
	char *tempStr;
	for(i=0; i<length; i++){
		FILE *pr = fopen("pagerankList.txt", "r");
		while(fscanf(pr, "%s", string) != EOF){

			starderliseinput(string);

			if(strcmp(string, arr[i])==0){
				while (fscanf ( pr, "%99s%99[ \t\n]", string, newLine)==2){
					if(strchr(newLine, '\n')){
						prValues[prCount++] = atof(string);
						break;
					}
				}
			}
		}
	}

//bubble sort
	for(i = 0; i<prCount; i++){
		for(j=i+1; j<prCount; j++){
			if(prValues[i] < prValues[j]){


				temp = prValues[i];
				prValues[i] = prValues[j];
				prValues[j] = temp;

				tempStr = arr[i];
				arr[i] = arr[j];
				arr[j] = tempStr;
			}
		}
	}

	free(prValues);
}
