#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a large maximum size for potential input data
#define MAX_SIZE 100000000

// Function to find the minimum of two integers
unsigned long long Minim(unsigned long long  a, unsigned long long b)
{
    return (a < b) ? a : b;
}

// Function to compute the minimum number of operations needed to transform the code fragment by the rule
unsigned long long  NrMinimOperatii(char *regula, char *fragment_cod, unsigned long long  **dp, unsigned long long  n, unsigned long long  m)
{
    // Initialize the dp array for base cases
    for (unsigned long long  i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (unsigned long long  j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }

    // Fill the dp array based on the operations: insertion, deletion, and substitution
    for (unsigned long long  i = 1; i <= n; i++)
    {
        for (unsigned long long  j = 1; j <= m; j++)
        {
              // Check if the current characters in regula and fragment_cod are the same
            if (regula[i-1] == fragment_cod[j-1])
            {
            // If the characters are the same, no operation is needed
            // Thus, the cost remains the same as it was for the previous characters
            dp[i][j] = dp[i-1][j-1];
            }
            else
            {
            // If the characters are different, we need to consider the cost of three possible operations:

           // 1. Cost of Insertion:
           // Adding a character to regula to match fragment_cod.
           // This means we take the cost of transforming the first i characters of regula
           // to the first j-1 characters of fragment_cod (dp[i][j-1]),
           // and add 1 to account for the insertion operation.
              unsigned long long cost_inserare = dp[i][j-1] + 1;

           // 2. Cost of Deletion:
           // Removing a character from regula to match fragment_cod.
           // This means we take the cost of transforming the first i-1 characters of regula
           // to the first j characters of fragment_cod (dp[i-1][j]),
          // and add 1 to account for the deletion operation.
              unsigned long long cost_stergere = dp[i-1][j] + 1;

           // 3. Cost of Substitution:
           // Replacing a character in regula to match fragment_cod.
          // This means we take the cost of transforming the first i-1 characters of regula
          // to the first j-1 characters of fragment_cod (dp[i-1][j-1]),
          // and add 1 to account for the substitution operation.
             unsigned long long cost_inlocuire = dp[i-1][j-1] + 1;

          // Find the minimum cost among insertion, deletion, and substitution.
          // This gives us the minimum number of operations needed to convert the first i characters of regula
          // to the first j characters of fragment_cod.
             dp[i][j] = Minim(Minim(cost_inserare, cost_stergere), cost_inlocuire);
            }

        }
    }
    return dp[n][m];
}

// Function to display the menu, using ANSI color code
void displayMenu()
{
    printf("                                  \033[1;33mMenu:\033[0m\n");
    printf("                       \033[1;36m1. Generate Random Data\033[0m\n");
    printf("                       \033[1;36m2. Print Results\033[0m\n");
    printf("                       \033[1;36m3. Open GitHub Repository\033[0m\n");
    printf("                       \033[1;36m4. Exit\033[0m\n");
}

// Function to generate random data and write to code_editor_in.txt
void generateRandomData()
{
    FILE *inputFile = fopen("code_editor_in.txt", "w");
    if (inputFile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    unsigned long long  numTestCases, maxValueRange;
    printf("Enter the number of test cases: ");
    scanf("%llu", &numTestCases);
    printf("Enter the maximum value range for random data: ");
    scanf("%llu", &maxValueRange);
    getchar();  // Consume the newline character

    fprintf(inputFile, "%llu\n", numTestCases);

    srand(time(0));

    for (unsigned long long  t = 0; t < numTestCases; t++)
    {
        unsigned long long  codeLength = rand() % maxValueRange + 1;
        unsigned long long  ruleLength = rand() % maxValueRange + 1;

        fprintf(inputFile, "%llu %llu\n", codeLength, ruleLength);

        for (unsigned long long  i = 0; i < codeLength; i++)
        {
            char randomChar = 'a' + rand() % 26; // Random character a-z
            fputc(randomChar, inputFile);
        }
        fputc('\n', inputFile);

        for (unsigned long long  i = 0; i < ruleLength; i++)
        {
            char randomChar = 'a' + rand() % 26; // Random character a-z
            fputc(randomChar, inputFile);
        }
        fputc('\n', inputFile);
    }

    fclose(inputFile);
    printf("\n");
    printf("\033[1;32mRandom data generated in code_editor_in.txt\033[0m\n");
    printf("\n\n");
}

// Function to read data from code_editor_in.txt, compute results, and write to code_editor_out.txt
void printResults()
{
    FILE *inputFile = fopen("code_editor_in.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("code_editor_out.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    int numTestCases;
    fscanf(inputFile, "%llu", &numTestCases);

    char *intrare = (char *)malloc(MAX_SIZE * sizeof(char));
    char *regula = (char *)malloc(MAX_SIZE * sizeof(char));

    for (unsigned long long  t = 0; t < numTestCases; t++)
    {
        unsigned long long  codeLength, ruleLength;
        fscanf(inputFile, "%llu %llu", &codeLength, &ruleLength);

        fscanf(inputFile, "%s", intrare);
        fscanf(inputFile, "%s", regula);

        int **dp = (unsigned long long  **)malloc((ruleLength + 1) * sizeof(unsigned long long  *));
        for (unsigned long long  i = 0; i <= ruleLength; i++)
        {
            dp[i] = (unsigned long long  *)malloc((codeLength + 1) * sizeof(unsigned long long ));
        }

        clock_t start, end;
        double cpu_time_used;

        start = clock();
        unsigned long long  distanta = NrMinimOperatii(regula, intrare, dp, ruleLength, codeLength);
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(outputFile, "Test case %llu:\n", t + 1);
        fprintf(outputFile, "Numarul minim de operatii necesare: %llu\n", distanta);
        fprintf(outputFile, "Time Complexity: %f\n", cpu_time_used);

        printf("\n\n");
        printf("\033[1;34mTest case %llu:\nNumarul minim de operatii necesare: %llu\033[0m\n", t + 1, distanta);
        printf("\033[1;34mTime Complexity: %f\033[0m\n", cpu_time_used);

        for (unsigned long long  i = 0; i <= ruleLength; i++)
        {
            free(dp[i]);
        }
        free(dp);
    }

    free(intrare);
    free(regula);
    fclose(inputFile);
    fclose(outputFile);

    printf("\033[1;32mResults written to code_editor_out.txt\033[0m\n");
    printf("\n");
}

// Function to open the GitHub repository in the default web browser
void openGithubRepository()
{
    system("start https://github.com/peca-ana-ace-ucv/HOMEWORK_ASSIGNMENT_AD");  // For Windows
    //system("xdg-open https://github.com/example/repository");  // For Linux
    // system("open https://github.com/example/repository");  // For macOS
}

int main()
{
    int choice;

    while (1)
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%llu", &choice);
        getchar();  // To consume the newline character after entering the choice

        switch (choice)
        {
            case 1:
            {
                generateRandomData();
                break;
            }
            case 2:
            {
                printResults();
                break;
            }
            case 3:
            {
                openGithubRepository();
                break;
            }
            case 4:
            {
                printf("\033[1;32mExiting the program.\033[0m\n");
                exit(0);
            }
            default:
            {
                printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
                break;
            }
        }
    }

    return 0;
}
