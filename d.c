#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int getIndexFromInOrder(int *inorder, int inorderSize, int val)
{
    for (int i = 0; i < inorderSize; i++)
    {
        if (inorder[i] == val)
            return i;
    }
    return -1;
}

struct TreeNode *newNode(int val)
{
    struct TreeNode *n = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    n->val = val;
    return n;
}

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    if (inorderSize == 0)
        return NULL;
    struct TreeNode *node = newNode(preorder[0]);
    int index = getIndexFromInOrder(inorder, inorderSize, node->val);
    int inorder_left_size = index;
    int inorder_right_size = inorderSize - (index + 1);
    node->left = buildTree(preorder + 1, inorder_left_size, inorder, inorder_left_size);
    node->right = buildTree(preorder + inorder_left_size + 1, inorder_right_size, inorder + index + 1, inorder_right_size);
    return node;
}

void preorderPrint(struct TreeNode *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->val);
    preorderPrint(root->left);
    preorderPrint(root->right);
}

void inorderPrint(struct TreeNode *root)
{
    if (root == NULL)
        return;

    inorderPrint(root->left);
    printf("%d ", root->val);
    inorderPrint(root->right);
}

int maxDepth(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    int a = maxDepth(root->left) + 1;
    int b = maxDepth(root->right) + 1;
    return a > b ? a : b;
}

void onlevel(struct TreeNode *root, int level)
{
    //here is not for leaf->right and leaf->left
    //is for the tree is not a full binary tree
    if (root == NULL)
    {
        printf("null ");
        return;
    }
    else if (level == 0)
    {
        printf("%d ", root->val);
    }
    else
    {
        onlevel(root->left, level - 1);
        onlevel(root->right, level - 1);
    }
}

int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    int depth = maxDepth(root);
    for (int i = 0; i < depth; i++)
    {
        onlevel(root, i);
    }
    return NULL;
}

void levelPrint(struct TreeNode *root, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        onlevel(root, i);
    }
}

void flatten(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    else if (root->left == NULL && root->right == NULL) //leaf
    {
        return;
    }
    else
    {
        flatten(root->left);
        if (root->left != NULL)
        {
            struct TreeNode *tmp = root->right;
            root->right = root->left;
            root->left = NULL;

            struct TreeNode *i = root->right;
            while (i->right != NULL)
            {
                i = i->right;
            }
            i->right = tmp;
        }
        flatten(root->right);
    }
}

void flatten1(struct TreeNode *root)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
        return;

    flatten1(root->left);

    struct TreeNode *tmp = root->right;
    root->right = root->left;
    root->left = NULL;

    struct TreeNode *i = root;
    for (; i->right != NULL; i = i->right)
        ;

    i->right = tmp;

    flatten1(root->right);
}

_Bool hasPathSum(struct TreeNode *root, int targetSum)
{
    if (root == NULL || targetSum <= 0) //is not leaf
    {
        //On the way of recursion (in spite of current root is leaf),
        //if targetSum == 0, return false
        return 0;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        return targetSum - root->val == 0;
    }
    else
    {
        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
}

struct TreeNode *sortedArrayToBST(int *nums, int numsSize)
{
    if (numsSize == 0)
        return NULL;

    int l = 0;
    int r = numsSize - 1;
    int mid = l + (r - l) / 2;
    struct TreeNode *n = newNode(nums[mid]);
    n->left = sortedArrayToBST(nums, mid);
    n->right = sortedArrayToBST(nums + mid + 1, numsSize - mid - 1);
    return n;
}

int *rightSideView(struct TreeNode *root, int *returnSize)
{
    if (root == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    int r_size = 0;
    int *r = rightSideView(root->right, &r_size);
    int l_size = 0;
    int *l = rightSideView(root->left, &l_size);
    if (r_size >= l_size)
    {
        *returnSize = r_size + 1;
        int *new = (int *)malloc(*returnSize);
        memset(new, 0, *returnSize);
        new[0] = root->val;
        memcpy(new + 1, r, r_size * sizeof(int));
        return new;
    }
    else
    {
        *returnSize = r_size + (l_size - r_size) + 1;
        int *new = (int *)malloc(*returnSize);
        memset(new, 0, *returnSize);
        new[0] = root->val;
        memcpy(new + 1, r, r_size * sizeof(int));
        memcpy(new + 1 + r_size, l + r_size, (l_size - r_size) * sizeof(int));
        return new;
    }
}

int main(int argc, char *argv[])
{
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};

    struct TreeNode *root = buildTree(preorder, sizeof(preorder) / sizeof(int), inorder, sizeof(inorder) / sizeof(int));
    preorderPrint(root);
    printf("\n");
    inorderPrint(root);
    printf("\n");

    int returnSize = 0;
    int *returnColumnSizes = NULL;
    levelOrder(root, &returnSize, &returnColumnSizes);
    printf("\n");

    flatten1(root);
    for (struct TreeNode *i = root; i != NULL; i = i->right)
    {
        printf("%d ", i->val);
    }
    printf("\n");

    int pre_a[] = {5, 4, 11, 7, 2, 8, 13, 4, 1};
    int in_a[] = {7, 11, 2, 4, 5, 13, 8, 4, 1};
    root = buildTree(pre_a, sizeof(pre_a) / sizeof(int), in_a, sizeof(in_a) / sizeof(int));
    printf("%d\n", hasPathSum(root, 18));

    int b_nums[] = {-10, -3, 0, 5, 9};
    struct TreeNode *bst = sortedArrayToBST(b_nums, sizeof(b_nums) / sizeof(int));
    levelPrint(bst, 3);
    printf("\n");

    int rts = 0;
    root = newNode(1);
    root->left = newNode(2);
    root->left->right = newNode(5);
    root->left->right->right = newNode(10);
    root->left->right->left = newNode(6);
    root->right = newNode(3);
    root->right->right = newNode(4);
    int *right_view = rightSideView(root, &rts);
    printf("rightSideView:");
    for (int i = 0; i < rts; i++)
    {
        printf("%d ", right_view[i]);
    }
    printf("\n");
    return 0;
}
