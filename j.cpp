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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
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

// https://www.naukri.com/code360/problems/number-of-islands_985348
class Number_of_Islands
{
  private:
    void bfs(vector<vector<int>> &grid, int n, int m, vector<vector<bool>> &visited,
             int row, int col)
    {
        visited[row][col] = true;
        queue<pair<int, int>> q;
        q.push({row, col});
        while (q.empty() == false)
        {
            pair<int, int> temp = q.front();
            q.pop();
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int row = i + temp.first;
                    int col = j + temp.second;
                    if (row >= 0 && row < n && col >= 0 && col < m &&
                        visited[row][col] == false && grid[row][col] == 1)
                    {
                        visited[row][col] = true;
                        q.push({row, col});
                    }
                }
            }
        }
    }

  public:
    int numberOfIslands(vector<vector<int>> &grid, int n, int m)
    {
        int ans = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] == false && grid[i][j] == 1)
                {
                    ans++;
                    bfs(grid, n, m, visited, i, j);
                }
            }
        }
        return ans;
    }
};

// https://www.naukri.com/code360/problems/largest-island_840701
vector<int> numberOfIslandII(int n, int m, vector<vector<int>> &queries, int q)
{
    int cnt = 0;
    vector<int> ans;
    DSU dsu(n * m);
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i = 0; i < q; i++)
    {
        int row = queries[i][0];
        int col = queries[i][1];
        visited[row][col] = true;
        cnt++;
        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, -1, 0, 1};
        for (int j = 0; j < 4; j++)
        {
            int _row = row + dr[j];
            int _col = col + dc[j];
            if (_row >= 0 && _row < n && _col >= 0 && _col < m)
            {
                if (visited[_row][_col])
                {
                    int nodeNo = m * row + col;
                    int _nodeNo = m * _row + _col;
                    if (dsu.find(nodeNo) != dsu.find(_nodeNo))
                    {
                        dsu._union(nodeNo, _nodeNo);
                        cnt--;
                    }
                }
            }
        }
        ans.push_back(cnt);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/count-islands_3651444
class Count_Islands
{
  private:
    bool bfs(vector<vector<int>> &grid, int n, int m, vector<vector<bool>> &visited,
             int row, int col)
    {
        bool isLand = true;
        visited[row][col] = true;
        queue<pair<int, int>> q;
        q.push({row, col});
        while (q.empty() == false)
        {
            pair<int, int> temp = q.front();
            q.pop();
            int dr[4] = {-1, 0, 1, 0};
            int dc[4] = {0, -1, 0, 1};
            for (int i = 0; i < 4; i++)
            {
                int row = temp.first + dr[i];
                int col = temp.second + dc[i];
                if (row >= 0 && row < n && col >= 0 && col < m && grid[row][col] == 0 &&
                    visited[row][col] == false)
                {
                    visited[row][col] = true;
                    q.push({row, col});
                }
                else if (row < 0 || row >= n || col < 0 || col >= m)
                    isLand = false;
            }
        }
        return isLand;
    }

  public:
    int countIslands(vector<vector<int>> &grid)
    {
        int cnt = 0;
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 0 && visited[i][j] == false)
                {
                    if (bfs(grid, n, m, visited, i, j))
                        cnt++;
                }
            }
        }
        return cnt;
    }
};

// https://www.naukri.com/code360/problems/maximum-in-subarrays-of-length-k_630474
void printSubarrayMax(int *arr, int n, int k)
{
    if (n == 0 || k == 0)
        return;
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < k; i++)
    {
        q.push({arr[i], i});
    }
    cout << q.top().first << " ";
    for (int i = k; i < n; i++)
    {
        q.push({arr[i], i});
        while (q.empty() == false && q.top().second <= i - k)
        {
            q.pop();
        }
        cout << q.top().first << " ";
    }
}

