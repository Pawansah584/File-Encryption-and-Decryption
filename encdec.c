#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 10000

// Function to apply ROT13 encryption/decryption to a string
char *applyROT13(char a[])
{
    size_t k = strlen(a);

    for (size_t j = 0; j < k; j++)
    {
        // Check if the character is a lowercase letter
        if ((a[j] >= 'a' && a[j] <= 'z'))
        {
            a[j] = ((a[j] - 'a' + 13) % 26) + 'a'; // Apply ROT13 to lowercase letters
        }
        // Check if the character is an uppercase letter
        else if ((a[j] >= 'A' && a[j] <= 'Z'))
        {
            a[j] = ((a[j] - 'A' + 13) % 26) + 'A'; // Apply ROT13 to uppercase letters
        }
        // Check if the character is a digit
        else if ((a[j] >= '0' && a[j] <= '9'))
        {
            a[j] = ((a[j] - '0' + 5) % 10) + '0'; // Apply ROT5 to digits
        }
    }
    return a;
}

// Function to clear the input buffer
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Function to read contents of a file into a string
int getFileContents(const char *filename, char *contents)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("\nFile not found!\n");
        return 0; // Return 0 to indicate failure
    }

    size_t j = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF && j < MAX_BUFFER_SIZE - 1)
    {
        contents[j++] = (char)ch;
    }
    fclose(file);
    contents[j] = '\0';

    return 1; // Return 1 to indicate success
}

// Function to handle incorrect filename and user choice
void handleIncorrectFilename(const char *filename)
{
    int tryAgain;
    printf("\nFile '%s' not found. Do you want to try again? (1 for yes, 0 for no): ", filename);
    scanf("%d", &tryAgain);
    clearInputBuffer();

    if (tryAgain)
    {
        printf("\nEnter new Filename: ");
    }
    else
    {
        printf("\nGoodbye and have a good day!\n");
        exit(0);
    }
}

// Function to encrypt a file using ROT13
void encryptFile()
{
    char filename[100]; // Increased the size to accommodate user input
    printf("\nEnter Filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

    char a[MAX_BUFFER_SIZE];

    if (!getFileContents(filename, a))
    {
        handleIncorrectFilename(filename);
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

        if (!getFileContents(filename, a))
        {
            handleIncorrectFilename(filename);
            return;
        }
    }
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s\n", applyROT13(a));
    fclose(file);
    printf("\nSuccessfully encrypted using ROT13.\n");
}

// Function to decrypt a file using ROT13
void decryptFile()
{
    char filename[100]; // Increased the size to accommodate user input
    printf("\nEnter Filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present
    char a[MAX_BUFFER_SIZE];

    if (!getFileContents(filename, a))
    {
        handleIncorrectFilename(filename);
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Remove newline character if present

        if (!getFileContents(filename, a))
        {
            handleIncorrectFilename(filename);
            return;
        }
    }
    int writeToFile;
    printf("\nDo you want to write the decrypted text to a different file? (1 for yes, 0 for no): ");
    scanf("%d", &writeToFile);
    clearInputBuffer();
    FILE *file;
    if (writeToFile)
    {
        printf("\nEnter new Filename: ");
        char newFilename[100]; // Increased the size to accommodate user input
        fgets(newFilename, sizeof(newFilename), stdin);
        newFilename[strcspn(newFilename, "\n")] = '\0'; // Remove newline character if present

        file = fopen(newFilename, "wb");
        if (file == NULL)
        {
            printf("Error opening file for writing.\n");
            return;
        }

        fprintf(file, "%s\n", applyROT13(a));
        fclose(file);

        printf("\nSuccessfully decrypted and written to a new file: %s\n", newFilename);
    }
    else
    {
        file = fopen(filename, "wb");
        if (file == NULL)
        {
            printf("Error opening file for writing.\n");
            return;
        }

        fprintf(file, "%s\n", applyROT13(a));
        fclose(file);
        printf("\nSuccessfully decrypted.\n");
    }
}

int main()
{
    int choose;
    int tryAgain = 1;
    while (tryAgain)
    {
        printf("\nWelcome to the ROT13 encryption tool.\n\n");
        printf("  1. Encrypt\n");
        printf("  2. Decrypt\n");
        printf("\nEnter option: ");
        scanf("%d", &choose);
        clearInputBuffer();

        switch (choose)
        {
        case 1:
            encryptFile();
            break;
        case 2:
            decryptFile();
            break;
        default:
            printf("Error\n");
            break;
        }
        int tryAgainChoice;
        printf("\nDo you want to try the program again? (1 for yes, 0 for no): ");
        scanf("%d", &tryAgainChoice);
        clearInputBuffer();
        tryAgain = tryAgainChoice ? 1 : 0;
    }
    printf("\nGoodbye and have a good day!\n");
    return 0;
}
