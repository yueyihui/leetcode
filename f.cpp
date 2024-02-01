#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <string>
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

vector<int> countSort(vector<int> &a)
{
    int max = 0;
    for (int i = 1; i < a.size(); i++)
    {
        if (a[max] < a[i])
            max = i;
    }
    vector<int> count(a[max] + 1, 0);
    for (int i = 0; i < a.size(); i++)
    {
        count[a[i]]++;
    }

    vector<int> rv(a.size());
    for (int i = 0, p = 0; i < a.size(); )
    {
        if (count[p] == 0)
            p++;
        else
        {
            rv[i++] = p;
            count[p]--;
        }
    }
    return rv;
}

class Middle
{
#define COLUMN (m[0].size())
#define ROW m.size()
  public:
    int partition(vector<vector<int>> &m, int low, int high);
    int findMiddleValue(vector<vector<int>> &m, int low, int high, int mid);
    int getMedian(vector<vector<int>> &m);
};

int Middle::partition(vector<vector<int>> &m, int low, int high)
{
    int pivot = m[high / COLUMN][high % COLUMN];
    int i = low - 1;
    for (int j = low; j <= high; j++)
    {
        if (m[j / COLUMN][j % COLUMN] <= pivot)
        {
            i++;
            std::swap(m[i / COLUMN][i % COLUMN],
                      m[j / COLUMN][j % COLUMN]);
        }
    }
    return i;
}

int Middle::findMiddleValue(vector<vector<int>> &m, int low, int high, int mid)
{
    if (low == high)
    {
        return m[low / COLUMN][low % COLUMN];
    }

    int i = partition(m, low, high);
    if (i == mid)
        return m[i / COLUMN][i % COLUMN];
    else if (i < mid)
        return findMiddleValue(m, i + 1, high, mid);
    else
        return findMiddleValue(m, low, i - 1, mid);
}

int Middle::getMedian(vector<vector<int>> &m)
{
    int len = ROW * COLUMN;
    int x = COLUMN / 2;
    int y = ROW / 2;
    int mid = x + y * COLUMN;
    return findMiddleValue(m, 0, len - 1, mid);
}

int getMedian(vector<vector<int>> &m)
{
    int max = 0, min = 0;
    int row = m.size();
    int col = m[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (m[i][j] > max)
                max = m[i][j];
            if (m[i][j] < min)
                min = m[i][j];
        }
    }
    while (min < max)
    {
        int equals = 0;
        int greater = 0;
        int smaller = 0;
        int mid = min + (max - min) / 2;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (m[i][j] > mid)
                    greater++;
                else if (m[i][j] < mid)
                    smaller++;
                else
                    equals++;
            }
        }
        if (greater > smaller && greater - smaller > equals)
        {
            min = mid + 1;
        }
        else if (greater < smaller && smaller - greater > equals)
        {
            max = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return min;
}

#ifdef ROW
#undef ROW
#endif
#define ROW arr.size()
#ifdef COLUMN
#undef COLUMN
#endif
#define COLUMN arr[0].size()
#define L2M(i) arr[(i)/COLUMN][(i)%COLUMN]
bool findInMatrix(int x, vector<vector<int>> &arr)
{
    int len = ROW * COLUMN;
    int l = 0;
    int r = len - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (x < L2M(mid))
        {
            r = mid - 1;
        }
        else if (x > L2M(mid))
        {
            l = mid + 1;
        }
        else
            return true;
    }
    return false;
}

class MinHeap
{
  public:
    void heapify(vector<int> &arr, int n, int root)
    {
        int min = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < n && arr[left] < arr[min])
            min = left;
        if (right < n && arr[right] < arr[min])
            min = right;
        if (min != root)
        {
            std::swap(arr[min], arr[root]);
            heapify(arr, n, min);
        }
    }
    vector<int> buildMinHeap(vector<int> &arr)
    {
        for (int i = arr.size() / 2 - 1; i >= 0; i--)
        {
            heapify(arr, arr.size(), i);
        }
        for (auto i : arr)
        {
            printf("%d ", i);
        }
        printf("\n");
        return arr;
    }
};

class MinimumKproduct
{
  private:
    void heapify(vector<int> &arr, int N, int root)
    {
        int max = root;
        int l = 2 * root + 1;
        int r = 2 * root + 2;
        if (l < N && arr[l] > arr[max])
            max = l;
        if (r < N && arr[r] > arr[max])
            max = r;
        if (max != root)
        {
            std::swap(arr[root], arr[max]);
            heapify(arr, N, max);
        }
    }

  public:
    int minProduct(vector<int> &arr, int n, int k)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i);
        }
        for (int i = n - 1; i >= 0; i--)
        {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        const int M = (int)1e9 + 7;
        int min = 1;
        for (int i = 0; i < k; i++)
        {
            min = (min * (long long)arr[i]) % M;
        }
        return min;
    }
};

class SubsetSum
{
  private:
    void permute(vector<int> &result, vector<int> &num, int l, int r, int sum)
    {
        if (l > r)
        {
            result.push_back(sum);
        }
        else
        {
            permute(result, num, l + 1, r, sum + num[l]);
            permute(result, num, l + 1, r, sum);
        }
    }

  public:
    vector<int> subsetSum(vector<int> &num)
    {
        vector<int> result;
        permute(result, num, 0, num.size() - 1, 0);
        std::sort(result.begin(), result.end());
        return result;
    }
};

class SubSequences
{
  private:
    void loop(vector<string> &rv, string in, string out)
    {
        if (in.empty())
        {
            if (!out.empty())
            {
                rv.push_back(out);
            }
        }
        else
        {
            loop(rv, in.substr(1), out + in[0]);
            loop(rv, in.substr(1), out);
        }
    }

