#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int *mem;
    int *min;
    int top;
    unsigned int capability;
};

struct stack *createStack(int capability)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->mem = (int *)malloc(sizeof(int) * capability);
    s->top = -1;
    s->min = NULL;
    s->capability = capability;
    return s;
}

bool is_empty(struct stack *s)
{
    return s->top < 0;
}

bool is_full(struct stack *s)
{
    return s->capability - 1 == s->top;
}

void push(struct stack *s, int val)
{
    if (is_full(s))
        return;

    s->mem[++s->top] = val;
    if (s->min == NULL || *s->min > val)
    {
        s->min = &s->mem[s->top];
    }
}

int min(struct stack *s)
{
    return is_empty(s) ? INT_MIN : *s->min;
}

int pop(struct stack *s)
{
    return is_empty(s) ? INT_MIN : s->mem[s->top--];
}

int top(struct stack *s)
{
    return is_empty(s) ? INT_MIN : s->mem[s->top];
}

void stackInsert(struct stack *s, int val)
{
    if (val < top(s))
    {
        int tmp = pop(s);
        stackInsert(s, val);
        val = tmp;
    }
    push(s, val);
}

void sortStack(struct stack *s)
{
    if (is_empty(s))
        return;
    int val = pop(s);
    sortStack(s);
    stackInsert(s, val);
}

void push_back(struct stack *s, int my)
{
    if (is_empty(s))
    {
        push(s, my);
    }
    else
    {
        int tmp = pop(s);
        push_back(s, my);
        push(s, tmp);
    }
}

void reverseStack(struct stack *s)
{
    if (is_empty(s))
    {
        return;
    }
    int my = pop(s);
    reverseStack(s);
    push_back(s, my);
}

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    int a = maxDepth(root->left) + 1;
    int b = maxDepth(root->right) + 1;
    return a > b ? a : b;
}

_Bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if (p == NULL && q == NULL) //leaf
    {
        return 1;
    }
    else if (p == NULL || q == NULL)
    {
        return 0;
    }
    else if (p->val != q->val)
    {
        return 0;
    }
    else
    {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
}

struct TreeNode *invertTree(struct TreeNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        struct TreeNode *tmp = root->right;
        root->right = invertTree(root->left);
        root->left = invertTree(tmp);
        return root;
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int N, int i)
{
    int max = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    if (left < N && arr[left] > arr[max])
        max = left;
    if (right < N && arr[right] > arr[max])
        max = right;
    if (max != i)
    {
        swap(&arr[i], &arr[max]);
        heapify(arr, N, max);
    }
}

void heapSort(int arr[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        heapify(arr, N, i);
    }
    for (int i = N - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main(int argc, char *argv[])
{
    struct TreeNode r3;
    r3.left = NULL;
    r3.right = NULL;
    struct TreeNode l2;
    l2.left = NULL;
    l2.right = &r3;
    struct TreeNode l1;
    l1.left = &l2;
    l1.right = NULL;
    struct TreeNode r1;
    r1.left = NULL;
    r1.right = NULL;
    struct TreeNode root;
    root.left = &l1;
    root.right = &r1;
    printf("maxDepth:%d\n", maxDepth(&root));

    struct TreeNode i2;
    i2.left = NULL;
    i2.right = NULL;
    i2.val = 2;
    struct TreeNode i1;
    i1.left = &i2;
    i1.right = NULL;
    i1.val = 1;
    invertTree(&i1);

    int arr[] = {1, 15, 12, 11, 13, 5, 22, 6, 7, 27, 0, 10, 0, 2, 25, 4, 3};
    int N = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, N);
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    struct stack *st = createStack(16);
    push(st, 5);
    push(st, -3);
    push(st, 3);
    push(st, 1);
    push(st, 5);
    push(st, -2);
    push(st, -5);
    push(st, 8);
    push(st, 4);
    push(st, 0);
    push(st, -6);
    printf("min:%d\n", min(st));
    sortStack(st);
    while (!is_empty(st))
    {
        printf("%d ", pop(st));
    }
    printf("\n");

    st = createStack(5);
    push(st, 5);
    push(st, 4);
    push(st, 3);
    push(st, 2);
    push(st, 1);
    reverseStack(st);
    while (!is_empty(st))
    {
        printf("%d ", pop(st));
    }
    printf("\n");

    return 0;
}
