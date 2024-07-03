#include "CircularQueue.h"
#include <bits/stdc++.h>
#include <iterator>
#include <stack>
#include <unordered_set>
using namespace std;

class Node
{
  public:
    int data;
    Node *prev;
    Node *next;
    Node()
    {
        this->data = 0;
        this->prev = NULL;
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
    Node(int data, Node *next, Node *prev)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
    static Node *newLinkList(vector<int> &arr)
    {
        Node *head = NULL, *pre = NULL;
        for (auto i : arr)
        {
            if (head == NULL)
            {
                head = new Node(i);
                pre = head;
            }
            else
            {
                pre->next = new Node(i);
                pre = pre->next;
            }
        }
        return head;
    }
    static Node *newLinkList(vector<int> &&arr)
    {
        Node *head = NULL, *pre = NULL;
        for (auto i : arr)
        {
            if (head == NULL)
            {
                head = new Node(i);
                pre = head;
            }
            else
            {
                pre->next = new Node(i);
                pre = pre->next;
            }
        }
        return head;
    }
    static void inorder(Node *head)
    {
        if (head == NULL)
            return;
        inorder(head->prev);
        printf(" %d", head->data);
        inorder(head->next);
    }
};

template <typename T>
class BinaryTreeNode
{
  public:
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    BinaryTreeNode<T> *parent;
    BinaryTreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    static BinaryTreeNode<T> *buildTree(vector<int> &arr, int i)
    {
        if (i >= arr.size())
            return NULL;
        BinaryTreeNode<T> *root = new BinaryTreeNode<T>(arr[i]);
        root->left = buildTree(arr, 2 * i + 1);
        root->right = buildTree(arr, 2 * i + 2);
        return root;
    }
    static BinaryTreeNode<T> *buildTree(vector<int> &&arr, int i)
    {
        if (i >= arr.size())
            return NULL;
        BinaryTreeNode<T> *root = new BinaryTreeNode<T>(arr[i]);
        root->left = buildTree(arr, 2 * i + 1);
        root->right = buildTree(arr, 2 * i + 2);
        return root;
    }
    static BinaryTreeNode<T> *buildTree1(vector<T> &arr)
    {
        return buildTree1(std::move(arr));
    }
    static BinaryTreeNode<T> *buildTree1(vector<T> &&arr)
    {
        int i = 0;
        BinaryTreeNode<T> *root = new BinaryTreeNode<T>(arr[i++]);
        queue<BinaryTreeNode<T> *> q;
        q.push(root);
        while (q.empty() == false && i < arr.size())
        {
            BinaryTreeNode<T> *temp = q.front();
            q.pop();
            if (arr[i] != -1 && arr[i] != '#')
            {
                temp->left = new BinaryTreeNode<T>(arr[i++]);
                q.push(temp->left);
            }
            else
            {
                i++;
            }
            if (arr[i] != -1 && arr[i] != '#')
            {
                temp->right = new BinaryTreeNode<T>(arr[i++]);
                q.push(temp->right);
            }
            else
            {
                i++;
            }
        }
        return root;
    }
    static void preorder(BinaryTreeNode<T> *root);
    void preorder()
    {
        printf(" %d", data);
        if (this->left != NULL)
            this->left->preorder();
        if (this->right != NULL)
            this->right->preorder();
    }
};

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

    ~TreeNode()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }

    static void preorder(TreeNode<T> *root);
    static TreeNode<T> *buildTree2(vector<T> &arr, T i);
};

class SortStack
{
  private:
    void insert(stack<int> &s, int val)
    {
        if (s.empty() || val > s.top())
            s.push(val);
        else
        {
            int t = s.top();
            s.pop();
            insert(s, val);
            s.push(t);
        }
    }

  public:
    void sortStack(stack<int> &s)
    {
        if (s.empty())
            return;
        int t = s.top();
        s.pop();
        sortStack(s);
        insert(s, t);
    }
};

vector<int> nextGreater(vector<int> &arr, int n)
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

string reverseString(string &str)
{
    stack<string> st;
    string a;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            if (a[0] >= 'A')
            {
                st.push(a);
                a.clear();
            }
        }
        else
        {
            a.push_back(str[i]);
        }
    }
    if (a[0] >= 'A')
    {
        st.push(a);
        a.clear();
    }
    while (st.empty() == false)
    {
        a.append(st.top());
        a.push_back(' ');
        st.pop();
    }
    return a;
}

//https://www.codingninjas.com/studio/problems/search-in-rotated-sorted-array_630450?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM
class Search_In_Rotated_Sorted_Array
{
  private:
    int partition(int *arr, int l, int r)
    {
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (arr[0] < arr[mid])
                l = mid + 1;
            else
                r = mid;
        }
        return r == 0 ? r : r - 1;
    }

    int binarySearch(int *arr, int l, int r, int key)
    {
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (arr[mid] == key)
                return mid;
            else if (arr[mid] < key)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }

  public:
    int search(int *arr, int n, int key)
    {
        int pi = partition(arr, 0, n - 1);
        if (arr[0] <= key && key <= arr[pi])
            return binarySearch(arr, 0, pi, key);
        else
            return binarySearch(arr, pi + 1, n - 1, key);
    }
};

class Remove_duplicates_from_DLL
{
  private:
    Node *split(Node *head)
    {
        Node *a = head, *b = head, *pre = NULL;
        while (a != NULL)
        {
            a = a->next;
            if (a != NULL)
            {
                a = a->next;
                pre = b;
                b = b->next;
            }
        }
        if (pre)
        {
            pre->next = NULL;
        }
        return b;
    }

    Node *merge(Node *a, Node *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;
        if (a->data == b->data)
        {
            a->next = merge(a->next, b->next);
            return a;
        }
        else if (a->data < b->data)
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
    Node *removeDuplicates(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        Node *bottom = split(head);
        return merge(removeDuplicates(head), removeDuplicates(bottom));
    }
};

//https://www.codingninjas.com/studio/problems/three-sum_6922132?interviewProblemRedirection=true&count=25&page=2&search=three&sort_entity=order&sort_order=ASC&leftPanelTabValue=SUBMISSION&customSource=studio_nav
class ThreeSum
{
  public:
    vector<vector<int>> triplet(int n, vector<int> &arr)
    {
        sort(arr.begin(), arr.end());
        vector<vector<int>> rv;
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && arr[i - 1] == arr[i])
            {
                continue;
            }
            int l = i + 1, r = n - 1;
            while (l < r)
            {
                if (arr[i] + arr[l] + arr[r] == 0)
                {
                    vector<int> t = {arr[i], arr[l], arr[r]};
                    rv.push_back(t);
                    for (l++; l < r && arr[l - 1] == arr[l]; l++)
                        ;
                    for (r--; r > l && arr[r + 1] == arr[r]; r--)
                        ;
                }
                else if (arr[i] + arr[l] + arr[r] < 0)
                    l++;
                else
                    r--;
            }
        }
        return rv;
    }
};

//https://www.codingninjas.com/studio/problems/longest-unique-substring_630418?interviewProblemRedirection=true&count=25&page=2&search=&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&company%5B%5D=Apple
int uniqueSubstrings(string str)
{
    vector<int> lastIndex(256, -1);
    int j = 0, ans = 0;
    for (int i = 0; i < str.length(); i++)
    {
        j = max(j, lastIndex[str[i]] + 1);
        ans = max(ans, i - j + 1);
        lastIndex[str[i]] = i;
    }
    return ans;
}

//https://www.codingninjas.com/studio/problems/right-view_764605?interviewProblemRedirection=true&count=25&page=2&search=&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&company%5B%5D=Apple
class RightView
{
  private:
    void rightview(BinaryTreeNode<int> *root, int level, vector<int> &ans)
    {
        if (root == NULL)
            return;
        if (ans.size() == level)
            ans.push_back(root->data);
        rightview(root->right, level + 1, ans);
        rightview(root->left, level + 1, ans);
    }

  public:
    vector<int> printRightView(BinaryTreeNode<int> *root)
    {
        vector<int> ans;
        rightview(root, 0, ans);
        return ans;
    }
};

//https://www.naukri.com/code360/problems/left-view-of-a-binary-tree_920519?leftPanelTabValue=PROBLEM&count=25
class LeftView
{
  private:
    void leftView(BinaryTreeNode<int> *root, vector<int> &ans, int i)
    {
        if (root == NULL)
            return;
        if (i == ans.size())
        {
            ans.push_back(root->data);
        }
        leftView(root->left, ans, i + 1);
        leftView(root->right, ans, i + 1);
    }

  public:
    vector<int> printLeftView(BinaryTreeNode<int> *root)
    {
        vector<int> ans;
        leftView(root, ans, 0);
        return ans;
    }
};

