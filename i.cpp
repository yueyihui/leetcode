#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;

template <typename T>
class TreeNode
{
  private:
    bool bubble;

  public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    int height;

    TreeNode(T val)
    {
        this->data = val;
        this->bubble = false;
        left = NULL;
        right = NULL;
        height = 1;
    }

    TreeNode()
    {
        this->data = -1;
        this->bubble = true;
        left = NULL;
        right = NULL;
        height = 1;
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

template <typename T>
class Node
{
  public:
    T data;
    Node<T> *next;
    Node<T> *child;
    Node(T data)
    {
        this->data = data;
        this->next = NULL;
        this->child = NULL;
    }
    static Node<T> *arrayToList(vector<T> &&arr)
    {
        Node<T> *head = NULL;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            Node<int> *temp = new Node<T>(arr[i]);
            temp->next = head;
            head = temp;
        }
        return head;
    }
    void print()
    {
        for (Node<T> *p = this; p != NULL; p = p->next)
        {
            printf(" %d", p->data);
        }
        printf("\n");
    }
};

template <typename T>
class LinkedListNode
{
  public:
    T data;
    LinkedListNode<T> *next;
    LinkedListNode<T> *random;
    LinkedListNode(T data)
    {
        this->data = data;
        this->next = NULL;
    }
    static LinkedListNode<T> *arrayToList(vector<T> &&arr)
    {
        LinkedListNode<T> *head = NULL;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            LinkedListNode<T> *temp = new LinkedListNode<T>(arr[i]);
            temp->next = head;
            head = temp;
        }
        return head;
    }
    void print()
    {
        for (LinkedListNode<T> *p = this; p != NULL; p = p->next)
        {
            printf(" %d", p->data);
        }
        printf("\n");
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
        return l & r & root->data == 0;
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

// https://www.naukri.com/code360/problems/floyd-warshall_2041979
int floydWarshall(int n, int m, int src, int dest, vector<vector<int>> &edges)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        dp[edges[i][0]][edges[i][1]] = edges[i][2];
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dp[i][k] != 1e9 && dp[k][j] != 1e9 &&
                    dp[i][j] > dp[i][k] + dp[k][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j];
                }
            }
        }
    }
    return dp[src][dest];
}

// https://www.naukri.com/code360/problems/prim-s-mst_1095633
// spanning tree
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    vector<pair<int, int>> adj[n + 1];
    for (int i = 0; i < m; i++)
    {
        adj[g[i].first.first].push_back({g[i].first.second, g[i].second});
        adj[g[i].first.second].push_back({g[i].first.first, g[i].second});
    }

    bool visited[n + 1] = {false};
    vector<pair<pair<int, int>, int>> ans;
    auto cmp = [](pair<pair<int, int>, int> &a, pair<pair<int, int>, int> &b)
    {
        return a.second > b.second;
    };
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(cmp)> q(cmp);
    q.push({{0, 1}, 0});
    while (q.empty() == false)
    {
        pair<pair<int, int>, int> temp = q.top();
        q.pop();
        int f = temp.first.first;
        int u = temp.first.second;
        int w = temp.second;
        if (visited[u] == true)
            continue;
        if (f != 0)
            ans.push_back(temp);
        visited[u] = true;
        for (auto v : adj[u])
        {
            if (visited[v.first] == false)
            {
                q.push({{u, v.first}, v.second});
            }
        }
    }
    return ans;
}

// https://www.naukri.com/code360/problems/check-if-the-string-is-a-palindrome_1062633
bool checkPalindrome(string s)
{
    int q = 0, p = s.length() - 1;
    while (q < p)
    {
        if (s[q] < '0' || (s[q] > '9' && s[q] < 'A') ||
            (s[q] > 'Z' && s[q] < 'a') || s[q] > 'z')
        {
            q++;
        }
        else if (s[p] < '0' || (s[p] > '9' && s[p] < 'A') ||
                 (s[p] > 'Z' && s[p] < 'a') || s[p] > 'z')
        {
            p--;
        }
        else if (toupper(s[q]) != toupper(s[p]))
            return false;
        else
        {
            q++;
            p--;
        }
    }
    return true;
}

// https://www.naukri.com/code360/problems/dijkstra-s-shortest-path_920469
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source)
{
    list<pair<int, int>> adj[vertices];
    for (int i = 0; i < edges; i++)
    {
        adj[vec[i][0]].push_back({vec[i][1], vec[i][2]});
        adj[vec[i][1]].push_back({vec[i][0], vec[i][2]});
    }
    auto cmp = [](pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    q.push({source, 0});
    vector<int> dist(vertices, INT_MAX);
    dist[source] = 0;
    while (q.empty() == false)
    {
        auto temp = q.top();
        q.pop();
        int u = temp.first;
        for (auto i = adj[u].begin(); i != adj[u].end(); i++)
        {
            int v = i->first;
            int w = i->second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                q.push({v, dist[v]});
            }
        }
    }
    return dist;
}

