#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct ListNode {
	int val;
	struct ListNode *next;
} ListNode;

struct HashTable
{
    char key[8];
    UT_hash_handle hh;
};

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
    int *q = nums + 1;
    int *p = q;
    while (p < nums + numsSize)
    {
        *q = *p;
        int same = 0;
        for (int *i = nums; i < q; i++)
        {
            if (*i == *q)
            {
                same = 1;
                break;
            }
        }
        if (same == 0)
        {
            q++;
        }
        p++;
    }
    return q - nums;
}

//https://www.naukri.com/code360/problems/find-duplicate_625160
//contains numbers from 0 to (N - 2)
int duplicateNumber(int *arr, int size)
{
    int dup = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != size - 1)
        {
            dup ^= i;
        }
        dup ^= arr[i];
    }
    return dup;
}

//https://www.naukri.com/code360/problems/duplicate-in-array_893397
//ntains numbers from 1 to (n - 1)
int findDuplicate(int *arr, int n)
{
    int dup = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            dup ^= i;
        }
        dup ^= arr[i] - 1;
    }
    return dup + 1;
}

// https://leetcode.com/problems/rotate-array/
void rotate(int *nums, int n, int k)
{
    k = k % n;
    int rotated[n];
    memset(rotated, 0, n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        rotated[(i + k) % n] = nums[i];
    }

    for (int i = 0; i < n; i++)
    {
        nums[i] = rotated[i];
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

int *getProductArrayExceptSelf(int *arr, int n)
{
    const int mod = 1000000007;
    int zero = 0;
    long product = 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
            product = (product * arr[i]) % mod;
        else
            zero++;
    }
    int *ans = (int *)malloc(n * sizeof(int));
    memset(ans, 0, n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (zero == 1)
        {
            if (arr[i] == 0)
                ans[i] = product;
            else
                ans[i] = 0;
        }
        else if (zero >= 2)
        {
            ans[i] = 0;
        }
        else
        {
            ans[i] = product / arr[i];
        }
    }
    return ans;
}

// https://leetcode.com/problems/length-of-last-word/
int lengthOfLastWord(char s[], int n)
{
    int i = n - 1;
    while (s[i] == ' ')
    {
        i--;
    }

    int j = i;
    while (j >= 0 && s[j] != ' ')
    {
        j--;
    }
    return i - j;
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

void shellsort(char *str)
{
    for (int gap = strlen(str) / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < strlen(str); i++)
        {
            int j = i;
            int val = str[j];
            for (; j >= gap; j -= gap)
            {
                if (val < str[j - gap])
                {
                    str[j] = str[j - gap];
                }
                else
                {
                    break;
                }
            }
            str[j] = val;
        }
    }
}

void swap(int* a,int*b)
{
    int x = *a;
    *a = *b;
    *b = x;
}
void selectSort(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
}

char ***groupAnagrams(char strs[][4], int strsSize)
{
    struct HashTable *table = NULL;

    for (int i = 0; i < strsSize; i++)
    {
        char *word = (char *)malloc(strlen(strs[i] + 1));
        strcpy(word, strs[i]);
        shellsort(word);
        struct HashTable *rv;
        HASH_FIND_INT(table, word, rv);
        if (rv != NULL)
        {
            printf("get hash:%s\n", strs[i]);
        }
        else
        {
            struct HashTable *s = (struct HashTable *)malloc(sizeof(struct HashTable));
            strcpy(s->key, word);
            HASH_ADD_INT(table, key, s);
            printf("add hash:%s\n", strs[i]);
        }
    }
    return NULL;
}

char *mergeAlternately(char *word1, char *word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int size = len1 + len2 + 2;
    char *merge = (char *)malloc(size);
    memset(merge, 0, size);

    int i = 0, j1 = 0, j2 = 0;
    while (j1 < len1 && j2 < len2)
    {
        if (i % 2 == 0)
        {
            merge[i++] = word1[j1++];
        }
        else
        {
            merge[i++] = word2[j2++];
        }
    }
    while (j1 < len1)
    {
        merge[i++] = word1[j1++];
    }
    while (j2 < len2)
    {
        merge[i++] = word2[j2++];
    }
    return merge;
}

void shellsort_int(int *arr, int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            int j = i;
            int val = arr[j];
            while (j >= gap && arr[j - gap] > val)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = val;
        }
    }
}

//Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
//Output: [4,0,3]
//Explanation:
//- 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
//- 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
//- 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
int *successfulPairs(int *spells, int spellsSize, int *potions, int potionsSize, long long success, int *returnSize)
{
    //don't sort spells, we traverse it
    //shellsort_int(spells, spellsSize);
    shellsort_int(potions, potionsSize);
    *returnSize = spellsSize;
    int *rv = (int *)malloc(sizeof(int) * spellsSize);
    memset(rv, 0, spellsSize);
    for (int i = 0; i < spellsSize; i++)
    {
        int l = 0;
        int r = potionsSize - 1;
        int start = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (spells[i] * potions[mid] >= success)
            {
                start = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (start >= 0)
        {
            rv[i] = potionsSize - start;
        }
        else
        {
            rv[i] = 0;
        }
    }
    return rv;
}

long long fast_pow(int x, int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n % 2 == 0)
        return fast_pow(x * x, n / 2);
    else
        return fast_pow(x * x, n / 2) * x;
}

//prime 0~9: 2 3 5 7 --- 4 nums
//even 0~9: 0,2,4,6,8 --- 5 nums
//for any array of length n, it has (n+1)/2 even index and n/2 odd index
int countGoodNumbers(long long n)
{
    return fast_pow(5, (n + 1) / 2) * fast_pow(4, n / 2);
}

int maxSubsequence(int arr[], int size)
{
    int max = 0;
    int thisSum = 0;
    int l = 0;
    int r = 0;
    for (int i = 0; i < size; i++)
    {
        thisSum += arr[i];
        if (thisSum > max)
        {
            r = i;
            max = thisSum;
        }
        else if (thisSum < 0)
        {
            //why it is i+1 instead i?
            //i-1 didn't make thisSum<0, but i
            //that i it must be a negative
            l = i + 1;
            r = l;
            thisSum = 0;
        }
    }
    printf("%s range:[%d]~[%d]\n", __func__, l, r);
    return max;
}

// https://www.naukri.com/code360/problems/maximum-subarray_893296
int *maximumsumSubarray(int arr[], int n)
{
    int *vec = (int *)malloc(sizeof(int) * n);
    memset(vec, 0, n);
    int sum = INT_MIN, this_sum = 0;
    int l = 0, r = 0, begin = 0;
    for (int i = 0; i < n; i++)
    {
        this_sum += arr[i];
        if (this_sum > sum)
        {
            sum = this_sum;
            l = begin;
            r = i;
        }
        if (this_sum < 0)
        {
            this_sum = 0;
            begin = i + 1;
        }
    }
    for (int i = l; i <= r; i++)
    {
        vec[i] = arr[l++];
    }
    return vec;
}

int *goodIndices(int *nums, int numsSize, int k, int *returnSize)
{
    int *left = (int *)malloc(numsSize * sizeof(int));
    int *right = (int *)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++)
    {
        left[i] = right[i] = 1;
    }

    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i - 1] >= nums[i])
        {
            left[i] += left[i - 1];
        }
        if (nums[numsSize - i - 1] <= nums[numsSize - i])
        {
            right[numsSize - i - 1] += right[numsSize - i];
        }
    }

    int *rv = (int *)malloc(numsSize * sizeof(int));
    memset(rv, 0, numsSize * sizeof(int));
    *returnSize = 0;
    for (int i = k; i < numsSize - k; i++)
    {
        if (left[i] > k && right[i] > k)
        {
            rv[*returnSize] = i;
            *returnSize += 1;
        }
    }
    return rv;
}

int **printPascal(int n)
{
    int **res = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++)
    {
        res[i] = (int *)malloc(sizeof(int) * (i + 1));
        memset(res[i], 0, sizeof(int) * (i + 1));
        res[i][0] = res[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
        }
    }
    return res;
}

int searchInsert(int arr[], int n, int m)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (m > arr[mid])
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}

// https://www.naukri.com/code360/problems/code-interesting-alphabets_53421
void print_pattern(int N)
{
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = i; j < N; j++)
        {
            printf("%c", 'A' + j);
        }
        printf("\n");
    }
}

