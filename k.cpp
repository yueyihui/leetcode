#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
class WordSearch
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

// https://leetcode.com/problems/min-stack/?source=submission-noac
class MinStack
{
  private:
    stack<int> st;
    stack<int> minSt;

  public:
    MinStack() { minSt.push(INT_MAX); }

    void push(int val)
    {
        st.push(val);
        minSt.push(std::min(val, minSt.top()));
    }

    void pop()
    {
        st.pop();
        minSt.pop();
    }

    int top() { return st.top(); }

    int getMin() { return minSt.top(); }
};

class MinStack1
{
  private:
    stack<long long> st;
    long long min;

  public:
    MinStack1() {}

    void push(int val)
    {
        if (st.empty())
        {
            st.push(val);
            min = val;
        }
        else if (min >= val)
        {
            st.push(2LL * val - min);
            min = val;
        }
        else
            st.push(val);
    }

    void pop()
    {
        if (st.empty())
            return;
        long long t = st.top();
        st.pop();
        if (min > t)
        {
            min = 2LL * min - t;
        }
    }

    int top()
    {
        if (st.empty())
            return -1;
        if (min > st.top())
            return min;
        else
            return st.top();
    }

    int getMin()
    {
        if (st.empty())
            return -1;
        return min;
    }
};

// https://leetcode.com/problems/partition-list/
ListNode *partition(ListNode *head, int x)
{
    vector<ListNode *> left;
    vector<ListNode *> right;
    for (ListNode *p = head; p != NULL; p = p->next)
    {
        if (p->val < x)
        {
            left.push_back(p);
        }
        else
            right.push_back(p);
    }
    ListNode head1;
    ListNode *p = &head1;
    for (int i = 0; i < left.size(); i++)
    {
        p->next = left[i];
        p = p->next;
    }
    for (int i = 0; i < right.size(); i++)
    {
        p->next = right[i];
        p = p->next;
    }
    p->next = NULL;
    return head1.next;
}

// https://leetcode.com/problems/restore-ip-addresses/description/
class Restore_IP_Addresses
{
  private:
    int dots(string &ip)
    {
        int dot = 0;
        for (int i = 0; i < ip.length(); i++)
        {
            if (ip[i] == '.')
                dot++;
        }
        return dot;
    }
    bool isValid(string &ip, int end)
    {
        int i = end;
        char last = '0';
        while (i >= 0 && ip[i] != '.')
        {
            last = ip[i];
            i--;
        }
        if (end - i == 1)
            return true;
        else
            return last != '0';
    }
    void _ipAddress(string &s, int start, string ip, vector<string> &vec)
    {
        int n = s.length();
        int num = 0;
        if (dots(ip) == 3)
        {
            for (int i = start; i < n; i++)
            {
                num *= 10;
                num += s[i] - '0';
                if (num > 255)
                    return;
                ip.push_back(s[i]);
            }
            if (isValid(ip, ip.length() - 1))
                vec.push_back(ip);
            return;
        }

        for (int i = start; i < n; i++)
        {
            num *= 10;
            num += s[i] - '0';
            if (num > 255)
                return;
            ip.push_back(s[i]);
            ip.push_back('.');
            if (isValid(ip, ip.length() - 2))
                _ipAddress(s, i + 1, ip, vec);
            ip.pop_back();
        }
    }

  public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> vec;
        _ipAddress(s, 0, "", vec);
        return vec;
    }
};

// https://leetcode.com/problems/string-to-integer-atoi/description/?source=submission-noac
class StringToInteger
{
  private:
    bool isDigi(char c) { return c >= '0' && c <= '9'; }

  public:
    int myAtoi(string s)
    {
        int n = s.length();
        long long num = 0;
        int i = 0;
        while (s[i] == ' ')
            i++;
        bool isPos = s[i] == '+';
        bool isNeg = s[i] == '-';
        if (isPos || isNeg)
            i++;
        while (i < n && isDigi(s[i]) && (INT_MIN <= num && num <= INT_MAX))
        {
            num = num * 10;
            num += (s[i] - '0');
            i++;
        }
        if (isNeg)
            num = -num;
        if (num < INT_MIN)
            num = INT_MIN;
        else if (num > INT_MAX)
            num = INT_MAX;
        return num;
    }
};

// https://www.naukri.com/code360/problems/closest-leaf-to-given-node-in-binary-tree_983627
class Closest_Leaf
{
  private:
    void buildGraph(BinaryTreeNode<int> *parent, BinaryTreeNode<int> *root,
                    unordered_map<int, vector<int>> &graph,
                    unordered_map<int, bool> &visited)
    {
        if (root == NULL)
            return;
        if (parent)
        {
            graph[root->data].push_back(parent->data);
            graph[parent->data].push_back(root->data);
            visited[root->data] = false;
            visited[parent->data] = false;
        }
        buildGraph(root, root->left, graph, visited);
        buildGraph(root, root->right, graph, visited);
    }
    int dfs(unordered_map<int, vector<int>> &graph, int parent, int root,
            unordered_map<int, bool> &visited)
    {
        if (visited[root] == true)
            return INT_MAX;

        visited[root] = true;
        if (graph[root].size() == 1 && graph[root][0] == parent)
            return 1;
        int rv = INT_MAX;

        for (auto next : graph[root])
        {
            if (visited[next] == false)
            {
                rv = min(rv, dfs(graph, root, next, visited));
            }
        }
        return rv + 1;
    }

