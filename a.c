#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;

} TreeNode;

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

//https://www.naukri.com/code360/problems/insertion-sort_3155179
void insertSort(int arr[], int n)
{
	for (int i = 1; i < n; i++) {
		int j = i;
		int tmp = arr[j];
		while (j >= 1 && arr[j - 1] > tmp) {
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

// https://www.naukri.com/code360/problems/reverse-bits_2181102
long reverseBits1(long n)
{
    long result = 0;
    for (int i = 0; i < 32; i++)
    {
        long lsb = n & 1;
        result |= lsb << (31 - i);
        n = n >> 1;
    }
    return result;
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

int partition(int arr[], int l, int r)
{
    int pivot = r;
    int i = l - 1;
    for (int j = l; j <= r; j++)
    {
        if (arr[j] < arr[pivot])
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[pivot]);
    return i + 1;
}

void quickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int pi = partition(arr, l, r);
        quickSort(arr, l, pi - 1);
        quickSort(arr, pi + 1, r);
    }
}

//https://www.naukri.com/code360/problems/set-k-bits_972999
int setKBits(int n, int k)
{
    int set = 1;
    for (int i = 0; i < k; i++)
    {
        n |= set;
        set <<= 1;
    }
    return n;
}

//https://www.naukri.com/code360/problems/remove-character_624477
void removeAllOccurrencesOfChar(char input[], char c)
{
    int i = 0;
    for (int j = 0; j < strlen(input); j++)
    {
        if (input[j] == c)
        {
            continue;
        }
        input[i] = input[j];
        i++;
    }
    for (int j = i; j < strlen(input); j++)
    {
        input[i] = 0;
    }
}

// chatgpt4
int *lower_bound(int *first, int *last, int value)
{
    int n = last - first;
    while (n > 0)
    {
        int mid = n / 2;
        int *it = first + mid;
        if (*it < value)
        {
            first = it + 1;
            n -= mid + 1;
        }
        else
            n = mid;
    }
    return first;
}

// https://www.naukri.com/code360/problems/reset-in-range_972998
int resetAllBitsInRange(int n, int l, int r)
{
    int reset = 0;
    for (int i = r; i <= l; i++)
    {
        reset <<= 1;
        reset |= 1;
    }
    for (int i = 1; i < r; i++)
    {
        reset <<= 1;
    }
    return n & (~reset);
}

// https://www.naukri.com/code360/problems/find-unique_625159
int findUnique(int *arr, int size)
{
    int ans = 0;
    for (int i = 0; i < size; i++)
    {
        ans ^= arr[i];
    }
    return ans;
}

// https://www.naukri.com/code360/problems/number-of-balanced-binary-trees_1062690
// count nodes from height of avl
int countBalancedBinaryTree(int n)
{
    const int MOD = 1e9 + 7;
    long *dp = (long *)malloc(sizeof(int) * n);
    memset(dp, 0, sizeof(int) * n);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        int a = dp[i - 1] * dp[i - 1] % MOD;
        int b = 2 * dp[i - 1] * dp[i - 2] % MOD;
        dp[i] = (a + b) % MOD;
    }
    return dp[n];
}

// https://www.naukri.com/code360/problems/locked-binary-tree_4874663
int locking(int n, int k, int par[], int lock[])
{
    int index = k;
    while (index != -1 && lock[index] != 1)
    {
        index = par[index];
    }
    return index == -1 ? 1 : !lock[index];
}

#define U(X) (X##U)
#define GENMASK(h, l)                \
    (((~U(0)) - (U(1) << (l)) + 1) & \
     (~U(0) >> (32 - 1 - (h))))

static inline uint32_t
_reg_mask(uint32_t hi, uint32_t lo)
{
    uint32_t width = hi - lo + 1;
    return (width == 32) ? UINT32_C(~0) : ((1ul << width) - 1);
}

static inline uint32_t
_reg_get(uint32_t d, uint32_t hi, uint32_t lo)
{
    return (d >> lo) & _reg_mask(hi, lo);
}

// https://www.naukri.com/code360/problems/ninja-and-sorted-list_2663294
bool ninjaAndSortedList(int n, int val, int arr[])
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] > val)
        {
            if (arr[l] > val)
                l = mid + 1;
            else
                r = mid - 1;
        }
        else if (arr[mid] < val)
        {
            if (arr[l] < val && arr[l] > arr[mid])
                r = mid - 1;
            else
                l = mid + 1;
        }
        else
            return true;
    }
    return false;
}