//https://www.naukri.com/code360/problems/number-pattern-3_624655
void number_pattern_3(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || j == i)
				printf("1");
			else
				printf("2");
		}
		printf("\n");
	}
}

//https://www.naukri.com/code360/problems/number-pattern_624932
void number_pattern(int n)
{
	for (int i = 1; i <= n; i++) {
		int num = i;
		for (int j = 0; j < i; j++) {
			printf("%d", num++);
		}
		printf("\n");
	}
}

// https://www.naukri.com/code360/problems/test-problem_955
void number_pattern_2(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            printf(" ");
        }
        int num = i + 1;
        for (int k = 0; k < i + 1; k++)
        {
            printf("%d", num++);
        }
        printf("\n");
    }
}

// https://www.naukri.com/code360/problems/pattern-triangle-of-numbers_22940
void number_pattern_1(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            printf(" ");
        }
        int num = i + 1;
        for (int k = 0; k < i; k++)
        {
            printf("%d", num++);
        }
        for (int k = 0; k <= i; k++)
        {
            printf("%d", num--);
        }
        printf("\n");
    }
}

// https://www.naukri.com/code360/problems/compare-versions_1062582
int compareVersions(char a[], char b[])
{
    int n = strlen(a);
    int m = strlen(b);
    for (int i = 0, j = 0; i < n || j < m; i++, j++)
    {
        long long numA = 0;
        long long numB = 0;
        while (i < n && a[i] != '.')
        {
            numA = numA * 10 + (a[i] - '0');
            i++;
        }
        while (j < m && b[j] != '.')
        {
            numB = numB * 10 + (b[j] - '0');
            j++;
        }
        if (numA > numB)
            return 1;
        else if (numA < numB)
            return -1;
    }
    return 0;
}

// https://www.naukri.com/code360/problems/number-pattern-1_893187
void printPattern(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("1");
        }
        printf("\n");
    }
}

int lower_bound(int *vec, int l, int r)
{
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (vec[mid] == 1)
            r = mid;
        else if (vec[mid] == 0)
            l = mid + 1;
    }
    return vec[r] == 1 ? r : -1;
}

// https://www.naukri.com/code360/problems/row-with-maximum-1-s_1112656
int rowWithMax1s(int **matrix, int n, int m)
{
    int prev = m;
    int row = 0;
    for (int i = 0; i < n; i++)
    {
        int index = lower_bound(matrix[i], 0, m - 1);
        if (index != -1 && index < prev)
        {
            prev = index;
            row = i;
        }
    }
    return prev == m ? -1 : row;
}

// https://www.naukri.com/code360/problems/ninja-and-subarrays_2674106
int sumOfSmallestAndSecondSmallest(int n, int arr[])
{
    int sum = INT_MIN;
    for (int i = 1; i < n; i++)
    {
        sum = MAX(sum, arr[i] + arr[i - 1]);
    }
    return sum;
}

//https://www.naukri.com/code360/problems/add-two-numbers-as-linked-lists_1170520
//https://leetcode.com/problems/add-two-numbers/
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
	struct ListNode dummy = { 0, NULL };
	struct ListNode *tail = &dummy;
	int carry = 0;
	while (l1 != NULL && l2 != NULL) {
		int sum = l1->val + l2->val + carry;
		struct ListNode *_new = (struct ListNode *)malloc(sizeof(struct ListNode));
		_new->val = sum % 10;
		carry = sum / 10;
		tail->next = _new;
		tail = tail->next;
		tail->next = NULL;
		l1 = l1->next;
		l2 = l2->next;
	}
	while (l1 != NULL) {
		int sum = l1->val + carry;
		struct ListNode *_new = (struct ListNode *)malloc(sizeof(struct ListNode));
		_new->val = sum % 10;
		carry = sum / 10;
		tail->next = _new;
		tail = tail->next;
		tail->next = NULL;
		l1 = l1->next;
	}
	while (l2 != NULL) {
		int sum = l2->val + carry;
		struct ListNode *_new = (struct ListNode *)malloc(sizeof(struct ListNode));
		_new->val = sum % 10;
		carry = sum / 10;
		tail->next = _new;
		tail = tail->next;
		tail->next = NULL;
		l2 = l2->next;
	}
	while (carry != 0) {
		int sum = carry;
		struct ListNode *_new = (struct ListNode *)malloc(sizeof(struct ListNode));
		_new->val = sum % 10;
		carry = sum / 10;
		tail->next = _new;
		tail = tail->next;
		tail->next = NULL;
	}
	return dummy.next;
}

