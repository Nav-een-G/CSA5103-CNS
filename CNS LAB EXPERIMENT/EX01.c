#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int key)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';
        else if (islower(text[i]))
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';
    }
}

void decrypt(char text[], int key)
{
    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
            text[i] = ((text[i] - 'A' - key + 26) % 26) + 'A';
        else if (islower(text[i]))
            text[i] = ((text[i] - 'a' - key + 26) % 26) + 'a';
    }
}

int main()
{
    char text[500];
    int key, choice;

    printf("===== CAESAR CIPHER =====\n");

    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25)
    {
        printf("Invalid key! Key must be between 1 and 25.\n");
        return 0;
    }

    printf("\n1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        encrypt(text, key);
        printf("\nEncrypted message: %s", text);
    }
    else if (choice == 2)
    {
        decrypt(text, key);
        printf("\nDecrypted message: %s", text);
    }
    else
    {
        printf("Invalid choice!\n");
    }

    return 0;
}
