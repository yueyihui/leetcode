#include <algorithm>
#include <bits/stdc++.h>
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

class MergeSort
{
  private:
    void merge(vector<int> &arr, int l, int mid, int r)
    {
        vector<int> L, R;
        for (int i = l; i <= mid; i++)
            L.push_back(arr[i]);

        for (int i = mid + 1; i <= r; i++)
            R.push_back(arr[i]);

        int i = 0, j = 0, k = l;
        while (i < L.size() && j < R.size())
        {
            if (L[i] < R[j])
            {
                arr[k++] = L[i++];
            }
            else
            {
                arr[k++] = R[j++];
            }
        }
        while (i < L.size())
            arr[k++] = L[i++];
        while (j < R.size())
            arr[k++] = R[j++];
    }

    void merge2(vector<int> &arr, int l, int mid, int r)
    {
        int r1 = l, r2 = mid + 1;
        vector<int> temp;
        while (r1 <= mid && r2 <= r)
        {
            if (arr[r1] < arr[r2])
            {
                temp.push_back(arr[r1++]);
            }
            else
            {
                temp.push_back(arr[r2++]);
            }
        }
        while (r1 <= mid)
        {
            temp.push_back(arr[r1++]);
        }
        while (r2 <= r)
        {
            temp.push_back(arr[r2++]);
        }
        for (int i = l; i <= r; i++)
        {
            arr[i] = temp[i - l];
        }
    }

  public:
    void mergeSort(vector<int> &arr, int l, int r)
    {
        if (l < r)
        {
            int mid = l + (r - l) / 2;
            mergeSort(arr, l, mid);
            mergeSort(arr, mid + 1, r);
            merge2(arr, l, mid, r);
        }
    }
};

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
    //Time Limit Exceeded
    int minimumElements(vector<int> &num, int x)
    {
        int len = -1;
        vector<int> assist;
        loop(num, x, assist, len, 0);
        return len;
    }

    int minimumElements2(vector<int> &num, int x)
    {
        //why -1?
        //every dp[i] store the min path to i
        //for j:num
        //i=(i-j)+j
        //dp[i] = dp[i-j]+1
        //for what dp[i] should remain 1
        vector<int> dp(x + 1, INT_MAX - 1);
        dp[0] = 0;
        for (int i = 1; i <= x; i++)
        {
            for (int j : num)
            {
                if (i >= j)
                {
                    dp[i] = min(dp[i], dp[i - j] + 1);
                }
            }
        }
        return dp[x] == INT_MAX - 1 ? -1 : dp[x];
    }
};

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
    //can't allow l==r, since r at the correct, the loop wouldn't quit
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

//https://www.codingninjas.com/studio/problems/longest-common-substring_1235207?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=3
int lcs(string &str1, string &str2)
{
    int longest = 0;
    int count[str1.size() + 1][str2.size() + 1];
    memset(count, 0, sizeof(count));
    for (int i = 1; i <= str1.size(); i++)
    {
        for (int j = 1; j <= str2.size(); j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                count[i][j] = count[i - 1][j - 1] + 1;
                longest = max(longest, count[i][j]);
            }
            else
            {
                count[i][j] = 0;
            }
        }
    }
    return longest;
}

//https://www.codingninjas.com/studio/problems/longest-common-subsequence_624879?interviewProblemRedirection=true&count=25
int lcs2(string s, string t)
{
    int longest = 0;
    vector<vector<int>> count(s.length() + 1, vector<int>(t.length() + 1, 0));
    for (int i = 1; i <= s.length(); i++)
    {
        for (int j = 1; j <= t.length(); j++)
        {
            if (s[i - 1] == t[j - 1])
                count[i][j] = count[i - 1][j - 1] + 1;
            else
                count[i][j] = max(count[i - 1][j], count[i][j - 1]);
        }
    }
    return count[s.length()][t.length()];
}

