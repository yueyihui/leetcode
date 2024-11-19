#include <bits/stdc++.h>
using namespace std;

class Node
{
  public:
    int data;
    Node *next;
    Node *prev;

    Node(int data)
    {
        next = NULL;
        prev = NULL;
        this->data = data;
    }

    ~Node()
    {
        if (next != NULL)
        {
            delete next;
        }
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
};

// https://www.naukri.com/code360/problems/max-stack_985280
class MaxStack
{
  private:
    stack<int> st;
    int max;

  public:
    MaxStack() { max = INT_MIN; }

    void specialPush(int value)
    {
        if (st.empty())
        {
            st.push(value);
            max = value;
        }
        else if (max >= value)
        {
            st.push(value);
        }
        else
        {
            st.push(2 * value - max);
            max = value;
        }
    }

    int specialPop()
    {
        if (st.empty())
            return -1;
        int t = st.top();
        st.pop();
        if (t > max)
        {
            int val = max;
            max = 2 * max - t;
            return val;
        }
        else
            return t;
    }

    int specialTop()
    {
        if (st.empty())
            return -1;
        int t = st.top();
        if (t > max)
        {
            return max;
        }
        else
        {
            return t;
        }
    }

    int specialMax()
    {
        if (st.empty())
            return -1;
        return max;
    }
};

// https://www.naukri.com/code360/problems/sorting-the-stack-recursively_1868989
class Sorting_Stack_Recursively
{
  private:
    void insert(stack<int> &s, int val)
    {
        if (s.empty())
            s.push(val);
        else
        {
            int t = s.top();
            if (t > val)
            {
                s.pop();
                insert(s, val);
                s.push(t);
                return;
            }
            s.push(val);
        }
    }

  public:
    stack<int> sortStack(stack<int> &s)
    {
        if (s.empty())
            return s;
        int t = s.top();
        s.pop();
        sortStack(s);
        insert(s, t);
        return s;
    }
};

stack<int> sortStack(stack<int> &input)
{
    stack<int> tmpSt;
    while (input.empty() == false)
    {
        int t = input.top();
        input.pop();
        while (tmpSt.empty() == false && tmpSt.top() < t)
        {
            input.push(tmpSt.top());
            tmpSt.pop();
        }
        tmpSt.push(t);
    }
    return tmpSt;
}

// https://www.naukri.com/code360/problems/word-search_892986
class Word_Search
{
  private:
    bool helper(vector<vector<char>> &board, int n, int m, string &word, int last,
                int row, int col)
    {
        if (word.length() == last)
            return true;
        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, -1, 0, 1};
        for (int i = 0; i < 4; i++)
        {
            int _row = row + dr[i];
            int _col = col + dc[i];
            if (_row >= 0 && _row < n && _col >= 0 && _col < m &&
                board[_row][_col] == word[last])
            {
                if (helper(board, n, m, word, last + 1, _row, _col))
                    return true;
            }
        }
        return false;
    }

  public:
    bool present(vector<vector<char>> &board, string &word, int n, int m)
    {
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < m; col++)
            {
                if (board[row][col] == word[0])
                {
                    if (helper(board, n, m, word, 1, row, col))
                        return true;
                }
            }
        }
        return false;
    }
};

// https://www.naukri.com/code360/problems/normal-bst-to-balanced-bst_920472
class BST_To_Balanced_BST
{
  private:
    void inorder(TreeNode<int> *root, vector<int> &vec)
    {
        if (root == NULL)
            return;
        inorder(root->left, vec);
        vec.push_back(root->data);
        inorder(root->right, vec);
    }

    TreeNode<int> *buildBalancedBst(vector<int> &vec, int l, int r)
    {
        if (l <= r)
        {
            int mid = l + (r - l) / 2;
            TreeNode<int> *root = new TreeNode<int>(vec[mid]);
            root->left = buildBalancedBst(vec, l, mid - 1);
            root->right = buildBalancedBst(vec, mid + 1, r);
            return root;
        }
        return NULL;
    }

  public:
    TreeNode<int> *balancedBst(TreeNode<int> *root)
    {
        vector<int> vec;
        inorder(root, vec);
        return buildBalancedBst(vec, 0, vec.size() - 1);
    }
};

