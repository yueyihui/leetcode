class TwoStack
{
  private:
    int *mem;
    int top1;
    int top2;
    int capbility;

  public:
    // Initialize TwoStack.
    TwoStack(int s)
    {
        // Write your code here.
        mem = (int *)malloc(sizeof(int) * s);
        top1 = -1;
        top2 = s;
        capbility = s;
    }

    // Push in stack 1.
    void push1(int num)
    {
        // Write your code here.
        if (top1 + 1 < top2)
        {
            mem[++top1] = num;
        }
    }

    // Push in stack 2.
    void push2(int num)
    {
        // Write your code here.
        if (top2 - 1 > top1)
        {
            mem[--top2] = num;
        }
    }

    // Pop from stack 1 and return popped element.
    int pop1()
    {
        // Write your code here.
        if (top1 >= 0)
        {
            return mem[top1--];
        }
        else
            return -1;
    }

    // Pop from stack 2 and return popped element.
    int pop2()
    {
        // Write your code here.
        if (top2 <= capbility - 1)
        {
            return mem[top2++];
        }
        else
            return -1;
    }
};
