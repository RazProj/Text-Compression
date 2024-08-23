#include <stdio.h>
#include <stdlib.h>

#define ASCII_QUANTITY_CHARS 128


typedef struct minHNode minHNode;
typedef struct minHeap minHeap;
typedef struct table table;

void huffmanCodes(FILE *file,char *argument,char data[], int freq[], int size);
minHNode* buildHuffmanTree(char data[], int freq[], int size);
minHeap* createAndBuildMinHeap(char data[], int freq[], int size);
minHeap* createMinHeap(unsigned capacity);
minHNode* newNode(char data, unsigned freq);
void buildMinHeap(minHeap* minHeap);
void minHeapify(minHeap* minHeap, int idx);
int isSizeOne(minHeap* minHeap);
minHNode* extractMin(minHeap* minHeap);
void insertMinHeap(minHeap* minHeap, minHNode* minHeapNode);
void printCodes(table* codes,FILE *file,minHNode* root, int arr[], int top);
int isLeaf(minHNode* root);
void printArr(table* codes,FILE* file,int arr[], int n,minHNode* root);
void swapMinHNode(minHNode** a, minHNode** b);
void addFirstBitToCode(table *codes, char key, int bit);
void addBitToCode(table *codes, char key, int bit);
void printAndAnalyze(FILE *file, FILE *argument, table *codes, int *freqs,int size);
int printCodeString(FILE *file, FILE *argument, table *codes);
int printCharCode(table charStruct, FILE *file);
void printAnalyze(FILE *file, int *freqs, int amount,int size);


void printTable(table *codes);