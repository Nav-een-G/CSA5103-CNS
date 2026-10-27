#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidKey(char key[])
{
    int i, j;

    if (strlen(key) != 26)
        return 0;

    for (i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
            return 0;

        key[i] = toupper(key[i]);

        for (j = i + 1; j < 26; j++)
        {
            if (key[i] == toupper(key[j]))
                return 0;
        }
    }

    return 1;
}

void encrypt(char text[], char key[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
            text[i] = key[text[i] - 'A'];

        else if (islower(text[i]))
            text[i] = tolower(key[text[i] - 'a']);
    }
}

void decrypt(char text[], char key[])
{
    int i, j;
    char upperKey[27];

    for (i = 0; i < 26; i++)
        upperKey[i] = toupper(key[i]);

    upperKey[26] = '\0';

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
        {
            for (j = 0; j < 26; j++)
            {
                if (upperKey[j] == text[i])
                {
                    text[i] = 'A' + j;
                    break;
                }
            }
        }
        else if (islower(text[i]))
        {
            for (j = 0; j < 26; j++)
            {
                if (tolower(upperKey[j]) == text[i])
                {
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main()
{
    char text[500];
    char key[100];
    int choice;

    printf("===== MONOALPHABETIC SUBSTITUTION CIPHER =====\n");

    printf("Alphabet:\n");
    printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

    printf("\nEnter 26-letter substitution key:\n");
    scanf("%s", key);

    if (!isValidKey(key))
    {
        printf("Invalid key!\n");
        printf("The key must contain exactly 26 unique letters.\n");
        return 0;
    }

    getchar();

    printf("\nEnter the message: ");
    fgets(text, sizeof(text), stdin);

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
