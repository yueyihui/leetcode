#include <bits/stdc++.h>
using namespace std;

template <typename T>
class TreeNode
{
    TreeNode<T> **children;
    int childCount;

  public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T data);
    int numChildren();
    void addChild(TreeNode<T> *child);
    TreeNode<T> *getChild(int index);
    void setChild(int index, TreeNode<T> *child);
};

template <typename T>
class BinaryTreeNode
{
  public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

// https://www.naukri.com/code360/problems/count-special-nodes-in-generic-tree_630522
class Count_Special_Nodes_In_Generic_Tree
{
  private:
    void solve(TreeNode<int> *root, unordered_set<int> &s, int &cnt)
    {
        if (root == NULL)
            return;
        auto it = s.find(root->data);
        if (it != s.end())
            return;
        else
        {
            s.insert(root->data);
            cnt++;
        }
        for (int i = 0; i < root->numChildren(); i++)
            solve(root->getChild(i), s, cnt);

        s.erase(root->data);
    }

  public:
    int countSpecialNodes(TreeNode<int> *root)
    {
        unordered_set<int> s;
        int cnt = 0;
        solve(root, s, cnt);
        return cnt;
    }
};

// https://www.naukri.com/code360/problems/maximum-sum-path-of-a-binary-tree_1214968
class Maximum_Sum_Path_Of_A_Binary_Tree
{
  private:
    int solve(BinaryTreeNode<int> *root, int &a)
    {
        if (root == NULL)
            return 0;
        int l = max(0, solve(root->left, a));
        int r = max(0, solve(root->right, a));
        a = max(a, l + r + root->data);
        return max(l, r) + root->data;
    }

  public:
    int maxPathSum(BinaryTreeNode<int> *root)
    {
        int ans = INT_MIN;
        solve(root, ans);
        return ans;
    }
};

// https://www.naukri.com/code360/problems/binary-tree-maximum-path-sum_1280142
class Binary_Tree_Maximum_Path_Sum
{
  private:
    int _maxPathSum(TreeNode<int> *root, int &sum)
    {
        if (root == NULL)
            return 0;
        int l = max(0, _maxPathSum(root->left, sum));
        int r = max(0, _maxPathSum(root->right, sum));
        sum = max(sum, l + r + root->data);
        return max(l, r) + root->data;
    }

  public:
    int maxPathSum(TreeNode<int> *root)
    {
        int sum = INT_MIN;
        _maxPathSum(root, sum);
        return sum;
    }
};

class DisjointSetUnion
{
  private:
    std::vector<int> parent;
    std::vector<int> rank;

  public:
    DisjointSetUnion(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// https://www.naukri.com/code360/problems/graph-valid-tree_1376618
bool checkgraph(vector<vector<int>> edges, int n, int m)
{
    if (m != n - 1)
        return false;
    DisjointSetUnion dsu(n);
    for (int i = 0; i < m; i++)
    {
        int a = dsu.find(edges[i][0]);
        int b = dsu.find(edges[i][1]);
        if (a == b)
            return false;
        else
            dsu.unionSets(edges[i][0], edges[i][1]);
    }
    return true;
}

int main(int argc, char *argv[])
{
    return 0;
}
