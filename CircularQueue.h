#include <bits/stdc++.h>

//https://www.codingninjas.com/studio/problems/circular-queue_1170058?interviewProblemRedirection=true&leftPanelTabValue=PROBLEM&count=25&search=queue&sort_entity=order&sort_order=ASC&customSource=studio_nav&attempt_status=NOT_ATTEMPTED
class CircularQueue
{
    private:
        int *buf;
        int front;
        int rear;
        int capability;
        bool isEmpty() { return rear == -1 && front == -1; }
        bool isFull() { return front == 0 && rear == edge() || front == rear + 1; }
        bool isLastOne() { return isEmpty() == false && front == rear; }
        int edge() { return capability - 1; }

      public:
        CircularQueue(int n) {
            front = rear = -1;
            buf = (int *)malloc(n * sizeof(int));
            capability = n;
        }
        bool enqueue(int value)
        {
            if (isFull())
                return false;
            if (isEmpty())
                front = 0;
            if (rear == edge())
                rear = 0;
            else
                rear++;
            buf[rear] = value;
            return true;
        }
        int dequeue()
        {
            if (isEmpty())
                return -1;
            int rv = buf[front];
            if (isLastOne())
                front = rear = -1;
            else if (front == edge())
                front = 0;
            else
                front++;
            return rv;
        }
};
