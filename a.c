#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize)
{
    int max = 0;
    char **last = strs + strsSize - 1;
    for (int i = 1; i < strsSize; i++)
    {
        char *a = strs[i - 1];
        char *b = strs[i];
        while (*a == *b)
        {
            a++;
            b++;
        }
        if (i == 1)
        {
            max = b - *strs;
            if (max == 0)
                return "";
        }
        else
            max = max < b - strs[i] ? max : b - strs[i];
    }
    char *rv = (char *)malloc(max + 1);
    memset(rv, 0, max + 1);
    strncpy(rv, *last, max);
    return rv;
}

void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int j = i;
            int tmp = arr[j];
            //why j>=gap?
            //because j is decreased by gap
            while (j >= gap && arr[j - gap] > tmp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
    }
}

void insertSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        int tmp = arr[j];
        while (j >= 1 && arr[j - 1] > tmp)
        {
            arr[j] = arr[j - 1];
            j -= 1;
        }
        arr[j] = tmp;
    }
}

int removeDuplicates(int *nums, int numsSize)
{
    int *a = nums;
    int *b = a;
    while (b < nums + numsSize)
    {
        *a = *b;
        int *i = nums;
        for (; i < a; i++)
        {
            if (*i == *a)
                break;
        }
        if (i == a)
        {
            a++;
        }
        b++;
    }
    return a - nums;
}

int comp(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : 0;
}

void twoSum(int *nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), comp);
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    int *left = &nums[0];
    int *right = nums + numsSize - 1;
    while (left < right)
    {
        if (*left + *right == 0)
        {
            printf("[%d,%d] ", *left, *right);
            for (left++; left < right && *left == *(left - 1); left++)
                ;
        }
        else if (*left + *right > 0)
        {
            right--;
        }
        else
        {
            left++;
        }
    }
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), comp);
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    for (int i = 0; i < numsSize; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int *left = &nums[i] + 1;
        int *right = nums + numsSize - 1;
        while (left < right)
        {
            if (*left + *right + nums[i] == 0)
            {
                printf("[%d,%d,%d] ", nums[i], *left, *right);
                do
                {
                    left++;
                } while (*left == *(left - 1));
            }
            else if (*left + *right + nums[i] > 0)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
    return NULL;
}

void swap(int *x, int *y)
{
    int tmp = *y;
    *y = *x;
    *x = tmp;
}

void permute(int *nums, int left, int right)
{
    if (left == right)
    {
        printf("[");
        for (int *i = nums; i <= nums + right; i++)
        {
            printf("%d ", *i);
        }
        printf("]\n");
        return;
    }
    else
    {
        for (int i = left; i <= right; i++)
        {
            //will have changed nums
            swap(nums + left, nums + i);
            permute(nums, left + 1, right);
            //change back
            swap(nums + left, nums + i);
        }
    }
}

//[0][1][2][3][4]
//[0][1][2][3]
int searchInsert(int *nums, int numsSize, int target)
{
    int l = 0;
    int r = numsSize - 1;
    //why include ==?
    //because of l==r are find out the right pos
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] < target)
        {
            l = mid + 1;
        }
        else if (target < nums[mid])
        {
            r = mid - 1;
        }
        else
            return mid;
    }
    return l;
}

_Bool search(int *left, int *right, int target)
{
    if (left > right)
        return 0;

    int *mid = left + (right - left) / 2;
    if (target < *mid)
    {
        return search(left, mid - 1, target);
    }
    else if (*mid < target)
    {
        return search(mid + 1, right, target);
    }
    else
    {
        return 1;
    }
}

