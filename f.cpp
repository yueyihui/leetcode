#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;

class A
{
  public:
    bool isIsomorphic(char *s, char *t);
};

bool A::isIsomorphic(char *s, char *t)
{
    std::unordered_map<char, char> s2t;
    std::unordered_map<char, char> t2s;
    return true;
}

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    for (int i = 0; i < n; i++)
    {
        nums1[m + i] = nums2[i];
    }

    for (int gap = (m + n) / 2; gap > 0; gap /= 2)
        for (int i = gap; i < m + n; i++)
        {
            int j = i;
            int tmp = nums1[j];
            while (j >= gap && nums1[j - gap] > tmp)
            {
                nums1[j] = nums1[j - gap];
                j -= gap;
            }
            nums1[j] = tmp;
        }
}

int removeDuplicates(int *nums, int numsSize)
{
    int *q = nums;
    int *p = q;
    while (p < nums + numsSize)
    {
        int *i = nums;
        for (; i < q; i++)
        {
            if (*i == *q)
                break;
        }
        if (i == q)
        {
            q++;
        }
        *q = *++p;
    }
    return q - nums;
}

void shellSort(vector<int> &arr)
{
    for (int gap = arr.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < arr.size(); i++)
        {
            int j = i;
            int x = arr[j];
            while (j >= gap && arr[j - gap] > x)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = x;
        }
    }
}

vector<vector<int>> findTriplets(vector<int> arr, int K)
{
    vector<vector<int>> rv;
    shellSort(arr);
    for (int i = 0; i < arr.size(); i++)
    {
        if (i > 0 && arr[i] == arr[i - 1])
            continue;

        int l = i + 1;
        int r = arr.size() - 1;
        while (l < r)
        {
            if (arr[i] + arr[l] + arr[r] < K)
            {
                l++;
            }
            else if (arr[i] + arr[l] + arr[r] > K)
            {
                r--;
            }
            else
            {
                vector<int> triple = {arr[i], arr[l], arr[r]};
                rv.push_back(triple);
                for (l++; l < r && arr[l] == arr[l - 1]; l++)
                    ;
                for (r--; l < r && arr[r] == arr[r + 1]; r--)
                    ;
            }
        }
    }
    return rv;
}

void insertQ(queue<int> &q, int k)
{
    int my = q.front();
    q.pop();
    if (k > 1)
    {
        insertQ(q, k - 1);
    }
    q.push(my);
}

queue<int> reverseElements(queue<int> q, int k)
{
    if (k <= 0)
        return q;

    insertQ(q, k);
    for (int i = 0; i < q.size() - k; i++)
    {
        q.push(q.front());
        q.pop();
    }
    return q;
}

void reverseQueue(queue<int> &q)
{
    stack<int> s;
    while (!q.empty())
    {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

bool isPalin(const char *l, const char *r)
{
    while (l < r)
    {
        if (*l++ != *r--)
            return false;
    }
    return true;
}

string longestPalinSubstring(string str)
{
    string rv;
    for (int i = 0; i < str.length(); i++)
    {
        int l = i;
        int r = str.length() - 1;
        //why consider case of l==r?
        //because abcd that the max palin is 1
        while (l <= r)
        {
            if (str[l] == str[r] && isPalin(&str[l], &str[r]))
            {
                if (rv.length() < r - l + 1)
                {
                    //rv = str.substr(l, r - l + 1);
                    rv.assign(str, l, r - l + 1);
                }
                break;
            }
            r--;
        }
    }
    return rv;
}

void setZeros(vector<vector<int>> &matrix)
{
    vector<std::pair<int, int>> target;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == 0)
            {
                target.push_back({i, j});
            }
        }
    }
    for (auto i = target.begin(); i != target.end(); i++)
    {
        for (auto j = matrix[i->first].begin(); j != matrix[i->first].end(); j++)
        {
            *j = 0;
        }
        for (auto j = matrix.begin(); j != matrix.end(); j++)
        {
            (*j)[i->second] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    std::unordered_map<char, char> a;
    a['a'] = 'b';
    a['a'] = 'b';
    std::cout << a.count('a') << std::endl;
    int nums1[] = {1, 4, 8, 0, 0, 0};
    int nums2[] = {2, 5, 6};
    merge(nums1, 6, 3, nums2, 3, 3);

    int nums3[] = {1, 8, 1, 4, 8, 0, 1, 0, 3, 0, 8, 4, 1, 23, 23, 0, 3, 4, 1};
    int len = removeDuplicates(nums3, sizeof(nums3) / sizeof(int));
    for (int i = 0; i < len; i++)
    {
        printf("%d ", nums3[i]);
    }
    printf("\n");

    vector<int> a3 = {1, 1, 4, 4, 0, 2, 1, 1, 2, 2, 2, 3, 3, 3};
    vector<vector<int>> rv = findTriplets(a3, 6);
    printf("findTriplets:");
    for (auto i : rv)
    {
        printf("[%d,%d,%d] ", i[0],i[1],i[2]);
    }
    printf("\n");

    string testcase[] = {"abcd", "abcba", "abccbc", "qweeq", "babcbabcbaccba", "abacdfgdcaba", "codingninjas",
                         "zzzzzzzzzzzzzzzzzzzzzzwwwwwwwwwwwwwwwwwyyyyyyyyyyyyyyyyyyydddddddddddddddddddddddddddddddddddddddddd"};
    for (int i = 0; i < sizeof(testcase) / sizeof(string); i++)
        std::cout << longestPalinSubstring(testcase[i]) << std::endl;

    {
        vector<vector<int>> testcase[] = {{{7, 19, 3},
                                           {4, 21, 0}},
                                          {{1, 0},
                                           {2, 7},
                                           {3, 0},
                                           {4, 8}},
                                          {{0, 2, 3},
                                           {1, 0, 3},
                                           {1, 2, 0}}};
        for (int i = 0; i < 3; i++)
        {
            setZeros(testcase[i]);
            for (auto j = testcase[i].begin(); j != testcase[i].end(); j++)
            {
                for (auto k = j->begin(); k != j->end(); k++)
                {
                    printf("%d ", *k);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
