#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
int romanToDecimal(char roman[]);                        // Converts Roman numeral string to decimal
void decimalToWords(int number, char words[]);           // Converts decimal number to words
int performOperation(int num1, int num2, char operator); // Performs arithmetic operations
int isRomanCharValid(char c);                            // Validates if character is a Roman numeral
int isOperatorValid(char c);                             // Validates if character is a valid arithmetic operator

// Main function
int main()
{
    FILE *inputFile, *outputFile;
    char line[100];

    // Open input and output files
    inputFile = fopen("Input.txt", "r");
    outputFile = fopen("Output.txt", "w");

    // Check if files were opened successfully
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    // Process each line in the input file
    while (fgets(line, sizeof(line), inputFile))
    {
        char roman1[50] = "", roman2[50] = "";
        char operator;
        int index = 0, decimal1, decimal2, result;
        char resultWords[200] = "";

        // Parse the first Roman numeral
        while (isRomanCharValid(line[index]))
        {
            strncat(roman1, &line[index], 1);
            index++;
        }

        // Skip spaces and capture the operator
        while (line[index] == ' ')
        {
            index++;
        }
        operator= line[index++];

        // Skip spaces and parse the second Roman numeral
        while (line[index] == ' ')
        {
            index++;
        }
        while (isRomanCharValid(line[index]))
        {
            strncat(roman2, &line[index], 1);
            index++;
        }

        // Convert Roman numerals to decimals
        decimal1 = romanToDecimal(roman1);
        decimal2 = romanToDecimal(roman2);

        // Perform the operation
        result = performOperation(decimal1, decimal2, operator);

        // Convert result to words
        decimalToWords(result, resultWords);

        // Write the result to the output file
        fprintf(outputFile, "%s\n", resultWords);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion complete. Check Output.txt for results.\n");
    return 0;
}

// Converts a Roman numeral string to its decimal equivalent
int romanToDecimal(char roman[])
{
    int total = 0;
    int prevValue = 0;

    for (int i = strlen(roman) - 1; i >= 0; i--)
    {
        int currentValue;

        switch (toupper(roman[i]))
        {
        case 'I':
            currentValue = 1;
            break;
        case 'V':
            currentValue = 5;
            break;
        case 'X':
            currentValue = 10;
            break;
        case 'L':
            currentValue = 50;
            break;
        case 'C':
            currentValue = 100;
            break;
        case 'D':
            currentValue = 500;
            break;
        case 'M':
            currentValue = 1000;
            break;
        default:
            return -1; // Invalid character
        }

        // Apply subtractive rule if necessary
        if (currentValue < prevValue)
        {
            total -= currentValue;
        }
        else
        {
            total += currentValue;
        }

        prevValue = currentValue;
    }

    return total;
}

// Converts a decimal number to its word equivalent
void decimalToWords(int number, char words[])
{
    // Arrays for number words
    char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    char *thousands[] = {"", "Thousand", "Million", "Billion"};

    if (number == 0)
    {
        strcpy(words, "Zero");
        return;
    }

    int part[4] = {0}; // Holds number parts (up to billions)
    int i = 0;

    while (number > 0)
    {
        part[i++] = number % 1000;
        number /= 1000;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        if (part[j] == 0)
            continue;

        int hundreds = part[j] / 100;
        int remainder = part[j] % 100;

        if (hundreds > 0)
        {
            strcat(words, units[hundreds]);
            strcat(words, " Hundred ");
        }

        if (remainder >= 10 && remainder < 20)
        {
            strcat(words, teens[remainder - 10]);
        }
        else
        {
            strcat(words, tens[remainder / 10]);
            if (remainder % 10 > 0)
            {
                strcat(words, " ");
                strcat(words, units[remainder % 10]);
            }
        }

        strcat(words, " ");
        strcat(words, thousands[j]);
        strcat(words, " ");
    }
}

// Performs arithmetic operation between two decimal numbers
int performOperation(int num1, int num2, char operator)
{
    switch (operator)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num2 != 0 ? num1 / num2 : 0; // Handle division by zero
    default:
        return 0;
    }
}

// Validates if a character is a valid Roman numeral
int isRomanCharValid(char c)
{
    c = toupper(c);
    return c == 'I' || c == 'V' || c == 'X' || c == 'L' || c == 'C' || c == 'D' || c == 'M';
}

// Validates if a character is a valid arithmetic operator
int isOperatorValid(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}