// https://www.naukri.com/code360/problems/reset-all-bits_973004
int resetAllExceptMSB(int n)
{
    if (n == 0)
        return 0;
    unsigned int ans = (1 << 15);
    while ((ans & n) == 0)
    {
        ans >>= 1;
    }
    return ans;
}

// https://www.naukri.com/code360/problems/position-of-right-most-set-bit_893048
int getRightMostSetBit(int n)
{
    if (n == 0)
        return 0;
    int i = 1;
    int flag = 1;
    while ((flag & n) == 0)
    {
        i++;
        flag <<= 1;
    }
    return i;
}

// https://www.naukri.com/code360/problems/flip-given-bits_973114
int flipSomeBits(int num, int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        num ^= (1 << (arr[i] - 1));
    }
    return num;
}

// https://www.naukri.com/code360/problems/number-of-mismatching-bits_920394
int numberOfMismatchingBits(int first, int second)
{
    int mask = 1, count = 0;
    for (int i = 0; i < 32; i++)
    {
        int a = mask & first;
        int b = mask & second;
        if ((a ^ b) != 0)
        {
            count++;
        }
        mask <<= 1;
    }
    return count;
}

// https://www.naukri.com/code360/problems/count-set-bits_1112627
int countSetBits(int n)
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += __builtin_popcount(i);
    return ans;
}

// https://www.naukri.com/code360/problems/flip-bits_1063248
int flipBits(int *arr, int n)
{
    int count = 0, sum = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
        {
            arr[i] = -1;
            count++;
        }
        else
            arr[i] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        ans = MAX(ans, sum);
        if (sum < 0)
            sum = 0;
    }
    return ans + count;
}

// https://www.naukri.com/code360/problems/longest-switching-subarray_799356
int switchingSubarray(int arr[], int n)
{
    if (n == 0 || n == 1)
        return n;
    int cur = 2;
    int ans = 2;
    int even = arr[0];
    int odd = arr[1];
    for (int i = 2; i < n; i++)
    {
        if (i % 2 == 0)
        {
            if (arr[i] == even)
                cur++;
            else
            {
                cur = 2;
                even = arr[i];
            }
        }
        else
        {
            if (arr[i] == odd)
                cur++;
            else
            {
                cur = 2;
                odd = arr[i];
            }
        }
        ans = MAX(ans, cur);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/minimum-cost-path_4296
int minCostPath(int **input, int n, int m)
{
    int dp[n][m];
    dp[0][0] = input[0][0];

    for (int j = 1; j < m; j++)
    {
        dp[0][j] = dp[0][j - 1] + input[0][j];
    }

    for (int i = 1; i < n; i++)
    {
        dp[i][0] = dp[i - 1][0] + input[i][0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            int a = dp[i - 1][j];
            int b = dp[i][j - 1];
            int c = dp[i - 1][j - 1];
            if (a < b)
                b = a;
            if (b < c)
                c = b;
            dp[i][j] = input[i][j] + c;
        }
    }

    return dp[n - 1][m - 1];
}

// https://www.naukri.com/code360/problems/trapping-rainwater_630519
long long getTrappedWater(long long *arr, int n)
{
    long long leftMax[n];
    leftMax[0] = arr[0];

    long long rightMax[n];
    rightMax[n - 1] = arr[n - 1];

    for (int i = 1; i < n; i++)
        leftMax[i] = MAX(leftMax[i - 1], arr[i]);

    for (int i = n - 2; i >= 0; i--)
        rightMax[i] = MAX(rightMax[i + 1], arr[i]);

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        int height = MIN(leftMax[i], rightMax[i]);
        ans += height - arr[i];
    }

    return ans;
}

void reverse(char input[], int l, int r)
{
    while (l < r)
    {
        int temp = input[l];
        input[l] = input[r];
        input[r] = temp;
        l++;
        r--;
    }
}

// https://www.naukri.com/code360/problems/reverse-string-word-wise_624402
void reverseStringWordWise(char input[])
{
    int len = strlen(input);
    reverse(input, 0, len - 1);
    int l = 0, r = 0;
    while (r < len)
    {
        if (input[r] == ' ')
        {
            reverse(input, l, r - 1);
            l = r + 1;
        }
        r++;
    }
    reverse(input, l, r - 1);
}

// https://www.naukri.com/code360/problems/delete-alternate-nodes_624615
void deleteAlternateNodes(Node *head)
{
    while (head != NULL && head->next != NULL)
    {
        Node *n = head->next;
        head->next = n->next;
        head = head->next;
        n->next = NULL;
    }
}

// https://www.naukri.com/code360/problems/star-pattern_624933
void printStart(int N)
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < N - i; j++)
            printf(" ");
        for (int j = 0; j < 2 * i - 1; j++)
            printf("*");
        printf("\n");
    }
}

