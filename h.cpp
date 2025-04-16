#include <bits/stdc++.h>
#include <unordered_map>
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
    static TreeNode<T> *buildTree1(vector<T> &arr)
    {
        return NULL;
    }
    static TreeNode<T> *buildTree1(vector<T> &&arr)
    {
        int i = 0;
        TreeNode<T> *root = new TreeNode<T>(arr[i++]);
        queue<TreeNode<T> *> q;
        q.push(root);
        while (q.empty() == false && i < arr.size())
        {
            TreeNode<T> *temp = q.front();
            q.pop();
            if (arr[i] != -1)
            {
                temp->left = new TreeNode<T>(arr[i++]);
                q.push(temp->left);
            }
            else
            {
                i++;
            }
            if (arr[i] != -1)
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

template <typename T>
class Node
{
  public:
    T data;
    Node<T> *next;
    Node<T> *child;

    Node(T data)
    {
        next = NULL;
        child = NULL;
        this->data = data;
    }
    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
    }
    void printLL()
    {
        for (Node<T> *n = this; n != NULL; n = n->next)
        {
            printf(" %d", n->data);
        }
        printf("\n");
    }
    static Node<T> *newLinkList(vector<T> &arr)
    {
        if (arr.size() < 1)
            return NULL;

        Node<T> *head = new Node<T>(arr[0]);
        Node<T> *n = head;
        for (int i = 1; i < arr.size(); i++)
        {
            n->next = new Node<T>(arr[i]);
            n = n->next;
        }
        return head;
    }
    static Node<T> *newLinkList(vector<T> &&arr)
    {
        if (arr.size() < 1)
            return NULL;

        Node<T> *head = new Node<T>(arr[0]);
        Node<T> *n = head;
        for (int i = 1; i < arr.size(); i++)
        {
            n->next = new Node<T>(arr[i]);
            n = n->next;
        }
        return head;
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

//https://www.codingninjas.com/studio/problems/inplace-rotate-matrix-90-degree_839734
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

//https://www.naukri.com/code360/problems/matrix-is-symmetric_799361
bool isMatrixSymmetric(vector<vector<int>> matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
                return false;
        }
    }
    return true;
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

//Euclidean algorithm
int gcd(int a, int b)
{
    while (b > 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

//https://www.naukri.com/code360/problems/max-gcd-pair_842786?count=25&search=&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=ATTEMPTED
//Sieve of Eratosthenes
int maxGCDPair(vector<int> &arr, int n)
{
    int high = 0;
    for (int i = 0; i < n; i++)
    {
        high = max(high, arr[i]);
    }

    vector<int> square(high + 1, 0);
    for (int i = 0; i < n; i++)
    {
        square[arr[i]]++;
    }

    for (int i = high; i >= 1; i--)
    {
        int count = 0;
        for (int j = i; j <= high; j += i)
        {
            if (square[j] > 1)
                return j;
            else if (square[j] == 1)
                count++;
            if (count == 2)
                return i;
        }
    }
    return 1;
}

pair<Node<int> *, Node<int> *> divideList(Node<int> *head)
{
    if (head == NULL || head->next == NULL)
        return {head, NULL};
    Node<int> *head1 = head->next;
    Node<int> *a = head, *b = head1;
    while (a != NULL && b != NULL)
    {
        a->next = b->next;
        a = a->next;
        if (a != NULL)
        {
            b->next = a->next;
            b = b->next;
        }
    }
    pair<Node<int> *, Node<int> *> p{head, head1};
    return p;
}

//https://www.naukri.com/code360/problems/flatten-the-multi-level-linked-list_839810?count=25&search=linked&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=NOT_ATTEMPTED
Node<int> *flattenMultiLinkedList(Node<int> *head)
{
    queue<Node<int> *> q;
    q.push(head);
    Node<int> *pre = NULL;
    while (q.empty() == false)
    {
        Node<int> *t = q.front();
        q.pop();
        if (pre != NULL)
        {
            pre->next = t;
        }
        while (t != NULL)
        {
            if (t->child != NULL)
            {
                q.push(t->child);
                t->child = NULL;
            }
            pre = t;
            t = t->next;
        }
    }
    return head;
}

class RearrangeLinkedList
{
  private:
    Node<int> *getMid(Node<int> *head)
    {
        Node<int> *fast = head, *slow = head, *pre = NULL;
        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                fast = fast->next;
                pre = slow;
                slow = slow->next;
            }
        }
        return slow;
    }

  public:
    Node<int> *rearrangeList(Node<int> *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        stack<Node<int> *> st;
        queue<Node<int> *> q;
        Node<int> *mid = getMid(head);
        for (Node<int> *i = mid->next; i != NULL; i = i->next)
        {
            st.push(i);
        }
        for (Node<int> *i = head; i != mid->next; i = i->next)
        {
            q.push(i);
        }
        mid->next = NULL;

        Node<int> *i = NULL;
        while (st.empty() == false && q.empty() == false)
        {
            Node<int> *t = st.top();
            st.pop();
            Node<int> *f = q.front();
            q.pop();
            f->next = t;
            if (i == NULL)
                i = t;
            else
            {
                i->next = f;
                i = t;
            }
        }
        while (q.empty() == false)
        {
            Node<int> *f = q.front();
            q.pop();
            if (i == NULL)
                i = f;
            else
            {
                i->next = f;
                i = f;
            }
        }
        return head;
    }
};

class AddOneToLinkedList
{
  private:
    int _addOne(Node<int> *head)
    {
        if (head == NULL)
            return 1;
        int carry = _addOne(head->next);
        head->data += carry;
        if (head->data == 10)
        {
            head->data = 0;
            return 1;
        }
        else
            return 0;
    }

  public:
    Node<int> *addOneToList(Node<int> *head)
    {
        if (head == NULL)
            return NULL;
        int carry = _addOne(head->next);
        head->data += carry;
        if (head->data == 10)
        {
            head->data = 0;
            Node<int> *t = head;
            head = new Node<int>(1);
            head->next = t;
        }
        return head;
    }
};

//https://www.naukri.com/code360/problems/kth-smallest-element_3621004?leftPanelTabValue=PROBLEM&count=25&page=2&search=&sort_entity=order&sort_order=ASC&attempt_status=NOT_ATTEMPTED&customSource=studio_nav
class KthSmallestElement
{
  private:
    int upper_bound(vector<int> &arr, int n, int base)
    {
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] > base)
                r = mid;
            else
                l = mid + 1;
        }
        return arr[l] > base ? l : n;
    }

  public:
    int kSmallestInMatrix(vector<vector<int>> &mat, int k)
    {
        int n = mat.size();
        int l = mat[0][0], r = mat[n - 1][n - 1];
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            int count = 0;
            for (int i = 0; i < n; i++)
            {
                count += upper_bound(mat[i], n, mid);
            }
            if (count < k)
            {
                l = mid + 1;
            }
            else
                r = mid;
        }
        return l;
    }
};

