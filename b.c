#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef _Bool bool;
#define true 1
#define false 0

int lengthOfLongestSubstring(char *s)
{
    int max = 0;
    char *p = s;
    char *q = p + 1;
    while (*q != '\0')
    {
        for (char *i = p; i < q; i++)
        {
            if (*i != *q)
            {
                continue;
            }
            else
            {
                max = max > q - p ? max : q - p;
                //why i+1?
                //becase we stop at i, if set p at i
                //it would stuck at i when invoke for
                p = i + 1;
                break;
            }
        }
        q++;
    }
    return max = max > q - p ? max : q - p;
}

int minSubArrayLen(int target, int *nums, int numsSize)
{
    int *p = nums, *q = nums + 1;
    int minLen = 0;
    int sum = *p + *q;
    while (q < nums + numsSize)
    {
        if (sum >= target)
        {
            if (minLen == 0 || minLen > q - p + 1)
            {
                minLen = q - p + 1;
            }
            sum -= *p++;
        }
        else
        {
            sum += *(++q);
        }
    }
    return minLen;
}

int removeDuplicates(int *nums, int numsSize)
{
    int *p = nums + 1;
    int *q = p;
    while (q < nums + numsSize)
    {
        *p = *q;
        int same = 0;
        for (int *i = nums; i < p; i++)
        {
            if (*i == *p)
            {
                same = 1;
                break;
            }
        }
        if (same == 0)
        {
            p++;
        }
        q++;
    }
    return p - nums;
}

void rotate(int *nums, int numsSize, int k)
{
    int tmp = nums[0];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < numsSize; j++)
        {
            int n = nums[j];
            nums[j] = tmp;
            tmp = n;
        }
        nums[0] = tmp;
    }
}

char **summaryRanges(int *nums, int numsSize, int *returnSize)
{
    int *q = nums;
    while (q < nums + numsSize)
    {
        int *left = q;
        q++;
        while (q < nums + numsSize && *q - *(q - 1) == 1)
        {
            q++;
        }
        int *right = q - 1;
        if (*left == *right)
            printf("[%d]\n", *left);
        else
            printf("[%d->%d]\n", *left, *right);
    }
    return NULL;
}

int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
    int len = numsSize / sizeof(int);

    int *L = (int *)malloc(numsSize);
    L[0] = 1;
    for (int i = 1; i < len; i++)
    {
        L[i] = L[i - 1] * nums[i - 1];
    }

    int *R = (int *)malloc(numsSize);
    R[len - 1] = 1;
    for (int i = len - 2; i >= 0; i--)
    {
        R[i] = R[i+1] * nums[i+1];
    }

    int *answer = (int *)malloc(numsSize);
    for (int i = 0; i < len; i++)
    {
        answer[i] = L[i] * R[i];
    }

    *returnSize = numsSize;

    return answer;
}

int lengthOfLastWord(char *s)
{
    int len = strlen(s);
    char *p = s + len;
    while (*p != ' ')
    {
        p--;
    }
    return len + s - 1 - p;
}

char *longestCommonPrefix(char **strs, int strsSize)
{
    char *a = strs[0];
    char *b = strs[1];
    int len = 0;
    for (int i = 1; i < strsSize;)
    {
        int n = 0;
        while ((*a != '\0' && *b != '\0') && *a == *b)
        {
            n++;
            a++;
            b++;
        }

        if (n == 0)
        {
            return "";
        }
        else
        {
            if (len == 0 || n < len)
            {
                len = n;
            }
        }
        a = strs[i];
        b = strs[++i];
    }

    char *prefix = (char *)malloc(len);
    strncpy(prefix, strs[0], len);
    return prefix;
}

bool isSubsequence(char *s, char *t)
{
    if (s == NULL || t == NULL)
        return false;

    while (*s != '\0' && *t != '\0')
    {
        if (*s == *t)
        {
            s++;
        }
        t++;
    }
    return *s == '\0' ? true : false;
}

bool isPalindrome(char *s)
{
    char *p = s, *q = s;
    while (*q != '\0')
    {
        if (('0' <= *q && *q <= '9') || ('A' <= *q && *q <= 'Z') || ('a' <= *q && *q <= 'z'))
        {
            *p++ = *q;
        }
        q++;
    }
    memset(p, 0, q - p);

    char *left = s, *right = p - 1;
    while (left < right)
    {
        if (*left == *right)
        {
            left++;
            right--;
        }
        else
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    int nums[] = {2, 3, 1, 2, 4, 3};
    printf("%d\n", minSubArrayLen(9, nums, sizeof(nums) / sizeof(int)));

    char s[] = "abcebedfjkl";
    printf("lengthOfLongestSubstring:%d\n", lengthOfLongestSubstring(s));

    int dup[] = {5, 1, 2, 4, 3, 4, 3, 5};
    printf("%d\n", removeDuplicates(dup, sizeof(dup) / sizeof(int)));

    int r[] = {1, 2, 3, 4, 5};
    rotate(r, sizeof(r) / sizeof(int), 3);
    for (int i = 0; i < sizeof(r) / sizeof(int); i++)
    {
        printf("%d ", r[i]);
    }
    printf("\n");

    int summary[] = {0, 2, 3, 4, 6, 8, 9};
    summaryRanges(summary, sizeof(summary) / sizeof(int), NULL);

    int returnSize = 0;
    int *rv = productExceptSelf(nums, sizeof(nums), &returnSize);
    int len = returnSize / sizeof(int);
    for (int *i = rv; i < rv + len; i++)
    {
        printf("%d ", *i);
    }
    printf("\n");

    char w[] = "Hello World";
    printf("lengthOfLastWord:%d\n", lengthOfLastWord(w));

    char *a = "Helabc";
    char *b = "Hell ddddd";
    char *strs[] = {a, b, w};
    printf("longestCommonPrefix:%s\n", longestCommonPrefix(strs, sizeof(strs) / sizeof(char *)));

    printf("isSubsequence:%d\n", isSubsequence("acb", "bbaaacccb"));
    printf("isSubsequence:%d\n", isSubsequence("bcc", "bbaaacccb"));
    printf("isSubsequence:%d\n", isSubsequence("bcd", "bbaaacccb"));

    char p0[] = "aaabb<ba?aca$";
    printf("isPalindrome:%d\n", isPalindrome(p0));
    char p1[] = "abbczcbba";
    printf("isPalindrome:%d\n", isPalindrome(p1));

    return 0;
}