// https://www.naukri.com/code360/problems/sliding-maximum_701652
vector<int> maxSlidingWindow(vector<int> &arr, int n, int k)
{
    deque<int> dq;
    vector<int> vec;
    for (int i = 0; i < n; i++)
    {
        if (dq.empty() == false && dq.front() <= i - k)
            dq.pop_front();
        while (dq.empty() == false && arr[i] > arr[dq.back()])
            dq.pop_back();
        dq.push_back(i);
        if (dq.empty() == false && (i + 1) >= k)
            vec.push_back(arr[dq.front()]);
    }
    return vec;
}

// https://www.naukri.com/code360/problems/k-th-largest-sum-contiguous-subarray_920398
int getKthLargest(vector<int> &arr, int k)
{
    priority_queue<int> q;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            q.push(sum);
        }
    }
    for (int i = 0; i < k - 1; i++)
    {
        q.pop();
    }
    return q.top();
}

// https://www.naukri.com/code360/problems/longest-subset-zero-sum_920321
// https://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
int LongestSubsetWithZeroSum(vector<int> arr)
{
    int n = arr.size();
    int len = 0, sum = 0;
    unordered_map<int, int> map;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        if (sum == 0)
            len = max(len, i + 1);

        auto it = map.find(sum);
        if (it != map.end())
            len = max(len, i - it->second);
        else
            map.insert({sum, i});
    }
    return len;
}

// https://www.naukri.com/code360/problems/print-binary-tree_1266040
class Print_Binary_Tree
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
    void _printTree(TreeNode<int> *root, vector<vector<string>> &print, int row,
                    int l, int r)
    {
        if (root == NULL)
            return;
        int mid = l + (r - l) / 2;
        print[row][mid] = to_string(root->data);
        _printTree(root->left, print, row + 1, l, mid - 1);
        _printTree(root->right, print, row + 1, mid + 1, r);
    }

  public:
    vector<vector<string>> printTree(TreeNode<int> *root)
    {
        int h = height(root);
        int w = pow(2, h) - 1;
        vector<vector<string>> print(h, vector<string>(w, ""));
        _printTree(root, print, 0, 0, w - 1);
        return print;
    }
};

// https://www.naukri.com/code360/problems/binary-tree-cameras_1231013
class Binary_Tree_Cameras
{
  private:
    enum
    {
        NONE,
        INSTALLED,
        BREAK,

    };

    int dfs(TreeNode<int> *root, int &cnt)
    {
        if (root == NULL)
            return BREAK;
        int a = dfs(root->left, cnt);
        int b = dfs(root->right, cnt);
        if (a == NONE || b == NONE)
        {
            cnt++;
            return INSTALLED;
        }
        else if (a == INSTALLED || b == INSTALLED)
            return BREAK;
        else
            return NONE;
    }

  public:
    int getMinCamera(TreeNode<int> *root)
    {
        int cnt = 0;
        if (dfs(root, cnt) == NONE)
        {
            cnt++;
        }
        return cnt;
    }
};

// https://www.naukri.com/code360/problems/binary-tree-to-a-circular-doubly-linked-list_920535
class Binary_Tree_To_Circular_Doubly_Linked_List
{
  private:
    void inorder(TreeNode<int> *root, vector<TreeNode<int> *> &vec)
    {
        if (root == NULL)
            return;
        inorder(root->left, vec);
        vec.push_back(root);
        inorder(root->right, vec);
    }

  public:
    TreeNode<int> *binaryTreeToCircularDLL(TreeNode<int> *root)
    {
        vector<TreeNode<int> *> vec;
        inorder(root, vec);
        int n = vec.size();
        TreeNode<int> *prev = vec[0];
        for (int i = 1; i < n; i++)
        {
            vec[i]->left = prev;
            prev->right = vec[i];
            prev = vec[i];
        }
        prev->right = vec[0];
        vec[0]->left = prev;
        prev = vec[0];
        return prev;
    }
};