//https://www.geeksforgeeks.org/check-leaves-level/
int levelLeaf(TreeNode<int> *root)
{
    bool leafExsited = false;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            TreeNode<int> *f = q.front();
            q.pop();
            if (f->left != NULL)
                q.push(f->left);
            if (f->right != NULL)
                q.push(f->right);
            if (f->left == NULL && f->right == NULL)
                leafExsited = true;
        }
        if (q.empty() == false && leafExsited == true)
        {
            return 0;
        }
    }
    return 1;
}

//https://www.naukri.com/code360/problems/triplets-in-binary-tree_668907?leftPanelTabValue=PROBLEM&count=25
class TripletsInBinaryTree
{
  private:
    void preorder(const int x, vector<vector<int>> &ans,
                  TreeNode<int> *grand, TreeNode<int> *parent, TreeNode<int> *child)
    {
        if (grand != NULL && parent != NULL && child != NULL)
        {
            if (grand->data + parent->data + child->data > x)
            {
                ans.push_back({grand->data, parent->data, child->data});
            }
        }
        if (child == NULL)
            return;
        preorder(x, ans, parent, child, child->left);
        preorder(x, ans, parent, child, child->right);
    }

  public:
    vector<vector<int>> findTriplets(TreeNode<int> *root, int x)
    {
        vector<vector<int>> ans;
        preorder(x, ans, NULL, NULL, root);
        return ans;
    }
};

//https://www.naukri.com/code360/problems/top-view-of-the-binary-tree_893067
vector<int> getTopView(TreeNode<int> *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    queue<pair<TreeNode<int> *, int>> q;
    q.push({root, 0});

    stack<int> left({root->data});
    vector<int> right;
    int l = 0, r = 0;
    while (q.empty() == false)
    {
        auto f = q.front();
        q.pop();
        if (f.second < l)
        {
            left.push(f.first->data);
            l = f.second;
        }
        else if (f.second > r)
        {
            right.push_back(f.first->data);
            r = f.second;
        }
        if (f.first->left != NULL)
        {
            q.push({f.first->left, f.second - 1});
        }
        if (f.first->right != NULL)
        {
            q.push({f.first->right, f.second + 1});
        }
    }
    while (left.empty() == false)
    {
        ans.push_back(left.top());
        left.pop();
    }
    for (int i : right)
    {
        ans.push_back(i);
    }
    return ans;
}

//https://www.naukri.com/code360/problems/largest-sub-tree-sum_920400?count=25&search=subtree&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&page=1
class LargestSubTreeSum
{
  private:
    int sum(TreeNode<int> *root, int &ans)
    {
        if (root == NULL)
            return 0;
        int a = sum(root->left, ans) + sum(root->right, ans) + root->data;
        ans = max(ans, a);
        return a;
    }

