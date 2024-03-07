#include "ringbuffer.h"
#include <bits/stdc++.h>
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
    static BinaryTreeNode<T> *buildTree(vector<int> &arr, int i)
    {
        if (i >= arr.size())
            return NULL;
        BinaryTreeNode<T> *root = new BinaryTreeNode<T>(arr[i]);
        root->left = buildTree(arr, 2 * i + 1);
        root->right = buildTree(arr, 2 * i + 2);
        return root;
    }
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
    return 0;
}
