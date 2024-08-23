#include "dataPreperation.h"
#include "huffman.h"


int main() {
    char* chars;
    int* freqs;
    int size;

    char *pythonCommand = "python C:\\Users\\razso\\Text-Compression-main\\pdfToTxt.py";
    _putenv("PYTHONPATH=C:\\Users\\razso\\CompressionProject\\venv\\Lib\\site-packages");
    if (system(pythonCommand) != 0) {  // Use Python to execute the script
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
    printf("Compression has completed");  // Indicate successful completion
    return EXIT_SUCCESS;
}