// https://www.naukri.com/code360/problems/bellmon-ford_2041977
vector<int> bellmonFord(int n, int m, int src, vector<vector<int>> &edges)
{
    vector<int> dist(n + 1, 100000000);
    dist[src] = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }
    return dist;
}

class DSU
{
  private:
    int *parent;
    int *rank;

  public:
    DSU(int v)
    {
        parent = new int[v + 1];
        rank = new int[v + 1];
        for (int i = 0; i <= v; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int find(int i)
    {
        if (i == parent[i])
            return i;
        else
            return parent[i] = find(parent[i]);
    }
    void union_set(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            rank[a]++;
        }
    }
};

// https://www.naukri.com/code360/problems/kruskal-s-minimum-spanning-tree-algorithm_1082553
int kruskalMST(int n, vector<vector<int>> &edges)
{
    sort(edges.begin(), edges.end(), [](vector<int> &a, vector<int> &b)
         { return a[2] < b[2]; });

    DSU dsu(n);
    int weight = 0;
    for (auto edge : edges)
    {
        if (dsu.find(edge[0]) != dsu.find(edge[1]))
        {
            dsu.union_set(edge[0], edge[1]);
            weight += edge[2];
        }
    }
    return weight;
}

// https://www.naukri.com/code360/problems/distance-between-two-nodes-of-a-tree_800303
class Distance_Two_Nodes_Of_Tree
{
  private:
    TreeNode<int> *lca(TreeNode<int> *root, int node1, int node2)
    {
        if (root == NULL || root->data == node1 || root->data == node2)
            return root;
        TreeNode<int> *l = lca(root->left, node1, node2);
        TreeNode<int> *r = lca(root->right, node1, node2);
        if (l != NULL && r != NULL)
            return root;
        else
            return l != NULL ? l : r;
    }

    int distance(TreeNode<int> *root, int node)
    {
        if (root == NULL)
            return 1e8;
        if (root->data == node)
            return 0;
        int a = distance(root->left, node);
        int b = distance(root->right, node);
        return min(a, b) + 1;
    }

  public:
    int findDistanceBetweenNodes(TreeNode<int> *root, int node1, int node2)
    {
        root = lca(root, node1, node2);
        int a = distance(root, node1);
        int b = distance(root, node2);
        return a + b > 1e8 ? -1 : a + b;
    }
};

// https://www.naukri.com/code360/problems/convert-bst-to-the-greater-sum-tree_800290
class Bst_To_GST
{
  private:
    void inorder(TreeNode<int> *root, int &sum)
    {
        if (root == NULL)
            return;
        inorder(root->right, sum);
        int temp = sum;
        sum += root->data;
        root->data = temp;
        inorder(root->left, sum);
    }

  public:
    TreeNode<int> *convertBstToGreaterSum(TreeNode<int> *root)
    {
        int sum = 0;
        inorder(root, sum);
        return root;
    }
};

// https://www.naukri.com/code360/problems/flatten-the-multi-level-linked-list_839660
Node<int> *flattenMultiLinkedList(Node<int> *head)
{
    Node<int> *tail = head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    for (Node<int> *p = head; p != NULL; p = p->next)
    {
        if (p->child != NULL)
        {
            tail->next = p->child;
            while (tail->next != NULL)
            {
                tail = tail->next;
            }
            p->child = NULL;
        }
    }
    return head;
}

// https://www.naukri.com/code360/problems/clone-linked-list-with-random-pointer_873376
LinkedListNode<int> *cloneRandomList(LinkedListNode<int> *head)
{
    if (head == NULL)
        return head;
    LinkedListNode<int> *cur = head, *n = head;
    while (cur != NULL)
    {
        n = cur->next;
        cur->next = new LinkedListNode<int>(cur->data);
        cur = cur->next;
        cur->next = n;
        cur = cur->next;
    }
    cur = head, n = head;
    while (cur != NULL)
    {
        n = cur->next;
        n->random = cur->random;
        cur = n->next;
    }
    cur = head, n = head->next;
    head = n;
    while (n->next != NULL)
    {
        cur->next = n->next;
        cur = cur->next;
        n->next = cur->next;
        n = n->next;
    }
    cur->next = NULL;
    n->next = NULL;
    return head;
}

// https://www.naukri.com/code360/problems/clone-a-linked-list-with-random-pointers_983604
LinkedListNode<int> *cloneLL(LinkedListNode<int> *head)
{
    for (LinkedListNode<int> *p = head; p != NULL;)
    {
        LinkedListNode<int> *n = p->next;
        p->next = new LinkedListNode<int>(p->data);
        p = p->next;
        p->next = n;
        p = p->next;
    }
    LinkedListNode<int> *new_head = head->next;
    LinkedListNode<int> *a = head, *b = new_head;
    while (b != NULL)
    {
        b->random = a->random;
        if (b->random != NULL)
            b->random = b->random->next;
        a = b->next;
        if (a != NULL)
            b = a->next;
        else
            b = NULL;
    }
    a = head, b = new_head;
    while (b->next != NULL)
    {
        a->next = b->next;
        a = a->next;
        b->next = a->next;
        b = b->next;
    }
    a->next = NULL;
    b->next = NULL;
    return new_head;
}

// https://www.naukri.com/code360/problems/modify-linked-list_1095632
class ModifyLinkedlist
{
  private:
    Node<int> *splite(Node<int> *head)
    {
        Node<int> *fast = head, *slow = head, *pre = NULL;
        while (fast)
        {
            fast = fast->next;
            if (fast)
            {
                fast = fast->next;
                pre = slow;
                slow = slow->next;
            }
        }
        if (pre)
        {
            pre->next = NULL;
        }
        return slow;
    }

