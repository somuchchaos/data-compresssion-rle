#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

// Function to compress file using RLE
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    
    if (!in || !out) {
        printf("Error opening files!\n");
        exit(1);
    }

    char current, next;
    int count = 1;
    
    current = fgetc(in);
    while (current != EOF) {
        next = fgetc(in);
        
        if (next == current) {
            count++;
        } else {
            // Write compressed data
            if (count > 3 || current == '#') {
                fprintf(out, "#%c%d", current, count);
            } else {
                for (int i = 0; i < count; i++) {
                    fputc(current, out);
                }
            }
            count = 1;
        }
        current = next;
    }

    fclose(in);
    fclose(out);
}

// Function to decompress RLE file
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    
    if (!in || !out) {
        printf("Error opening files!\n");
        exit(1);
    }

    char current;
    while ((current = fgetc(in)) != EOF) {
        if (current == '#') {
            char repeatedChar = fgetc(in);
            if (repeatedChar == EOF) break;

            char numStr[10];
            int i = 0;
            char ch;

            while ((ch = fgetc(in)) != EOF && isdigit(ch)) {
                numStr[i++] = ch;
            }
            numStr[i] = '\0';
            int count = atoi(numStr);

            for (int j = 0; j < count; j++) {
                fputc(repeatedChar, out);
            }

            if (ch != EOF) {
                ungetc(ch, in);
            }
        } else {
            fputc(current, out);
        }
    }

    fclose(in);
    fclose(out);
}

int main() {
    int choice;
    char inputFile[MAX_LEN], outputFile[MAX_LEN];
    
    printf("RLE Compression Tool\n");
    printf("--------------------\n");
    printf("1. Compress file\n");
    printf("2. Decompress file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter input filename: ");
            scanf("%s", inputFile);
            printf("Enter output filename: ");
            scanf("%s", outputFile);
            compressFile(inputFile, outputFile);
            printf("File compressed successfully!\n");
            break;

        case 2:
            printf("Enter input filename: ");
            scanf("%s", inputFile);
            printf("Enter output filename: ");
            scanf("%s", outputFile);
            decompressFile(inputFile, outputFile);
            printf("File decompressed successfully!\n");
            break;

        case 3:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
