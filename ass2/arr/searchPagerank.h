#ifndef SEARCH_H
#define SEARCH_H


void starderliseinput(char *c);
void getFreq(char **temp , int len);
void sortfeq(char **temp, int *feq, int len);
void printresult(char **temp, int *feq, int len);
int getMax(int *feq,int len);
int getfeq(int *feq,int length);
void sortpageRank(char **arr, int length);

#endif