// https://www.naukri.com/code360/problems/give-me-triangle_893275
void ninjaPuzzle(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            printf(" ");
        for (int j = 0; j < n - i; j++)
            printf("*");
        printf("\n");
    }
}

// https://www.naukri.com/code360/problems/is-subsequence_892991
bool isSubSequence(char *str1, char *str2)
{
    int i = 0, j = 0;
    while (str2[j] != '\0')
    {
        if (str1[i] == str2[j])
            i++;
        j++;
    }
    return str1[i] == '\0' ? true : false;
}

// https://www.naukri.com/code360/problems/loot-houses_630510
int maxMoneyLooted(int houses[], int n)
{
    int dp[n];
    dp[0] = houses[0];
    dp[1] = MAX(houses[0], houses[1]);
    for (int i = 2; i < n; i++)
    {
        dp[i] = MAX(dp[i - 1], houses[i] + dp[i - 2]);
    }
    return dp[n - 1];
}

// https://www.naukri.com/code360/problems/highest-occurring-character_624400
char highestOccurringChar(char input[])
{
    char result = 0;
    long long highest = 0;
    long long freq[26] = {0};
    int n = strlen(input);
    for (int i = 0; i < n; i++)
    {
        freq[input[i] - 'a']++;
    }
    for (int i = 0; i < n; i++)
    {
        if (freq[input[i] - 'a'] > highest)
        {
            result = input[i];
            highest = freq[input[i] - 'a'];
        }
    }
    return result;
}

// https://www.naukri.com/code360/problems/check-permutation_624575
bool isPermutation(char input1[], char input2[])
{
    long long freq1[26] = {0};
    long long freq2[26] = {0};
    int n1 = strlen(input1);
    int n2 = strlen(input2);
    if (n1 != n2)
        return false;

    for (int i = 0; i < n1; i++)
        freq1[input1[i] - 'a']++;

    for (int i = 0; i < n2; i++)
        freq2[input2[i] - 'a']++;

    for (int i = 0; i < 26; i++)
        if (freq1[i] != freq2[i])
            return false;

    return true;
}

// https://www.naukri.com/code360/problems/binary-to-decimal_624649
int binary_to_decimal(int N)
{
    int n = 0, result = 0;
    while (N > 0)
    {
        int i = N % 10;
        result += i * pow(2, n);
        n++;
        N /= 10;
    }
    return result;
}

/*
 *https://www.naukri.com/code360/problems/convert-to-base-2_1462446
 *https://leetcode.com/problems/convert-to-base-2/
 *string baseNeg2(int n) {}
 */

// https://www.naukri.com/code360/problems/nth-node-from-end_920751
Node *nthNodeFromEnd(Node *head, int n)
{
    Node *q = head, *p = head;
    for (int i = 0; i < n - 1; i++)
        p = p->next;
    while (p->next != NULL)
    {
        q = q->next;
        p = p->next;
    }
    return q;
}

// https://www.naukri.com/code360/problems/move-zeros-to-left_1094877
void moveZerosToLeft(int *arr, int n)
{
    int w = n;
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] != 0)
        {
            w--;
            arr[w] = arr[i];
        }
        else if (arr[i] == 0)
            cnt++;
    }
    for (int i = 0; i < cnt; i++)
        arr[i] = 0;
}

// https://leetcode.com/problems/powx-n/
double myPow(double x, int n)
{
    if (n == 0)
        return 1.0;
    if (n == 1)
        return x;
    long long N = n;
    if (n < 0)
    {
        x = 1 / x;
        N = -N;
    }
    if (n % 2 == 0)
        return myPow(x * x, N / 2);
    else
        return myPow(x * x, N / 2) * x;
}

