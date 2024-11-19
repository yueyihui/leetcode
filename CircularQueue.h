#include <bits/stdc++.h>

// https://www.naukri.com/code360/problems/circular-queue_1170058
class CircularQueue
{
  private:
    int *buffer;
    int front;
    int rear;
    int capability;

  public:
    CircularQueue(int n)
    {
        buffer = (int *)malloc(n * sizeof(int));
        memset(buffer, 0, n * sizeof(int));
        capability = n;
        front = -1;
        rear = -1;
    }

    bool enqueue(int value)
    {
        if ((rear + 1) % capability == front)
        {
            return false;
        }
        else if (front == -1)
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % capability;
        }
        buffer[rear] = value;
        return true;
    }

    int dequeue()
    {
        if (front == -1)
        {
            return -1;
        }
        else
        {
            int v = buffer[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                front = (front + 1) % capability;
            }
            return v;
        }
    }
};

class CircularQueue2
{
  private:
    int *buffer;
    int front;
    int rear;
    int capability;

  public:
    CircularQueue2(int n)
    {
        n = n + 1;
        buffer = (int *)malloc(n * sizeof(int));
        memset(buffer, 0, n * sizeof(int));
        capability = n;
        front = 0;
        rear = 0;
    }

    bool enqueue(int value)
    {
        if ((rear + 1) % capability == front)
        {
            return false;
        }
        buffer[rear] = value;
        rear = (rear + 1) % capability;
        return true;
    }

    int dequeue()
    {
        if (front == rear)
        {
            return -1;
        }
        else
        {
            int v = buffer[front];
            front = (front + 1) % capability;
            return v;
        }
    }
};
