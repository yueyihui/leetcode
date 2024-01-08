#include <iostream>
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

    return 0;
}