//why binary search haven't make use of mid instead of mid+/-1?
//because of in the last case [x][x+1], now, left=mid, if mid < target then left will no progress 
_Bool searchMatrix(int **matrix, int matrixSize, int matrixColSize, int target)
{
    int **top = matrix;
    int **bottom = matrix + matrixSize - 1;
    while (top <= bottom)
    {
        int **mid = top + (bottom - top) / 2;
        if (target < **mid)
        {
            bottom = mid - 1;
        }
        else if (*(*mid + matrixColSize - 1) < target)
        {
            top = mid + 1;
        }
        else
        {
            //printf("[%d,%d]\n", **mid, *(*mid + matrixColSize - 1));
            return search(*mid, *mid + matrixColSize - 1, target);
        }
    }
    //printf("not found\n");
    return 0;
}

int *searchRange(int *nums, int numsSize, int target)
{
    int l = 0;
    int r = numsSize - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (target < nums[mid])
            r = mid - 1;
        else if (nums[mid] < target)
            l = mid + 1;
        else
        {
            int *left = &nums[mid];
            int *right = left;
            while (left - 1 >= nums && *(left - 1) == target)
            {
                left--;
            }
            while (right + 1 <= nums + numsSize - 1 && *(right + 1) == target)
            {
                right++;
            }
            printf("[%ld,%ld]\n", left - nums, right - nums);
            return NULL;
        }
    }
    printf("[-1,-1]\n");
    return NULL;
}

int hammingWeight(unsigned int n)
{
    unsigned int b = 1;
    int counter = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((b & n) != 0)
            counter++;
        b <<= 1;
    }
    return counter;
}

int singleNumber(int *nums, int numsSize)
{
    int bundle = 0;
    for (int i = 0; i < numsSize; i++)
    {
        bundle ^= nums[i];
    }
    return bundle;
}

char *addBinary(char *a, char *b)
{
    char *ra = a + strlen(a) - 1;
    char *rb = b + strlen(b) - 1;
    unsigned int ia = 0;
    unsigned int ib = 0;
    for (char *i = a; i <= ra; i++)
    {
        if (*i == '1')
            ia |= 1 << (ra - i);
    }
    for (char *i = b; i <= rb; i++)
    {
        if (*i == '1')
            ib |= 1 << (rb - i);
    }

#define BITS 8
    char *rv = (char *)malloc(BITS);
    memset(rv, 0, BITS);

    unsigned int flag = 1;
    for (int i = BITS - 1; i >= 0; i--, flag <<= 1)
    {
        if ((flag & (ia + ib)) > 0)
        {
            rv[i] = '1';
        }
        else
            rv[i] = '0';
    }
    return rv;
}

unsigned int reverseBits(unsigned int n)
{
    unsigned int flag = 1;
    unsigned int reverse = 0;
    for (int i = 0; i < 32; i++, flag <<= 1)
    {
        if ((n & flag) > 0)
        {
            reverse |= 1 << (31 - i);
        }
    }
    return reverse;
}

int majorityElement(int *nums, int numsSize)
{
    //shellsort
    for (int gap = numsSize / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < numsSize; i++)
        {
            int j = i;
            int tmp = nums[j];
            while (j >= gap && nums[j - gap] > tmp)
            {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = tmp;
        }
    }

    return nums[numsSize / 2];
}

int removeElement(int *nums, int numsSize, int val)
{
    int *q = nums;
    int *p = nums;
    while (p < nums + numsSize)
    {
        if (*p == val)
        {

        }
        else
        {
            *q++ = *p;
        }
        p++;
    }
    return q - nums;
}

void rotate(int *nums, int numsSize, int k)
{
    for (int i = 0; i < k; i++)
    {
        int pre = nums[numsSize - 1];
        for (int j = 0; j < numsSize; j++)
        {
            int tmp = nums[j];
            nums[j] = pre;
            pre = tmp;
        }
    }
}

int lengthOfLastWord(char *s)
{
    int size = strlen(s);
    char *a = s + size - 1;
    while (a >= s && *a == ' ')
    {
        a--;
    }
    char *b = a;
    while (a >= s && *a != ' ')
    {
        a--;
    }
    return b - a;
}