  public:
    int largestSubtreeSum(TreeNode<int> *root)
    {
        int ans = INT_MIN;
        sum(root, ans);
        return ans;
    }
};

//https://www.naukri.com/code360/problems/subtree-of-another-tree_893071?count=25&search=subtree&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&page=1
class SubtreeOfAnotherTree
{
  private:
    bool isSame(TreeNode<int> *a, TreeNode<int> *b)
    {
        if (a == NULL && b == NULL)
            return true;
        if (a == NULL && b != NULL)
            return false;
        if (a != NULL & b == NULL)
            return false;
        if (a->data == b->data)
        {
            return isSame(a->left, b->left) && isSame(a->right, b->right);
        }
        else
            return false;
    }

  public:
    bool isSubtree(TreeNode<int> *T, TreeNode<int> *S)
    {
        if (T == NULL && S != NULL)
            return false;
        if (T != NULL && S == NULL || T == NULL && S == NULL)
            return true;
        if (T->data == S->data)
        {
            return isSame(T, S);
        }
        return isSubtree(T->left, S) || isSubtree(T->right, S);
    }
};

//https://www.naukri.com/code360/problems/count-nodes-in-all-subtrees_1071162?count=25&search=subtree&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&page=1&attempt_status=NOT_ATTEMPTED
//undirected graph
class CountElementsInAllSubtrees
{
  private:
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, int i, vector<int> &ans)
    {
        ans[i] = 1;
        visited[i] = true;
        for (int j = 0; j < adj[i].size(); j++)
        {
            if (visited[adj[i][j]] == false)
            {
                dfs(adj, visited, adj[i][j], ans);
                ans[i] += ans[adj[i][j]];
            }
        }
    }

  public:
    vector<int> countNodesInAllSubtrees(int n, vector<vector<int>> &adj)
    {
        vector<int> ans(n, 0);
        vector<bool> visited(n, false);
        dfs(adj, visited, 0, ans);
        return ans;
    }
};

//https://www.naukri.com/code360/problems/bfs-in-graph_973002?count=25&search=graph&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&page=2&attempt_status=NOT_ATTEMPTED
vector<int> bfsTraversal(int n, vector<vector<int>> &adj)
{
    vector<int> ans;
    queue<int> q;
    q.push(0);
    vector<bool> visited(n, false);
    visited[0] = true;
    while (q.empty() == false)
    {
        int i = q.front();
        q.pop();
        ans.push_back(i);
        for (int j = 0; j < adj[i].size(); j++)
        {
            if (visited[adj[i][j]] == false)
            {
                visited[adj[i][j]] = true;
                q.push(adj[i][j]);
            }
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/detect-cycle-in-a-directed-graph_1542162
class DetectCycleDirectedGraph
{
  private:
    bool dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &trace, int i)
    {
        trace[i] = true;
        visited[i] = true;
        for (int j = 0; j < adj[i].size(); j++)
        {
            if (visited[adj[i][j]] == false)
            {
                if (dfs(adj, visited, trace, adj[i][j]))
                    return true;
            }
            else if (trace[adj[i][j]])
                return true;
        }
        trace[i] = false;
        return false;
    }

  public:
    bool isCyclic(vector<vector<int>> &edges, int v, int e)
    {
        vector<bool> visited(v, false);
        vector<bool> trace(v, false);
        vector<vector<int>> adj(v, vector<int>());
        for (int i = 0; i < e; i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]);
        }
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == false)
                if (dfs(adj, visited, trace, i))
                    return true;
        }
        return false;
    }
};

//https://www.naukri.com/code360/problems/minimum-depth-in-a-binary-tree_696332
int minDepth(TreeNode<int> *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    if (root->left == NULL)
    {
        return minDepth(root->right) + 1;
    }
    else if (root->right == NULL)
    {
        return minDepth(root->left) + 1;
    }
    else
    {
        int a = minDepth(root->left);
        int b = minDepth(root->right);
        return a < b ? a + 1 : b + 1;
    }
}

