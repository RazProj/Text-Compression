#include "dataPreperation.h"


void extractCharsAndFreqs(const char *filename, char **outChars, int **outFreqs, int *outSize) {

    int frequencies[ASCII_QUANTITY_CHARS] = {0};
    int c;
    int uniqueChars = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Unable to open file");
        terminateProgram();
    }

    while ((c = fgetc(file)) != EOF) {
        if (frequencies[c]++ == 0) uniqueChars++;  // Count unique characters
    }

    *outChars = malloc(uniqueChars * sizeof(char));
    *outFreqs = malloc(uniqueChars * sizeof(int));
    *outSize = 0;

    if (!*outChars || !*outFreqs) {
        perror("Memory allocation failed");
        terminateProgram();
    }
    for (int i = 0; i < ASCII_QUANTITY_CHARS; i++) {
        if (frequencies[i] > 0) {
            (*outChars)[*outSize] = (char) i;
            (*outFreqs)[*outSize] = frequencies[i];
            (*outSize)++;
        }
    }
    fclose(file);
}


void terminateProgram() {
    printf("Terminating the program...\n");
    exit(EXIT_SUCCESS);
}