    Node<int> *reverse(Node<int> *head)
    {
        Node<int> *pre = NULL, *cur = head;
        while (cur != NULL)
        {
            Node<int> *n = cur->next;
            cur->next = pre;
            pre = cur;
            cur = n;
        }
        return pre;
    }

    // https://www.naukri.com/code360/problems/merge-linkedlist_3125813
    // merge list
    Node<int> *merge(Node<int> *a, Node<int> *b)
    {
        Node<int> *head = a;
        while (a != NULL && b != NULL)
        {
            Node<int> *n = a->next;
            a->next = b;
            a = a->next;
            b = n;
        }
        return head;
    }

  public:
    Node<int> *modifyLL(Node<int> *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        Node<int> *second = splite(head);
        second = reverse(second);
        return merge(head, second);
    }
};

// https://www.naukri.com/code360/problems/smart-linked-list_920439
// linkedlist delete greater(big) value on right side
Node<int> *smartList(Node<int> *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node<int> *rv = smartList(head->next);
    if (rv->data > head->data)
    {
        return rv;
    }
    else
    {
        head->next = rv;
        return head;
    }
}

// https://www.naukri.com/code360/problems/insertion-sort-in-linked-list_1090544
class Insert_Sort_LinkedList
{
  private:
    Node<int> *insert(Node<int> *head, Node<int> *node)
    {
        if (head->next == NULL)
        {
            if (head->data < node->data)
            {
                head->next = node;
                return head;
            }
            else
            {
                node->next = head;
                return node;
            }
        }
        Node<int> *ret = insert(head->next, node);
        if (head->data < ret->data)
        {
            head->next = ret;
            return head;
        }
        else
        {
            ret->next = insert(ret->next, head);
            return ret;
        }
    }

  public:
    Node<int> *insertionSortLL(Node<int> *head)
    {
        Node<int> *newHead = head;
        head = head->next;
        newHead->next = NULL;
        while (head != NULL)
        {
            Node<int> *n = head->next;
            head->next = NULL;
            newHead = insert(newHead, head);
            head = n;
        }
        return newHead;
    }
};

// https://www.naukri.com/code360/problems/insertion-sort-in-linked-list_1090544
Node<int> *insertionSortLL(Node<int> *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    Node<int> *st = head;
    Node<int> *temp = st->next;
    while (temp != nullptr)
    {
        if (temp->data >= st->data)
        {
            st = temp;
            temp = temp->next;
        }
        else
        {
            st->next = temp->next;
            Node<int> *prev = nullptr;
            Node<int> *curr = head;
            while (curr != st && curr->data <= temp->data)
            {
                prev = curr;
                curr = curr->next;
            }
            if (prev == nullptr)
            {
                temp->next = head;
                head = temp;
            }
            else
            {
                temp->next = curr;
                prev->next = temp;
            }
        }
        temp = st->next;
    }
    return head;
}

// https://www.naukri.com/code360/problems/find-pattern-in-string_1112621
// kmp Knuth–Morris–Pratt algorithm
class KMP
{
  private:
    void longestPrefixSuffix(string &p, vector<int> &lps)
    {
        lps[0] = 0;
        int len = 0, i = 1;
        while (i < p.length())
        {
            if (p[i] == p[len])
            {
                len++;
                lps[i] = len;
                i++;
            }
            else
            {
                if (len == 0)
                {
                    lps[i] = 0;
                    i++;
                }
                else
                {
                    len = lps[len - 1];
                }
            }
        }
    }