void reverse_chars(char *a, char *b)
{
    while (a < b)
    {
        char tmp = *a;
        *a = *b;
        *b = tmp;
        a++;
        b--;
    }
}

//1. build up slip window, left and i
//2. carry is sperate of slip window
//3. if we use i and i-1, it would lead the last word or range words loss process in loop
//
//why chars[write++] = chars[i]?
//[0][1]......[write][x][x][x][x][x][l]....[i][i+1].....[size-1]
//                                   a......a   b?......
//l and i are determine the slip window, [write] is compose position
int compress(char *chars, int charsSize)
{
    int left = 0;
    int write = 0;
    for (int i = 0; i < charsSize; i++)
    {
        //i==charSize-1 is used for the last word or range
        if (i == charsSize - 1 || chars[i] != chars[i + 1])
        {
            chars[write++] = chars[i];
            int nums = i - left + 1;
            if (nums > 1)
            {
                int start_position = write;
                while (nums > 0)
                {
                    chars[write++] = nums % 10 + '0';
                    nums /= 10;
                }
                reverse_chars(&chars[start_position], &chars[write - 1]);
            }
            left = i + 1;
        }
    }
    return write;
}

char *reverseWords(char *s)
{
    char *l = s;
    char *r = s + strlen(s) - 1;
    reverse_chars(l, r);
    r = s;
    l = s;
    char *r_bound = s + strlen(s);
    while (l < r_bound)
    {
        while (*l == ' ')
        {
            l++;
        }
        r = l;
        while (*r != ' ' && r < r_bound)
        {
            r++;
        }
        char *bound = r - 1;
        reverse_chars(l, bound);
        l = r;
    }

    l = s;
    r = r_bound;
    while (*l == ' ')
    {
        l++;
    }
    while (*r == ' ' || *r == '\0')
    {
        r--;
    }

    char *p = s;
    while (l <= r)
    {
        *p++ = *l++;
    }
    *(p + 1) = '\0';

    return s;
}

//compress
int compressDuplicates_sort(char *chars, int charsSize)
{
    int l = 0;
    int r = l + 1;
    int writer = l + 1;
    while (r < charsSize)
    {
        while (chars[l] == chars[r])
        {
            r++;
        }
        if (r - l > 1)
        {
            int a = writer;
            for (int nums = r - l; nums > 0; nums /= 10)
            {
                chars[writer++] = '0' + nums % 10;
            }
            int b = writer - 1;
            reverse_chars(&chars[a], &chars[b]);
        }
        chars[writer++] = chars[r];
        l = r++;
    }
    return writer;
}

