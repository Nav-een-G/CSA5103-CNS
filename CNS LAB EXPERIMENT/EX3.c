#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[])
{
    int used[26] = {0};
    int row = 0, col = 0;
    int i;
    char ch;

    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }
}

void displayMatrix()
{
    int i, j;

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepareText(char input[], char output[])
{
    int i = 0, k = 0;
    char a, b;

    while (input[i] != '\0')
    {
        if (!isalpha(input[i]))
        {
            i++;
            continue;
        }

        a = toupper(input[i]);

        if (a == 'J')
            a = 'I';

        if (input[i + 1] != '\0')
        {
            int next = i + 1;

            while (input[next] != '\0' && !isalpha(input[next]))
                next++;

            if (input[next] != '\0')
            {
                b = toupper(input[next]);

                if (b == 'J')
                    b = 'I';

                if (a == b)
                {
                    output[k++] = a;
                    output[k++] = 'X';
                    i++;
                }
                else
                {
                    output[k++] = a;
                    output[k++] = b;
                    i = next + 1;
                }
            }
            else
            {
                output[k++] = a;
                output[k++] = 'X';
                i++;
            }
        }
        else
        {
            output[k++] = a;
            output[k++] = 'X';
            i++;
        }
    }

    output[k] = '\0';
}

void processPair(char a, char b, int encrypt, char *x, char *y)
{
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2)
    {
        if (encrypt)
        {
            *x = matrix[r1][(c1 + 1) % 5];
            *y = matrix[r2][(c2 + 1) % 5];
        }
        else
        {
            *x = matrix[r1][(c1 + 4) % 5];
            *y = matrix[r2][(c2 + 4) % 5];
        }
    }
    else if (c1 == c2)
    {
        if (encrypt)
        {
            *x = matrix[(r1 + 1) % 5][c1];
            *y = matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            *x = matrix[(r1 + 4) % 5][c1];
            *y = matrix[(r2 + 4) % 5][c2];
        }
    }
    else
    {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

void encrypt(char prepared[], char result[])
{
    int i, k = 0;

    for (i = 0; prepared[i] != '\0'; i += 2)
    {
        processPair(prepared[i], prepared[i + 1], 1,
                    &result[k], &result[k + 1]);

        k += 2;
    }

    result[k] = '\0';
}

void decrypt(char cipher[], char result[])
{
    int i, k = 0;

    for (i = 0; cipher[i] != '\0'; i += 2)
    {
        processPair(cipher[i], cipher[i + 1], 0,
                    &result[k], &result[k + 1]);

        k += 2;
    }

    result[k] = '\0';
}

int main()
{
    char key[100];
    char plaintext[500];
    char prepared[1000];
    char result[1000];
    int choice;

    printf("===== PLAYFAIR CIPHER =====\n");

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);

    createMatrix(key);
    displayMatrix();

    printf("\n1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    getchar();

    if (choice == 1)
    {
        printf("\nEnter plaintext: ");
        fgets(plaintext, sizeof(plaintext), stdin);

        prepareText(plaintext, prepared);

        encrypt(prepared, result);

        printf("\nPrepared plaintext: %s\n", prepared);
        printf("Encrypted text: %s\n", result);
    }
    else if (choice == 2)
    {
        printf("\nEnter ciphertext: ");
        fgets(plaintext, sizeof(plaintext), stdin);

        int i, k = 0;

        for (i = 0; plaintext[i] != '\0'; i++)
        {
            if (isalpha(plaintext[i]))
            {
                result[k++] = toupper(plaintext[i]);
            }
        }

        result[k] = '\0';

        if (k % 2 != 0)
        {
            printf("Ciphertext must contain an even number of letters.\n");
            return 0;
        }

        decrypt(result, prepared);

        printf("\nDecrypted text: %s\n", prepared);
        printf("Note: Extra X characters may need to be removed manually.\n");
    }
    else
    {
        printf("Invalid choice!\n");
    }

    return 0;
}