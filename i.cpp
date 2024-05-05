#include <bits/stdc++.h>
#include <vector>
using namespace std;

template <typename T>
class TreeNode
{
  private:
    bool bubble;

  public:
    T val;
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T val)
    {
        this->val = val;
        this->data = val;
        this->bubble = false;
        left = NULL;
        right = NULL;
    }

    TreeNode()
    {
        this->val = -1;
        this->data = -1;
        this->bubble = true;
        left = NULL;
        right = NULL;
    }

    bool isBubble()
    {
        return bubble;
    }

    vector<T> toVector()
    {
        vector<T> ans;
        queue<TreeNode<T> *> q;
        q.push(this);
        while (q.empty() == false)
        {
            TreeNode<T> *temp = q.front();
            q.pop();
            ans.push_back(temp->data);
            if (temp->isBubble())
            {
                continue;
            }
            if (temp->left != NULL)
                q.push(temp->left);
            else
            {
                TreeNode<T> *bubble = new TreeNode<T>();
                q.push(bubble);
            }
            if (temp->right != NULL)
                q.push(temp->right);
            else
            {
                TreeNode<T> *bubble = new TreeNode<T>();
                q.push(bubble);
            }
        }
        return ans;
    }

    static TreeNode<T> *buildTree(vector<T> &arr)
    {
        return buildTree(std::move(arr));
    }

    static TreeNode<T> *buildTree(vector<T> &&arr)
    {
        int i = 0;
        TreeNode<T> *root = new TreeNode<T>(arr[i++]);
        queue<TreeNode<T> *> q;
        q.push(root);
        while (q.empty() == false)
        {
            TreeNode<T> *temp = q.front();
            q.pop();
            if (arr[i] != -1 && arr[i] != '#')
            {
                temp->left = new TreeNode<T>(arr[i++]);
                q.push(temp->left);
            }
            else
            {
                i++;
            }
            if (arr[i] != -1 && arr[i] != '#')
            {
                temp->right = new TreeNode<T>(arr[i++]);
                q.push(temp->right);
            }
            else
            {
                i++;
            }
        }
        return root;
    }
};

class Binary_Tree_Pruning
{
  private:
    bool prune(TreeNode<int> *root)
    {
        if (root == NULL)
            return true;
        bool l = prune(root->left);
        bool r = prune(root->right);
        if (l)
        {
            if (root->left)
            {
                delete root->left;
                root->left = NULL;
            }
        }
        if (r)
        {
            if (root->right)
            {
                delete root->right;
                root->right = NULL;
            }
        }
        return l & r & root->val == 0;
    }

  public:
    TreeNode<int> *binaryTreePruning(TreeNode<int> *root)
    {
        if (prune(root))
        {
            if (root)
            {
                delete root;
                return NULL;
            }
        }
        return root;
    }
};

// https://www.naukri.com/code360/problems/rotate-function_1264290
// Power(k) = 0 * Ck[0] + 1 * Ck[1] + ... + (n - 1) * Ck[n - 1]
// Sum(k) = Ck[0] + Ck[1] + ... + Ck[n - 1]
// PowerSum(k) = Power(k) + Sum(k) = 1 * Ck[0] + 2 * Ck[1] + ... + n * Ck[n - 1]
// PowerSum(k) - n *Ck[n - 1] = 0 * Ck[n - 1] + 1 * Ck[0] + 2 * Ck[1] + ... + (n - 1) * Ck[n - 2]
int maxRotateFunction(vector<int> &arr)
{
    int n = arr.size();
    int powerSum = 0;
    for (int i = 0; i < n; i++)
    {
        powerSum += arr[i] * i;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    int ans = powerSum;
    int total = arr.size();
    for (int i = n - 1; i > 0; i--)
    {
        powerSum = powerSum + sum - arr[i] * total;
        ans = max(ans, powerSum);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/convert-a-binary-tree-to-its-sum-tree_920395
class Convert_Binary_Tree_Sum_Tree
{
  private:
    int sum(TreeNode<int> *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int sumL = sum(root->left);
        int sumR = sum(root->right);
        int rv = sumL + sumR + root->data;
        root->data = sumL + sumR;
        return rv;
    }

  public:
    TreeNode<int> *convertToSumTree(TreeNode<int> *root)
    {
        if (root != NULL)
            sum(root);
        return root;
    }
};

// https://www.naukri.com/code360/problems/longest-substring-without-repeating-characters_758894
// cisco longest substring
int lengthOfLongestSubstring(string &s)
{
    if (s.empty() == true)
        return 0;
    int q = 0, p = 1;
    int ans = 0;
    while (p < s.length())
    {
        ans = max(ans, p - q);
        string temp(&s[q], p - q);
        size_t i = temp.find(s[p]);
        if (i != string::npos)
        {
            q += i + 1;
        }
        p++;
    }
    return ans;
}

// https://www.naukri.com/code360/problems/longest-repeating-subsequence_1118110
// https://www.geeksforgeeks.org/longest-repeating-subsequence/
int longestRepeatingSubsequence(string st, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (st[i - 1] == st[j - 1] && i != j)
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][n];
}

// https://www.naukri.com/code360/problems/longest-repeating-substring_980523
int longestRepeatingSubstring(string &str, int k)
{
    int countArray[26] = {0};
    int left = 0;
    int ans = 0;
    int maxCount = INT_MIN;
    for (int right = 0; right < str.size(); right++)
    {
        countArray[str[right] - 'A']++;
        maxCount = max(maxCount, countArray[str[right] - 'A']);
        if (right - left + 1 - maxCount > k)
        {
            countArray[str[left] - 'A']--;
            left++;
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}

int main(int argc, char *argv[])
{
    {
        vector<int> arr = {4, 3, 2, 6};
        printf("Rotate Function:%d\n", maxRotateFunction(arr));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, 1, 1, 0, 1, 0, 1, 0, 0,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1});
        Binary_Tree_Pruning p;
        root = p.binaryTreePruning(root);
        vector<int> ans = root->toVector();
        printf("Binary Tree Pruning:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, -2, 1, 3, 1, -1, -1, -1, -1, -1, -1});
        Convert_Binary_Tree_Sum_Tree c;
        root = c.convertToSumTree(root);
        vector<int> ans = root->toVector();
        printf("Convert a binary tree to its sum tree:");
        for (auto i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        string s("axbab 9xbb");
        printf("Longest Substring Without Repeating Characters:%d\n", lengthOfLongestSubstring(s));
    }
    {
        string st("AABCBDC");
        printf("Longest Repeating Subsequence:%d\n", longestRepeatingSubsequence(st, st.length()));
    }
    {
        string str("ABCCAA");
        printf("Longest Repeating Substring:%d\n", longestRepeatingSubstring(str, 2));
    }
    return 0;
}