vector<string> findCommonElements(string arr1[], string arr2[], int n, int m)
{
    vector<string> ans;
    unordered_map<string, int> counter;
    for (int i = 0; i < n; i++)
    {
        counter[arr1[i]]++;
    }
    for (int i = 0; i < m; i++)
    {
        unordered_map<string, int>::iterator iter = counter.find(arr2[i]);
        if (iter != counter.end() && iter->second > 0)
        {
            ans.push_back(iter->first);
            iter->second--;
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/swap-and-maximise_1164405
//sum of the absolute difference
//maxAbsSum
int maxSum(vector<int> &arr, int n)
{
    sort(arr.begin(), arr.end());
    int l = 0, r = n - 1;
    int ans = 0;
    while (l < r)
    {
        ans += arr[r] - arr[l];
        l++;
        ans += arr[r] - arr[l];
        r--;
    }
    ans += arr[l] - arr[0];
    return ans;
}

//https://www.naukri.com/code360/problems/connect-n-ropes-with-minimum-cost_630476
//minSum
long long connectRopes(int *arr, int n)
{
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++)
    {
        q.push(arr[i]);
    }
    long long cost = 0;
    while (q.size() > 1)
    {
        int x = q.top();
        q.pop();
        int y = q.top();
        q.pop();
        int sum = x + y;
        cost += sum;
        q.push(sum);
    }
    return cost;
}

//https://www.naukri.com/code360/problems/remove-duplicates-from-string_630470
string removeDuplicates(string str, int n)
{
    vector<int> dp(26, 0);
    string ans;
    for (int i = 0; i < n; i++)
    {
        if (dp[str[i] - 'a'] == 0)
        {
            dp[str[i] - 'a']++;
            ans.push_back(str[i]);
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/duplicate-subtrees_920530
//https://leetcode.com/problems/find-duplicate-subtrees/
class DuplicateSubtrees
{
  private:
    string subtree(TreeNode<int> *root, unordered_map<string, int> &mp, vector<int> &ans)
    {
        if (root == NULL)
            return "";
        string strL = subtree(root->left, mp, ans);
        string strR = subtree(root->right, mp, ans);
        string temp = to_string(root->data) + "," + strL + "," + strR;
        mp[temp]++;
        if (mp[temp] == 2)
        {
            ans.push_back(root->data);
        }
        return temp;
    }

  public:
    vector<int> duplicateSubtrees(TreeNode<int> *root)
    {
        vector<int> ans;
        if (root == NULL)
            return ans;
        unordered_map<string, int> mp;
        subtree(root, mp, ans);
        if (ans.empty())
            return {-1};
        else
            return ans;
    }
};

class TopViewOfBinaryTree
{
  public:
    vector<int> getTopView(TreeNode<int> *root)
    {
        stack<TreeNode<int> *> left;
        queue<TreeNode<int> *> right;
        queue<pair<TreeNode<int> *, int>> q;
        q.push({root, 0});
        left.push(root);
        int l = 0, r = 0;
        while (q.empty() == false)
        {
            auto temp = q.front();
            q.pop();
            if (temp.second < l)
            {
                left.push(temp.first);
                l--;
            }
            else if (temp.second > r)
            {
                right.push(temp.first);
                r++;
            }
            if (temp.first->left)
                q.push({temp.first->left, temp.second - 1});
            if (temp.first->right)
                q.push({temp.first->right, temp.second + 1});
        }
        vector<int> ans;
        while (left.empty() == false)
        {
            ans.push_back(left.top()->data);
            left.pop();
        }
        while (right.empty() == false)
        {
            ans.push_back(right.front()->data);
            right.pop();
        }
        return ans;
    }
};

// https://www.naukri.com/code360/problems/bottom-view-of-binary-tree_893110
vector<int> bottomView(TreeNode<int> *root)
{
    map<int, int> m;
    queue<pair<int, TreeNode<int> *>> q;
    q.push({0, root});
    while (q.empty() == false)
    {
        auto temp = q.front();
        q.pop();
        m[temp.first] = temp.second->data;
        if (temp.second->left)
            q.push({temp.first - 1, temp.second->left});
        if (temp.second->right)
            q.push({temp.first + 1, temp.second->right});
    }
    vector<int> ans;
    for (auto i : m)
    {
        ans.push_back(i.second);
    }
    return ans;
}

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
vector<vector<int>> levelOrderBottom(TreeNode<int> *root)
{
    if (root == NULL)
        return {};
    vector<vector<int>> vv;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int n = q.size();
        vector<int> v;
        for (int i = 0; i < n; i++)
        {
            auto temp = q.front();
            q.pop();
            v.push_back(temp->data);
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        vv.push_back(v);
    }

    for (int i = 0, j = vv.size() - 1; i < j; i++, j--)
    {
        swap(vv[i], vv[j]);
    }
    return vv;
}

// https://www.naukri.com/code360/problems/binary-tree-leaves-to-doubly-linked-list_983643
class Binary_Tree_Leaves_to_dll
{
    void preorder(TreeNode<int> *root, TreeNode<int> **pre,
                  TreeNode<int> **head)
    {
        if (root == NULL)
            return;
        if (root->left == NULL && root->right == NULL)
        {
            if (*head == NULL)
            {
            }
            else
            {
                (*head)->right = root;
                root->left = (*head);
            }
            *head = root;
            if (pre != NULL)
            {
                *pre = NULL;
            }
            return;
        }

        preorder(root->left, &root->left, head);
        preorder(root->right, &root->right, head);
    }

    TreeNode<int> *leafToDLL(TreeNode<int> *root)
    {
        if (root == NULL || root->left == NULL && root->right == NULL)
            return root;
        TreeNode<int> *head = NULL;
        preorder(root, NULL, &head);
        while (head->left != NULL)
        {
            head = head->left;
        }
        return head;
    }
};

// https://www.naukri.com/code360/problems/maximum-width-in-binary-tree_763671
int getMaxWidth(TreeNode<int> *root)
{
    if (root == NULL)
        return 0;
    int maxWidth = INT_MIN;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int width = q.size();
        maxWidth = max(maxWidth, width);
        for (int i = 0; i < width; i++)
        {
            TreeNode<int> *temp = q.front();
            q.pop();
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
    return maxWidth;
}

// https://www.naukri.com/code360/problems/number-of-pairs-with-given-sum_630509
long long pairsWithGivenSum(int arr[], int n, int sum)
{
    long long ans = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        ans += m[sum - arr[i]];
        m[arr[i]]++;
    }
    return ans;
}

// https://www.naukri.com/code360/problems/rotate-linked-list_920454
Node<int> *rotate(Node<int> *head, int k)
{
    if (k == 0 || head == NULL || head->next == NULL)
        return head;
    int len = 1;
    Node<int> *last = head;
    while (last->next != NULL)
    {
        last = last->next;
        len++;
    }
    k = len - (k % len);
    Node<int> *p = head;
    while (k > 0)
    {
        Node<int> *n = p->next;
        p->next = NULL;
        last->next = p;
        last = last->next;
        p = n;
        k--;
    }
    return p;
}

// https://www.naukri.com/code360/problems/leaders-in-an-array_873144
vector<int> findLeaders(vector<int> &elements, int n)
{
    vector<int> ans;
    int i = INT_MIN;
    for (; n > 0; n--)
    {
        if (elements[n - 1] > i)
        {
            i = elements[n - 1];
            ans.push_back(i);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// https://www.naukri.com/code360/problems/maximum-distance_758901
int maximumDistance(int arr[], int n)
{
    int dist = 0;
    unordered_map<int, int> map;
    for (int i = 0; i < n; i++)
    {
        auto it = map.find(arr[i]);
        if (it == map.end())
        {
            map[arr[i]] = i;
        }
        else
        {
            dist = max(dist, i - it->second);
        }
    }
    return dist;
}

// https://www.naukri.com/code360/problems/distinct-subsequences_799558
// https://www.geeksforgeeks.org/count-distinct-subsequences/
int distinctSubsequences(string S)
{
    const int MOD = 1e9 + 7;
    vector<int> last(256, -1);
    int n = S.length();
    int dp[n + 1] = {0};
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = (2 * dp[i - 1]) % MOD;
        if (last[S[i - 1]] != -1)
        {
            dp[i] = (dp[i] - dp[last[S[i - 1]]] + MOD) % MOD;
        }
        last[S[i - 1]] = i - 1;
    }
    return dp[n];
}

// https://leetcode.com/problems/distinct-subsequences-ii/
// hard
int distinctSubseqII(string s)
{
    const int MOD = 1e9 + 7;
    int n = s.length();
    vector<int> last(256, -1);
    last[s[0]] = 1;
    int all = 1, mine = 1;
    for (int i = 1; i < n; i++)
    {
        mine = all + 1;
        if (last[s[i]] == -1)
        {
            all = (all + mine) % MOD;
        }
        else
            all = (all + (mine - last[s[i]] + MOD) % MOD) % MOD;
        last[s[i]] = mine;
    }
    return all;
}

// https://www.naukri.com/code360/problems/distinct-subsequences_981277
// https://leetcode.com/problems/distinct-subsequences/
// hard
int numDistinct(string s, string t)
{
    int MOD = 1e9 + 7;
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][m];
}

// https://www.naukri.com/code360/problems/distinct-subsets-count_764603
int countDistinctArrays(vector<int> &arr)
{
    unordered_map<int, int> m;
    for (int i = 0; i < arr.size(); i++)
    {
        m[arr[i]]++;
    }
    long long mod = 1e9 + 7, ans = 1;
    for (auto it : m)
    {
        ans = (ans * (it.second + 1)) % mod;
    }
    return ans - 1;
}

// https://www.naukri.com/code360/problems/edit-distance_630420
// Moderate Solution
// dp[i][0] and dp[0][j] == shortestSupersequence
int editDistance(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
            }
        }
    }
    return dp[n][m];
}

// https://www.naukri.com/code360/problems/smallest-subarray-with-k-distinct-elements_630523
vector<int> smallestSubarrayWithKDistinct(vector<int> &arr, int k)
{
    bool got = false;
    unordered_map<int, int> map;
    int n = arr.size();
    int l = 0, r = n;
    for (int i = 0, j = 0; i < n; i++)
    {
        map[arr[i]]++;
        while (map.size() == k)
        {
            if (i - j < r - l)
            {
                l = j;
                r = i;
                got = true;
            }
            auto it = map.find(arr[j]);
            it->second--;
            if (it->second == 0)
                map.erase(it);
            j++;
        }
    }
    if (got)
        return {l, r};
    else
        return {-1};
}

// https://www.naukri.com/code360/problems/longest-sub-string-with-k-distinct-characters_920521
int getLengthofLongestSubstring(string s, int k)
{
    unordered_map<char, int> freq;
    int ans = INT_MIN;
    for (int i = 0, j = 0; i < s.length(); i++)
    {
        freq[s[i]]++;
        while (freq.size() > k)
        {
            auto it = freq.find(s[j]);
            it->second--;
            if (it->second == 0)
                freq.erase(it);
            j++;
        }
        ans = max(ans, i - j + 1);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/subarray-with-distinct-integers_893062
// https://www.naukri.com/code360/problems/subarrays-with-at-most-k-distinct-values_1473804
// https://www.geeksforgeeks.org/count-of-subarrays-having-exactly-k-distinct-elements/
class Subarray_with_distinct_integers
{
  private:
    // Count of subarrays with at most K different elements
    int atMost(vector<int> &arr, int n, int b)
    {
        int cnt = 0;
        unordered_map<int, int> map;
        for (int i = 0, j = 0; i < n; i++)
        {
            map[arr[i]]++;
            while (map.size() > b)
            {
                auto it = map.find(arr[j]);
                it->second--;
                if (it->second == 0)
                    map.erase(it);
                j++;
            }
            cnt += i - j + 1;
        }
        return cnt;
    }

  public:
    int goodSubarrays(vector<int> &arr, int n, int b)
    {
        return atMost(arr, n, b) - atMost(arr, n, b - 1);
    }
};

// https://www.naukri.com/code360/problems/count-with-k-different-characters_1214627
class Count_exactly_K_Different_Characters
{
  private:
    int countSubStr(string &str, int k)
    {
        unordered_map<char, int> dp;
        int count = 0;
        for (int l = 0, r = 0; r < str.length(); r++)
        {
            dp[str[r]]++;
            while (dp.size() > k)
            {
                auto it = dp.find(str[l]);
                it->second--;
                if (it->second == 0)
                    dp.erase(it);
                l++;
            }
            count += r - l + 1;
        }
        return count;
    }

  public:
    int countSubStrings(string str, int k)
    {
        return countSubStr(str, k) - countSubStr(str, k - 1);
    }
};

// https://www.naukri.com/code360/problems/longest-repeating-substring_980523
int longestRepeatingSubstring(string &str, int k)
{
    vector<int> dp(256, 0);
    int n = str.length();
    int maxCount = INT_MIN, ans = INT_MIN;
    for (int l = 0, r = 0; r < n; r++)
    {
        dp[str[r]]++;
        maxCount = max(maxCount, dp[str[r]]);
        while (maxCount + k < r - l + 1)
        {
            dp[str[l]]--;
            l++;
            maxCount = max(maxCount, dp[str[l]]);
        }
        ans = max(ans, r - l + 1);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/disjoint-intervals_1089562
// Disjoint Intervals
int disjointIntervals(vector<pair<int, int>> arr, int n)
{
    auto cmp = [](pair<int, int> &a, pair<int, int> &b)
    {
        return a.second < b.second;
    };
    sort(arr.begin(), arr.end(), cmp);

    int last = 0;
    int maxSize = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[last].second < arr[i].first)
        {
            maxSize++;
            last = i;
        }
    }
    return maxSize;
}

// https://www.naukri.com/code360/problems/2-sum_893025
pair<int, int> twoSum(vector<int> &arr, int n, int target)
{
    unordered_map<int, int> mp;
    pair<int, int> ans = {-1, -1};
    for (int i = 0; i < n; i++)
    {
        auto it = mp.find(target - arr[i]);
        if (it != mp.end())
        {
            if (ans.first == -1 || it->second < ans.first)
            {
                ans.first = it->second;
                ans.second = i;
            }
        }
        mp.insert({arr[i], i});
    }
    return ans;
}

//https://leetcode.com/problems/two-sum/description/
vector<int> twoSum(vector<int> &nums, int target)
{
	unordered_map<int, int> map;
	for (int i = 0; i < nums.size(); i++) {
		int diff = target - nums[i];
		auto it = map.find(diff);
		if (it != map.end())
			return { it->second, i };
		else
			map.insert({ nums[i], i });
	}
	return {};
}

// https://www.naukri.com/code360/problems/detect-cycle-in-an-undirected-graph_758967
class Detect_Cycle_In_Undirected_Graph
{
  private:
    bool dfs(vector<int> adj[], int cur, int pre, vector<bool> &visited)
    {
        visited[cur] = true;
        for (auto next : adj[cur])
        {
            if (next != pre)
            {
                if (visited[next] == false)
                {
                    if (dfs(adj, next, cur, visited))
                        return true;
                }
                else
                    return true;
            }
        }
        return false;
    }

  public:
    bool detectCycle(int V, vector<int> adj[])
    {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == false && dfs(adj, i, -1, visited))
                return true;
        }
        return false;
    }
};

// https://www.naukri.com/code360/problems/bst-iterator_1112601
class BSTiterator
{
  private:
    stack<TreeNode<int> *> st;
    void inorder(TreeNode<int> *root, stack<TreeNode<int> *> &st)
    {
        if (root == NULL)
            return;
        inorder(root->left, st);
        st.push(root);
        inorder(root->right, st);
    }

  public:
    BSTiterator(TreeNode<int> *root)
    {
        stack<TreeNode<int> *> temp;
        inorder(root, temp);
        while (temp.empty() == false)
        {
            TreeNode<int> *top = temp.top();
            temp.pop();
            st.push(top);
        }
    }

    int next()
    {
        TreeNode<int> *temp = st.top();
        st.pop();
        return temp->data;
    }

    bool hasNext() { return !st.empty(); }
};

// https://www.naukri.com/code360/problems/cousins-of-given-node-in-binary-tree_873363
vector<int> cousinsOfNode(TreeNode<int> *root, int node)
{
    vector<int> ans;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        bool ret = false;
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            auto temp = q.front();
            q.pop();
            if (temp->left && temp->left->data == node ||
                temp->right && temp->right->data == node)
            {
                ret = true;
                continue;
            }
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        if (ret)
            break;
    }
    while (q.empty() == false)
    {
        auto front = q.front();
        q.pop();
        ans.push_back(front->data);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// https://www.naukri.com/code360/problems/h_920474
class Merge_Two_BSTs
{
    void inorder(TreeNode<int> *root, vector<int> &vec)
    {
        if (root == NULL)
            return;
        inorder(root->left, vec);
        vec.push_back(root->data);
        inorder(root->right, vec);
    }

    vector<int> mergeBST(TreeNode<int> *root1, TreeNode<int> *root2)
    {
        vector<int> ans;
        vector<int> v1, v2;
        inorder(root1, v1);
        inorder(root2, v2);
        int i = 0, j = 0;
        int n = v1.size(), m = v2.size();
        while (i < n && j < m)
        {
            if (v1[i] < v2[j])
            {
                ans.push_back(v1[i++]);
            }
            else
            {
                ans.push_back(v2[j++]);
            }
        }
        while (i < n)
        {
            ans.push_back(v1[i++]);
        }
        while (j < m)
        {
            ans.push_back(v2[j++]);
        }
        return ans;
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
        vector<vector<int>> matrix = {{1, 2, 3}, {2, 4, 5}, {3, 5, 8}};
        std::cout << "Matrix Is Symmetric:" << isMatrixSymmetric(matrix) << std::endl;
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
    {
        vector<int> arr = {4, 2, 10, 8, 6, 4, 3, 2, 1, 7};
        printf("maxGCDPair:%d\n", maxGCDPair(arr, arr.size()));
    }
    {
        Node<int> *head = Node<int>::newLinkList({1, 2, 3, 4, 5});
        pair<Node<int> *, Node<int> *> p = divideList(head);
        printf("divideList first:");
        p.first->printLL();
        printf("divideList second:");
        p.second->printLL();
    }
    {
        Node<int> *head = new Node<int>(10);
        head->next = new Node<int>(5);
        head->next->next = new Node<int>(12);
        head->next->next->next = new Node<int>(7);
        head->next->next->next->child = new Node<int>(17);
        head->next->next->next->next = new Node<int>(11);
        head->child = new Node<int>(4);
        head->child->next = new Node<int>(20);
        head->child->next->child = new Node<int>(2);
        head->child->next->next = new Node<int>(13);
        head->child->next->next->child = new Node<int>(16);
        head = flattenMultiLinkedList(head);
        printf("Flatten The Multi-Level Linked List:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        Node<int> *head = Node<int>::newLinkList({1, 2, 3, 4, 5, 6});
        RearrangeLinkedList ll;
        head = ll.rearrangeList(head);
        printf("Rearrange Linked List:");
        head->printLL();
    }
    {
        Node<int> *head = Node<int>::newLinkList({1, 7, 7, 9});
        AddOneToLinkedList a;
        head = a.addOneToList(head);
        printf("Add One to Linked List");
        head->printLL();
    }
    {
        Node<int> *head = Node<int>::newLinkList({9, 9, 9, 9});
        AddOneToLinkedList a;
        head = a.addOneToList(head);
        printf("Add One to Linked List");
        head->printLL();
    }
    {
        vector<vector<int>> mat = {{1, 2, 2}, {1, 3, 4}, {1, 5, 7}};
        KthSmallestElement k;
        printf("Kth Smallest Element:%d\n", k.kSmallestInMatrix(mat, 5));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, 2, 3}, 0);
        printf("levelLeaf:%d\n", levelLeaf(root));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, 2, 3, 5, 6, 7}, 0);
        TripletsInBinaryTree t;
        vector<vector<int>> ans = t.findTriplets(root, 8);
        printf("Triplets in Binary Tree:");
        for (auto i : ans)
        {
            for (auto j : i)
            {
                printf(" %d", j);
            }
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, 2, 3, 4, 5}, 0);
        vector<int> ans = getTopView(root);
        printf("Top View of the Binary Tree:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, -2, 3, 4, 7, -9, 2}, 0);
        LargestSubTreeSum l;
        printf("Largest sub-tree sum: %d\n", l.largestSubtreeSum(root));
    }
    {
        TreeNode<int> *T = TreeNode<int>::buildTree({1, 2, 3, 4, 5}, 0);
        TreeNode<int> *S = TreeNode<int>::buildTree({2, 4, 5}, 0);
        SubtreeOfAnotherTree s;
        std::cout << "Subtree of Another Tree: " << s.isSubtree(T, S) << std::endl;
    }
    {
        vector<vector<int>> adj = {{1, 3, 4}, {0, 5}, {3}, {0, 2, 6}, {0}, {1}, {3}};
        CountElementsInAllSubtrees c;
        vector<int> ans = c.countNodesInAllSubtrees(adj.size(), adj);
        printf("Count elements in all subtrees:");
        for (auto i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<vector<int>> adj = {{1, 2, 3}, {0, 2}, {0, 1}, {0}};
        vector<int> ans = bfsTraversal(adj.size(), adj);
        printf("BFS in Graph:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<vector<int>> edges = {{0, 1}, {0, 2}};
        DetectCycleDirectedGraph d;
        std::cout << "Detect Cycle in a Directed Graph: " << d.isCyclic(edges, 3, 2) << std::endl;
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree1({8, 1, 2, 5, 2, -1, -1, 9, -1, -1, -1, -1, -1});
        printf("Minimum Depth Of Binary Tree:%d\n", minDepth(root));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree1({1, 2, 3, 4, -1, -1, 5, -1, -1, -1, -1});
        printf("Minimum Depth Of Binary Tree:%d\n", minDepth(root));
    }
    {
        string str1[] = {"ab", "dc", "ab", "ab"};
        string str2[] = {"dc", "ab", "ab"};
        vector<string> ans = findCommonElements(str1, str2, 4, 3);
        printf("Common Elements:");
        for (string i : ans)
        {
            printf(" %s", i.c_str());
        }
        printf("\n");
    }
    {
        vector<int> arr = {7, 2, 4, 5};
        std::cout << "Swap And Maximise:" << maxSum(arr, arr.size()) << std::endl;
    }
    {
        int arr[] = {4, 3, 2, 6};
        printf("Connect N Ropes With Minimum Cost:%lld\n", connectRopes(arr, sizeof(arr) / sizeof(int)));
    }
    {
        string str = "abcadeecfb";
        std::cout << "Remove Duplicates From String:" << removeDuplicates(str, str.length()) << std::endl;
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree1({1, 2, 3, 4, -1, 2, 4, -1, -1, 4, -1, -1, -1, -1, -1});
        DuplicateSubtrees d;
        vector<int> ans = d.duplicateSubtrees(root);
        printf("Duplicate Subtrees:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree1({1, 2, 3, 4, 5, -1, 6, -1, 7, -1, -1,
                                                         8, -1, 9, -1, -1, 11, 10, -1, -1, -1, -1, -1});
        TopViewOfBinaryTree t;
        vector<int> ans = t.getTopView(root);
        printf("Top View Of Binary Tree:");
        for (auto i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree1({1, 2, 3, 4, -1, 5, 6, -1, 7, -1, -1, -1, -1, -1, -1});
        printf("Maximum Width In Binary Tree: %d\n", getMaxWidth(root));
    }
    {
        Node<int> *head = Node<int>::newLinkList({1, 2, 3, 4, 5});
        head = rotate(head, 2);
        printf("Rotate Linked List:");
        head->printLL();
    }
    {
        int arr[] = {1, 3, 1, 4, 5, 6, 4, 8, 3};
        printf("Maximum Distance:%d\n", maximumDistance(arr, sizeof(arr) / sizeof(int)));
    }
    {
        printf("Distinct Subsequences:%d\n", distinctSubsequences("deed"));
    }
    return 0;
}
