class Queue
{
#define CAPBILITY 512
  public:
    Queue()
    {
        head = 0;
        rear = -1;
        size = 0;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == CAPBILITY;
    }

    void enqueue(int data)
    {
        if (isFull())
            return;
        size++;
        if (rear == CAPBILITY - 1)
        {
            rear = -1;
        }
        arr[++rear] = data;
    }

    int dequeue()
    {
        if (isEmpty())
            return -1;
        size--;
        if (head == CAPBILITY - 1)
        {
            int rv = arr[head];
            head = 0;
            return rv;
        }
        return arr[head++];
    }

    int front()
    {
        return isEmpty() ? -1 : arr[head];
    }

  private:
    int head;
    int rear;
    int size;
    int arr[CAPBILITY];
};