// https://www.naukri.com/code360/problems/print-nodes-at-distance-k-from-a-given-node_842560
class Print_Nodes_at_Distance_K_From_Given_Node
{
  private:
    void bfs(
        unordered_map<BinaryTreeNode<int> *, vector<BinaryTreeNode<int> *>> &map,
        BinaryTreeNode<int> *from, BinaryTreeNode<int> *target, int K,
        vector<BinaryTreeNode<int> *> &nodes)
    {
        if (K == 0)
        {
            nodes.push_back(target);
            return;
        }
        vector<BinaryTreeNode<int> *> vec = map[target];
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i] != from)
                bfs(map, target, vec[i], K - 1, nodes);
        }
    }

  public:
    vector<BinaryTreeNode<int> *> printNodesAtDistanceK(BinaryTreeNode<int> *root,
                                                        BinaryTreeNode<int> *target,
                                                        int K)
    {
        unordered_map<BinaryTreeNode<int> *, vector<BinaryTreeNode<int> *>> map;
        queue<pair<BinaryTreeNode<int> *, BinaryTreeNode<int> *>> q;
        q.push({NULL, root});
        while (q.empty() == false)
        {
            auto temp = q.front();
            q.pop();
            vector<BinaryTreeNode<int> *> adj;
            BinaryTreeNode<int> *parent = temp.first;
            BinaryTreeNode<int> *I = temp.second;
            if (parent != NULL)
                adj.push_back(parent);
            if (I->left != NULL)
            {
                adj.push_back(I->left);
                q.push({I, I->left});
            }
            if (I->right != NULL)
            {
                adj.push_back(I->right);
                q.push({I, I->right});
            }
            map.insert({I, adj});
        }

        vector<BinaryTreeNode<int> *> nodes;
        bfs(map, NULL, target, K, nodes);
        return nodes;
    }
};

// https://www.naukri.com/code360/problems/find-pairs_759395
vector<vector<int>> getAllPairSum(Node *head, int x)
{
    vector<vector<int>> ans;
    Node *l = head;
    Node *r = head;
    while (r->next != NULL)
        r = r->next;
    while (l < r)
    {
        if (l->data + r->data == x)
        {
            ans.push_back({l->data, r->data});
            l = l->next;
            r = r->prev;
        }
        else if (l->data + r->data > x)
        {
            r = r->prev;
        }
        else
            l = l->next;
    }
    return ans;
}

// https://www.naukri.com/code360/problems/uncommon-characters_795133
string findUncommonCharacters(string s1, string s2)
{
    string ans;
    vector<int> dp1(26, 0);
    vector<int> dp2(26, 0);
    for (int i = 0; i < s1.length(); i++)
    {
        if (dp1[s1[i] - 'a'] != 1)
            dp1[s1[i] - 'a']++;
    }
    for (int i = 0; i < s2.length(); i++)
    {
        if (dp2[s2[i] - 'a'] != 1)
            dp2[s2[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (dp1[i] != dp2[i])
            ans.push_back('a' + i);
    }
    return ans;
}

// https://www.naukri.com/code360/problems/set-matrix-ones_981213
void setMatrixOnes(vector<vector<int>> &MAT, int n, int m)
{
    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (MAT[i][j] == 1)
            {
                vec.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < vec.size(); i++)
    {
        int row = vec[i].first;
        int col = vec[i].second;
        for (int th = 0; th < m; th++)
            MAT[row][th] = 1;
        for (int th = 0; th < n; th++)
            MAT[th][col] = 1;
    }
}

// https://www.naukri.com/code360/problems/print-the-pattern_893299
vector<string> printPattern(int n)
{
    int top = 0, bottom = n - 1;
    vector<string> ans(n);
    int s = 0;
    while (top < bottom)
    {
        for (int i = 0; i < n; i++)
        {
            s++;
            ans[top].append(to_string(s)).push_back(' ');
        }
        top++;
        for (int i = 0; i < n; i++)
        {
            s++;
            ans[bottom].append(to_string(s)).push_back(' ');
        }
        bottom--;
    }
    if (n % 2 != 0)
    {
        for (int i = 0; i < n; i++)
        {
            s++;
            ans[top].append(to_string(s)).push_back(' ');
        }
    }
    return ans;
}

int main(int argc, char *argv[])
{
}