//https://www.geeksforgeeks.org/minimum-count-of-numbers-required-from-given-array-to-represent-s/
int findMinCountToReachSum(int sum, vector<int> components)
{
    vector<int> numWays(sum + 1, INT_MAX - 1);
    numWays[0] = 0;
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 0; j < components.size(); j++)
        {
            if (i >= components[j])
            {
                numWays[i] = min(numWays[i], numWays[i - components[j]] + 1);
            }
        }
    }
    return numWays[sum] == INT_MAX - 1 ? -1 : numWays[sum];
}

Node *findIntersection(Node *firstHead, Node *secondHead)
{
    if (firstHead == NULL || secondHead == NULL)
        return NULL;
    unordered_set<Node *> set;
    while (firstHead != NULL)
    {
        set.insert(firstHead);
        firstHead = firstHead->next;
    }
    while (secondHead != NULL)
    {
        if (set.find(secondHead) != set.end())
            return secondHead;
        else
            secondHead = secondHead->next;
    }
    return NULL;
}

//https://www.codingninjas.com/studio/problems/find-number-of-islands_630512?interviewProblemRedirection=true&count=25
class Find_Number_Of_Islands
{
  private:
    void bfs(vector<vector<bool>> &visited, int i, int j, vector<vector<int>> &arr, int n, int m)
    {
        visited[i][j] = true;
        queue<pair<int, int>> q;
        q.push({i, j});
        while (q.empty() == false)
        {
            pair<int, int> coordinate = q.front();
            q.pop();
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int a = coordinate.first + row;
                    int b = coordinate.second + col;
                    if (a >= 0 && a < n && b >= 0 && b < m && arr[a][b] == 1 &&
                        visited[a][b] == false)
                    {
                        visited[a][b] = true;
                        q.push({a, b});
                    }
                }
            }
        }
    }

  public:
    int getTotalIslands(vector<vector<int>> &arr, int n, int m)
    {
        int counter = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (arr[i][j] == 1 && visited[i][j] == false)
                {
                    counter++;
                    bfs(visited, i, j, arr, n, m);
                }
            }
        }
        return counter;
    }
};

//https://www.codingninjas.com/studio/problems/identical-trees_799364?interviewProblemRedirection=true&count=25
bool identicalTrees(BinaryTreeNode<int> *root1, BinaryTreeNode<int> *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;
    else if (root1 != NULL && root2 != NULL && root1->data == root2->data)
    {
        if (identicalTrees(root1->left, root2->left))
            return identicalTrees(root1->right, root2->right);
        else
            return false;
    }
    else
        return false;
}

//https://www.codingninjas.com/studio/problems/remove-duplicates-from-sorted-array_1102307?interviewProblemRedirection=true&count=25
int removeDuplicates(vector<int> &arr, int n)
{
    int i = 0, j = 1;
    while (j < n)
    {
        if (arr[i] != arr[j])
        {
            i++;
            arr[i] = arr[j];
        }
        j++;
    }
    return i + 1;
}

//https://www.codingninjas.com/studio/problems/add-two-linked-lists_799487?interviewProblemRedirection=true&count=25
class Add_Two_Numbers
{
  private:
    Node *reverse(Node *p)
    {
        Node *pre = NULL, *cur = p;
        while (cur != NULL)
        {
            Node *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }

  public:
    Node *addTwoLists(Node *first, Node *second)
    {
        first = reverse(first);
        second = reverse(second);
        Node *head = NULL, *p = NULL;
        int carry = 0;
        while (first != NULL && second != NULL)
        {
            int val = first->data + second->data + carry;
            if (val >= 10)
            {
                carry = 1;
                val -= 10;
            }
            else
            {
                carry = 0;
            }
            if (head == NULL)
            {
                head = new Node(val);
                p = head;
            }
            else
            {
                p->next = new Node(val);
                p = p->next;
            }
            first = first->next;
            second = second->next;
        }
        while (first != NULL)
        {
            int val = first->data + carry;
            if (val >= 10)
            {
                carry = 1;
                val -= 10;
            }
            else
            {
                carry = 0;
            }
            p->next = new Node(val);
            p = p->next;
            first = first->next;
        }
        while (second != NULL)
        {
            int val = second->data + carry;
            if (val >= 10)
            {
                carry = 1;
                val -= 10;
            }
            else
            {
                carry = 0;
            }
            p->next = new Node(val);
            p = p->next;
            second = second->next;
        }
        if (carry == 1)
        {
            p->next = new Node(1);
            p = p->next;
        }
        return reverse(head);
    }
};

vector<vector<int>> mergeIntervals(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(),
         [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
    vector<vector<int>> res = {{intervals[0][0], intervals[0][1]}};
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] <= res.back()[1] && res.back()[1] <= intervals[i][1])
        {
            res.back()[1] = intervals[i][1];
        }
        else if (intervals[i][1] <= res.back()[1])
        {
        }
        else if (res.back()[1] < intervals[i][0])
        {
            res.push_back({intervals[i][0], intervals[i][1]});
        }
    }
    return res;
}

class Palindrome_Linked_List
{
  private:
    vector<int> ll2Vec(Node *head)
    {
        vector<int> res;
        while (head != NULL)
        {
            res.push_back(head->data);
            head = head->next;
        }
        return res;
    }

  public:
    bool isPalindrome(Node *head)
    {
        vector<int> arr = ll2Vec(head);
        int l = 0, r = arr.size() - 1;
        while (l < r)
        {
            if (arr[l] == arr[r])
            {
                l++;
                r--;
            }
            else
                return false;
        }
        return true;
    }
};

//https://www.codingninjas.com/studio/problems/palindrome-partitioning_799931?interviewProblemRedirection=true&count=25
class Palindrome_Partition
{
  private:
    bool isPalin(string &s, int l, int r)
    {
        while (l < r)
        {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    void findPalin(string &s, int start, vector<vector<string>> &res, vector<string> &r)
    {
        if (start >= s.length())
        {
            res.push_back(r);
            return;
        }

        for (int end = start; end < s.length(); end++)
        {
            if (isPalin(s, start, end))
            {
                r.push_back(s.substr(start, end - start + 1));
                findPalin(s, end + 1, res, r);
                r.pop_back();
            }
        }
    }

  public:
    vector<vector<string>> partition(string &s)
    {
        vector<string> r;
        vector<vector<string>> res;
        findPalin(s, 0, res, r);
        return res;
    }
};

//https://www.codingninjas.com/studio/problems/reset-matrix_920040?interviewProblemRedirection=true&count=25
vector<vector<int>> findGoodMatrix(vector<vector<int>> &arr)
{
    vector<int> row(arr.size(), 1), col(arr.front().size(), 1);
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.front().size(); j++)
        {
            if (arr[i][j] == 0)
            {
                row[i] = 0;
                col[j] = 0;
            }
        }
    }
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] == 0)
        {
            for (int j = 0; j < arr.front().size(); j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < col.size(); i++)
    {
        if (col[i] == 0)
        {
            for (int j = 0; j < arr.size(); j++)
            {
                arr[j][i] = 0;
            }
        }
    }
    return arr;
}

//https://www.codingninjas.com/studio/problems/spiral-matrix_840698?interviewProblemRedirection=true&count=25
vector<int> spiralPathMatrix(vector<vector<int>> matrix, int n, int m)
{
    vector<int> ans;
    vector<pair<int, int>> path;
    int lE = 0, rE = m - 1;
    int tE = 0, bE = n - 1;
    while (lE <= rE && tE <= bE)
    {
        for (int i = lE; i <= rE; i++)
        {
            path.push_back({tE, i});
        }
        tE++;
        if (tE > bE)
            break;
        for (int i = tE; i <= bE; i++)
        {
            path.push_back({i, rE});
        }
        rE--;
        if (lE > rE)
            break;
        for (int i = rE; i >= lE; i--)
        {
            path.push_back({bE, i});
        }
        bE--;
        if (tE > bE)
            break;
        for (int i = bE; i >= tE; i--)
        {
            path.push_back({i, lE});
        }
        lE++;
    }
    for (int i = 0; i < path.size(); i++)
    {
        auto p = path[i];
        ans.push_back({matrix[p.first][p.second]});
    }
    return ans;
}