// https://www.naukri.com/code360/problems/second-minimum-node-in-a-binary-tree_1376617
class Second_Minimum_Node_In_Binary_Tree
{
  private:
    void preorder(TreeNode<int> *root, int &min, int &second)
    {
        if (root == NULL)
            return;
        if (root->data < min)
        {
            second = min;
            min = root->data;
        }
        else if (min < root->data && root->data < second)
        {
            second = root->data;
        }
        preorder(root->left, min, second);
        preorder(root->right, min, second);
    }

  public:
    int secondMinimumNode(TreeNode<int> *root)
    {
        if (root == NULL)
            return -1;
        int min = INT_MAX, second = INT_MAX;
        preorder(root, min, second);
        if (second == INT_MAX)
            return -1;
        return second;
    }
};

// https://www.naukri.com/code360/problems/maximum-tree_1266104
class Maximum_Binary_Tree
{
  private:
    int findIndex(vector<int> tree, int l, int r)
    {
        int maxi = INT_MIN;
        int idx = -1;
        for (int i = l; i <= r; i++)
        {
            if (tree[i] > maxi)
            {
                maxi = tree[i];
                idx = i;
            }
        }
        return idx;
    }

    BinaryTreeNode<int> *preorder(vector<int> tree, int l, int r)
    {
        if (l > r)
        {
            return NULL;
        }
        int idx = findIndex(tree, l, r);
        BinaryTreeNode<int> *node = new BinaryTreeNode<int>(tree[idx]);
        node->left = preorder(tree, l, idx - 1);
        node->right = preorder(tree, idx + 1, r);
        return node;
    }

  public:
    BinaryTreeNode<int> *constructMaximumBinaryTree(vector<int> &tree, int n)
    {
        return preorder(tree, 0, n - 1);
    }
};

// https://www.naukri.com/code360/problems/construct-binary-tree-from-inorder-and-postorder-traversal_1266106
class Construct_Binary_Tree_from_Inorder_Postorder
{
  private:
    int findIndex(vector<int> &vec, int val)
    {
        for (int i = 0; i < vec.size(); i++)
            if (vec[i] == val)
                return i;
        return -1;
    }

    TreeNode<int> *build(vector<int> &postOrder, int post_l, int post_r,
                         vector<int> &inOrder, int in_l, int in_r)
    {
        if (post_l > post_r || in_l > in_r)
            return NULL;
        int val = postOrder[post_r];
        TreeNode<int> *root = new TreeNode<int>(val);
        int idx = findIndex(inOrder, val);
        int left_num = idx - in_l;
        root->left =
            build(postOrder, post_l, post_l + left_num - 1, inOrder, in_l, idx - 1);
        root->right =
            build(postOrder, post_l + left_num, post_r - 1, inOrder, idx + 1, in_r);
        return root;
    }

  public:
    TreeNode<int> *getTreeFromPostorderAndInorder(vector<int> &postOrder,
                                                  vector<int> &inOrder)
    {
        if (inOrder.size() != postOrder.size() || inOrder.size() == 0)
        {
            return nullptr;
        }

        return build(postOrder, 0, postOrder.size() - 1, inOrder, 0,
                     inOrder.size() - 1);
    }
};

// https://www.naukri.com/code360/problems/sort-using-stack_2542082
// https://www.geeksforgeeks.org/sort-stack-using-temporary-stack/
// https://www.naukri.com/code360/problems/sorting-the-stack-recursively_1868989
// two stack
vector<int> sortArray(vector<int> &arr)
{
    stack<int> st;
    while (arr.empty() == false)
    {
        int b = arr.back();
        arr.pop_back();
        while (st.empty() == false && st.top() < b)
        {
            arr.push_back(st.top());
            st.pop();
        }
        st.push(b);
    }
    while (st.empty() == false)
    {
        arr.push_back(st.top());
        st.pop();
    }
    return arr;
}