//https://leetcode.com/problems/reverse-integer/description/
//https://www.naukri.com/code360/problems/reverse-integer_1263846
int reverseInteger(int n)
{
	int ans = 0;
	while (n != 0) {
		int digit = n % 10;
		n = n / 10;
		if (ans > INT_MAX / 10 || ans < INT_MIN / 10)
			return -1;
		ans = ans * 10 + digit;
	}
	return ans;
}

void printBinary(int n)
{
	int size = sizeof(n) * 8;

	for (int i = size - 1; i >= 0; i--) {
		int bit = (n >> i) & 1;
		printf("%d", bit);
	}
	printf("\n");
}

// https://www.naukri.com/code360/problems/print-spiral_547
void spiralPrint(int nRows, int mCols, int input[][mCols])
{
	int print[nRows * mCols];
	memset(print, 0, nRows * mCols * sizeof(int));

	int w = 0;
	int left = 0, right = mCols - 1;
	int top = 0, bottom = nRows - 1;
	while (left <= right && top <= bottom) {
		for (int i = left; i <= right; i++) {
			print[w++] = input[top][i];
		}
		top++;

		for (int i = top; i <= bottom; i++) {
			print[w++] = input[i][right];
		}
		right--;

		for (int i = right; i >= left && top <= bottom; i--) {
			print[w++] = input[bottom][i];
		}
		bottom--;

		for (int i = bottom; i >= top && left <= right; i--) {
			print[w++] = input[i][left];
		}
		left++;
	}
	for (int i = 0; i < w; i++) {
		printf("%d ", print[i]);
	}
}

// https://www.naukri.com/code360/problems/reverse-of-a-number_624652
int reverse_number(int num)
{
    int reverse = 0;
    while (num > 0)
    {
        reverse *= 10;
        reverse += num % 10;
        num /= 10;
    }
    return reverse;
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

    {
        int arr[] = {10, 7, 8, 9, 1, 5};
        quickSort(arr, 0, sizeof(arr) / sizeof(int) - 1);
        printf("quickSort:");
        for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    {
        printf("Set K Bits:%d\n", setKBits(5, 2));
        printf("Set K Bits:%d\n", setKBits(16, 3));
    }
    {
        char input[] = "aabccbaa";
        removeAllOccurrencesOfChar(input, 'a');
        printf("Remove character:%s\n", input);
    }
    {
        int arr[] = {1, 3, 3, 5, 8, 10, 12};
        int n = sizeof(arr) / sizeof(int);
        int *lb = lower_bound(arr, arr + n, 6);
        if (lb != arr + n)
        {
            printf("The lower bound of 4 in the array is at index %ld.\n", lb - arr);
        }
    }
    {
        printf("Reset in Range:%#x\n", resetAllBitsInRange(23, 4, 2));
    }
    {
        double norm = 1500;
        double x1[3] = {10, 10, 10};
        double y1[3] = {norm, norm - 500, norm + 500};

        double norm1 = 20500;
        double x2[3] = {100, 100, 100};
        double y2[3] = {norm1, norm1 - norm1 * 0.08, norm1 + norm1 * 0.08};

        double k[3] = {0};
        double b[3] = {0};

        for (int i = 0; i < 3; i++)
        {
            k[i] = (y2[i] - y1[i]) / (x2[i] - x1[i]);
            b[i] = y1[i] - k[i] * x1[i];
        }
        for (int i = 10; i <= 100; i += 10)
        {
            printf("%.0lf", floor(floor(k[0] * i + b[0]) * 0.7));
            for (int j = 1; j < 3; j++)
                printf(", %.0lf", floor(k[j] * i + b[j]));
            printf("\n");
        }
    }
    {
        unsigned int val = 0x12B00177;
        printf("_reg_mask:%#x\n", _reg_get(val, 27, 20));
        printf("GENMASK:%#x\n", (val & GENMASK(27, 20)) >> 20);
    }
    {
        int arr[] = {9, 9, 9, 1, 0, 2, 3, 6, 6};
        printf("%d\n", ninjaAndSortedList(sizeof(arr) / sizeof(int), 6, arr));
    }
    {
        printf("Count Set Bits:%d\n", countSetBits(2));
    }
    {
        int arr[] = {1, 0, 0, 1, 0};
        printf("Flip Bits:%d\n", flipBits(arr, sizeof(arr) / sizeof(int)));
    }
    {
        printf("Binary to decimal: %d\n", binary_to_decimal(1100));
    }
    return 0;
}