// https://www.naukri.com/code360/problems/sum-of-two-arrays_893186
int *addTwoArrays(int *a, int n, int *b, int m)
{
    int len = n + m;
    int temp[len];
    memset(temp, 0, len * sizeof(int));

    int i = n - 1, j = m - 1;
    int w = n + m - 1;
    int carry = 0;
    while (i >= 0 && j >= 0)
    {
        int sum = a[i--] + b[j--] + carry;
        temp[w--] = sum % 10;
        carry = sum / 10;
    }
    while (i >= 0)
    {
        int sum = a[i--] + carry;
        temp[w--] = sum % 10;
        carry = sum / 10;
    }
    while (j >= 0)
    {
        int sum = b[j--] + carry;
        temp[w--] = sum % 10;
        carry = sum / 10;
    }
    while (carry > 0)
    {
        int sum = carry;
        temp[w--] = sum % 10;
        carry = sum / 10;
    }
    len = n + m - w - 1;
    int *ans = (int *)malloc(len * sizeof(int));
    memset(ans, 0, len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        w++;
        ans[i] = temp[w];
    }
    return ans;
}

//https://www.naukri.com/code360/problems/intersection-of-2-arrays_1082149
int *findArrayIntersection(int *arr1, int n, int *arr2, int m)
{
	int temp[n + m];
	int w = 0;
	int i = 0, j = 0;
	while (i < n && j < m) {
		if (arr1[i] < arr2[j])
			i++;
		else if (arr1[i] > arr2[j])
			j++;
		else {
			temp[w++] = arr1[i];
			i++;
			j++;
		}
	}
	int *ans = (int *)malloc(w * sizeof(int));
	memset(ans, 0, w * sizeof(int));
	for (int i = 0; i < w; i++)
		ans[i] = temp[i];
	return ans;
}

// https://leetcode.com/problems/rotate-list/
struct ListNode *rotateRight(struct ListNode *head, int k)
{
    if (head == NULL || head->next == NULL)
        return head;
    int len = 0;
    struct ListNode *a = head, *b = head;
    while (a != NULL)
    {
        a = a->next;
        len++;
    }
    if (k >= len)
        k = k % len;
    if (k == 0)
        return head;
    a = head;
    for (int i = 0; i < k; i++)
    {
        b = b->next;
    }
    while (b->next != NULL)
    {
        a = a->next;
        b = b->next;
    }
    struct ListNode *_head = a->next;
    a->next = NULL;
    b->next = head;
    return _head;
}

// https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
int getDecimalValue(ListNode *head)
{
	int result = 0;
	while (head != NULL) {
		result <<= 1;
		result |= head->val;
		head = head->next;
	}
	return result;
}

//https://leetcode.com/problems/remove-element/
int removeElement(int *nums, int numsSize, int val)
{
	int w = -1;
	int cnt = 0;
	for (int i = 0; i < numsSize; i++) {
		if (nums[i] != val) {
			w++;
			nums[w] = nums[i];
		} else {
			cnt++;
		}
	}
	return numsSize - cnt;
}

// https://www.naukri.com/code360/problems/occurrence-of-x-in-a-sorted-array_630456
// binary search
int count(int *arr, int n, int x)
{
    int left = -1, right = -1;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] < x)
        {
            l = mid + 1;
        }
        else if (arr[mid] > x)
            r = mid - 1;
        else
        {
            left = mid;
            r = mid - 1;
        }
    }
    if (left == -1)
        return 0;
    l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] < x)
        {
            l = mid + 1;
        }
        else if (arr[mid] > x)
            r = mid - 1;
        else
        {
            right = mid;
            l = mid + 1;
        }
    }
    if (right == -1)
        return 0;
    return right - left + 1;
}