//https://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/
//https://www.naukri.com/code360/problems/maximum-sum-of-non-adjacent-elements_843261
int maximumNonAdjacentSum(vector<int> &nums)
{
    int n = nums.size();
    int dp[n][2] = {{0}};
    dp[0][0] = 0;
    dp[0][1] = nums[0];
    for (int i = 1; i < n; i++)
    {
        dp[i][1] = dp[i - 1][0] + nums[i];
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

//https://www.codingninjas.com/studio/problems/minimum-path-sum_985349?interviewProblemRedirection=true&leftPanelTabValue=SUBMISSION&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=2
int minSumPath(vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    dp[0][1] = dp[1][0] = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = grid[i - 1][j - 1] + min(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    return dp[m][n];
}

int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        dp[i][0] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = 1;
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
    }
    return dp[m - 1][n - 1];
}

//https://www.codingninjas.com/studio/problems/ninja-s-training_3621003?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=2
int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int>(3, 0));
    for (int i = 0; i < 3; i++)
        dp[0][i] = points[0][i];

    for (int i = 1; i < points.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (j)
            {
                case 0:
                    dp[i][j] = points[i][j] + max(dp[i - 1][j + 1], dp[i - 1][j + 2]);
                    break;
                case 1:
                    dp[i][j] = points[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j + 1]);
                    break;
                case 2:
                    dp[i][j] = points[i][j] + max(dp[i - 1][j - 1], dp[i - 1][j - 2]);
                    break;
            }
        }
    }
    return max(max(dp.back()[0], dp.back()[1]), dp.back()[2]);
}

//https://www.codingninjas.com/studio/problems/find-the-single-element_6680465?leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&page=4&attempt_status=COMPLETED
int getSingleElement(vector<int> &arr)
{
    if (arr.size() == 1)
        return arr[0];
    if (arr[0] != arr[1])
        return arr[0];
    if (arr[arr.size() - 1] != arr[arr.size() - 2])
        return arr[arr.size() - 1];
    int l = 0, r = arr.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid - 1] != arr[mid] && arr[mid] != arr[mid + 1])
            return arr[mid];
        else if ((mid % 2 == 0 && arr[mid] != arr[mid - 1]) ||
                 (mid % 2 != 0 && arr[mid] != arr[mid + 1]))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

//https://www.codingninjas.com/studio/problems/first-and-last-position-of-an-element-in-sorted-array_1082549?leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=ATTEMPTED
class FirstLastPos
{
  private:
    int left_bound(vector<int> &arr, int l, int r, int k)
    {
        int result = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] == k)
            {
                result = mid;
                r = mid - 1;
            }
            else if (arr[mid] < k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return result;
    }

    int right_bound(vector<int> &arr, int l, int r, int k)
    {
        int result = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] == k)
            {
                result = mid;
                l = mid + 1;
            }
            else if (arr[mid] < k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return result;
    }

  public:
    pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
    {
        int l = left_bound(arr, 0, n - 1, k);
        if (l == -1)
            return {-1, -1};
        else
        {
            int r = right_bound(arr, l, n - 1, k);
            return {l, r};
        }
    }
};

//https://www.codingninjas.com/studio/problems/next-greater-element_670312?leftPanelTabValue=SUBMISSION&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=ATTEMPTED
class NextGreaterElement
{
  private:
    int upper_bound(vector<int> &arr, int l, int r, int x)
    {
        if (l > r)
            return -1;
        if (l == r)
        {
            if (arr[l] > x)
                return l;
            else
                return -1;
        }

        int mid = l + (r - l) / 2;
        l = upper_bound(arr, l, mid - 1, x);
        if (l != -1)
            return l;
        else if (arr[mid] > x)
            return mid;
        else
            return upper_bound(arr, mid + 1, r, x);
    }