  public:
    int findClosestLeafNodeDistance(BinaryTreeNode<int> *root, int x)
    {
        if (root == NULL || root->left == NULL && root->right == NULL)
            return 0;
        unordered_map<int, vector<int>> graph;
        unordered_map<int, bool> visited;
        buildGraph(NULL, root, graph, visited);
        // is leaf
        if (graph[x].size() == 1 && x != root->data)
            return 0;
        int ans = INT_MAX;

        visited[x] = true;
        for (auto next : graph[x])
        {
            int dep = dfs(graph, x, next, visited);
            ans = min(ans, dep);
        }
        return ans;
    }
};

// https://www.naukri.com/code360/problems/verify-preorder-sequence-in-binary-search-tree_1281309
bool isBSTPreorder(vector<int> &arr)
{
    stack<int> st;
    int root = INT_MIN;
    for (int next : arr)
    {
        if (next < root)
            return false;
        while (st.empty() == false && st.top() < next)
        {
            root = st.top();
            st.pop();
        }
        st.push(next);
    }
    return true;
}

//https://leetcode.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
	int n = nums1.size();
	int m = nums2.size();
	vector<double> temp;
	int i = 0, j = 0;
	while (i < n && j < m) {
		if (nums1[i] < nums2[j])
			temp.push_back(nums1[i++]);
		else
			temp.push_back(nums2[j++]);
	}
	while (i < n)
		temp.push_back(nums1[i++]);
	while (j < m)
		temp.push_back(nums2[j++]);
	int l = 0, r = temp.size() - 1;
	int mid = l + (r - l) / 2;
	if (temp.size() % 2 == 0) {
		return (temp[mid] + temp[mid + 1]) / 2.0;
	} else
		return temp[mid];
}

double findMedianSortedArrays1(vector<int> &nums1, vector<int> &nums2)
{
	int n = nums1.size();
	int m = nums2.size();
	int i = 0, j = 0;
	int q = 0, p = 0;
	for (int count = 0; count <= (n + m) / 2; count++) {
		q = p;
		if (i < n && j < m) {
			if (nums1[i] < nums2[j])
				p = nums1[i++];
			else
				p = nums2[j++];

		} else if (i < n)
			p = nums1[i++];
		else
			p = nums2[j++];
	}
	if ((n + m) % 2 == 1)
		return static_cast<double>(p);
	else
		return (static_cast<double>(q) + static_cast<double>(p)) / 2.0;
}

//https://leetcode.com/problems/path-sum/
bool hasPathSum(TreeNode<int> *root, int targetSum)
{
	if (root == NULL)
		return false;
	if (root->left == NULL && root->right == NULL)
		return targetSum == root->data ? true : false;
	return hasPathSum(root->left, targetSum - root->data) ||
	       hasPathSum(root->right, targetSum - root->data);
}

// https://leetcode.com/problems/restore-ip-addresses/description/
class _Restore_IP_Addresses
{
  private:
    bool isValid(const string &seg)
    {
        if (seg.size() > 1 && seg[0] == '0')
            return false;
        int num = stoi(seg);
        return 0 <= num && num <= 255;
    }

    void _restoreIp(string &s, int start, vector<string> &ip,
                    vector<string> &addresses)
    {
        if (ip.size() == 4 && start == s.length())
        {
            string _ip = ip[0] + "." + ip[1] + "." + ip[2] + "." + ip[3];
            addresses.push_back(_ip);
        }
        if (ip.size() == 4 || start == s.length())
            return;
        for (int len = 1; len <= 3; len++)
        {
            if (start + len > s.length())
                return;
            string seg = s.substr(start, len);
            if (isValid(seg))
            {
                ip.push_back(seg);
                _restoreIp(s, start + len, ip, addresses);
                ip.pop_back();
            }
        }
    }

  public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> ip;
        vector<string> addresses;
        _restoreIp(s, 0, ip, addresses);
        return addresses;
    }
};

// https://leetcode.com/problems/string-to-integer-atoi/
class String2Integer
{
  private:
    bool isInt(char c) { return '0' <= c && c <= '9'; }

  public:
    int myAtoi(string s)
    {
        int n = s.length();
        long long num = 0;
        int i = 0;
        while (s[i] == ' ')
            i++;
        bool isPos = s[i] == '+';
        bool isNeg = s[i] == '-';
        if (isPos || isNeg)
            i++;
        while (i < n && isInt(s[i]) && INT_MIN <= num && num <= INT_MAX)
        {
            num *= 10;
            num += s[i] - '0';
            i++;
        }
        if (isNeg)
            num = -num;
        if (num < INT_MIN)
            num = INT_MIN;
        else if (INT_MAX < num)
            num = INT_MAX;
        return num;
    }
};