  public:
    vector<string> subsequences(string str)
    {
        vector<string> rv;
        string out;
        loop(rv, str, out);
        return rv;
    }
};

//pascal triangle
//https://www.codingninjas.com/studio/problems/number-of-subsets_3952532?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=2
int findWays(vector<int> &arr, int k)
{
    const int MOD = 1e9 + 7;
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    for (int i : arr)
    {
        for (int j = k; j >= i; j--)
        {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }
    return dp[k];
}

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<int> count;
    for (int i = 0; i < n; i++)
    {
        if (count.empty() || count.back() < arr[i])
        {
            count.push_back(arr[i]);
        }
        else
        {
            auto lb = std::lower_bound(count.begin(), count.end(), arr[i]);
            *lb = arr[i];
        }
    }
    return count.size();
}

int* lower_bound(int arr[], int n, int value)
{
    int distance = n - 1;
    int *it = NULL;
    int step = 0;
    while (distance > 0)
    {
        it = arr;
        step = distance / 2;
        it += step;
        if (*it < value)
        {
            arr = ++it;
            distance -= step + 1;
        }
        else
            distance = step;
    }
    return arr;
}

int lower_bound2(int arr[], int n, int x)
{
    int l = 0, r = n - 1;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] < x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return arr[l] < x ? -1 : l;
}

int upperBound(vector<int> &arr, int n, int x)
{
    int l = 0, r = n - 1;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] <= x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return arr[l] <= x ? -1 : l;
}

//https://www.codingninjas.com/studio/problems/minimum-elements_3843091?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=ATTEMPTED
class MinElements
{
  private:
    void loop(vector<int> &num, int x, vector<int> &assist, int &len, int i)
    {
        if (x == 0)
        {
            if (len == 0)
                len = assist.size();
            else
                len = assist.size() < len ? assist.size() : len;
        }
        else if (x < 0)
        {
            return;
        }
        else
        {
            for (; i < num.size(); i++)
            {
                assist.push_back(num[i]);
                loop(num, x - num[i], assist, len, i);
                assist.pop_back();
            }
        }
    }

  public:
    int minimumElements(vector<int> &num, int x)
    {
        int len = -1;
        vector<int> assist;
        loop(num, x, assist, len, 0);
        return len;
    }
};

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

    vector<int> lar = {12, 1, 20, 1, 15, 5, 5, 8, 10, 0, 2, 3, 4, 11};
    auto v = countSort(lar);
    printf("countSort:");
    for (auto i : v)
    {
        printf("%d ", i);
    }
    printf("\n");

    Middle m;
    vector<vector<int>> matrix = {{1, 12, 3}, {6, 15, 2}, {7, 0, 9}};
    printf("getMedian:%d\n", m.getMedian(matrix));
    printf("getMedian:%d\n", getMedian(matrix));

    vector<vector<int>> search_in_matrix = {{1, 2, 4, 5},
                                            {8, 12, 14, 16},
                                            {23, 25, 26, 29}};
    std::cout << "findInMatrix:" << findInMatrix(26, search_in_matrix) << std::endl;
    std::cout << "findInMatrix:" << findInMatrix(15, search_in_matrix) << std::endl;

    vector<int> minheap = {9, 3, 2, 6, 7};
    MinHeap minHeap;
    minHeap.buildMinHeap(minheap);

    MinimumKproduct minK;
    vector<int> ar = {1, 2, 7, 2, 3, 2};
    std::cout << "minProduct:" << minK.minProduct(ar, ar.size(), 3) << std::endl;

    vector<int> subset = {1, 2, 7};
    SubsetSum sss;
    auto sub = sss.subsetSum(subset);
    for (auto i : sub)
    {
        printf("%d ", i);
    }
    std::cout << std::endl;

    {
        vector<int> arr = {1, 1, 4, 5};
        std::cout << "findWays: " << findWays(arr, 5) << std::endl;
        arr = {16, 8, 2, 4, 2};
        std::cout << "findWays: " << findWays(arr, 8) << std::endl;
        arr = {3, 3, 3, 3};
        std::cout << "findWays: " << findWays(arr, 5) << std::endl;
        arr = {16, 8, 5, 2, 3, 6};
        std::cout << "findWays: " << findWays(arr, 8) << std::endl;
    }

    {
        SubSequences s;
        auto rv = s.subsequences("abc");
        for (auto i : rv)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    {
        int arr[] = {1, 13, 24, 2, 3, 4};
        std::cout << "longestIncreasingSubsequence:"
                  << longestIncreasingSubsequence(arr, sizeof(arr) / sizeof(int))
                  << std::endl;
    }

    {
        printf("-------------\n");
        int arr[] = {1, 1, 1, 3, 5, 5, 16, 28, 19};
        std::cout << lower_bound2(arr, sizeof(arr) / sizeof(int), 12) << std::endl;
        std::cout << lower_bound2(arr, sizeof(arr) / sizeof(int), 2) << std::endl;
        std::cout << lower_bound2(arr, sizeof(arr) / sizeof(int), 5) << std::endl;
        std::cout << lower_bound2(arr, sizeof(arr) / sizeof(int), 7) << std::endl;
        int arr1[] = {1,5,5,5,5,5};
        std::cout << lower_bound2(arr1, sizeof(arr1) / sizeof(int), 2) << std::endl;
        int arr2[] = {1, 5};
        std::cout << lower_bound2(arr2, sizeof(arr2) / sizeof(int), 2) << std::endl;
        int arr3[] = {1, 5, 8};
        std::cout << lower_bound2(arr3, sizeof(arr3) / sizeof(int), 2) << std::endl;
        printf("-------------\n");
    }
    return 0;
}