//https://www.naukri.com/code360/problems/spiral-matrix_800309
vector<long> spiralPathMatrix(vector<vector<long>> matrix, long n, long m)
{
    vector<long> ans;
    int left = 0, right = m - 1, top = 0, bottom = n - 1;
    int dir = 0;
    while (left <= right && top <= bottom)
    {
        if (dir == 0)
        {
            for (int i = left; i <= right; i++)
            {
                ans.push_back(matrix[top][i]);
            }
            top++;
        }
        else if (dir == 1)
        {
            for (int i = top; i <= bottom; i++)
            {
                ans.push_back(matrix[i][right]);
            }
            right--;
        }
        else if (dir == 2)
        {
            for (int i = right; i >= left; i--)
            {
                ans.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        else if (dir == 3)
        {
            for (int i = bottom; i >= top; i--)
            {
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
        dir = (dir + 1) % 4;
    }
    return ans;
}

//https://www.codingninjas.com/studio/problems/sorted-linked-list-to-balanced-bst_842564?interviewProblemRedirection=true&count=25
class Sorted_Linked_List_to_Balanced_BST
{
  private:
    TreeNode<int> *rightRotate(TreeNode<int> *root)
    {
        TreeNode<int> *y = root->left;
        TreeNode<int> *T = y->right;
        y->right = root;
        root->left = T;
        return y;
    }

    TreeNode<int> *leftRotate(TreeNode<int> *root)
    {
        TreeNode<int> *y = root->right;
        TreeNode<int> *T = y->left;
        y->left = root;
        root->right = T;
        return y;
    }

    int height(TreeNode<int> *root)
    {
        if (root == NULL)
            return 0;
        int a = height(root->left);
        int b = height(root->right);
        return a > b ? a + 1 : b + 1;
    }

    TreeNode<int> *insertAVL(TreeNode<int> *root, int data)
    {
        if (root == NULL)
            return new TreeNode<int>(data);
        else if (data < root->data)
            root->left = insertAVL(root->left, data);
        else if (data > root->data)
            root->right = insertAVL(root->right, data);
        int l_h = height(root->left);
        int r_h = height(root->right);
        if (l_h - r_h > 1)
        {
            // left left case
            if (data < root->left->data)
            {
                return rightRotate(root);
            }
            else
            { // left right case
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        else if (r_h - l_h > 1)
        {
            // right right case
            if (data > root->right->data)
            {
                return leftRotate(root);
            }
            else
            { // right left case
                root->right = rightRotate(root->right);
                return leftRotate(root->right);
            }
        }
        else
            return root;
    }

  public:
    TreeNode<int> *sortedListToBST(Node *head)
    {
        TreeNode<int> *root = NULL;
        while (head != NULL)
        {
            root = insertAVL(root, head->data);
            head = head->next;
        }
        return root;
    }
};

template <typename T>
void TreeNode<T>::preorder(TreeNode<T> *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void BinaryTreeNode<T>::preorder(BinaryTreeNode<T> *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

//https://www.codingninjas.com/studio/problems/partition_1172151?interviewProblemRedirection=true&count=25
Node *findPartition(Node *head, int x)
{
    if (head == NULL)
        return NULL;
    if (head->data < x)
    {
        head->next = findPartition(head->next, x);
        return head;
    }
    else
    {
        Node *p = head, *pre = NULL;
        while (p != NULL && p->data >= x)
        {
            pre = p;
            p = p->next;
        }
        if (p == NULL)
        {
            return head;
        }
        else
        {
            pre->next = p->next;
            p->next = findPartition(head, x);
            return p;
        }
    }
}

//https://www.codingninjas.com/studio/problems/reverse-vowels-in-a-string_1231000?interviewProblemRedirection=true&count=25
class Reverse_vowels
{
  private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

  public:
    string reverseVowels(string &s)
    {
        int l = 0, r = s.length() - 1;
        while (l < r)
        {
            if (isVowel(s[l]) && isVowel(s[r]))
            {
                swap(s[l], s[r]);
                l++;
                r--;
            }
            else if (isVowel(s[l]))
            {
                r--;
            }
            else if (isVowel(s[r]))
                l++;
            else
            {
                l++;
                r--;
            }
        }
        return s;
    }
};

//https://www.codingninjas.com/studio/problems/minimal-tree_1214534?interviewProblemRedirection=true&count=25
class Minimal_Tree
{
  private:
    BinaryTreeNode<int> *buildTree(vector<int> &arr, int l, int r)
    {
        if (l > r)
            return NULL;

        int mid = l + (r - l) / 2;
        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(arr[mid]);
        root->left = buildTree(arr, l, mid - 1);
        root->right = buildTree(arr, mid + 1, r);
        return root;
    }

  public:
    BinaryTreeNode<int> *minimalTree(vector<int> &arr)
    {
        return buildTree(arr, 0, arr.size() - 1);
    }
};

BinaryTreeNode<int> *modifyTree(BinaryTreeNode<int> *root, int low, int high)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->data < low)
    {
        return modifyTree(root->right, low, high);
    }
    else if (root->data > high)
    {
        return modifyTree(root->left, low, high);
    }
    else
    {
        root->left = modifyTree(root->left, low, high);
        root->right = modifyTree(root->right, low, high);
        return root;
    }
}

bool findBinaryTreeNode(BinaryTreeNode<int> *root, int data)
{
    if (root == NULL)
        return false;
    if (root->data == data)
        return true;
    else
        return findBinaryTreeNode(root->left, data) || findBinaryTreeNode(root->right, data);
}

//https://www.naukri.com/code360/problems/range-sum-of-bst_1262280
int rangeSum(TreeNode<int> *root, int low, int high)
{
    if (root == NULL)
        return 0;
    int l = rangeSum(root->left, low, high);
    int r = rangeSum(root->right, low, high);
    if (root->data >= low and root->data <= high)
        return root->data + l + r;
    else
        return l + r;
}

template <typename T>
TreeNode<T> *TreeNode<T>::buildTree2(vector<T> &arr, T i)
{
    if (i >= arr.size())
        return NULL;
    TreeNode<T> *root = new TreeNode<T>(arr[i]);
    root->left = buildTree2(arr, 2 * i + 1);
    root->right = buildTree2(arr, 2 * i + 2);
    return root;
}

Node *partitionList(Node *head, int k)
{
    if (head == NULL)
        return NULL;

    if (head->data < k)
    {
        head->next = partitionList(head->next, k);
        return head;
    }
    else
    {
        Node *p = head, *pre = NULL;
        while (p != NULL && p->data >= k)
        {
            pre = p;
            p = p->next;
        }
        if (p != NULL)
        {
            pre->next = p->next;
            p->next = partitionList(head, k);
            return p;
        }
        else
        {
            return head;
        }
    }
}

//https://www.codingninjas.com/studio/problems/next-greater-node-in-linked-list_1262083?interviewProblemRedirection=true&count=25
class NextGreaterNode
{
  private:
    void deep(stack<int> &a, stack<int> &s, Node *head)
    {
        if (head->next != NULL)
            deep(a, s, head->next);
        if (s.empty())
        {
            a.push(0);
        }
        else
        {
            while (s.empty() == false && s.top() <= head->data)
            {
                s.pop();
            }
            if (s.empty())
                a.push(0);
            else
                a.push(s.top());
        }
        s.push(head->data);
    }

  public:
    vector<int> findNextGreaterNodeList(Node *head)
    {
        vector<int> res;
        stack<int> a, s;
        deep(a, s, head);
        while (a.empty() == false)
        {
            res.push_back(a.top());
            a.pop();
        }
        return res;
    }
};

Node *findKthFromLast(Node *head, int k)
{
    Node *q = head, *p = head;
    for (int i = 0; i < k; i++)
    {
        p = p->next;
    }
    while (p != NULL)
    {
        q = q->next;
        p = p->next;
    }
    return q;
}

class FlattenBinaryTreetoLinkedList
{
  private:
    TreeNode<int> *flatten(TreeNode<int> *root)
    {
        if (root == NULL)
            return NULL;
        root->left = flatten(root->left);
        root->right = flatten(root->right);
        TreeNode<int> *tmp = root->right;
        root->right = root->left;
        root->left = NULL;
        TreeNode<int> *p = root;
        while (p->right != NULL)
        {
            p = p->right;
        }
        p->right = tmp;
        return root;
    }

  public:
    void flattenBinaryTree(TreeNode<int> *root) { root = flatten(root); }
};

class ListToTree
{
  private:
    Node *getMid(Node *head)
    {
        Node *fast = head, *slow = head, *pre = NULL;
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
        if (pre != NULL)
        {
            pre->next = NULL;
        }
        return slow;
    }

    Node *tree(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        Node *mid = getMid(head);
        Node *left = head;
        Node *right = mid->next;
        mid->prev = tree(left);
        mid->next = tree(right);
        return mid;
    }

  public:
    Node *listToTree(Node *head)
    {
        Node *p = head;
        while (p != NULL)
        {
            p->prev = NULL;
            p = p->next;
        }
        return tree(head);
    }
};

class MergePointOfTwoLinkedLists
{
  private:
    int length(Node *head)
    {
        int n = 0;
        while (head != NULL)
        {
            n++;
            head = head->next;
        }
        return n;
    }

  public:
    int findIntersection(Node *firstHead, Node *secondHead)
    {
        int f = length(firstHead);
        int s = length(secondHead);
        if (f > s)
        {
            for (int i = 0; i < f - s; i++)
            {
                firstHead = firstHead->next;
            }
        }
        else
        {
            for (int i = 0; i < s - f; i++)
            {
                secondHead = secondHead->next;
            }
        }
        while (firstHead != NULL && secondHead != NULL && firstHead != secondHead)
        {
            firstHead = firstHead->next;
            secondHead = secondHead->next;
        }
        return firstHead == NULL ? -1 : firstHead->data;
    }
};

Node *linkedListCat(Node *a, Node *b)
{
    Node *p = a;
    while (p->next != NULL)
        p = p->next;
    p->next = b;
    return a;
}

//https://www.naukri.com/code360/problems/is-binary-heap-tree_893136
bool isBinaryHeapTree(BinaryTreeNode<int> *root)
{
    if (root == NULL)
        return false;
    bool last = false;
    queue<BinaryTreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        BinaryTreeNode<int> *cur = q.front();
        q.pop();

        if (cur->left)
        {
            if (last || cur->left->data > cur->data)
                return false;
            else
                q.push(cur->left);
        }
        else
            last = true;

        if (cur->right)
        {
            if (last || cur->right->data > cur->data)
                return false;
            else
                q.push(cur->right);
        }
        else
            last = true;
    }
    return true;
}

//https://www.naukri.com/code360/problems/sum-tree_10373?interviewProblemRedirection=true&count=25
class SumTree
{
  private:
    void preorder(BinaryTreeNode<int> *root, vector<int> &ans)
    {
        if (root == NULL)
            return;
        ans.push_back(root->data);
        preorder(root->left, ans);
        preorder(root->right, ans);
    }

  public:
    vector<int> sumTree(BinaryTreeNode<int> *root)
    {
        queue<BinaryTreeNode<int> *> q;
        q.push(root);
        while (q.empty() == false)
        {
            BinaryTreeNode<int> *cur = q.front();
            q.pop();
            cur->data = 0;
            if (cur->left)
            {
                cur->data += cur->left->data;
                q.push(cur->left);
            }
            if (cur->right)
            {
                cur->data += cur->right->data;
                q.push(cur->right);
            }
        }
        vector<int> ans;
        preorder(root, ans);
        return ans;
    }
};

class ReverseLL
{
  private:
    void reverse(Node *q, Node *p)
    {
        Node *cur = q, *pre = NULL;
        while (cur != p)
        {
            Node *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        cur->next = pre;
    }

  public:
    Node *reverseLL(Node *head, int low, int high)
    {
        Node *q = head, *p = head;
        for (int i = 0; i < high - low; i++)
        {
            p = p->next;
        }
        Node *pre = NULL;
        for (int i = 1; i < low; i++)
        {
            pre = q;
            q = q->next;
            p = p->next;
        }
        Node *temp = p->next;
        reverse(q, p);
        q->next = temp;
        if (pre)
        {
            pre->next = p;
            return head;
        }
        else
        {
            return p;
        }
    }
};

//https://www.naukri.com/code360/problems/delete-node-in-ll_5881?count=25&search=linked&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=NOT_ATTEMPTED
Node *deleteNode(Node *head, int pos)
{
    Node *cur = head, *pre = NULL;
    while (pos > 0 && cur != NULL)
    {
        pre = cur;
        cur = cur->next;
        pos--;
    }
    if (cur == NULL)
        return head;
    else
    {
        if (pre == NULL)
            return cur->next;
        else
        {
            pre->next = cur->next;
            return head;
        }
    }
}

int findNode(Node *head, int n)
{
    Node *p = head;
    int i = 0;
    while (p != NULL && p->data != n)
    {
        i++;
        p = p->next;
    }
    return p == NULL ? -1 : i;
}

class DeletionInCircularLinkedList
{
  public:
    Node *deleteNode(Node *head, int key)
    {
        if (head == NULL)
            return NULL;
        else if (head->next == head)
        {
            if (head->data == key)
            {
                delete head;
                head = NULL;
            }
            return head;
        }
        else if (head->data == key)
        {
            Node *n = head;
            for (; n->next != head; n = n->next)
                ;
            n->next = head->next;
            delete head;
            return n->next;
        }
        else
        {
            for (Node *pre = head, *p = head->next; p != head; pre = p, p = p->next)
            {
                if (p->data == key)
                {
                    pre->next = p->next;
                    delete p;
                    return head;
                }
            }
            return head;
        }
    }
};

class MergeSortLinkedList
{
  private:
    Node *splite(Node *head)
    {
        Node *fast = head, *slow = head, *pre = NULL;
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
        if (pre != NULL)
        {
            pre->next = NULL;
        }
        return slow;
    }

    Node *merge(Node *a, Node *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;

        if (a->data < b->data)
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
    Node *mergeSort(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node *buttom = splite(head);
        return merge(mergeSort(head), mergeSort(buttom));
    }
};

Node *sortList(Node *head)
{
    int count[3] = {0};
    Node *n = head;
    for (; n != NULL; n = n->next)
    {
        count[n->data]++;
    }
    n = head;
    for (int i = 0; i < 3; i++)
    {
        while (count[i]-- > 0)
        {
            n->data = i;
            n = n->next;
        }
    }
    return head;
}

//https://www.naukri.com/code360/problems/linked-list-to-binary-tree_981256?count=25&search=linked&sort_entity=order&sort_order=ASC&leftPanelTabValue=PROBLEM&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&page=2
BinaryTreeNode<int> *LLtoTree(Node *head)
{
    if (head == NULL)
        return NULL;
    queue<BinaryTreeNode<int> *> q;
    Node *n = head;
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(n->data);
    n = n->next;
    q.push(root);
    while (q.empty() == false)
    {
        BinaryTreeNode<int> *t = q.front();
        q.pop();
        if (n != NULL)
        {
            t->left = new BinaryTreeNode<int>(n->data);
            n = n->next;
            q.push(t->left);
        }
        if (n != NULL)
        {
            t->right = new BinaryTreeNode<int>(n->data);
            n = n->next;
            q.push(t->right);
        }
    }
    return root;
}

//https://www.naukri.com/code360/problems/add-linked-lists_920495?count=25&search=add%20lin&sort_entity=order&sort_order=ASC&leftPanelTabValue=SUBMISSION&customSource=studio_nav&attempt_status=NOT_ATTEMPTED&page=1
Node *addLL(Node *head1, Node *head2)
{
    stack<int> q1;
    stack<int> q2;
    while (head1 != NULL)
    {
        q1.push(head1->data);
        head1 = head1->next;
    }
    while (head2 != NULL)
    {
        q2.push(head2->data);
        head2 = head2->next;
    }
    Node *i = NULL;
    int carry = 0;
    while (q1.empty() == false && q2.empty() == false)
    {
        int t1 = q1.top();
        q1.pop();
        int t2 = q2.top();
        q2.pop();
        Node *j = new Node(t1 + t2 + carry);
        if (j->data >= 10)
        {
            j->data %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        j->next = i;
        i = j;
    }
    while (q1.empty() == false)
    {
        int t = q1.top();
        q1.pop();
        Node *j = new Node(t + carry);
        if (j->data >= 10)
        {
            j->data %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        j->next = i;
        i = j;
    }
    while (q2.empty() == false)
    {
        int t = q2.top();
        q2.pop();
        Node *j = new Node(t + carry);
        if (j->data >= 10)
        {
            j->data %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        j->next = i;
        i = j;
    }
    if (carry == 1)
    {
        Node *j = new Node(1);
        j->next = i;
        i = j;
    }
    while (i->data == 0 && i->next != NULL)
    {
        i = i->next;
    }
    return i;
}

class QuickSortOnLinkedList
{
  private:
    Node *getTail(Node *head)
    {
        while (head != NULL && head->next != NULL)
        {
            head = head->next;
        }
        return head;
    }

    Node *partition(Node *head, Node *tail)
    {
        Node *pi = head;
        for (Node *j = head; j != tail; j = j->next)
        {
            if (j->data < tail->data)
            {
                swap(head->data, j->data);
                pi = head;
                head = head->next;
            }
        }
        swap(head->data, tail->data);
        return pi;
    }

    void quickSort(Node *head, Node *tail)
    {
        if (head == NULL || head == tail)
            return;
        Node *pi = partition(head, tail);
        quickSort(head, pi);
        quickSort(pi->next, tail);
    }

  public:
    Node *quickSortLL(Node *head)
    {
        if (head != NULL && head->next != NULL)
        {
            quickSort(head, getTail(head));
        }
        return head;
    }
};

vector<int> printLeftRightMostNodes(BinaryTreeNode<int> *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    queue<BinaryTreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            BinaryTreeNode<int> *f = q.front();
            q.pop();
            if (i == 0 || i == n - 1)
                ans.push_back(f->data);
            if (f->left != NULL)
                q.push(f->left);
            if (f->right != NULL)
                q.push(f->right);
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/count-subtrees_920526
//Cisco rangeSum
class CountSubtrees
{
  private:
    bool getCount(BinaryTreeNode<int> *root, int low, int high, int &count)
    {
        if (root == NULL)
            return true;
        bool l = getCount(root->left, low, high, count);
        bool r = getCount(root->right, low, high, count);
        if (l & r & (low <= root->data && root->data <= high))
        {
            count++;
            return true;
        }
        return false;
    }

  public:
    int getCount(BinaryTreeNode<int> *root, int low, int high)
    {
        int count = 0;
        getCount(root, low, high, count);
        return count;
    }
};

//https://www.naukri.com/code360/problems/convert-binary-tree-to-mirror-tree_873140
class MirrorTree
{
  private:
    BinaryTreeNode<int> *mirror(BinaryTreeNode<int> *root)
    {
        if (root == NULL || (root->left == NULL && root->right == NULL))
            return root;

        BinaryTreeNode<int> *temp = root->right;
        root->right = mirror(root->left);
        root->left = mirror(temp);
        return root;
    }

  public:
    void mirrorTree(BinaryTreeNode<int> *root)
    {
        if (root == NULL)
            return;
        root = mirror(root);
    }
};

//https://www.naukri.com/code360/problems/isomorphic-trees_794946
bool checkTree(BinaryTreeNode<int> *tree1, BinaryTreeNode<int> *tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;
    if (tree1->data != tree2->data)
        return false;
    return checkTree(tree1->left, tree2->left) && checkTree(tree1->right, tree2->right) ||
           checkTree(tree1->left, tree2->right) && checkTree(tree1->right, tree2->left);
}

//https://www.naukri.com/code360/problems/binary-tree-to-bst_893074
//Note: The conversion must be done in such a way that keeps the original structure of the Binary Tree.
class BinaryTreeToBST
{
  private:
    void preorder(BinaryTreeNode<int> *root, deque<int> &arr)
    {
        if (root == NULL)
            return;
        arr.push_back(root->data);
        preorder(root->left, arr);
        preorder(root->right, arr);
    }

    void inorder(BinaryTreeNode<int> *root, deque<int> &arr)
    {
        if (root == NULL)
            return;
        inorder(root->left, arr);
        root->data = arr.front();
        arr.pop_front();
        inorder(root->right, arr);
    }

  public:
    BinaryTreeNode<int> *binaryTreeToBst(BinaryTreeNode<int> *root)
    {
        deque<int> arr;
        preorder(root, arr);
        sort(arr.begin(), arr.end());
        inorder(root, arr);
        return root;
    }
};

//https://www.naukri.com/code360/problems/spiral-order-traversal-of-a-binary-tree_630521
vector<int> spiralOrder(BinaryTreeNode<int> *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    stack<BinaryTreeNode<int> *> s1, s2;
    s1.push(root);
    while (s1.empty() == false || s2.empty() == false)
    {
        while (s1.empty() == false)
        {
            BinaryTreeNode<int> *temp = s1.top();
            s1.pop();
            ans.push_back(temp->data);
            if (temp->left != NULL)
            {
                s2.push(temp->left);
            }
            if (temp->right != NULL)
            {
                s2.push(temp->right);
            }
        }
        while (s2.empty() == false)
        {
            BinaryTreeNode<int> *temp = s2.top();
            s2.pop();
            ans.push_back(temp->data);
            if (temp->right != NULL)
            {
                s1.push(temp->right);
            }
            if (temp->left != NULL)
            {
                s1.push(temp->left);
            }
        }
    }
    return ans;
}

//https://www.naukri.com/code360/problems/sum-of-k-smallest-elements-in-bst_920525
class SumOfKSmallestElementsInBST
{
  private:
    void preorder(BinaryTreeNode<int> *root, vector<int> &small, const int k)
    {
        if (root == NULL)
        {
            return;
        }
        preorder(root->left, small, k);
        if (small.size() < k)
            small.push_back(root->data);
        preorder(root->right, small, k);
    }

  public:
    long ksmallestElementSum(BinaryTreeNode<int> *root, int k)
    {
        vector<int> small;
        preorder(root, small, k);
        long sum = 0;
        for (int i : small)
        {
            sum += i;
        }
        return sum;
    }
};

//https://www.naukri.com/code360/problems/elements-in-two-bsts_981278
//2 vector merge sort
class ElementsInTwoBSTs
{
  private:
    void preorder(BinaryTreeNode<int> *root, vector<int> &res)
    {
        if (root == NULL)
            return;
        preorder(root->left, res);
        res.push_back(root->data);
        preorder(root->right, res);
    }

  public:
    vector<int> allElements(BinaryTreeNode<int> *root1, BinaryTreeNode<int> *root2)
    {
        vector<int> a;
        preorder(root1, a);
        vector<int> b;
        preorder(root2, b);

        vector<int> res;
        int i = 0, j = 0;
        while (i < a.size() && j < b.size())
        {
            if (a[i] < b[j])
            {
                res.push_back(a[i++]);
            }
            else
            {
                res.push_back(b[j++]);
            }
        }
        while (i < a.size())
        {
            res.push_back(a[i++]);
        }
        while (j < b.size())
        {
            res.push_back(b[j++]);
        }
        return res;
    }
};

//https://www.naukri.com/code360/problems/tree-symmetricity_630426
class SymmetricTree
{
  private:
    bool mirror(BinaryTreeNode<int> *root1, BinaryTreeNode<int> *root2)
    {
        if (root1 == NULL && root2 == NULL)
            return true;
        if (root1 == NULL || root2 == NULL)
            return false;
        if (root1->data == root2->data)
        {
            return mirror(root1->left, root2->right) &&
                   mirror(root1->right, root2->left);
        }
        else
            return false;
    }

  public:
    bool isSymmetric(BinaryTreeNode<int> *root)
    {
        if (root == NULL)
            return true;
        else
            return mirror(root->left, root->right);
    }
};


//https://www.naukri.com/code360/problems/multiply-linked-lists_983603
class MultiplyLinkedLists
{
  private:
    //https://www.tutorialspoint.com/multiply-strings-in-cplusplus
    string multiplyStr(string s1, string s2)
    {
        int n = s1.size();
        int m = s2.size();
        string ans(n + m, '0');
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                int p = (s1[i] - '0') * (s2[j] - '0') + (ans[i + j + 1] - '0');
                ans[i + j + 1] = p % 10 + '0';
                ans[i + j] += p / 10;
            }
        }
        for (int i = 0; i < m + n; i++)
        {
            if (ans[i] != '0')
                return ans.substr(i);
        }
        return "0";
    }

    Node *str2LL(string s)
    {
        Node *head = new Node(s[0] - '0');
        Node *n = head;
        for (int i = 1; i < s.length(); i++)
        {
            n->next = new Node(s[i] - '0');
            n = n->next;
        }
        return head;
    }

  public:
    Node *multiplyLL(Node *head1, Node *head2)
    {
        string s1;
        while (head1 != NULL)
        {
            s1 += std::to_string(head1->data);
            head1 = head1->next;
        }
        string s2;
        while (head2 != NULL)
        {
            s2 += std::to_string(head2->data);
            head2 = head2->next;
        }
        string s = multiplyStr(s1, s2);
        return str2LL(s);
    }
};

//https://www.naukri.com/code360/problems/detect-and-remove-cycle_920523
bool detectAndRemoveCycle(Node *head)
{
    Node *fast = head, *slow = head, *pre = NULL;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            fast = fast->next;
            pre = slow;
            slow = slow->next;
        }
        if (slow == fast)
        {
            fast = head;
            while (fast != slow)
            {
                fast = fast->next;
                pre = slow;
                slow = slow->next;
            }
            pre->next = NULL;
            return true;
        }
    }
    return false;
}

//https://www.naukri.com/code360/problems/check-for-duplicate-subtree_1089641
class CheckDuplicateSubtree
{
  private:
    string subtree(BinaryTreeNode<char> *root, unordered_set<string> &mp, bool &flag)
    {
        //why return #?
        //in a big tree it can't say ab == ab
        //it may #ab a#b ab#
        if (root == NULL)
            return "#";
        if (root->left == NULL && root->right == NULL)
            return string(1, root->data);
        string strL = subtree(root->left, mp, flag);
        string strR = subtree(root->right, mp, flag);
        string temp = strL + strR + root->data;
        if (mp.find(temp) != mp.end())
        {
            flag = true;
        }
        else
        {
            mp.insert(temp);
        }
        return temp;
    }

  public:
    bool similarSubtree(BinaryTreeNode<char> *root)
    {
        unordered_set<string> mp;
        bool flag = false;
        subtree(root, mp, flag);
        return flag;
    }
};

// https://www.naukri.com/code360/problems/lowest-common-ancestor-of-a-binary-tree-iii_1280134
// LCA
class LowestCommonAncestorBinaryTreeIII
{
  private:
    int depth(BinaryTreeNode<int> *root)
    {
        int i = 0;
        while (root != NULL)
        {
            i++;
            root = root->parent;
        }
        return i;
    }

  public:
    BinaryTreeNode<int> *leastCommonAncestor(BinaryTreeNode<int> *n1, BinaryTreeNode<int> *n2)
    {
        int d1 = depth(n1);
        int d2 = depth(n2);
        if (d1 > d2)
        {
            for (int i = 0; i < d1 - d2; i++)
            {
                n1 = n1->parent;
            }
        }
        else
        {
            for (int i = 0; i < d2 - d1; i++)
            {
                n2 = n2->parent;
            }
        }
        while (n1 != n2)
        {
            n1 = n1->parent;
            n2 = n2->parent;
        }
        return n1;
    }
};

class Count_Univalue_Subtrees
{
  private:
    bool postOrder(BinaryTreeNode<int> *root, int &nums)
    {
        if (root == NULL)
            return true;
        bool l = postOrder(root->left, nums);
        bool r = postOrder(root->right, nums);
        if (l & r)
        {
            if ((root->left != NULL && root->left->data != root->data) ||
                (root->right != NULL && root->right->data != root->data))
            {
                return false;
            }
            nums++;
            return true;
        }
        return false;
    }

  public:
    int countUnivalTrees(BinaryTreeNode<int> *root)
    {
        int nums = 0;
        postOrder(root, nums);
        return nums;
    }
};

// https://www.naukri.com/code360/problems/larget-number-in-binary-tree_790727
class LargestNumberInBinaryTree
{
  private:
    template <typename T>
    void preorder(BinaryTreeNode<int> *root,
                  priority_queue<string, vector<string>, T> &q)
    {
        if (root == NULL)
            return;
        q.push(to_string(root->data));
        preorder(root->left, q);
        preorder(root->right, q);
    }

  public:
    string printLargest(BinaryTreeNode<int> *root)
    {
        if (root == NULL)
            return "";
        auto cmp = [](string a, string b)
        { return a + b < b + a; };
        priority_queue<string, vector<string>, decltype(cmp)> q(cmp);
        preorder(root, q);
        string ans;
        while (q.empty() == false)
        {
            ans += q.top();
            q.pop();
        }
        for (int i = 0; i < ans.size(); i++)
        {
            if (ans[i] != '0')
            {
                return ans.substr(i);
            }
        }
        return "0";
    }
};

// https://www.naukri.com/code360/problems/k-most-frequent-words_696192
vector<string> kMostFreqWords(string words[], int n, int k)
{
    auto cmp = [](pair<string, int> &a, pair<string, int> &b)
    {
        if (a.second == b.second)
        {
            return a.first > b.first;
        }
        else
            return a.second < b.second;
    };
    priority_queue<pair<string, int>,
                   vector<pair<string, int>>,
                   decltype(cmp)>
        q(cmp);
    unordered_map<string, int> map;
    for (int i = 0; i < n; i++)
    {
        map[words[i]]++;
    }
    for (auto it : map)
    {
        q.push({it.first, it.second});
    }
    vector<string> ans;
    while (k > 0)
    {
        pair<string, int> temp = q.top();
        q.pop();
        ans.push_back(temp.first);
        k--;
    }
    return ans;
}

// https://www.naukri.com/code360/problems/unival-trees_697311
class CountUnivalueSubtrees
{
  private:
    bool postOrder(BinaryTreeNode<int> *root, int &nums)
    {
        if (root == NULL)
            return true;
        bool l = postOrder(root->left, nums);
        bool r = postOrder(root->right, nums);
        if (l & r)
        {
            if ((root->left != NULL && root->left->data != root->data) ||
                (root->right != NULL && root->right->data != root->data))
            {
                return false;
            }
            nums++;
            return true;
        }
        return false;
    }

  public:
    int countUnivalTrees(BinaryTreeNode<int> *root)
    {
        int nums = 0;
        postOrder(root, nums);
        return nums;
    }
};

// https://www.naukri.com/code360/problems/merge-linkedlist_3125813
void merge(Node *head1, Node *head2)
{
    Node *a = head1, *b = head2;
    while (a != NULL && b != NULL)
    {
        Node *n = a->next;
        a->next = b;
        a = b;
        b = n;
    }
}

// https://www.naukri.com/code360/problems/k-sum-path-in-a-binary-tree_893543
class K_Sum_Path_In_Binary_Tree
{
  private:
    void preorder(BinaryTreeNode<int> *root, int k, vector<vector<int>> &ans, vector<int> &r)
    {
        if (root == NULL)
            return;
        r.push_back(root->data);
        preorder(root->left, k, ans, r);
        preorder(root->right, k, ans, r);
        int sum = 0;
        int n = r.size();
        for (auto i = r.end() - 1; i >= r.begin(); i--)
        {
            sum += *i;
            if (sum == k)
            {
                vector<int> temp(i, r.end());
                ans.push_back(temp);
            }
        }
        r.pop_back();
    }

  public:
    vector<vector<int>> kPathSum(BinaryTreeNode<int> *root, int k)
    {
        vector<vector<int>> ans;
        if (root != NULL)
        {
            vector<int> r;
            preorder(root, k, ans, r);
        }
        return ans;
    }
};

// https://www.naukri.com/code360/problems/binary-tree-from-parent-array_873336
BinaryTreeNode<int> *createTree(vector<int> &parent)
{
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < parent.size(); i++)
    {
        mp[parent[i]].push_back(i);
    }
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(mp[-1][0]);
    queue<BinaryTreeNode<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        BinaryTreeNode<int> *temp = q.front();
        q.pop();
        auto iter = mp.find(temp->data);
        if (iter == mp.end())
        {
            continue;
        }
        if (iter->second.size() > 0)
        {
            temp->left = new BinaryTreeNode<int>(iter->second[0]);
            q.push(temp->left);
        }
        if (iter->second.size() > 1)
        {
            temp->right = new BinaryTreeNode<int>(iter->second[1]);
            q.push(temp->right);
        }
    }
    return root;
}

// https://www.naukri.com/code360/problems/bst-delete_973001
class BST_Delete
{
  private:
    BinaryTreeNode<int> *findMinNode(BinaryTreeNode<int> *root)
    {
        while (root && root->left != NULL)
        {
            root = root->left;
        }
        return root;
    }

  public:
    BinaryTreeNode<int> *bstDelete(BinaryTreeNode<int> *root, int key)
    {
        if (root == NULL)
            return NULL;
        else if (key < root->data)
            root->left = bstDelete(root->left, key);
        else if (root->data < key)
            root->right = bstDelete(root->right, key);
        else
        {
            if (root->left == NULL)
                return root->right;
            else if (root->right == NULL)
                return root->left;
            else
            {
                BinaryTreeNode<int> *temp = findMinNode(root->right);
                root->data = temp->data;
                root->right = bstDelete(root->right, temp->data);
            }
        }
        return root;
    }
};

// https://www.naukri.com/code360/problems/time-to-burn-tree_630563
class Time_To_Burn_Tree
{
  private:
    int findTime(
        BinaryTreeNode<int> *root, BinaryTreeNode<int> *target,
        unordered_map<BinaryTreeNode<int> *, BinaryTreeNode<int> *> &parent)
    {
        queue<BinaryTreeNode<int> *> q;
        int time = 0;
        q.push(target);
        unordered_map<BinaryTreeNode<int> *, bool> vis;
        vis[target] = true;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                auto top = q.front();
                q.pop();
                if (top->left && !vis[top->left])
                {
                    vis[top->left] = true;
                    q.push(top->left);
                }
                if (top->right && !vis[top->right])
                {
                    vis[top->right] = true;
                    q.push(top->right);
                }
                if (parent[top] && !vis[parent[top]])
                {
                    vis[parent[top]] = true;
                    q.push(parent[top]);
                }
            }
            if (q.size() > 0)
                time++;
        }
        return time;
    }

    BinaryTreeNode<int> *findParent(
        BinaryTreeNode<int> *root, int start,
        unordered_map<BinaryTreeNode<int> *, BinaryTreeNode<int> *> &parent)
    {
        queue<BinaryTreeNode<int> *> q;
        q.push(root);
        BinaryTreeNode<int> *temp;
        parent[root] = NULL;
        while (!q.empty())
        {
            auto top = q.front();
            q.pop();
            if (top->data == start)
                temp = top;
            if (top->left)
            {
                q.push(top->left);
                parent[top->left] = top;
            }
            if (top->right)
            {
                q.push(top->right);
                parent[top->right] = top;
            }
        }
        return temp;
    }

  public:
    int timeToBurnTree(BinaryTreeNode<int> *root, int start)
    {
        unordered_map<BinaryTreeNode<int> *, BinaryTreeNode<int> *> parent;
        BinaryTreeNode<int> *target = findParent(root, start, parent);
        return findTime(root, target, parent);
    }
};

int main(int argc, char *argv[])
{
    {
        stack<int> st;
        st.push(1);
        st.push(0);
        st.push(0);
        st.push(2);
        SortStack ss;
        ss.sortStack(st);
        printf("Sort Stack:");
        while(st.empty()==false)
        {
            printf("%d ", st.top());
            st.pop();
        }
        printf("\n");
    }
    {
        vector<int> arr = {4, 3, 5};
        auto rv = nextGreater(arr, arr.size());
        printf("Next Greater Element:");
        for (auto i : rv)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        CircularQueue cq(3);
        cq.enqueue(2);
        cq.enqueue(3);
        cq.dequeue();
        cq.enqueue(4);
        cq.enqueue(6);
        cq.enqueue(7);
        cq.dequeue();
    }
    {
        string str = "Welcome   to Coding Ninjas";
        std::cout << "reverseString:" << reverseString(str) << std::endl;
    }
    {
        int arr[] = {3, 1, 2};
        Search_In_Rotated_Sorted_Array s;
        printf("Search In Rotated Sorted Array:%d\n", s.search(arr, sizeof(arr) / sizeof(int), 3));
        printf("Search In Rotated Sorted Array:%d\n", s.search(arr, sizeof(arr) / sizeof(int), 0));
        printf("Search In Rotated Sorted Array:%d\n", s.search(arr, sizeof(arr) / sizeof(int), 2));
    }
    {
        vector<int> arr = {1, 2, 2, 2, 3};
        Node *head = Node::newLinkList(arr);
        Remove_duplicates_from_DLL rm;
        printf("removeDuplicates:");
        for (Node *p = rm.removeDuplicates(head); p != NULL; p = p->next)
        {
            printf("%d ", p->data);
        }
        printf("\n");
    }
    {
        vector<int> arr = {-1, -1, 2, 0, 1};
        ThreeSum sum;
        vector<vector<int>> rv = sum.triplet(arr.size(), arr);
        printf("ThreeSum:");
        for (auto i : rv)
        {
            printf("[");
            for (auto j : i)
            {
                printf("%d,", j);
            }
            printf("] ");
        }
        printf("\n");
    }
    {
        string str = "abcaab";
        printf("uniqueSubstrings:%d\n", uniqueSubstrings(str));
    }
    {
        vector<int> arr = {5, 6, 7, 8};
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree(arr, 0);
        RightView view;
        auto rv = view.printRightView(root);
        printf("printRightView:");
        for (auto i : rv)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        vector<int> arr = {5, 6, 7, 8};
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree(arr, 0);
        LeftView view;
        auto rv = view.printLeftView(root);
        printf("printLeftView:");
        for (auto i : rv)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        vector<int> arr = {25, 10, 5};
        printf("findMinCountToReachSum:%d\n", findMinCountToReachSum(30, arr));
        arr = {6, 10, 5, 1};
        printf("findMinCountToReachSum:%d\n", findMinCountToReachSum(4, arr));
    }
    {
        Node *intersection = new Node(8);
        intersection->next = new Node(9);

        Node *head1 = new Node(4);
        head1->next = new Node(1);
        head1->next->next = intersection;

        Node *head2 = new Node(5);
        head2->next = new Node(6);
        head2->next->next = new Node(3);
        head2->next->next->next = intersection;
        printf("findIntersection:%d\n", findIntersection(head1, head2)->data);
    }
    {
        vector<vector<int>> arr = {{0, 1, 1, 0, 0}, {1, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {1, 0, 0, 0, 1}};
        Find_Number_Of_Islands f;
        printf("getTotalIslands:%d\n", f.getTotalIslands(arr, 4, 5));
    }
    {
        BinaryTreeNode<int> *root1 = new BinaryTreeNode<int>(1);
        root1->left = new BinaryTreeNode<int>(2);
        BinaryTreeNode<int> *root2 = new BinaryTreeNode<int>(1);
        root2->left = new BinaryTreeNode<int>(2);
        std::cout << "identicalTrees:" << std::boolalpha << identicalTrees(root1, root2) << std::endl;
    }
    {
        vector<int> arr = {1, 2, 2, 2, 3};
        int n = removeDuplicates(arr, arr.size());
        printf("after removeDuplicates:");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    {
        Add_Two_Numbers add;
        Node *first = new Node(9);
        first->next = new Node(9);
        Node *second = new Node(9);
        second->next = new Node(9);
        Node *p = add.addTwoLists(first, second);
        printf("Add Two Numbers As Linked Lists ll:");
        while (p != NULL)
        {
            printf("%d", p->data);
            p = p->next;
        }
        printf("\n");
    }
    {
        vector<vector<int>> intervals = {{1, 5}, {2, 3}, {6, 8}};
        vector<vector<int>> merge = mergeIntervals(intervals);
        printf("mergeIntervals");
        for (int i = 0; i < merge.size(); i++)
        {
            printf("{%d,%d} ", merge[i][0], merge[i][1]);
        }
        printf("\n");
    }
    {
        vector<int> arr = {1, 2, 3, 2, 1};
        Node *head = Node::newLinkList(arr);
        Palindrome_Linked_List pll;
        std::cout << "isPalindrome:" << std::boolalpha << pll.isPalindrome(head) << std::endl;
    }
    {
        string s = "BaaB";
        Palindrome_Partition pp;
        vector<vector<string>> res = pp.partition(s);
        printf("Palindrome Partitioning:\n");
        for (auto i : res)
        {
            for (auto j : i)
            {
                std::cout << "\"" << j << "\" ";
            }
            std::cout << std::endl;
        }
    }
    {
        vector<vector<int>> arr = {{1, 0, 1}, {1, 1, 1}, {1, 1, 1}};
        vector<vector<int>> good = findGoodMatrix(arr);
        for (int i = 0; i < good.size(); i++)
        {
            for (int j = 0; j < good.front().size(); j++)
            {
                printf("%d ", good[i][j]);
            }
            printf("\n");
        }
    }
    {
        vector<vector<int>> matrix = {{1, 2, 3, 4}, {14, 15, 16, 5}, {13, 20, 17, 6}, {12, 19, 18, 7}, {11, 10, 9, 8}};
        vector<int> spiral = spiralPathMatrix(matrix, matrix.size(), matrix.front().size());
        printf("spiralPathMatrix:");
        for (auto i : spiral)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        vector<int> arr = {1, 2, 3, 4, 5};
        Node *head = Node::newLinkList(arr);
        Sorted_Linked_List_to_Balanced_BST bst;
        TreeNode<int> *root = bst.sortedListToBST(head);
        printf("BST:");
        TreeNode<int>::preorder(root);
        printf("\n");
    }
    {
        vector<int> arr = {-3, 5, -2, 6, 4, 7};
        Node *head = Node::newLinkList(arr);
        head = findPartition(head, 2);
        printf("findPartition:");
        while (head != NULL)
        {
            printf("%d ", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        string s = "abced";
        Reverse_vowels r;
        std::cout << "Reverse vowels in a string:" << r.reverseVowels(s) << std::endl;
    }
    {
        //convert vector to balanced binary search tree(AVL BST)
        vector<int> arr = {1, 2, 3, 4, 5};
        Minimal_Tree t;
        t.minimalTree(arr);
    }
    {
        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(1);
        BinaryTreeNode<int> *l = new BinaryTreeNode<int>(0);
        BinaryTreeNode<int> *r = new BinaryTreeNode<int>(9);
        root->left = l;
        root->right = r;
        BinaryTreeNode<int> *new_root = modifyTree(root, 2, 8);
        printf("trimBST %d %d %d\n", root->data, l->data, r->data);
        std::cout << "find " << root->data << ":" << std::boolalpha << findBinaryTreeNode(new_root, root->data) << std::endl;
        std::cout << "find " << l->data << ":" << std::boolalpha << findBinaryTreeNode(new_root, l->data) << std::endl;
        std::cout << "find " << r->data << ":" << std::boolalpha << findBinaryTreeNode(new_root, r->data) << std::endl;
    }
    {
        vector<int> arr = {24, 15, 33, 12, 21, 30, 36, 9};
        TreeNode<int> *root = TreeNode<int>::buildTree2(arr, 0);
        printf("rangeSum:%d\n", rangeSum(root, 18, 24));
    }
    {
        vector<int> arr = {3, 6, 2, 7, 9};
        Node *head = Node::newLinkList(arr);
        head = partitionList(head, 6);
        printf("partitionList:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        vector<int> arr = {52, 98, 91};
        Node *head = Node::newLinkList(arr);
        NextGreaterNode g;
        vector<int> res = g.findNextGreaterNodeList(head);
        printf("Next Greater Node In Linked List:");
        for (auto i : res)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        vector<int> arr = {43, 6, 9, 1, 5};
        Node *head = Node::newLinkList(arr);
        Node *p = findKthFromLast(head, 3);
        printf("findKthFromLast:%d\n", p->data);
    }
    {
        TreeNode<int> *root = new TreeNode<int>(15);
        root->left = new TreeNode<int>(40);
        root->right = new TreeNode<int>(62);
        root->right->left = new TreeNode<int>(10);
        root->right->right = new TreeNode<int>(20);
        FlattenBinaryTreetoLinkedList f;
        f.flattenBinaryTree(root);
        printf("flattenBinaryTree:");
        TreeNode<int>::preorder(root);
        printf("\n");
    }
    {
        vector<int> arr = {1, 4, 5, 8, 9};
        Node *head = Node::newLinkList(arr);
        ListToTree l;
        head = l.listToTree(head);
        printf("List to Tree:");
        Node::inorder(head);
        printf("\n");
    }
    {
        Node *a = Node::newLinkList({4, 1});
        Node *b = Node::newLinkList({5, 6, 1});
        Node *i = Node::newLinkList({8, 4, 5});
        a = linkedListCat(a, i);
        b = linkedListCat(b, i);
        MergePointOfTwoLinkedLists m;
        printf("findIntersection:%d\n", m.findIntersection(a, b));
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree({1, 2, 3, 4, 5}, 0);
        std::cout << "isBinaryHeapTree:" << isBinaryHeapTree(root) << std::endl;
        root = BinaryTreeNode<int>::buildTree({10, 8, 9, 5, 5, 4, 5, 1, 2}, 0);
        std::cout << "isBinaryHeapTree:" << isBinaryHeapTree(root) << std::endl;
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree({1, 2, 3, 4, 5, 6}, 0);
        SumTree st;
        vector<int> ans = st.sumTree(root);
        printf("sumTree:");
        for (auto i : ans)
        {
            printf("%d ", i);
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({1, 3, 2, 4, 6, 5});
        ReverseLL r;
        head = r.reverseLL(head, 2, 3);
        printf("reverseLL:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({3, 4, 5, 2, 6, 1, 9});
        head = deleteNode(head, 3);
        printf("deleteNode:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({1, 2, 3, 4, 5});
        Node *n = head;
        while (n->next != NULL)
        {
            n = n->next;
        }
        n->next = head;
        DeletionInCircularLinkedList del;
        head = del.deleteNode(head, 3);
        printf("deleteNode: %d",head->data);
        for (Node *n = head->next; n != head; n = n->next)
        {
            printf(" %d", n->data);
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({10, 9, 8, 7, 6, 5, 4, 3});
        MergeSortLinkedList m;
        head = m.mergeSort(head);
        printf("MergeSort Linked List:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({1, 0, 2, 1, 0, 2, 1});
        head = sortList(head);
        printf("Sort linked list of 0s 1s 2s:");
        for (Node *n = head; n != NULL; n = n->next)
        {
            printf(" %d", n->data);
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({1, 2, 3, 4, 5, 6});
        BinaryTreeNode<int> *root = LLtoTree(head);
        printf("Linked List to binary Tree:");
        BinaryTreeNode<int>::preorder(root);
        printf("\n");
    }
    {
        Node *head1 = Node::newLinkList({0, 0, 0, 1, 0, 0, 0, 0});
        Node *head2 = Node::newLinkList({5, 5, 1, 7, 1, 1, 5, 2, 7, 6, 1, 4});
        Node *head = addLL(head1, head2);
        printf("addLL:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({5, 4, 3, 2, 1});
        QuickSortOnLinkedList q;
        head = q.quickSortLL(head);
        printf("Quick Sort on Linked List:");
        while (head != NULL)
        {
            printf(" %d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree({1, 2, 3, 4, 5, 6}, 0);
        vector<int> ans = printLeftRightMostNodes(root);
        printf("Leftmost & Rightmost Nodes of Binary Tree:");
        for (int i = 0; i < ans.size(); i++)
        {
            printf(" %d", ans[i]);
        }
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree({40, 30, 50, 20, 35}, 0);
        CountSubtrees c;
        printf("Count Subtrees:%d\n", c.getCount(root, 15, 32));
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree({0, 1, 2}, 0);
        MirrorTree m;
        m.mirrorTree(root);
        printf("Convert binary tree to mirror tree:");
        BinaryTreeNode<int>::preorder(root);
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root1 = BinaryTreeNode<int>::buildTree({1, 2, 3, 4}, 0);
        BinaryTreeNode<int> *root2 = BinaryTreeNode<int>::buildTree({1, 2, 4, 3}, 0);
        std::cout << "Isomorphic Trees:" << checkTree(root1, root2) << std::endl;
    }
    {
        BinaryTreeNode<int> *root1 = BinaryTreeNode<int>::buildTree({1, 2, 3, 4}, 0);
        BinaryTreeNode<int> *root2 = BinaryTreeNode<int>::buildTree({1, 3, 2, 4}, 0);
        std::cout << "Isomorphic Trees:" << checkTree(root1, root2) << std::endl;
    }
    {
        BinaryTreeNode<int> *root1 = BinaryTreeNode<int>::buildTree1({1, 2, 3, 4, -1, -1, -1, -1, -1});
        BinaryTreeNode<int> *root2 = BinaryTreeNode<int>::buildTree1({1, 3, 2, -1, -1, -1, 4, -1, -1});
        std::cout << "Isomorphic Trees:" << checkTree(root1, root2) << std::endl;
    }
    {
        BinaryTreeNode<int> *root1 = BinaryTreeNode<int>::buildTree1({1, 2, 3, 4, -1, -1, -1, -1, -1});
        BinaryTreeNode<int> *root2 = BinaryTreeNode<int>::buildTree1({1, 3, 2, -1, -1, 4, -1, -1, -1});
        std::cout << "Isomorphic Trees:" << checkTree(root1, root2) << std::endl;
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({5, 6, 10, 2, 3, -1, 9, -1, -1, -1, -1, -1, -1});
        BinaryTreeToBST b;
        root = b.binaryTreeToBst(root);
        printf("Binary Tree To BST:");
        root->preorder();
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({1, 2, 3, -1, -1, 4, 5, -1, -1, -1, -1});
        vector<int> ans = spiralOrder(root);
        printf("Spiral Order Traversal of a Binary Tree:");
        for (int i : ans)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({8, 4, 12, 1, 6, -1, -1, -1, -1, -1, 7, -1, -1});
        SumOfKSmallestElementsInBST s;
        printf("Sum Of K Smallest Elements In BST: %ld\n", s.ksmallestElementSum(root, 4));
    }
    {
        BinaryTreeNode<int> *root1 = BinaryTreeNode<int>::buildTree1({10, 5, 16, 2, 7, -1, 20, -1, -1, -1, -1, -1, -1});
        BinaryTreeNode<int> *root2 = BinaryTreeNode<int>::buildTree1({10, 7, 16, 2, -1, -1, 20, -1, -1, -1, -1});
        ElementsInTwoBSTs e;
        vector<int> res = e.allElements(root1, root2);
        printf("Elements In Two BSTs:");
        for (int i : res)
        {
            printf(" %d", i);
        }
        printf("\n");
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({1, 2, 2, 3, 4, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1});
        SymmetricTree s;
        std::cout << "Symmetric Tree:" << s.isSymmetric(root) << std::endl;
    }
    {
        Node *head1 = Node::newLinkList({1, 5, 4});
        Node *head2 = Node::newLinkList({3, 6, 4});
        MultiplyLinkedLists m;
        Node *head = m.multiplyLL(head1, head2);
        printf("Multiply Linked Lists:");
        while (head != NULL)
        {
            printf("%d", head->data);
            head = head->next;
        }
        printf("\n");
    }
    {
        vector<vector<long>> matrix = {{1, 2, 3, 4}, {10, 11, 12, 5}, {9, 8, 7, 6}};
        vector<long> ans = spiralPathMatrix(matrix, 3, 4);
        printf("Spiral Matrix:");
        for (auto i : ans)
        {
            printf(" %ld", i);
        }
        printf("\n");
    }
    {
        Node *head = Node::newLinkList({1, 2, 3});
        Node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = head;
        std::cout << "Detect And Remove Cycle:" << detectAndRemoveCycle(head) << std::endl;
    }
    {
        string str = "abac#b###c###";
        vector<char> v(str.begin(), str.end());
        BinaryTreeNode<char> *root = BinaryTreeNode<char>::buildTree1(v);
        CheckDuplicateSubtree c;
        std::cout << "Check for Duplicate Subtree:" << c.similarSubtree(root) << std::endl;
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({1, 1, 1, -1, -1, -1, -1});
        Count_Univalue_Subtrees c;
        printf("Count Univalue Subtrees:%d\n", c.countUnivalTrees(root));
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({1, 2, 3});
        LargestNumberInBinaryTree l;
        string num = l.printLargest(root);
        std::cout << "Largest Number in Binary Tree:" << num << std::endl;
    }
    {
        BinaryTreeNode<int> *root = BinaryTreeNode<int>::buildTree1({10, 5, -3, 3, 2, -1, 11, 3, -2, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1});
        K_Sum_Path_In_Binary_Tree k;
        vector<vector<int>> ans = k.kPathSum(root, 8);
        printf("K - Sum Path In A Binary Tree:");
        for (auto i : ans)
        {
            for (auto j : i)
            {
                printf(" %d", j);
            }
            printf(" ");
        }
        printf("\n");
    }
    {
        vector<int> parent = {-1, 0, 1, 2, 2, 3};
        BinaryTreeNode<int> *root = createTree(parent);
    }
    return 0;
}
