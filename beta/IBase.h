/**
 * Methods NOT tested yet!!!
 **/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct stringArray {
    /* A string array actually. */
    string_ptr val;
    int numOfElement;
};

typedef struct stringArray stringArray;

typedef char* char_ptr;
typedef char* string;
typedef char** char_ptr_ptr;
typedef char** string_ptr;


int MaxInt(int a, int b) 
{
    return (a > b ? a : b);
}

int MinInt(int a, int b) 
{
    return (a < b ? a : b);
}

int GetLengthOfInt(int value) 
{
    // 0 is considered to has zero bit.
    int result = 0;

    while (value) {
        result++;
        value /= 10;
    }
    return result;
}

string ConvertIntToString(int value) {
    int lengthOfValue = GetLengthOfInt(value);
    string result = (string)malloc(lengthOfValue + 1);
    int i = 0;

    for (i = lengthOfValue - 1; i >= 0; i--)
    {
        result[i] = value % 10 + '0';
        value /= 10;
    }
    result[lengthOfValue] = '\0';   /* To ensure that strlen can be normally used. */
    return result;
}

string AttachString(string str1, string str2) 
{
    int len1 = strlen(str1), len2 = strlen(str2);
    int lenOfResult = len1 + len2;
    int i = 0, j = 0;
    string result = (string)malloc(len1 + 1);

    for (i = 0; i < len1; i++)
    {
        result[j++] = str1[i];
    }

    for (i = 0; i < len2; i++) 
    {
        result[j++] = str2[i];
    }
    result[j] = '\0';
    return result;
}

int ConvertStringToInt(string str) 
{
    int len = strlen(str);
    int val = 0, f = 1, cur = 0;

    while (cur < len && (str[cur] < '0' || str[cur] > '9')) 
    {
        if (cur == '-') f = -1;
        cur++;
    }

    while (cur < len && str[cur] >= '0' && str[cur] <= '9') 
    {
        val = val * 10 + str[cur] - '0';
        cur++;
    }
    return (val * f);
}

stringArray SplitString(string str, char separator) 
{
    /* Multiple connected separators are considered as one. */
    int numOfWords = 1; /* number of splited words */
    int len = strlen(str);
    int check = 0;
    int i = 0, j = 0, l = 0, r = 0, cur = 0;
    stringArray result;

    /* Get num of words */
    while (i < len && str[i] == separator) i++;

    for (i; i < len; i++) {
        check = 0;
        while (i < len && str[i] == separator) 
        {
            check = 1;
            i++;
        }
        if (check) 
        {
            numOfWords++;
        }
    }

    result.val = (string_ptr)malloc(sizeof(numOfWords * sizeof(string)));

    /* Get words. l and r are used to mark the starting and end of the */
    while (l < len && str[l] == separator) l++;
    for (i = 0; i < numOfWords;) {
        r = l;
        while (r < len && str[r] != separator) r++;
        result.val[i] = (string)malloc(sizeof(char) * (r - l) + 1);

        cur = 0;

        while (l < r) result.val[i][cur++] = str[l++];
        result.val[i][cur] = '\0';

        while (l < len && str[i] == separator) l++;
        i++;
    }

    result.numOfElement = numOfWords;
    return result;
}

void ReadString(string str) {
    scanf("%s", str);
}
