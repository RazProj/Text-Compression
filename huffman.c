#include "huffman.h"

// Node of the Huffman Tree
struct minHNode {
    char data;            // Character stored in this node
    unsigned freq;        // Frequency of the character
    struct MinHNode *left, *right; // Pointers to left and right child nodes
};

// Min-Heap structure for building the Huffman Tree
struct minHeap {
    unsigned size;        // Current number of elements in the heap
    unsigned capacity;    // Maximum capacity of the heap
    minHNode **array;     // Array of pointers to nodes in the heap
};

// Table to store the Huffman codes for each character
struct table {
    int length;           // Length of the Huffman code
    char *code;           // The Huffman code itself
};

// Main function to generate Huffman codes and print them
void huffmanCodes(FILE *file, char *argument, char *data, int *freq, int size) {
    minHNode *root = buildHuffmanTree(data, freq, size); // Build the Huffman Tree
    table codes[ASCII_QUANTITY_CHARS] = {0}; // Initialize the table for Huffman codes
    int arr[size], top = 0;
    fprintf(file,"Huffman codes : \n");
    printCodes(codes, file, root, arr, top); // Print the Huffman codes
    FILE *file_src = fopen(argument, "r");
    printAndAnalyze(file, file_src, codes, freq, size); // Analyze and print the results
    fclose(file_src);
}

// Function to build the Huffman Tree using the Min-Heap
minHNode *buildHuffmanTree(char *data, int *freq, int size) {
    minHNode *left, *right, *top;
    minHeap *minHeap = createAndBuildMinHeap(data, freq, size); // Create and build the Min-Heap

    // Extract the two minimum elements from the heap and create a new internal node
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq); // '$' is a special marker for internal nodes
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top); // Insert the new node into the heap
    }
    return extractMin(minHeap); // Return the root of the Huffman Tree
}

// Create and build the Min-Heap from the given data and frequencies
minHeap *createAndBuildMinHeap(char *data, int *freq, int size) {
    minHeap *minHeap = createMinHeap(size); // Create a Min-Heap with the given size
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]); // Insert nodes into the heap
    minHeap->size = size;
    buildMinHeap(minHeap); // Build the Min-Heap
    return minHeap;
}

// Create a Min-Heap with a given capacity
minHeap *createMinHeap(unsigned capacity) {
    minHeap *minHeap = malloc(sizeof(minHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = malloc(minHeap->capacity * sizeof(minHNode *)); // Allocate memory for the heap array
    return minHeap;
}

// Create a new node with a given character and frequency
minHNode *newNode(char data, unsigned freq) {
    minHNode *temp = malloc(sizeof(minHNode));
    temp->left = temp->right = NULL; // Initialize left and right children as NULL
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Build the Min-Heap (heapify all non-leaf nodes)
void buildMinHeap(minHeap *minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i); // Heapify all non-leaf nodes
}

// Heapify function to maintain the Min-Heap property
void minHeapify(minHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // Compare the current node with its children
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    // Swap and continue heapifying if needed
    if (smallest != idx) {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if the size of the heap is one (used to determine if we have the final tree)
int isSizeOne(minHeap *minHeap) {
    return (minHeap->size == 1);
}

// Extract the minimum node from the Min-Heap
minHNode *extractMin(minHeap *minHeap) {
    minHNode *temp = minHeap->array[0]; // The root of the heap is the minimum element
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0); // Heapify after extraction
    return temp;
}

// Insert a new node into the Min-Heap
void insertMinHeap(minHeap *minHeap, minHNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    // Fix the Min-Heap property if it is violated
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Swap two nodes in the Min-Heap
void swapMinHNode(minHNode **a, minHNode **b) {
    minHNode *t = *a;
    *a = *b;
    *b = t;
}

// Recursively print the Huffman codes by traversing the tree
void printCodes(table *codes, FILE *file, minHNode *root, int *arr, int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(codes, file, root->left, arr, top + 1); // Traverse the left subtree
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(codes, file, root->right, arr, top + 1); // Traverse the right subtree
    }
    if (isLeaf(root)) {
        // Print the character and its corresponding code
        if (root->data == '\n')
            fprintf(file, "newLine : ");
        else if (root->data == ' ')
            fprintf(file, "space : ");
        else if (root->data == '\t')
            fprintf(file, "tab : ");
        else {
            fprintf(file, "%c : ", root->data);
        }
        printArr(codes, file, arr, top, root); // Print the Huffman code
    }
}

// Check if a node is a leaf (i.e., has no children)
int isLeaf(minHNode *root) {
    return !(root->left) || !(root->right);
}

// Print the Huffman code array and store it in the table
void printArr(table *codes, FILE *file, int *arr, int n, minHNode *root) {
    int i = 0;
    char key = root->data; // Get the character corresponding to the node
    addFirstBitToCode(codes, key, arr[i]); // Add the first bit to the code
    fprintf(file, "%d", arr[i]);
    for (i = 1; i < n; ++i) {
        fprintf(file, "%d", arr[i]);
        addBitToCode(codes, key, arr[i]); // Add subsequent bits to the code
    }
    fprintf(file, "\n");
}

// Add the first bit to the Huffman code table
void addFirstBitToCode(table *codes, char key, int bit) {
    int k = (int) key;
    codes[k].code = calloc(5,sizeof(char)); // Allocate memory for the code string
    if(bit == 0)
        codes[k].code[0] = '0';
    if(bit == 1)
        codes[k].code[0] = '1';
    codes[k].length = 1;
}

// Add subsequent bits to the Huffman code table
void addBitToCode(table *codes, char key, int bit) {
    int k = (int) key;
    int current = codes[k].length;
    codes[k].length++;
    codes[k].code = realloc(codes[k].code, (codes[k].length + 5) * sizeof(char)); // Reallocate memory to add more bits
    if(bit == 0)
        codes[k].code[current] = '0';
    if(bit == 1)
        codes[k].code[current] = '1';

}

// Print the Huffman code string for the source file and analyze it
void printAndAnalyze(FILE *file, FILE *file_src, table *codes, int *freqs, int size) {
    int amount = printCodeString(file, file_src, codes); // Print the Huffman-encoded string
    printAnalyze(file, freqs, amount, size); // Print the analysis of the compression
}

// Print the Huffman code string for each character in the source file
int printCodeString(FILE *file, FILE *file_src, table *codes) {
    fprintf(file, "Huffman String is : ");
    char c;
    int total = 0 , newLine = 0 , count = 0;
    while ((c = fgetc(file_src)) != EOF) {
        count += printCharCode(codes[c], file); // Print the Huffman code for each character
        total += count;
        newLine += count;
        if(newLine > 50) {
            fprintf(file, "\n\t\t\t\t\t"); // Add line breaks for readability
            newLine = 0;
        }
        count = 0;
    }
    return total;
}

// Print the Huffman code for a single character
int printCharCode(table charStruct, FILE *file) {
    int idx = 0;
    while (charStruct.code[idx] != '\0') {
        fprintf(file, "%c", charStruct.code[idx]); // Print each bit of the Huffman code
        idx++;
    }
    return idx;
}

// Analyze and print the compression results
void printAnalyze(FILE *file, int *freqs, int amount, int size) {
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += freqs[i];
    }
    fprintf(file,"\nOriginal file size : %d bits", sum*8); // Original size in bits
    fprintf(file,"\nAfter compression : %d bits", amount); // Compressed size in bits
}