int main(int argc, char *argv[])
{
    int nums[] = {0, -3, 0, -1, 1, 0, -1, 2, 1, -1, -4, 4, 1, 1, 1, 0, 2, -2, 3, -2, 4, 2};
    printf("threeSum:");
    threeSum(nums, sizeof(nums) / sizeof(int), NULL, NULL);
    printf("\n");

    int nums1[] = {0, -3, 0, -1, 1, 0, -1, 2, 1, -1, -4, 4, 1, 1, 9, 1, 0, 2, -2, 3, -2, 4, 2, -5};
    printf("twoSum:");
    twoSum(nums1, sizeof(nums1) / sizeof(int));
    printf("\n");

    shellSort(nums, sizeof(nums) / sizeof(int));
    for (int i = 0; i < sizeof(nums) / sizeof(int); i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    printf("permute:\n");
    int nums2[] = {1, 2, 3};
    permute(nums2, 0, 2);

    int nums3[5] = {0, 2, 5, 6};
    printf("index:%d\n", searchInsert(nums3, 4, 1));

    int a1[] = {1, 3, 5, 7};
    int a2[] = {10, 11, 16, 20};
    int a3[] = {23, 30, 34, 40};
    int a4[] = {41, 42, 45, 48};
    int a5[] = {50, 55, 56, 59};
    int a6[] = {63, 64, 70, 71};
    int a7[] = {72, 79, 81, 88};
    int a8[] = {92, 95, 100, 112};
    int *a[] = {a1, a2, a3, a3, a4, a5, a6, a7, a8};
    for (int i = 0; i < 20; i++)
    {
        if (searchMatrix(a, sizeof(a) / sizeof(int *), sizeof(a1) / sizeof(int), i))
            printf("searchMatrix %d\n", i);
    }

    int range[] = {3, 4, 5, 7, 7, 7, 7, 10};
    searchRange(range, sizeof(range) / sizeof(int), 5);
    searchRange(range, sizeof(range) / sizeof(int), 7);

    printf("hammingWeight:%d\n", hammingWeight(432));

    int sing[] = {1, 2, 2, 1, 4};
    printf("singleNumber:%d\n", singleNumber(sing, sizeof(sing) / sizeof(int)));

    printf("add:%s\n", addBinary("1010", "0011"));

    int is[] = {4, -1, -10, 0, 9, 4, 23, 1, 9, -5, 3};
    insertSort(is, sizeof(is) / sizeof(int));
    for (int i = 0; i < sizeof(is) / sizeof(int); i++)
    {
        printf("%d ", is[i]);
    }
    printf("\n");

    char *flower = "flower";
    char *flow = "flow";
    char *flight = "flight";
    char *strs[] = {flower, flow, flight};
    printf("longestCommonPrefix:%s\n", longestCommonPrefix(strs, sizeof(strs) / sizeof(char *)));

    printf("reverseBits:%u\n", reverseBits(234));

    int major[] = {2, 21, 2, 2, 2, 1, 2, 4, 2, 2, 0, 6, 7, 2, 4, 2, 2, 2, 1, 2, 2, 4, 2, 5, 2, 12, 18, 2, 14, 2, 9, 2, 11, 2, 1, 0};
    printf("majorityElement:%d\n", majorityElement(major, sizeof(major) / sizeof(int)));

    int len = removeElement(major, sizeof(major) / sizeof(int), 2);
    len = removeElement(major, len, 1);
    len = removeElement(major, len, 0);
    len = removeElement(major, len, 4);
    printf("after removeElement:");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", major[i]);
    }
    printf("\n");

    //a1[] = {1, 3, 5, 7};
    rotate(a1, sizeof(a1) / sizeof(int), 3);
    for (int i = 0; i < sizeof(a1) / sizeof(int); i++)
    {
        printf("%d ", a1[i]);
    }
    printf("\n");

    char www[] = "   fly me   to   the 444fmoon   aoaaaabc  ?????";
    printf("lengthOfLastWord:%d\n", lengthOfLastWord(www));

    len = compress(www, sizeof(www) / sizeof(char));
    printf("len:%d\n", len);
    char *buf = (char *)malloc(len + 1);
    memset(buf, 0, len + 1);
    snprintf(buf, len, "%s", www);
    printf("%s\n", buf);

    char words[] = "  the sky is blue ";
    printf("before:|%s|\n", words);
    printf("reverseWords:|%s|\n", reverseWords(words));

    char dup_sort[][64] = {"aaaaabbbbbccccdefghhhhh", "ijklmnopq",
                           "123456aaabbbbddddd", "aaabbbbaaaapjkaaa   dfgwwww",
                           "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                           "aaaaaaaaaaaaaaaabbbbbbbbbbbbbbaa    wwww"};
    for (int i = 0; i < sizeof(dup_sort) / sizeof(char[64]); i++)
    {
        printf("origin:%s\n", dup_sort[i]);
        len = compressDuplicates_sort(dup_sort[i], strlen(dup_sort[i]));
        printf("compress:");
        for (int j = 0; j < len; j++)
        {
            printf("%c", dup_sort[i][j]);
        }
        printf("\n");
    }

    return 0;
}
