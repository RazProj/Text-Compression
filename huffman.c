#include "huffman.h"

struct minHNode {
    char data;
    unsigned freq;
    struct MinHNode *left, *right;
};

struct minHeap {
    unsigned size;
    unsigned capacity;
    minHNode **array;
};

struct table {
    int length;
    char *code;
};

void huffmanCodes(FILE *file, char *argument, char *data, int *freq, int size) {
    minHNode *root = buildHuffmanTree(data, freq, size);
    table codes[ASCII_QUANTITY_CHARS] = {0};
    int arr[size], top = 0;
    fprintf(file,"Huffman codes : \n");
    printCodes(codes, file, root, arr, top);
    FILE *file_src = fopen(argument, "r");
    printAndAnalyze(file, file_src, codes, freq,size);
    fclose(file_src);
}

minHNode *buildHuffmanTree(char *data, int *freq, int size) {
    minHNode *left, *right, *top;
    minHeap *minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

minHeap *createAndBuildMinHeap(char *data, int *freq, int size) {
    minHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

minHeap *createMinHeap(unsigned capacity) {
    minHeap *minHeap = malloc(sizeof(minHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = malloc(minHeap->capacity * sizeof(minHNode *));
    return minHeap;
}

minHNode *newNode(char data, unsigned freq) {
    minHNode *temp = malloc(sizeof(minHNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

void buildMinHeap(minHeap *minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void minHeapify(minHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(minHeap *minHeap) {
    return (minHeap->size == 1);
}

minHNode *extractMin(minHeap *minHeap) {
    minHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(minHeap *minHeap, minHNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void swapMinHNode(minHNode **a, minHNode **b) {
    minHNode *t = *a;
    *a = *b;
    *b = t;
}


void printCodes(table *codes, FILE *file, minHNode *root, int *arr, int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(codes, file, root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(codes, file, root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        if (root->data == '\n')
            fprintf(file, "newLine : ");
        else if (root->data == ' ')
            fprintf(file, "space : ");
        else if (root->data == '\t')
            fprintf(file, "tab : ");
        else {
            fprintf(file, "%c : ", root->data);
        }
        printArr(codes, file, arr, top, root);
    }
}

int isLeaf(minHNode *root) {
    return !(root->left) || !(root->right);
}

void printArr(table *codes, FILE *file, int *arr, int n, minHNode *root) {
    int i = 0;
    char key = root->data;
    addFirstBitToCode(codes, key, arr[i]);
    fprintf(file, "%d", arr[i]);
    for (i = 1; i < n; ++i) {
        fprintf(file, "%d", arr[i]);
        addBitToCode(codes, key, arr[i]);
    }
    fprintf(file, "\n");
}

void addFirstBitToCode(table *codes, char key, int bit) {
    int k = (int) key;
    codes[k].code = calloc(5,sizeof(char));
    if(bit == 0)
        codes[k].code[0] = '0';
    if(bit == 1)
        codes[k].code[0] = '1';
    codes[k].length = 1;
}

void addBitToCode(table *codes, char key, int bit) {
    int k = (int) key;
    int current = codes[k].length;
    codes[k].length++;
    codes[k].code = realloc(codes[k].code, (codes[k].length + 5) * sizeof(char));
    if(bit == 0)
        codes[k].code[current] = '0';
    if(bit == 1)
        codes[k].code[current] = '1';

}

void printAndAnalyze(FILE *file, FILE *file_src, table *codes, int *freqs,int size) {
    int amount = printCodeString(file, file_src, codes);
    printAnalyze(file, freqs, amount,size);
}

int printCodeString(FILE *file, FILE *file_src, table *codes) {
    fprintf(file, "Huffman String is : ");
    char c;
    int total = 0 , newLine = 0 , count = 0;
    while ((c = fgetc(file_src)) != EOF) {
        count += printCharCode(codes[c], file);
        total += count;
        newLine += count;
        if(newLine > 50) {
            fprintf(file, "\n\t\t\t\t\t");
            newLine = 0;
        }
        count = 0;
    }
    return total;
}

int printCharCode(table charStruct, FILE *file) {
    int idx = 0;
    while (charStruct.code[idx] != '\0') {
        fprintf(file, "%c", charStruct.code[idx]);
        idx++;
    }
    return idx;
}

void printAnalyze(FILE *file, int *freqs, int amount,int size) {
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += freqs[i];
    }
    fprintf(file,"\nOriginal file size : %d bits",sum*8);
    fprintf(file,"\nAfter compression : %d bits",amount);
}