  public:
    bool findPattern(string p, string s)
    {
        vector<int> lps(p.length(), 0);
        longestPrefixSuffix(p, lps);
        int i = 0, j = 0;
        while (i < s.length())
        {
            if (s[i] == p[j])
            {
                i++;
                j++;
                if (j == p.length())
                    return true;
            }
            else
            {
                if (j == 0)
                {
                    i++;
                }
                else
                {
                    j = lps[j - 1];
                }
            }
        }
        return false;
    }
};

// https://www.naukri.com/code360/problems/two-substrings_920397
// Overlapping ABBA, by KMP
bool findOverlap(string &s)
{
    const char *str = s.c_str();
    const char *i = strstr(str, "AB");
    if (i == NULL)
        return false;
    const char *j = strstr(str, "BA");
    if (j == NULL)
        return false;

    return i + 1 != j && j + 1 != i;
}

// https://www.naukri.com/code360/problems/majority-element_893051
// boyer moore majority vote algorithm
int majorityElement(vector<int> &nums)
{
    int major = -1;
    int vote = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (vote == 0)
        {
            major = nums[i];
            vote = 1;
        }
        else
        {
            if (major == nums[i])
                vote++;
            else
                vote--;
        }
    }
    return major;
}

// https://www.naukri.com/code360/problems/0-1-knapsack_920542
// https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
int knapsack(vector<int> weight, vector<int> value, int n, int W)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (weight[i - 1] <= j)
            {
                dp[i][j] =
                    max(value[i - 1] + dp[i - 1][j - weight[i - 1]], dp[i - 1][j]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W];
}

// https://www.naukri.com/code360/problems/longest-increasing-subsequence_630459
class Longest_Increasing_Subsequence
{
  private:
    int lower_bound(vector<int> &arr, int n, int value)
    {
        if (n == 0)
            return -1;
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] < value)
                l = mid + 1;
            else
                r = mid;
        }
        return arr[r] < value ? -1 : r;
    }

  public:
    int longestIncreasingSubsequence(int arr[], int n)
    {
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            int lb = lower_bound(ans, ans.size(), arr[i]);
            if (lb == -1)
            {
                ans.push_back(arr[i]);
            }
            else
                ans[lb] = arr[i];
        }
        return ans.size();
    }
};

// https://www.naukri.com/code360/problems/two-sum_839653
vector<pair<int, int>> twoSum(vector<int> &arr, int target, int n)
{
    sort(arr.begin(), arr.end());
    vector<pair<int, int>> ans;
    int l = 0, r = n - 1;
    while (l < r)
    {
        int value = arr[l] + arr[r];
        if (value < target)
        {
            l++;
        }
        else if (value > target)
        {
            r--;
        }
        else
        {
            ans.push_back({arr[l], arr[r]});
            l++;
            r--;
        }
    }
    if (ans.size() == 0)
    {
        ans.push_back({-1, -1});
    }
    return ans;
}

// https://www.naukri.com/code360/problems/excel-column-number_630461
long long excelColumnNumber(string input)
{
    long long column = 0;
    for (char c : input)
    {
        int value = c - 'A' + 1;
        column = column * 26 + value;
    }
    return column;
}

class Path_In_A_Tree
{
  private:
    bool find(TreeNode<int> *root, int x, vector<int> &path)
    {
        if (root == NULL)
            return false;
        else if (root->data == x)
        {
            path.push_back(root->data);
            return true;
        }
        else
        {
            path.push_back(root->data);
            if (find(root->left, x, path))
                return true;
            else
            {
                if (find(root->right, x, path))
                    return true;
                else
                    path.pop_back();
            }
        }
        return false;
    }

  public:
    vector<int> pathInATree(TreeNode<int> *root, int x)
    {
        vector<int> path;
        find(root, x, path);
        return path;
    }
};

// https://www.naukri.com/code360/problems/merge-sort-in-place_1118623
class Merge_Sort_In_Place
{
  private:
    void merge(vector<int> &arr, int l, int mid, int r)
    {
        vector<int> temp;
        int i = l, j = mid + 1;
        while (i <= mid && j <= r)
        {
            if (arr[i] < arr[j])
                temp.push_back(arr[i++]);
            else
                temp.push_back(arr[j++]);
        }
        while (i <= mid)
            temp.push_back(arr[i++]);
        while (j <= r)
            temp.push_back(arr[j++]);

        i = l;
        for (; i <= r; i++)
            arr[i] = temp[i - l];
    }