// https://www.naukri.com/code360/problems/colour-the-graph_13022
class Colour_The_Graph
{
  private:
    bool bfs(vector<vector<int>> &adj, vector<int> &color, int v)
    {
        color[v] = 1;
        queue<int> q;
        q.push(v);
        while (q.empty() == false)
        {
            int v = q.front();
            q.pop();
            for (int i = 0; i < adj[v].size(); i++)
            {
                int node = adj[v][i];
                if (color[node] == 0)
                {
                    color[node] = -color[v];
                    q.push(node);
                }
                else if (color[node] == color[v])
                    return false;
            }
        }
        return true;
    }

    bool doColor(vector<vector<int>> &adj, int n, int m)
    {
        vector<int> color(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            if (color[i] == 0)
            {
                if (bfs(adj, color, i) == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

// https://www.naukri.com/code360/problems/compress-the-string_526
string getCompressedString(string &input)
{
    string res;
    int cnt = 1;
    int q = 0, p = 1;
    int n = input.length();
    while (p < n)
    {
        if (input[q] != input[p])
        {
            res.push_back(input[q]);
            q = p;
            if (cnt > 1)
            {
                res += to_string(cnt);
                cnt = 1;
            }
        }
        else
            cnt++;
        p++;
    }
    res.push_back(input[q]);
    if (cnt > 1)
    {
        res += to_string(cnt);
    }
    return res;
}

// https://www.naukri.com/code360/problems/number-pattern_893203
vector<vector<int>> numberPattern(int n)
{
    vector<vector<int>> ans;
    int num = 1;
    for (int i = n; i > 0; i--)
    {
        vector<int> temp;
        for (int j = 0; j < i - 1; j++)
        {
            temp.push_back(-1);
        }
        for (int k = 0; k <= n - i; k++)
        {
            if (num > 9)
                num = 1;
            temp.push_back(num++);
        }
        ans.push_back(temp);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/next-greater-element_799354
vector<int> nextGreater(vector<int> &arr, int n)
{
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (st.empty() == false && st.top() <= arr[i])
        {
            st.pop();
        }
        if (st.empty() == false)
            ans[i] = st.top();
        st.push(arr[i]);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/stock-span_5243295
vector<int> findStockSpans(vector<int> &prices)
{
    int n = prices.size();
    vector<int> span(n, 1);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        int _span = span[i];
        while (st.empty() == false && prices[i] > prices[st.top()])
        {
            int t = st.top();
            st.pop();
            _span += span[t];
        }
        span[i] = _span;
        st.push(i);
    }
    return span;
}

//https://www.naukri.com/code360/problems/painter-s-partition-problem_1089557
class Painter_Partition_Problem {
    private:
	bool isPossible(vector<int> &boards, int k, int mid)
	{
		int painter = 1, sum = 0;
		for (int i = 0; i < boards.size(); i++) {
			if (sum + boards[i] <= mid) {
				sum += boards[i];

			} else {
				painter++;
				if (painter > k || boards[i] > mid) {
					return false;
				}
				sum = boards[i];
			}
		}
		return true;
	}

    public:
	int findLargestMinDistance(vector<int> &boards, int k)
	{
		int sum = 0;
		for (int i = 0; i < boards.size(); i++) {
			sum += boards[i];
		}
		int ans = 0;
		int l = 0, r = sum;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (isPossible(boards, k, mid)) {
				ans = mid;
				r = mid - 1;

			} else {
				l = mid + 1;
			}
		}
		return ans;
	}
};

// https://www.naukri.com/code360/problems/tree-ordering_3119013
// https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/
class Tree_ordering
{
  private:
    bool preorder(TreeNode<int> *root, vector<int> &A, int &i, vector<int> &flip)
    {
        if (root == NULL)
        {
            i--;
            return true;
        }
        if (root->data != A[i])
            return false;
        if (root->left && root->left->data != A[i + 1])
        {
            swap(root->left, root->right);
            flip.push_back(root->data);
        }
        return preorder(root->left, A, ++i, flip) &&
               preorder(root->right, A, ++i, flip);
    }

  public:
    vector<int> treeOrdering(TreeNode<int> *root, vector<int> A)
    {
        int i = 0;
        vector<int> flip;
        if (preorder(root, A, i, flip) == false)
            return {-1};
        return flip;
    }
};

//https://www.naukri.com/code360/problems/modify-linked-list_1095632
Node *modifyLL(Node *head)
{
	deque<Node *> dq;
	while (head != NULL) {
		Node *n = head->next;
		head->next = NULL;
		dq.push_back(head);
		head = n;
	}
	Node temp(0);
	head = &temp;
	while (dq.size() >= 2) {
		Node *a[2] = { NULL };
		a[0] = dq.front();
		dq.pop_front();
		a[1] = dq.back();
		dq.pop_back();
		for (int i = 0; i < 2; i++) {
			head->next = a[i];
			head = head->next;
		}
	}
	if (dq.empty() == false) {
		Node *a = dq.front();
		dq.pop_front();
		head->next = a;
	}
	return temp.next;
}

// https://www.naukri.com/code360/problems/unique-subsets_3625236
class Subsets_II
{
  private:
    void solve(vector<int> &arr, int i, vector<vector<int>> &vv, vector<int> &v)
    {
        if (i == arr.size())
        {
            vv.push_back(v);
            return;
        }

        v.push_back(arr[i]);
        solve(arr, i + 1, vv, v);
        v.pop_back();
        while (i + 1 < arr.size() && arr[i] == arr[i + 1])
        {
            i++;
        }
        solve(arr, i + 1, vv, v);
    }

  public:
    vector<vector<int>> uniqueSubsets(int n, vector<int> &arr)
    {
        sort(arr.begin(), arr.end());
        vector<vector<int>> vv;
        vector<int> v;
        solve(arr, 0, vv, v);
        sort(vv.begin(), vv.end());
        return vv;
    }
};

// https://leetcode.com/problems/convert-to-base-2/
// int to bin base -2
string baseNeg2(int n)
{
	if (n == 0)
		return "0";
	int base = -2;
	string result;
	while (n != 0) {
		int rem = n % base;
		n = n / base;
		if (rem < 0) {
			rem += -base;
			n += 1;
		}
		result = to_string(rem) + result;
	}
	return result;
}

//https://leetcode.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s)
{
	int n = s.length();
	if (n == 0)
		return 0;
	int r = 0;
	int len = INT_MIN;
	string temp;
	while (r < n) {
		char c = s[r];
		auto pos = temp.find(c);
		if (pos == string::npos) {
			temp.push_back(c);
			len = max(len, (int)temp.length());
			r++;

		} else {
			temp.erase(0, pos + 1);
		}
	}
	return len;
}

// https://leetcode.com/problems/sort-list/
class Sort_List
{
  private:
    ListNode *split(ListNode *head)
    {
        ListNode *fast = head, *slow = head, *prev = NULL;
        while (fast)
        {
            fast = fast->next;
            if (fast)
            {
                fast = fast->next;
                prev = slow;
                slow = slow->next;
            }
        }
        if (prev != NULL)
            prev->next = NULL;
        return slow;
    }
    ListNode *merge(ListNode *a, ListNode *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;
        if (a->val < b->val)
        {
            a->next = merge(a->next, b);
            return a;
        }
        else
        {
            b->next = merge(a, b->next);
            return b;
        }
    }

  public:
    ListNode *sortList(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *second = split(head);
        return merge(sortList(head), sortList(second));
    }
};

// https://www.naukri.com/code360/problems/three-sum_6922132
// Three Sum
vector<vector<int>> triplet(int n, vector<int> &arr)
{
    vector<vector<int>> vv;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++)
    {
        if (i >= 1 && arr[i - 1] == arr[i])
            continue;
        int q = i + 1, p = n - 1;
        while (q < p)
        {
            int sum = arr[i] + arr[q] + arr[p];
            if (sum == 0)
            {
                vector<int> v({arr[i], arr[q], arr[p]});
                vv.push_back(v);
                do
                {
                    q++;

                } while (q < p && arr[q - 1] == arr[q]);
                do
                {
                    p--;

                } while (q < p && arr[p + 1] == arr[p]);
            }
            else if (sum < 0)
            {
                q++;
            }
            else if (sum > 0)
            {
                p--;
            }
        }
    }
    return vv;
}

// https://www.naukri.com/code360/problems/binary-tree-multiplication_2675976
class Mirror_Node_Multiply
{
  private:
    const int MOD = 1e9 + 7;

    int dfs(TreeNode<int> *root1, TreeNode<int> *root2)
    {
        if (root1 == NULL && root2 == NULL)
            return 0;
        int a = root1->data * root2->data;
        int b = dfs(root1->left, root2->right);
        int c = dfs(root1->right, root2->left);
        return ((a + b) % MOD + c) % MOD;
    }

  public:
    int mirrorMultiplication(TreeNode<int> *root)
    {
        if (root == NULL)
            return 0;
        return ((root->data * root->data) % MOD + dfs(root->left, root->right)) % MOD;
    }
};

// https://www.naukri.com/code360/problems/ternarytotree_1102306
class Convert_ternary_expression_to_binary_tree
{
  private:
    BinaryTreeNode<char> *preorder(string &str, int &i)
    {
        if (i >= str.length())
            return NULL;
        BinaryTreeNode<char> *root = new BinaryTreeNode<char>(str[i++]);
        if (i < str.length() && str[i] == '?')
        {
            root->left = preorder(str, ++i);

            if (i < str.length() && str[i] == ':')
                root->right = preorder(str, ++i);
        }
        return root;
    }

  public:
    BinaryTreeNode<char> *toBinaryTree(string &str)
    {
        int i = 0;
        return preorder(str, i);
    }
};

// https://www.naukri.com/code360/problems/binary-tree-from-bracket_1118117
class Binary_Tree_From_Bracket
{
  private:
    BinaryTreeNode<int> *solve(string &str, int &i)
    {
        if (i >= str.length() || str[i] == ')')
        {
            return NULL;
        }
        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(str[i++] - '0');
        if (i < str.length() && str[i] == '(')
        {
            i++;
            root->left = solve(str, i);
            i++;
        }
        if (i < str.length() && str[i] == '(')
        {
            i++;
            root->right = solve(str, i);
            i++;
        }
        return root;
    }

  public:
    BinaryTreeNode<int> *treeFromBracket(string &str)
    {
        int i = 0;
        return solve(str, i);
    }
};

// https://www.naukri.com/code360/problems/pair-with-diff-k_5393
// k-diff pairs
int getPairsWithDifferenceK(int *arr, int n, int k)
{
    unordered_map<int, int> m;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        m[arr[i]]++;
    }
    for (auto kv = m.begin(); kv != m.end(); kv++)
    {
        if (k == 0)
        {
            if (kv->second > 1)
                cnt += kv->second * (kv->second - 1) / 2;
        }
        else
        {
            auto it = m.find(kv->first + k);
            if (it != m.end())
                cnt += it->second * kv->second;
        }
    }
    return cnt;
}

// https://leetcode.com/problems/k-diff-pairs-in-an-array/submissions/1480767609/
// unique k-diff pairs
int findPairs(vector<int> &nums, int k)
{
    unordered_map<int, int> m;
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        m[nums[i]]++;
    }
    for (auto i : m)
    {
        if (k == 0)
        {
            if (i.second > 1)
                cnt++;
        }
        else if (m.find(i.first + k) != m.end())
            cnt++;
    }
    return cnt;
}

// https://www.naukri.com/code360/problems/anagram-pairs_626517
bool isAnagram(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();
    if (n != m)
        return false;

    int isAnagram = 0;
    for (int i = 0; i < n; i++)
    {
        isAnagram ^= str1[i] ^ str2[i];
    }
    return !isAnagram;
}

// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
class Kth_Smallest_Element_BST
{
  private:
    void preorder(TreeNode<int> *root, vector<int> &v)
    {
        if (root == NULL)
            return;
        preorder(root->left, v);
        v.push_back(root->data);
        preorder(root->right, v);
    }

  public:
    int kthSmallest(TreeNode<int> *root, int k)
    {
        vector<int> v;
        preorder(root, v);
        return v[k - 1];
    }
};

// https://www.naukri.com/code360/problems/zig-zag-traversal_1062662
vector<int> zigZagTraversal(BinaryTreeNode<int> *root)
{
    if (root == NULL)
        return {};
    int level = 0;
    vector<int> ans;
    deque<BinaryTreeNode<int> *> q;
    q.push_back(root);
    while (q.empty() == false)
    {
        int n = q.size();
        while (n > 0)
        {
            if (level % 2 == 0)
            {
                auto temp = q.front();
                q.pop_front();
                ans.push_back(temp->data);
                if (temp->left)
                    q.push_back(temp->left);
                if (temp->right)
                    q.push_back(temp->right);
            }
            else
            {
                auto temp = q.back();
                q.pop_back();
                ans.push_back(temp->data);
                if (temp->right)
                    q.push_front(temp->right);
                if (temp->left)
                    q.push_front(temp->left);
            }
            n--;
        }
        level++;
    }
    return ans;
}

// https://leetcode.com/problems/unique-binary-search-trees-ii/description/
class Unique_Binary_Search_Trees_II
{
  private:
    vector<TreeNode<int> *> buildTree(int start, int end)
    {
        vector<TreeNode<int> *> ans;
        if (start > end)
        {
            ans.push_back(NULL);
            return ans;
        }
        for (int i = start; i <= end; i++)
        {
            vector<TreeNode<int> *> left = buildTree(start, i - 1);
            vector<TreeNode<int> *> right = buildTree(i + 1, end);
            for (int j = 0; j < left.size(); j++)
            {
                for (int k = 0; k < right.size(); k++)
                {
                    TreeNode<int> *root = new TreeNode<int>(i);
                    root->left = left[j];
                    root->right = right[k];
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }

  public:
    vector<TreeNode<int> *> generateTrees(int n) { return buildTree(1, n); }
};

// https://www.naukri.com/code360/problems/max-product-subset_1170054
long long int maxProductSubset(vector<int> &arr, int n)
{
    if (n == 1)
        return arr[0];
    const long long int MOD = 1e9 + 7;
    bool hasPostive = false;
    long long int ans = 1;
    int neg = 0;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            neg++;
        }
        else if (arr[i] > 0)
        {
            ans = (ans * (long long int)arr[i]) % MOD;
            hasPostive = true;
        }
    }
    if (neg == 1 && hasPostive == false)
        return 0;
    if (neg % 2 != 0)
        neg--;
    for (int i = 0; i < neg; i++)
    {
        ans = (ans * (long long int)arr[i]) % MOD;
    }
    return ans;
}

// https://leetcode.com/problems/validate-binary-tree-nodes/description/
class Validate_Binary_Tree_Nodes
{
  private:
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
        int find(int x)
        {
            if (parent[x] == x)
                return x;
            return parent[x] = find(parent[x]);
        }
        void _union(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x != y)
            {
                if (rank[x] < rank[y])
                    swap(x, y);

                parent[y] = x;
                if (rank[x] == rank[y])
                    rank[x]++;
            }
        }
    };

  public:
    bool validateBinaryTreeNodes(int n, vector<int> &leftChild, vector<int> &rightChild)
    {
        vector<bool> visited(n, false);
        DSU d(n);
        for (int i = 0; i < n; i++)
        {
            if (leftChild[i] != -1)
            {
                if (visited[leftChild[i]] != false)
                    return false;
                visited[leftChild[i]] = true;
                if (d.find(i) != d.find(leftChild[i]))
                    d._union(i, leftChild[i]);
                else
                    return false;
            }
            if (rightChild[i] != -1)
            {
                if (visited[rightChild[i]] != false)
                    return false;
                visited[rightChild[i]] = true;
                if (d.find(i) != d.find(rightChild[i]))
                    d._union(i, rightChild[i]);
                else
                    return false;
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (i == d.find(i))
            {
                cnt++;
            }
        }
        return cnt == 1;
    }
};

// https://leetcode.com/problems/binary-search-tree-iterator/
class BSTIterator
{
  private:
    stack<TreeNode<int> *> st;
    void partialInorder(TreeNode<int> *root)
    {
        while (root != NULL)
        {
            st.push(root);
            root = root->left;
        }
    }

  public:
    BSTIterator(TreeNode<int> *root) { partialInorder(root); }

    int next()
    {
        TreeNode<int> *top = st.top();
        st.pop();
        partialInorder(top->right);
        return top->data;
    }

    bool hasNext() { return st.empty() == false; }
};

// https://leetcode.com/problems/linked-list-in-binary-tree/description/
class Linked_List_in_Binary_Tree
{
  private:
    bool solve(ListNode *head, TreeNode<int> *root)
    {
        if (root == NULL && head != NULL)
            return false;
        if (head == NULL)
            return true;
        if (head->val != root->data)
            return false;
        else
            return solve(head->next, root->left) ||
                   solve(head->next, root->right);
    }

  public:
    bool isSubPath(ListNode *head, TreeNode<int> *root)
    {
        if (root == NULL || head == NULL)
            return false;
        return solve(head, root) || isSubPath(head, root->left) ||
               isSubPath(head, root->right);
    }
};

// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/description/
class Maximum_Sum_BST_in_Binary_Tree
{
  private:
    class NodeValue
    {
      public:
        int minNode, maxNode, sum;
        NodeValue(int minNode, int maxNode)
        {
            this->minNode = minNode;
            this->maxNode = maxNode;
            this->sum = 0;
        }

        NodeValue(int minNode, int maxNode, int maxSum)
        {
            this->minNode = minNode;
            this->maxNode = maxNode;
            this->sum = maxSum;
        }
    };

    int maxSum;
    NodeValue maxSumBSTHelper(TreeNode<int> *root)
    {
        if (!root)
            return NodeValue(INT_MAX, INT_MIN);

        auto left = maxSumBSTHelper(root->left);
        auto right = maxSumBSTHelper(root->right);

        if (left.maxNode < root->data && root->data < right.minNode)
        {
            maxSum = max(maxSum, root->data + left.sum + right.sum);
            return NodeValue(min(root->data, left.minNode),
                             max(root->data, right.maxNode),
                             root->data + left.sum + right.sum);
        }
        return NodeValue(INT_MIN, INT_MAX);
    }

  public:
    int maxSumBST(TreeNode<int> *root)
    {
        maxSum = 0;
        maxSumBSTHelper(root);
        return max(maxSum, 0);
    }
};

// https://leetcode.com/problems/longest-common-prefix/
string longestCommonPrefix(vector<string> &strs)
{
    int longest = INT_MAX;
    for (int i = 0, j = 1; j < strs.size(); i++, j++)
    {
        int n = strs[i].length();
        int m = strs[j].length();
        int prefix = 0;
        while (prefix < n && prefix < m &&
               strs[i][prefix] == strs[j][prefix])
        {
            prefix++;
        }
        longest = min(longest, prefix);
    }
    return strs[0].substr(0, longest);
}

int main(int argc, char *argv[])
{
    return 0;
}
