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

class Node
{
  public:
    int data;
    Node *next;
    Node *child;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
        this->child = NULL;
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

// https://www.naukri.com/code360/problems/invert-a-binary-tree_1281382
class Invert_Binary_Tree
{
  private:
    bool storeParents(TreeNode<int> *root, stack<TreeNode<int> *> &parents, TreeNode<int> *leaf)
    {
        parents.push(root);

        if (!root->left and !root->right)
        {
            if (root->data == leaf->data)
                return true;
            else
                parents.pop();
            return false;
        }

        if (root->left)
        {
            if (storeParents(root->left, parents, leaf))
                return true;
        }

        if (root->right)
        {
            if (storeParents(root->right, parents, leaf))
                return true;
        }

        parents.pop();
        return false;
    }

  public:
    TreeNode<int> *invertBinaryTree(TreeNode<int> *root, TreeNode<int> *leaf)
    {
        if (!root)
            return NULL;

        stack<TreeNode<int> *> parents;
        storeParents(root, parents, leaf);

        TreeNode<int> *head = parents.top();
        parents.pop();

        TreeNode<int> *par = head;
        while (!parents.empty())
        {
            auto p = parents.top();
            parents.pop();

            if (p->right == head)
            {
                p->right = p->left;
                p->left = NULL;
            }
            else
            {
                p->left = NULL;
            }

            head->left = p;
            head = p;
        }

        return par;
    }
};

class DSU
{
  private:
    int *parent;
    int *rank;

  public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int find(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }
    void _union(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (a < b)
                swap(a, b);
            parent[b] = a;
            rank[a]++;
        }
    }
};

// https://www.naukri.com/code360/problems/minimum-spanning-tree_631769
int minimumSpanningTree(vector<vector<int>> &edges, int n)
{
    sort(edges.begin(), edges.end(),
         [](vector<int> &a, vector<int> &b) -> bool
         { return a[2] < b[2]; });
    DSU dsu(n);
    int ans = 0;
    for (auto edge : edges)
    {
        int x = edge[0];
        int y = edge[1];
        int w = edge[2];
        if (dsu.find(x) != dsu.find(y))
        {
            dsu._union(x, y);
            ans += w;
        }
    }
    return ans;
}

// https://www.naukri.com/code360/problems/flatten-linked-list_893175
Node *flattenLL(Node *head)
{
    if (head == NULL)
        return head;
    Node *tail = NULL;
    queue<Node *> q;
    q.push(head);
    while (q.empty() == false)
    {
        Node *temp = q.front();
        q.pop();
        if (tail)
        {
            tail->next = temp;
        }
        while (temp)
        {
            tail = temp;
            if (temp->child)
            {
                q.push(temp->child);
                temp->child = NULL;
            }
            temp = temp->next;
        }
    }
    return head;
}

// https://www.naukri.com/code360/problems/flatten-linked-list_893175
Node *flattenLL1(Node *head)
{
    if (!head)
        return nullptr;
    std::queue<Node *> q;
    Node *current = head;
    while (current)
    {
        if (current->child)
        {
            q.push(current->child);
            current->child = nullptr;
        }
        if (!current->next && !q.empty())
        {
            current->next = q.front();
            q.pop();
        }
        current = current->next;
    }
    return head;
}

// https://www.naukri.com/code360/problems/insertion-in-circular-linked-list_4609562
Node *insert(int k, int val, Node *head)
{
    Node *last = head->next;
    while (last->next != head)
    {
        last = last->next;
    }
    if (k == 0)
    {
        Node *temp = new Node(val);
        temp->next = head;
        last->next = temp;
        return temp;
    }
    else
    {
        Node *pre = last;
        Node *n = head;
        for (int i = 0; i < k; i++)
        {
            pre = n;
            n = n->next;
        }
        Node *temp = new Node(val);
        pre->next = temp;
        temp->next = n;
        return head;
    }
}

// https://www.naukri.com/code360/problems/reverse-a-sublist-of-linked-list_1092613
Node *reverseSublist(Node *head, int x, int y)
{
    Node dummy(0);
    dummy.next = head;
    Node *prev = &dummy;
    for (int i = 1; i < x; i++)
    {
        prev = prev->next;
    }
    Node *a = prev->next;
    Node *b = a->next;
    for (int i = 0; i < y - x; i++)
    {
        a->next = b->next;
        b->next = prev->next;
        prev->next = b;
        b = a->next;
    }
    return dummy.next;
}

class MaxStack
{
  private:
    stack<int> st;
    int maxEle;

  public:
    int getMax() { return maxEle; }
    void pop()
    {
        if (st.empty())
            return;
        int t = st.top();
        st.pop();
        if (t > maxEle)
        {
            maxEle = 2 * maxEle - t;
        }
    }
    void push(int x)
    {
        if (st.empty())
        {
            maxEle = x;
            st.push(x);
            return;
        }
        if (x > maxEle)
        {
            st.push(2 * x - maxEle);
            maxEle = x;
        }
        else
            st.push(x);
    }
    bool empty() { return st.empty(); }
};

// https://www.naukri.com/code360/problems/king-nodes-in-binary-tree_2191536
class King_Nodes_In_Binary_Tree
{
  private:
    void preorder(BinaryTreeNode<int> *root, MaxStack &st, int &nodes)
    {
        if (root == NULL)
            return;

        if (st.empty() || root->data >= st.getMax())
        {
            nodes++;
        }
        st.push(root->data);
        preorder(root->left, st, nodes);
        preorder(root->right, st, nodes);
        st.pop();
    }

  public:
    int CountKingNodes(BinaryTreeNode<int> *root)
    {
        MaxStack st;
        int nodes = 0;
        preorder(root, st, nodes);
        return nodes;
    }
};

int main(int argc, char *argv[])
{
    return 0;
}
