#include <queue>

class Stack
{
    // Define the data members.
  private:
    queue<int> q1;
    queue<int> q2;

  public:
    Stack()
    {
        // Implement the Constructor.
    }

    int getSize()
    {
        // Implement the getSize() function.
        if (isEmpty())
            return 0;
        else if (q1.empty())
            return q2.size();
        else
            return q1.size();
    }

    bool isEmpty()
    {
        if (q1.empty() && q2.empty())
            return true;
        else
            false;
    }

    void push(int element)
    {
        // Implement the push() function.
        if (isEmpty())
            q1.push(element);
        else if (q1.empty())
            q2.push(element);
        else
            q1.push(element);
    }

    int pop()
    {
        if (isEmpty())
        {
            return -1;
        }
        else if (q2.empty())
        {
            while (q1.size() > 1)
            {
                q2.push(q1.front());
                q1.pop();
            }
            int x = q1.front();
            q1.pop();
            return x;
        }
        else
        {
            while (q2.size() > 1)
            {
                q1.push(q2.front());
                q2.pop();
            }
            int x = q2.front();
            q2.pop();
            return x;
        }
    }

    int top()
    {
        if (isEmpty())
        {
            return -1;
        }
        else if (q1.empty())
        {
            return q2.back();
        }
        else
        {
            return q1.back();
        }
    }
};
