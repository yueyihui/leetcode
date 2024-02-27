#include <bits/stdc++.h>
using namespace std;

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
    return 0;
}
