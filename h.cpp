#include <bits/stdc++.h>
#include <ios>
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
    return 0;
}