// https://www.naukri.com/code360/problems/unique-binary-search-trees_1266110
long long int numTrees(int n)
{
    long long int dp[n + 1];
    memset(dp, 0, (n + 1) * sizeof(long long int));
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        // j is left nodes, i is tree nodes include root
        for (int j = 0; j < i; j++)
        {
            // j is left subtree nodes
            // i-1-j is i-root-left == right nodes
            dp[i] += dp[j] * dp[i - 1 - j];
        }
    }
    return dp[n];
}

// https://leetcode.com/problems/edit-distance/
int minDistance(char *word1, char *word2)
{
    int n = strlen(word1);
    int m = strlen(word2);
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
                dp[i][j] = MIN(MIN(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
        }
    }
    return dp[n][m];
}

int main(int argc, char *argv[])
{
    int nums[] = {2, 3, 1, 2, 4, 3};
    printf("%d\n", minSubArrayLen(9, nums, sizeof(nums) / sizeof(int)));

    char s[] = "abcebedfjkl";
    printf("lengthOfLongestSubstring:%d\n", lengthOfLongestSubstring(s));

    int dup[] = {5, 1, 2, 4, 3, 4, 3, 5};
    printf("removeDuplicates:%d\n", removeDuplicates(dup, sizeof(dup) / sizeof(int)));

    int r[] = {1, 2, 3, 4, 5, 6, 7};
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

    {
        int arr[] = {1, 2, 3, 4};
        int *ans = getProductArrayExceptSelf(arr, sizeof(arr) / sizeof(int));
        printf("getProductArrayExceptSelf:");
        for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
        {
            printf(" %d", ans[i]);
        }
        printf("\n");
    }

    char w[] = "Hello World   ";
    printf("lengthOfLastWord:%d\n", lengthOfLastWord(w, strlen(w)));

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

    char gr[][4] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    groupAnagrams(gr, sizeof(gr) / sizeof(char[4]));

    printf("mergeAlternately:%s\n", mergeAlternately("abc", "defgh"));

    int spells[] = {5,1,3};
    int potions[] = {1, 2, 3, 4, 5};
    rv = successfulPairs(spells, sizeof(spells) / sizeof(int), potions, sizeof(potions) / sizeof(int), 7, &returnSize);
    printf("successfulPairs:");
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", rv[i]);
    }
    printf("\n");

    printf("fast_pow:%lld\n", fast_pow(2, 10));
    printf("countGoodNumbers:%d\n",countGoodNumbers(1));
    printf("countGoodNumbers:%d\n",countGoodNumbers(4));

    int m[] = {-1, 4, 12, -8, 3, -1, -3, 4, -3, 4, 6 - 5};
    printf("maxSubsequence:%d\n", maxSubsequence(m, sizeof(m) / sizeof(int)));

    returnSize = 0;
    int good[] = {2, 1, 1, 1, 3, 4, 1};
    rv = goodIndices(good, sizeof(good) / sizeof(int), 2, &returnSize);
    printf("goodIndices:");
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", rv[i]);
    }
    printf("\n");

    int ss[] = {4, 1, 2, 3, -1, 0, 44, 2, 22, 31, 221, -14, -9, -11, 5, 6, 7, 4};
    selectSort(ss, sizeof(ss) / sizeof(int));
    printf("selectSort:");
    for (int i = 0; i < sizeof(ss) / sizeof(int); i++)
    {
        printf("%d ", ss[i]);
    }
    printf("\n");

    int **pascal = printPascal(5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("%d ", pascal[i][j]);
        }
        printf("\n");
    }

    {
        int arr[] = {3, 5, 9, 21, 35};
        printf("searchInsert:%d\n", searchInsert(arr, sizeof(arr) / sizeof(int), 8));
    }
    {
        //constraint of topic: if size 7, value must 0~5, and have one duplicate
        int arr[] = {0, 3, 1, 5, 4, 3, 2};
        printf("Find Duplicate:%d\n", duplicateNumber(arr, sizeof(arr) / sizeof(int)));
    }
    {
        //constraint of topic: if size 7, value must 1~6, and have one duplicate
        int arr[] = {6, 3, 1, 5, 4, 3, 2};
        printf("Duplicate In Array:%d\n", findDuplicate(arr, sizeof(arr) / sizeof(int)));
    }
    return 0;
}