  public:
    vector<int> nextGreaterElement(vector<int> &arr, int n)
    {
        vector<int> rv(n, -1);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--)
        {
            while (st.empty() == false && st.top() <= arr[i])
            {
                st.pop();
            }
            if (st.empty() == false)
            {
                rv[i] = st.top();
            }
            st.push(arr[i]);
        }
        return rv;
    }

    //Time Limit Exceeded
    vector<int> nextGreaterElement2(vector<int> &arr, int n)
    {
        vector<int> rv;
        for (int i = 0; i < n; i++)
        {
            int j = upper_bound(arr, i + 1, n - 1, arr[i]);
            if (j != -1)
                rv.push_back(arr[j]);
            else
                rv.push_back(j);
        }
        return rv;
    }
};

//https://www.codingninjas.com/studio/problems/search-in-rotated-sorted-array_1082554?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=3
class Search_In_Rotated_Sorted_Array
{
  private:
    int partition(vector<int> &arr)
    {
        int l = 0, r = arr.size() - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (arr[0] > arr[mid])
                r = mid;
            else
                l = mid + 1;
        }
        return r;
    }
    int binarySearch(vector<int> &arr, int l, int r, int k)
    {
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] == k)
                return mid;
            else if (arr[mid] < k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }

  public:
    int search(vector<int> &arr, int n, int k)
    {
        int pivot = partition(arr);
        if (arr[pivot] <= k && k <= arr[n - 1])
            return binarySearch(arr, pivot, n - 1, k);
        else
            return binarySearch(arr, 0, pivot - 1, k);
    }
};

//https://www.codingninjas.com/studio/problems/longest-consecutive-sequence_759408?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=sort&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&page=3
class Longest_Consecutive_Sequence
{
  private:
    void shellSort(vector<int> &arr, int n)
    {
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i++)
            {
                int j = i;
                int tmp = arr[j];
                while (j >= gap && arr[j - gap] > tmp)
                {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = tmp;
            }
        }
    }

  public:
    int lengthOfLongestConsecutiveSequence(vector<int> &arr, int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        shellSort(arr, n);
        int r = 1, longest = 1, sub = 1;
        while (r < n)
        {
            if (arr[r] - arr[r - 1] == 1)
            {
                sub++;
            }
            else if (arr[r] == arr[r - 1])
            {
            }
            else
            {
                longest = max(longest, sub);
                sub = 1;
            }
            r++;
        }
        longest = max(longest, sub);
        return longest;
    }
};

//https://www.codingninjas.com/studio/problems/merge-k-sorted-arrays_975379?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=sort&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&page=3
class Merge_K_Sorted_Arrays
{
  private:
    void merge(vector<int> &v1, vector<int> &v2)
    {
        if (v2.size() == 0)
            return;
        vector<int> temp(v1);
        v1.clear();
        int l = 0, r = 0;
        while (l < temp.size() && r < v2.size())
        {
            if (temp[l] < v2[r])
            {
                v1.push_back(temp[l++]);
            }
            else
                v1.push_back(v2[r++]);
        }
        while (l < temp.size())
            v1.push_back(temp[l++]);
        while (r < v2.size())
            v1.push_back(v2[r++]);
    }

  public:
    vector<int> mergeKSortedArrays(vector<vector<int>> &kArrays, int k)
    {
        vector<int> rv;
        for (int i = 0; i < k; i++)
        {
            merge(rv, kArrays[i]);
        }
        return rv;
    }
};

//https://www.codingninjas.com/studio/problems/min-stack_3843991?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=min%20stack&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=1
class MinStack
{
  private:
    stack<int> s;
    int min;

  public:
    MinStack() {}

    void push(int num)
    {
        if (s.empty())
        {
            min = num;
            s.push(num);
        }
        else if (num < min)
        {
            s.push(2 * num - min);
            min = num;
        }
        else
        {
            s.push(num);
        }
    }

    int pop()
    {
        if (s.empty())
            return -1;
        if (s.top() < min)
        {
            int t = top();
            min = 2 * min - s.top();
            s.pop();
            return t;
        }
        else
        {
            int t = top();
            s.pop();
            return t;
        }
    }

