#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[])
{
    int i;
    int keyIndex = 0;
    int keyLength = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            int shift = toupper(key[keyIndex % keyLength]) - 'A';

            if (isupper(text[i]))
                text[i] = ((text[i] - 'A' + shift) % 26) + 'A';
            else
                text[i] = ((text[i] - 'a' + shift) % 26) + 'a';

            keyIndex++;
        }
    }
}

void decrypt(char text[], char key[])
{
    int i;
    int keyIndex = 0;
    int keyLength = strlen(key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            int shift = toupper(key[keyIndex % keyLength]) - 'A';

            if (isupper(text[i]))
                text[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';
            else
                text[i] = ((text[i] - 'a' - shift + 26) % 26) + 'a';

            keyIndex++;
        }
    }
}

int validKey(char key[])
{
    int i;

    if (strlen(key) == 0)
        return 0;

    for (i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha(key[i]))
            return 0;
    }

    return 1;
}

int main()
{
    char text[500];
    char key[100];
    int choice;

    printf("===== POLYALPHABETIC SUBSTITUTION CIPHER =====\n");
    printf("(Vigenere Cipher)\n");

    printf("\nEnter the message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key: ");
    scanf("%s", key);

    if (!validKey(key))
    {
        printf("Invalid key! Key must contain letters only.\n");
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
