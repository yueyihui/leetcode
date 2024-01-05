#include <stdio.h>
#include <stdlib.h>

#define CAPABILITY 8
typedef struct
{
    int stack[CAPABILITY];
    int *min;
    int size;
} MinStack;

MinStack *minStackCreate()
{
    MinStack *s = (MinStack*)malloc(sizeof(MinStack));
    s->min = s->stack;
    s->size = 0;
    return s;
}

void minStackPush(MinStack *obj, int val)
{
    if (obj->size == CAPABILITY)
        return;

    for (int i = obj->size - 1; i >= 0; i--)
    {
        obj->stack[i + 1] = obj->stack[i];
    }
    obj->min++;
    obj->size++;
    obj->stack[0] = val;
    if (val < *obj->min)
    {
        obj->min = obj->stack;
    }
}

void minStackPop(MinStack *obj)
{
    if (obj->size == 0)
        return;

    obj->min = obj->stack;

    for (int i = 1; i < obj->size; i++)
    {
        obj->stack[i - 1] = obj->stack[i];
        if (*obj->min >= obj->stack[i - 1])
        {
            obj->min = &obj->stack[i - 1];
        }
    }
    obj->size--;
}

int minStackTop(MinStack *obj)
{
    return obj->stack[0];
}

int minStackGetMin(MinStack *obj)
{
    return *obj->min;
}

void minStackFree(MinStack *obj)
{
    free(obj);
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
    int sel = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    if (left < N && arr[left] > arr[sel])
        sel = left;
    if (right < N && arr[right] > arr[sel])
        sel = right;
    if (sel != i)
    {
        swap(&arr[i], &arr[sel]);
        heapify(arr, N, sel);
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
    MinStack *st = minStackCreate();
    minStackPush(st, 1);
    minStackPush(st, 0);
    minStackPush(st, -3);
    printf("min:%d\n", minStackGetMin(st));
    printf("top:%d\n", minStackTop(st));
    minStackPop(st);
    printf("min:%d\n", minStackGetMin(st));
    printf("top:%d\n", minStackTop(st));

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

    return 0;
}