    int top()
    {
        if (s.empty())
            return -1;
        else
            return s.top() < min ? min : s.top();
    }

    int getMin()
    {
        if (s.empty())
            return -1;
        else
            return min;
    }
};

//https://www.codingninjas.com/studio/problems/set-matrix-zeros_3846774?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=COMPLETED&page=10
class Set_Matrix_Zeros
{
  public:
    void setZeros(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix.front().size();
        vector<int> row(n, 0);
        vector<int> col(m, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (row[i] or col[j])
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

//https://www.naukri.com/code360/problems/matrix-flip-bit_920503
//Matrix Flip
int countFlip(vector<vector<int>> &mat)
{
    int n = mat.size();
    vector<bool> row(n, false), col(n, false);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 0)
            {
                row[i] = true;
                col[j] = true;
            }
        }
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (row[i] || col[j])
            {
                if (mat[i][j] == 1)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

//https://www.naukri.com/code360/problems/kth-largest-element_796007
class KthLargestElement
{
  private:
    void heapify(vector<int> &arr, int N, int i)
    {
        int max = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < N && arr[l] > arr[max])
            max = l;
        if (r < N && arr[r] > arr[max])
            max = r;
        if (max != i)
        {
            swap(arr[i], arr[max]);
            heapify(arr, N, max);
        }
    }
    void heapSort(vector<int> &arr)
    {
        for (int i = arr.size() / 2 - 1; i >= 0; i--)
        {
            heapify(arr, arr.size(), i);
        }
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

  public:
    int findKthLargest(vector<int> &nums, int k)
    {
        heapSort(nums);
        return nums[nums.size() - k];
    }
};

class ConsecutiveElements
{
  private:
    int partition(vector<int> &arr, int l, int r)
    {
        int pivot = r;
        int i = l - 1;
        for (int j = l; j < r; j++)
        {
            if (arr[j] <= arr[pivot])
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        i++;
        swap(arr[i], arr[pivot]);
        return i;
    }

    void quickSort(vector<int> &arr, int l, int r)
    {
        if (l < r)
        {
            int pi = partition(arr, l, r);
            quickSort(arr, l, pi - 1);
            quickSort(arr, pi + 1, r);
        }
    }

  public:
    bool isConsecutive(vector<int> &arr, int n)
    {
        quickSort(arr, 0, n - 1);
        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] + 1 != arr[i])
                return false;
        }
        return true;
    }
};

//https://www.naukri.com/code360/problems/consecutive-elements_795127
bool isConsecutive(vector<int> &arr, int n)
{
    int minElem = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        minElem = min(minElem, arr[i]);
    }
    int expect = 0;
    int actual = 0;
    for (int i = 0; i < n; i++)
    {
        expect += minElem + i;
        actual += arr[i];
    }
    return expect == actual;
}

//https://www.naukri.com/code360/problems/fourth-largest-element-in-the-array_630422
int getFourthLargest(int arr[], int n)
{
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++)
    {
        if (q.size() == 4)
        {
            if (arr[i] > q.top())
            {
                q.pop();
                q.push(arr[i]);
            }
        }
        else
            q.push(arr[i]);
    }
    if (q.size() < 4)
        return INT_MIN;
    else
        return q.top();
}

//https://www.naukri.com/code360/problems/kth-largest-element-in-the-unsorted-array_893030
int kthLargest(vector<int> &arr, int size, int K)
{
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < arr.size(); i++)
    {
        if (q.size() == K)
        {
            if (arr[i] > q.top())
            {
                q.pop();
                q.push(arr[i]);
            }
        }
        else
            q.push(arr[i]);
    }
    return q.top();
}

