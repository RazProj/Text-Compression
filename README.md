# Huffman Compression Project

### Overview

This project provides a set of utilities for extracting text from PDF files and compressing data using Huffman coding.
The core features include converting PDF files to text, preparing data for compression, and applying Huffman encoding to compress data.

### Project Structure

* pdfToTxt.py: A script that extracts text from a PDF file using the PyPDF2 library and saves it to a .txt file.
* importFile.py: A utility script that allows the user to select a PDF file through a file dialog and copies it to the working directory.
* compression.c: A C program that handles data compression using Huffman coding.
* dataPreperation.c: A C program that prepares data for compression by building frequency table.
* dataPreperation.h: Header file for dataPreperation.c.
* huffman.c: A C program that implements Huffman coding for data compression and decompression.
* huffman.h: Header file for huffman.c.
* HuffmanCodes.txt: A text file containing Huffman codes used for encoding and decoding.

### How It Works
PDF to Text Extraction
The pdfToTxt.py script uses the PyPDF2 library to read the content of each page in a PDF file,
filters the text to include only printable ASCII characters, and saves the output to a text file.

Data Compression
The C programs implement Huffman coding, a lossless data compression algorithm.
The dataPreperation.c script prepares the data, and huffman.c handles the actual encoding and decoding process using the Huffman tree.

