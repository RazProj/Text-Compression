#include "dataPreperation.h"
#include "huffman.h"


int main() {
    char* chars;
    int* freqs;
    int size;

    char *pythonScript = "pdfToTxt.py";
    _putenv("PYTHONPATH=C:\\Users\\razso\\CompressionProject\\venv\\Lib\\site-packages");
    if (system(pythonScript) != 0) {  // Check if the Python script executed successfully
        perror("Failed to execute Python script\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen("HuffmanCodes.txt", "w");
    if (file == NULL) {  // Check if the file was opened successfully
        perror("Unable to open file HuffmanCodes.txt");
        return EXIT_FAILURE;
    }

    extractCharsAndFreqs("extracted_text.txt", &chars, &freqs, &size) ;

    huffmanCodes(file, "extracted_text.txt", chars, freqs, size);

    fclose(file);  // Close the file when done
    free(chars);  // Free allocated memory
    free(freqs);
    remove("extracted_text.txt");
    printf("Success");  // Indicate successful completion
    return EXIT_SUCCESS;
}