// https://leetcode.com/problems/word-search/
class WordSearch1
{
  private:
    bool dfs(vector<vector<char>> &board, int row, int col, string &word,
             int start)
    {
        if (start == word.length())
            return true;
        if (row < 0 || row >= board.size() || col < 0 ||
            col >= board[0].size() || board[row][col] != word[start])
            return false;

        char temp = board[row][col];
        board[row][col] = '#';

        bool got = dfs(board, row, col - 1, word, start + 1) ||
                   dfs(board, row - 1, col, word, start + 1) ||
                   dfs(board, row, col + 1, word, start + 1) ||
                   dfs(board, row + 1, col, word, start + 1);

        board[row][col] = temp;
        return got;
    }

  public:
    bool exist(vector<vector<char>> &board, string word)
    {
        int rowSize = board.size();
        int colSize = board[0].size();
        for (int i = 0; i < rowSize; i++)
            for (int j = 0; j < colSize; j++)
            {
                if (board[i][j] == word[0] && dfs(board, i, j, word, 0))
                    return true;
            }
        return false;
    }
};

// https://leetcode.com/problems/validate-ip-address/
class ValidateIpAddress
{
  private:
    string validIPv4(string &queryIP, int index, vector<string> &ip)
    {
        int n = queryIP.length();
        if (index > n && ip.size() == 4)
            return "IPv4";
        else if (index > n || ip.size() == 4)
            return "Neither";
        string temp;
        while (index < n && queryIP[index] != '.')
        {
            if ('0' <= queryIP[index] && queryIP[index] <= '9')
                temp.push_back(queryIP[index]);
            else
                return "Neither";
            index++;
        }
        if (temp.length() == 0 || temp.length() > 3)
            return "Neither";
        else if (temp.length() > 1 && temp[0] == '0')
            return "Neither";

        int integer = stoi(temp);
        if (integer < 0 || integer > 255)
            return "Neither";
        else
        {
            ip.push_back(temp);
            return validIPv4(queryIP, index + 1, ip);
        }
    }

    string validIPv6(string &queryIP, int index, vector<string> &ip)
    {
        int n = queryIP.length();
        if (index > n && ip.size() == 8)
            return "IPv6";
        else if (index > n || ip.size() == 8)
            return "Neither";
        string temp;
        while (index < n && queryIP[index] != ':')
        {
            if ('0' <= queryIP[index] && queryIP[index] <= '9' ||
                'a' <= queryIP[index] && queryIP[index] <= 'f' ||
                'A' <= queryIP[index] && queryIP[index] <= 'F')
            {
                temp.push_back(queryIP[index]);
            }
            else
                return "Neither";
            index++;
        }
        if (temp.length() == 0 || temp.length() > 4)
            return "Neither";
        else
        {
            ip.push_back(temp);
            return validIPv6(queryIP, index + 1, ip);
        }
    }

  public:
    string validIPAddress(string queryIP)
    {
        int n = queryIP.length();
        vector<string> ip;
        for (int i = 0; i < n; i++)
        {
            if (queryIP[i] == '.')
            {
                return validIPv4(queryIP, 0, ip);
            }
            if (queryIP[i] == ':')
            {
                return validIPv6(queryIP, 0, ip);
            }
        }
        return "Neither";
    }
};

// https://leetcode.com/problems/longest-palindromic-substring/
class LongestPalindromicSubstring
{
  private:
    int start;
    int maxLen;
    void _longestPalindrome(string &s, int left, int right)
    {
        while (left >= 0 && right < s.length() && s[left] == s[right])
        {
            left--;
            right++;
        }
        int len = right - left - 1;
        if (len > maxLen)
        {
            maxLen = len;
            start = left + 1;
        }
    }

  public:
    LongestPalindromicSubstring()
    {
        start = 0;
        maxLen = 0;
    }
    string longestPalindrome(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            _longestPalindrome(s, i, i);
            _longestPalindrome(s, i, i + 1);
        }
        return s.substr(start, maxLen);
    }
};

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
class SortArray2BST
{
    TreeNode<int> *_arrayToBST(vector<int> &nums, int l, int r)
    {
        if (l > r)
            return NULL;
        int mid = l + (r - l) / 2;
        TreeNode<int> *root = new TreeNode<int>(nums[mid]);
        root->left = _arrayToBST(nums, l, mid - 1);
        root->right = _arrayToBST(nums, mid + 1, r);
        return root;
    }

  public:
    TreeNode<int> *sortedArrayToBST(vector<int> &nums)
    {
        return _arrayToBST(nums, 0, nums.size() - 1);
    }
};

int main(int argc, char *argv[])
{
    return 0;
}
