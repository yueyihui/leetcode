#include <bits/stdc++.h>
using namespace std;

template <typename T>
class TreeNode
{
  public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    static void preorder(TreeNode<T> *root)
    {
        if (root == NULL)
            return;
        printf(" %d", root->data);
        preorder(root->left);
        preorder(root->right);
    }
    static TreeNode<T> *buildTree(vector<T> &arr, T i)
    {
        if (i >= arr.size())
            return NULL;
        if (arr[i] == -1)
            return NULL;
        TreeNode<T> *root = new TreeNode<T>(arr[i]);
        root->left = buildTree(arr, 2 * i + 1);
        root->right = buildTree(arr, 2 * i + 2);
        return root;
    }
    static TreeNode<T> *buildTree(vector<T> &&arr, T i)
    {
        if (i >= arr.size())
            return NULL;
        if (arr[i] == -1)
            return NULL;
        TreeNode<T> *root = new TreeNode<T>(arr[i]);
        root->left = buildTree(arr, 2 * i + 1);
        root->right = buildTree(arr, 2 * i + 2);
        return root;
    }
};

//https://www.codingninjas.com/studio/problems/break-number_759411?interviewProblemRedirection=true&count=25&search=&company%5B%5D=Apple&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav
class BreakNumber
{
  private:
    void _breakNumber(int n, int i, vector<vector<int>> &res, vector<int> &r)
    {
        if (n == 0)
        {
            res.push_back(r);
            return;
        }
        while (n - i >= 0)
        {
            r.push_back(i);
            _breakNumber(n - i, i, res, r);
            i++;
            r.pop_back();
        }
    }

  public:
    vector<vector<int>> breakNumber(int n)
    {
        vector<int> r;
        vector<vector<int>> res;
        _breakNumber(n, 1, res, r);
        return res;
    }
};

class InorderPreorder
{
  private:
    int getIndex(int *arr, int n, int x)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == x)
                return i;
        }
        return -1;
    }

    TreeNode<int> *build(int *inorder, int insize, int *preorder, int presize)
    {
        if (presize == 0)
            return NULL;
        TreeNode<int> *root = new TreeNode<int>(preorder[0]);
        int rootIndex = getIndex(inorder, insize, preorder[0]);
        int inorder_left_size = rootIndex;
        int inorder_right_size = insize - (rootIndex + 1);
        root->left = build(inorder, inorder_left_size, preorder + 1, inorder_left_size);
        root->right = build(inorder + rootIndex + 1, inorder_right_size, preorder + 1 + inorder_left_size, inorder_right_size);
        return root;
    }

  public:
    TreeNode<int> *buildBinaryTree(vector<int> &inorder, vector<int> &preorder)
    {
        return build(&inorder[0], inorder.size(), &preorder[0], preorder.size());
    }
};

//https://www.codingninjas.com/studio/problems/flip-equivalent-binary-tree_1234687?interviewProblemRedirection=true&count=25
bool flipEquivalent(TreeNode<int> *root1, TreeNode<int> *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL || root1->data != root2->data)
        return false;

    return flipEquivalent(root1->left, root2->left) && flipEquivalent(root1->right, root2->right) ||
           flipEquivalent(root1->left, root2->right) && flipEquivalent(root1->right, root2->left);
}

//https://www.codingninjas.com/studio/problems/number-of-ways_1062651?interviewProblemRedirection=true&count=25
int countWays(int n)
{
    vector<int> ans(n + 1, 0);
    ans[0] = 1;
    for (int i = 3; i <= n; i++)
        ans[i] += ans[i - 3];
    for (int i = 5; i <= n; i++)
        ans[i] += ans[i - 5];
    for (int i = 10; i <= n; i++)
        ans[i] += ans[i - 10];
    return ans[n];
}

class LargestTreeValue
{
  private:
    int height(TreeNode<int> *root)
    {
        if (root == NULL)
            return 0;
        int a = height(root->left);
        int b = height(root->right);
        return a > b ? a + 1 : b + 1;
    }
    int onLevel(TreeNode<int> *root, int level)
    {
        if (root == NULL)
            return 0;
        if (level == 0)
            return root->data;
        int l = onLevel(root->left, level - 1);
        int r = onLevel(root->right, level - 1);
        return l > r ? l : r;
    }

  public:
    vector<int> largestInRow(TreeNode<int> *root)
    {
        vector<int> res;
        int h = height(root);
        for (int level = 0; level < h; level++)
        {
            res.push_back(onLevel(root, level));
        }
        return res;
    }
};

//https://www.codingninjas.com/studio/problems/inplace-rotate-matrix-90-degree_839734?interviewProblemRedirection=true&count=25
void inplaceRotate(vector<vector<int>> &inputArray)
{
    int n = inputArray.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            swap(inputArray[i][j], inputArray[j][i]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            swap(inputArray[j][i], inputArray[n - 1 - j][i]);
        }
    }
}

class IsItTree
{
  private:
    bool isCyclic(vector<vector<int>> &adj, int V, vector<bool> &visited, int v, int from)
    {
        visited[v] = true;
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (visited[adj[v][i]] == false)
            {
                if (isCyclic(adj, V, visited, adj[v][i], v))
                {
                    return true;
                }
            }
            else if (adj[v][i] != from)
            {
                return true;
            }
        }
        return false;
    }

  public:
    bool isTree(vector<vector<int>> &adj, int V)
    {
        vector<bool> visited(V, false);
        if (isCyclic(adj, V, visited, 0, -1))
        {
            return false;
        }
        for (auto i : visited)
        {
            if (i == false)
            {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    {
        BreakNumber b;
        auto res = b.breakNumber(4);
        printf("breakNumber:\n");
        for (auto i : res)
        {
            for (auto j : i)
            {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    {
        vector<int> inorder = {4, 2, 7, 1, 3};
        vector<int> preorder = {1, 2, 4, 7, 3};
        InorderPreorder ip;
        TreeNode<int> *root = ip.buildBinaryTree(inorder, preorder);
        printf("preorder:");
        TreeNode<int>::preorder(root);
        printf("\n");
    }
    {
        TreeNode<int> *root1 = TreeNode<int>::buildTree({7, 9, 13, 8, -1, 4, 2}, 0);
        TreeNode<int> *root2 = TreeNode<int>::buildTree({7, 13, 9, 2, 4, 8, -1}, 0);
        std::cout << "flipEquivalent:" << std::boolalpha << flipEquivalent(root1, root2) << std::endl;
    }
    {
        printf("countWays:%d\n", countWays(20));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({13, 10, 7, 4, 9, 12, 8, 4}, 0);
        LargestTreeValue l;
        vector<int> largest = l.largestInRow(root);
        printf("largestInRow:");
        for (auto i : largest)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<vector<int>> arr = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        inplaceRotate(arr);
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
        vector<vector<int>> adj(4);
        adj[0].push_back(1);
        adj[1].push_back(0);
        adj[1].push_back(2);
        adj[2].push_back(1);
        adj[2].push_back(3);
        adj[3].push_back(2);
        IsItTree t;
        std::cout << "isTree:" << t.isTree(adj, adj.size()) << std::endl;
    }
    {
        vector<vector<int>> adj(3);
        adj[0].push_back(1);
        adj[1].push_back(2);
        adj[2].push_back(0);
        IsItTree t;
        std::cout << "isTree:" << t.isTree(adj, adj.size()) << std::endl;
    }
    return 0;
}