    void _mergeSort(vector<int> &arr, int l, int r)
    {
        if (l < r)
        {
            int mid = l + (r - l) / 2;
            _mergeSort(arr, l, mid);
            _mergeSort(arr, mid + 1, r);
            merge(arr, l, mid, r);
        }
    }

  public:
    vector<int> mergeSort(vector<int> &arr)
    {
        _mergeSort(arr, 0, arr.size() - 1);
        return arr;
    }
};

// https://www.naukri.com/code360/problems/all-prime-numbers_624970
// Sieve of Eratosthenes
void all_prime_numbers(int n)
{
    vector<bool> arr(n + 1, true);
    for (int i = 2; i <= n; i++)
    {
        for (int j = i; j <= n / i; j++)
        {
            arr[j * i] = false;
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (arr[i] == true)
            printf(" %d", i);
    }
}

// https://www.naukri.com/code360/problems/largest-distance-between-two-nodes-in-a-tree_1093218
// largest distance between two nodes in a tree
class Largest_Distance_In_Tree
{
  private:
    pair<int, int> bfs(int start, const vector<vector<int>> &adj)
    {
        vector<bool> visited(adj.size(), false);
        queue<pair<int, int>> q;
        visited[start] = true;
        q.push({start, 0});
        pair<int, int> farthest = {start, 0};

        while (!q.empty())
        {
            int node = q.front().first;
            int dist = q.front().second;
            q.pop();
            farthest = {node, dist};

            for (int neighbor : adj[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push({neighbor, dist + 1});
                }
            }
        }
        return farthest;
    }

  public:
    int largestDistance(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(n);
        for (const auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        pair<int, int> farthestFromRoot = bfs(0, adj);
        pair<int, int> farthestFromFarthest = bfs(farthestFromRoot.first, adj);
        return farthestFromFarthest.second;
    }
};

// https://www.naukri.com/code360/problems/floor-from-bst_920457
int floorInBST(TreeNode<int> *root, int X)
{
    if (root == NULL)
        return -1;
    int rv = floorInBST(root->right, X);
    if (rv != -1)
        return rv;
    else if (root->data <= X)
        return root->data;
    else
        return floorInBST(root->left, X);
}

// https://www.naukri.com/code360/problems/boundary-traversal_790725
class Boundary_Traversal_of_Binary_Tree
{
  private:
    bool isLeaf(TreeNode<int> *root)
    {
        return root->left == NULL && root->right == NULL;
    }
    void addLeftBoundary(TreeNode<int> *root, vector<int> &ans)
    {
        if (root == NULL)
            return;
        TreeNode<int> *cur = root->left;
        while (cur != NULL)
        {
            if (isLeaf(cur) == false)
            {
                ans.push_back(cur->data);
            }
            if (cur->left != NULL)
                cur = cur->left;
            else
                cur = cur->right;
        }
    }
    void addLeaves(TreeNode<int> *root, vector<int> &ans)
    {
        if (isLeaf(root))
        {
            ans.push_back(root->data);
            return;
        }
        if (root->left)
            addLeaves(root->left, ans);
        if (root->right)
            addLeaves(root->right, ans);
    }
    void addRightBoundary(TreeNode<int> *root, vector<int> &ans)
    {
        stack<int> st;
        TreeNode<int> *cur = root->right;
        while (cur)
        {
            if (!isLeaf(cur))
                st.push(cur->data);
            if (cur->right)
                cur = cur->right;
            else
                cur = cur->left;
        }
        while (st.empty() == false)
        {
            ans.push_back(st.top());
            st.pop();
        }
    }

  public:
    vector<int> traverseBoundary(TreeNode<int> *root)
    {
        vector<int> ans;
        if (root == NULL)
            return ans;
        if (isLeaf(root) == false)
            ans.push_back(root->data);
        addLeftBoundary(root, ans);
        addLeaves(root, ans);
        addRightBoundary(root, ans);
        return ans;
    }
};

// https://www.naukri.com/code360/problems/serialise-deserialise-a-binary-tree_920328
class Serialize_and_Deserialize_Binary_Tree
{
  public:
    string serializeTree(TreeNode<int> *root)
    {
        string s = "";
        queue<TreeNode<int> *> q;
        q.push(root);
        while (q.empty() == false)
        {
            TreeNode<int> *temp = q.front();
            q.pop();

            if (temp->data == -1)
            {
                s += "#,";
                continue;
            }
            else
            {
                s += to_string(temp->data);
                s += ',';
            }

            if (temp->left)
                q.push(temp->left);
            else
            {
                q.push(new TreeNode<int>(-1));
            }

            if (temp->right)
                q.push(temp->right);
            else
                q.push(new TreeNode<int>(-1));
        }
        // 1,2,3,#,4,5,#,#,#,#,#,
        return s;
    }

    TreeNode<int> *deserializeTree(string &s)
    {
        int i = 0;
        string str = "";
        while (i < s.length() && s[i] != ',')
        {
            str += s[i];
            i++;
        }
        i++;
        TreeNode<int> *root = new TreeNode<int>(stoi(str));
        queue<TreeNode<int> *> q;
        q.push(root);
        while (i < s.length())
        {
            TreeNode<int> *temp = q.front();
            q.pop();
            if (s[i] != '#')
            {
                str = "";
                while (i < s.length() && s[i] != ',')
                {
                    str += s[i];
                    i++;
                }
                temp->left = new TreeNode<int>(stoi(str));
                q.push(temp->left);
            }
            else
            {
                i++;
            }
            i++; // to skip ,

            if (s[i] != '#')
            {
                str = "";
                while (i < s.length() && s[i] != ',')
                {
                    str += s[i];
                    i++;
                }
                temp->right = new TreeNode<int>(stoi(str));
                q.push(temp->right);
            }
            else
            {
                i++;
            }
            i++; // to skip ,
        }
        return root;
    }
};

// https://www.naukri.com/code360/problems/diagonal-traversal-of-a-binary-tree_920477
// 135 degrees traversal
vector<int> diagonalTraversal(TreeNode<int> *root)
{
    vector<int> ans;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        TreeNode<int> *temp = q.front();
        q.pop();
        for (TreeNode<int> *cur = temp; cur != NULL; cur = cur->right)
        {
            ans.push_back(cur->data);
            if (cur->left)
                q.push(cur->left);
        }
    }
    return ans;
}

// https://www.naukri.com/code360/problems/diagonal-traversal_920391
vector<vector<int>> diagonal(TreeNode<int> *root)
{
    vector<vector<int>> ans;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        vector<int> ans1;
        for (int n = q.size(); n > 0; n--)
        {
            TreeNode<int> *temp = q.front();
            q.pop();
            while (temp != NULL)
            {
                ans1.push_back(temp->data);
                if (temp->left)
                    q.push(temp->left);
                temp = temp->right;
            }
        }
        ans.push_back(ans1);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/bottom-right-view-of-binary-tree_1081489
// 135 degrees
vector<int> bottomRightView(TreeNode<int> *root)
{
    vector<int> ans;
    queue<TreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int n = q.size();
        int last = 0;
        for (int i = 0; i < n; i++)
        {
            TreeNode<int> *temp = q.front();
            q.pop();
            while (temp != NULL)
            {
                if (temp->left)
                    q.push(temp->left);
                if (temp->right == NULL)
                    last = temp->data;
                temp = temp->right;
            }
        }
        ans.push_back(last);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// https://www.naukri.com/code360/problems/kth-missing-element_893215
int missingK(vector<int> vec, int n, int k)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        int diff = vec[mid] - (mid + 1);
        if (diff < k)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l + k;
}

// https://www.naukri.com/code360/problems/construct-a-strict-binary-tree_893101
class Construct_strict_binary_tree
{
  private:
    TreeNode<int> *preorder(vector<int> &pre, vector<char> &typeNL, int &i)
    {
        if (typeNL[i] == 'L')
        {
            return new TreeNode<int>(pre[i++]);
        }
        TreeNode<int> *root = new TreeNode<int>(pre[i++]);
        root->left = preorder(pre, typeNL, i);
        root->right = preorder(pre, typeNL, i);
        return root;
    }

  public:
    TreeNode<int> *constructSBT(vector<int> &pre, vector<char> &typeNL)
    {
        int i = 0;
        return preorder(pre, typeNL, i);
    }
};

// https://www.naukri.com/code360/problems/insertion-in-avl-tree_1263690
class Insertion_in_AVL_Tree
{
  private:
    int heightOf(TreeNode<int> *root)
    {
        if (root == NULL)
            return 0;
        return root->height;
    }

    void updateHeight(TreeNode<int> *root)
    {
        if (root == NULL)
            return;
        root->height = max(heightOf(root->left), heightOf(root->right)) + 1;
    }

    TreeNode<int> *leftRotate(TreeNode<int> *root)
    {
        TreeNode<int> *y = root->right;
        root->right = y->left;
        y->left = root;
        updateHeight(root);
        updateHeight(y);
        return y;
    }

    TreeNode<int> *rightRotate(TreeNode<int> *root)
    {
        TreeNode<int> *y = root->left;
        root->left = y->right;
        y->right = root;
        updateHeight(root);
        updateHeight(y);
        return y;
    }

    TreeNode<int> *insertIntoAvl(TreeNode<int> *root, int data)
    {
        if (root == NULL)
            return new TreeNode<int>(data);

        if (root->data < data)
            root->right = insertIntoAvl(root->right, data);
        else if (root->data > data)
            root->left = insertIntoAvl(root->left, data);

        updateHeight(root);
        int lh = heightOf(root->left);
        int rh = heightOf(root->right);
        if (lh - rh > 1)
        {
            // left left
            if (data < root->left->data)
                return rightRotate(root);
            // left right
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        else if (rh - lh > 1)
        {
            // right right
            if (data > root->right->data)
                return leftRotate(root);
            // right left
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        else
            return root;
    }

  public:
    TreeNode<int> *insertionInAvlTree(vector<int> &allNodeValues, int n)
    {
        TreeNode<int> *root = NULL;
        for (int i = 0; i < n; i++)
        {
            root = insertIntoAvl(root, allNodeValues[i]);
        }
        return root;
    }
};

// https://www.naukri.com/code360/problems/diameter-of-the-binary-tree_920552
class DiameterOfBinaryTree
{
  private:
    int diameter(TreeNode<int> *root, int &dia)
    {
        if (root == NULL)
            return 0;
        int ld = diameter(root->left, dia);
        int rd = diameter(root->right, dia);
        dia = max(ld + rd, dia);
        return max(ld, rd) + 1;
    }

  public:
    int diameterOfBinaryTree(TreeNode<int> *root)
    {
        int dia = 0;
        diameter(root, dia);
        return dia;
    }
};

// https://www.naukri.com/code360/problems/longest-word-made-from-other-words_1229401
// a word is constructed by words
class Longest_Word
{
  private:
    bool canBeConstructed(const string &word, const unordered_set<string> &wordSet)
    {
        for (int i = 1; i < word.size(); ++i)
        {
            string prefix = word.substr(0, i);
            string suffix = word.substr(i);
            if (wordSet.find(prefix) != wordSet.end() &&
                (wordSet.find(suffix) != wordSet.end() || canBeConstructed(suffix, wordSet)))
            {
                return true;
            }
        }
        return false;
    }

  public:
    vector<string> findLongestWordList(vector<string> &wordList)
    {
        sort(wordList.begin(), wordList.end(),
             [](const string &a, const string &b)
             { return a.size() > b.size(); });
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<string> result;
        for (const string &word : wordList)
        {
            if (canBeConstructed(word, wordSet))
            {
                if (result.empty())
                    result.push_back(word);
                else if (result.back().size() == word.size())
                    result.push_back(word);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

// https://www.naukri.com/code360/problems/minimum-swaps-to-convert-binary-tree-into-bst_1118109
// https://www.naukri.com/code360/library/minimum-swap-required-to-convert-binary-tree-to-binary-search-tree
class Minimum_Swaps_To_Convert_Into_BST
{
  private:
    void _inorder(vector<int> &arr, vector<int> &inorder, int i)
    {
        if (i >= arr.size())
            return;
        _inorder(arr, inorder, 2 * i + 1);
        inorder.push_back(arr[i]);
        _inorder(arr, inorder, 2 * i + 2);
    }

  public:
    int minimumSwaps(vector<int> &arr, int n)
    {
        int i = 0, ans = 0;
        vector<vector<int>> dp;
        vector<int> inorder;
        _inorder(arr, inorder, i);
        for (int i = 0; i < n; i++)
        {
            vector<int> temp;
            temp.push_back(inorder[i]);
            temp.push_back(i);
            dp.push_back(temp);
        }
        sort(dp.begin(), dp.end(),
             [](vector<int> &a, vector<int> &b) -> bool
             { return a[0] < b[0]; });
        for (int i = 0; i < n; i++)
        {
            if (i == dp[i][1])
                continue;
            else
            {
                swap(dp[i][0], dp[dp[i][1]][0]);
                swap(dp[i][1], dp[dp[i][1]][1]);
            }
            if (i != dp[i][1])
                i--;
            ans++;
        }
        return ans;
    }
};

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
        string s("N2 i&nJA?a& jnI2n");
        printf("Check If The String Is A Palindrome:%s\n", checkPalindrome(s) == 1 ? "true" : "false");
    }
    {
        vector<vector<int>> edges = {{0, 1, 5}, {0, 2, 8}, {1, 2, 9}, {1, 3, 2}, {2, 3, 6}};
        vector<int> dist = dijkstra(edges, 4, edges.size(), 0);
        printf("Dijkstra's shortest path:");
        for (int w : dist)
        {
            printf(" %d", w);
        }
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({5, 6, 2, 4, 3, -1, -1, 9, 7, -1, -1, -1, -1, -1, -1});
        Distance_Two_Nodes_Of_Tree d;
        printf("Distance between two nodes of a Tree:%d\n", d.findDistanceBetweenNodes(root, 7, 2));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({4, 2, 5, -1, 3, -1, 6, -1, -1, -1, -1});
        Bst_To_GST b;
        root = b.convertBstToGreaterSum(root);
        vector<int> ans = root->toVector();
        printf("Convert Bst To The Greater Sum Tree:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        LinkedListNode<int> *head = LinkedListNode<int>::arrayToList({1, 2, 3, 4, 5});
        LinkedListNode<int> *clone = cloneRandomList(head);
        printf("Copy List with Random Pointer:");
        clone->print();
    }
    {
        Node<int> *head = Node<int>::arrayToList({1, 2, 3, 4});
        ModifyLinkedlist m;
        head = m.modifyLL(head);
        printf("Modify Linked list:");
        head->print();
    }
    {
        Node<int> *head = Node<int>::arrayToList({4, 2, 3, 5, 1});
        Insert_Sort_LinkedList i;
        head = i.insertionSortLL(head);
        printf("Insertion Sort in Linked List:");
        for (Node<int> *i = head; i != NULL; i = i->next)
        {
            printf(" %d", i->data);
        }
        printf("\n");
    }
    {
        Node<int> *head = Node<int>::arrayToList({4, 2, 3, 5, 1});
        head = insertionSortLL(head);
        printf("Insertion Sort in Linked List:");
        for (Node<int> *i = head; i != NULL; i = i->next)
        {
            printf(" %d", i->data);
        }
        printf("\n");
    }
    {
        string str("yxxyxxy");
        string pattern("xxy");
        KMP k;
        printf("Find Pattern in String - KMP Algorithm:%s\n",
               k.findPattern(pattern, str) == true ? "true" : "false");
    }
    {
        vector<int> nums = {4, 2, 1, 4, 4};
        printf("Majority Element:%d\n", majorityElement(nums));
    }
    {
        int arr[] = {5, 4, 11, 1, 16, 8};
        Longest_Increasing_Subsequence lis;
        printf("Longest Increasing Subsequence:%d\n",
               lis.longestIncreasingSubsequence(arr, sizeof(arr) / sizeof(int)));
    }
    {
        vector<int> arr = {2, 7, 11, 13};
        vector<pair<int, int>> ans = twoSum(arr, 9, arr.size());
        printf("Two Sum:");
        for (auto i : ans)
        {
            printf("%d %d\n", i.first, i.second);
        }
    }
    {
        printf("Excel Column Number:%lld\n", excelColumnNumber("AAA"));
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({1, 2, 3, 4, -1, -1, -1, -1, -1});
        Path_In_A_Tree p;
        vector<int> path = p.pathInATree(root, 4);
        printf("Path In A Tree:");
        for (int i : path)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<int> arr = {1, -4, -2, 5, 3};
        Merge_Sort_In_Place m;
        vector<int> ans = m.mergeSort(arr);
        printf("Merge Sort In-Place:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        printf("All prime numbers:");
        all_prime_numbers(20);
        printf("\n");
    }
    {
        TreeNode<int> *root = TreeNode<int>::buildTree({10, 12, -1, 3, -1, 16, -1, 12, -1, 12, -1, -1, -1});
        Serialize_and_Deserialize_Binary_Tree sd;
        string s = sd.serializeTree(root);
        std::cout << "Serialize Binary Tree: " << s << std::endl;
        root = sd.deserializeTree(s);
        vector<int> res = root->toVector();
        std::cout << "Deserialize Binary Tree:";
        for (int i : res)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<string> wordList = {"cat", "banana", "dog", "nana", "my", "walk",
                                   "walker", "baby", "dogwalkers", "s", "babymybaby"};
        Longest_Word lw;
        vector<string> ans = lw.findLongestWordList(wordList);
        std::cout << "Longest Word:";
        for (auto s : ans)
        {
            std::cout << " " << s;
        }
        std::cout << std::endl;
    }
    return 0;
}