//https://www.naukri.com/code360/problems/count-distinct-element-in-every-k-size-window_920336
vector<int> countDistinctElements(vector<int> &arr, int k)
{
    vector<int> ans;
    unordered_map<int, int> m;
    for (int i = 0; i < k; i++)
    {
        auto iter = m.find(arr[i]);
        if (iter == m.end())
        {
            m.insert({arr[i], 1});
        }
        else
            iter->second++;
    }
    ans.push_back(m.size());
    int back = 0;
    auto iter = m.find(arr[back++]);
    if (iter->second > 1)
        iter->second--;
    else
    {
        m.erase(iter);
    }
    for (int i = k; i < arr.size(); i++)
    {
        auto iter = m.find(arr[i]);
        if (iter == m.end())
        {
            m.insert({arr[i], 1});
        }
        else
        {
            iter->second++;
        }
        ans.push_back(m.size());
        iter = m.find(arr[back++]);
        if (iter->second > 1)
            iter->second--;
        else
        {
            m.erase(iter);
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/dfs-traversal_630462
class DFS
{
  private:
    void dfs(vector<vector<int>> &graph, vector<bool> &visited, const int i, vector<int> &res)
    {
        visited[i] = true;
        res.push_back(i);
        for (int j = 0; j < graph[i].size(); j++)
        {
            if (visited[graph[i][j]] == false)
            {
                dfs(graph, visited, graph[i][j], res);
            }
        }
    }

  public:
    vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>> &edges)
    {
        vector<vector<int>> graph(V);
        for (int e = 0; e < E; e++)
        {
            graph[edges[e][0]].push_back(edges[e][1]);
            graph[edges[e][1]].push_back(edges[e][0]);
        }
        vector<vector<int>> ans;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == false)
            {
                vector<int> res;
                dfs(graph, visited, i, res);
                ans.push_back(res);
            }
        }
        return ans;
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

    {
        string testcase[] = {"abcd", "abcba", "abccbc", "qweeq", "babcbabcbaccba", "abacdfgdcaba", "codingninjas",
                             "zzzzzzzzzzzzzzzzzzzzzzwwwwwwwwwwwwwwwwwyyyyyyyyyyyyyyyyyyydddddddddddddddddddddddddddddddddddddddddd"};
        for (int i = 0; i < sizeof(testcase) / sizeof(string); i++)
            std::cout << "longestPalinSubstring:" << longestPalinSubstring(testcase[i]) << std::endl;
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

    {
        vector<int> num = {1, 2, 3};
        MinElements m;
        std::cout << "minimumElements:" << m.minimumElements2(num, 7) << std::endl;

        num = {1, 9, 10};
        std::cout << "minimumElements:" << m.minimumElements2(num, 7) << std::endl;
    }

    {
        MergeSort m;
        vector<int> arr = {3, 4, 1, 6, 2, 5, 7};
        m.mergeSort(arr, 0, arr.size() - 1);
        for (auto i : arr)
        {
            printf("%d ", i);
        }
        std::cout << std::endl;
    }

    {
        string str1("tsoqqppopp");
        string str2("tsoprr");
        std::cout << "Longest Common Substring:" << lcs(str1, str2) << std::endl;

        string s("adebc");
        string t("dcadb");
        std::cout << "Longest Common Substring:" << lcs2(s, t) << std::endl;
    }

    {
        vector<vector<int>> grid = {{8, 1, 6},
                                    {4, 4, 16},
                                    {2, 7, 20},
                                    {20, 7, 20}};
        std::cout << "minSumPath:" << minSumPath(grid) << std::endl;
    }

    {
        std::cout << "matrix[3][4] uniquePaths:" << uniquePaths(3, 4) << std::endl;
    }

    {
        vector<vector<int>> points = {{1, 2, 5}, {3, 1, 1}, {3, 3, 3}};
        std::cout << "ninjaTraining:" << ninjaTraining(points.size(), points) << std::endl;
    }

    {
        vector<int> arr = {1, 1, 2, 2, 3, 3, 6, 6, 7, 9, 9};
        std::cout << "getSingleElement:" << getSingleElement(arr) << std::endl;
    }

    {
        vector<int> arr = {3, 4, 4, 4, 4, 5, 5, 5, 6};
        FirstLastPos flp;
        pair<int, int> pos = flp.firstAndLastPosition(arr, arr.size(), 5);
        printf("firstAndLastPosition:[%d,%d]\n", pos.first, pos.second);
    }
    {
        vector<int> arr = {1, 4, 9, 2, 9, 10, 6};
        NextGreaterElement nge;
        vector<int> rv = nge.nextGreaterElement(arr, arr.size());
        std::cout << "Next Greater Element:";
        for (auto i : rv)
        {
            printf("%d ", i);
        }
        std::cout << std::endl;
    }
    {
        Search_In_Rotated_Sorted_Array s;
        vector<int> arr = {11, 13, 5, 8, 9, 10};
        std::cout << "Search In Rotated Sorted Array:" << s.search(arr, arr.size(), 5) << std::endl;
    }
    {
        vector<int> arr = {100, 4, 200, 1, 3, 2};
        Longest_Consecutive_Sequence lcs;
        std::cout << "Longest Consecutive Sequence:" << lcs.lengthOfLongestConsecutiveSequence(arr, arr.size()) << std::endl;
    }
    {
        vector<vector<int>> arr = {{1, 5, 9}, {45, 90}, {2, 6, 78, 100, 234}};
        Merge_K_Sorted_Arrays merge;
        vector<int> rv = merge.mergeKSortedArrays(arr, arr.size());
        printf("Merge K Sorted Arrays:");
        for (auto i : rv)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        MinStack ms;
        ms.push(1);
        ms.push(2);
        ms.getMin();
        ms.pop();
        ms.top();
        ms.getMin();
    }
    {
        vector<vector<int>> arr = {{7, 9, 3}, {4, 2, 0}, {5, 6, 7}};
        Set_Matrix_Zeros smz;
        smz.setZeros(arr);
        for (auto i : arr)
        {
            for (auto j : i)
            {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    {
        vector<int> nums = {1, 5, 10, 100, 10, 5};
        printf("Maximum sum of non-adjacent elements:%d\n", maximumNonAdjacentSum(nums));
    }
    {
        vector<int> nums = {3, 4, 6, 9, 5, 1, 7, 8};
        KthLargestElement k;
        printf("Kth largest element:%d\n", k.findKthLargest(nums, 4));
    }
    {
        vector<int> arr = {3, 1, 2, 4};
        ConsecutiveElements c;
        printf("Consecutive elements:%d\n", c.isConsecutive(arr, arr.size()));
    }
    {
        vector<int> arr = {3, 4, 5, 6, 7};
        printf("Consecutive elements:%d\n", isConsecutive(arr, arr.size()));
    }
    {
        int arr[] = {3, 5, 1, 3, 1, 6, 2, 7};
        printf("Fourth Largest Element in the Array:%d\n", getFourthLargest(arr, sizeof(arr) / sizeof(int)));
    }
    {
        vector<int> arr = {3, 5, 1, 3, 1, 6, 2, 7};
        printf("Kth largest element in the unsorted array:%d\n", kthLargest(arr, arr.size(), 4));
    }
    {
        vector<int> arr = {1, 2, 1, 3, 4, 2, 3};
        vector<int> ans = countDistinctElements(arr, 3);
        printf("Count Distinct Element in Every K Size Window:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<vector<int>> mat = {{1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
        printf("Matrix Flip Bit:%d\n", countFlip(mat));
    }
    {
        vector<vector<int>> edges = {
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0},
            {6, 0},
            {7, 0},
            {8, 0},
            {9, 0},
        };
        DFS dfs;
        vector<vector<int>> ans = dfs.depthFirstSearch(10, 9, edges);
        printf("DFS Traversal:");
        for (auto i : ans)
        {
            for (auto j : i)
            {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
    return 0;
}
