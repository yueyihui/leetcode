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

struct TreeNode *searchBST(struct TreeNode *root, int val)
{
    if (root == NULL)
        return NULL;
    if (root->val == val)
    {
        return root;
    }
    struct TreeNode *l = searchBST(root->left, val);
    return l != NULL ? l : searchBST(root->right, val);
}

struct TreeNode *insert(struct TreeNode *root, struct TreeNode *sub_tree)
{
    if (root == NULL)
        return sub_tree;

    if (sub_tree == NULL)
        return root;

    if (sub_tree->val < root->val)
    {
        root->left = insert(root->left, sub_tree);
        return root;
    }
    else if (root->val < sub_tree->val)
    {
        root->right = insert(root->right, sub_tree);
        return root;
    }
    else
    {
        root->left = insert(root->left, sub_tree->left);
        root->right = insert(root->right, sub_tree->right);
        return root;
    }
}

struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->val == key)
    {
        struct TreeNode *new = insert(root->right, root->left);
        free(root);
        return new;
    }
    else if (root->val < key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        root->left = deleteNode(root->left, key);
    }
    return root;
}

int goodNodes(struct TreeNode *root)
{
    if (root == NULL)
        return 0;

    int l = goodNodes(root->left);
    if (l != 0 && root->val > root->left->val)
    {
        l--;
    }

    int r = goodNodes(root->right);
    if (r != 0 && root->val > root->right->val)
    {
        r--;
    }
    return r + l + 1;
}

struct TreeNode *lcaOf3Nodes(struct TreeNode *root, int nodes[3])
{
    if (root == NULL)
        return NULL;

    for (int i = 0; i < 3; i++)
    {
        if (nodes[i] == root->val)
            return root;
    }

    struct TreeNode *l = lcaOf3Nodes(root->left, nodes);
    struct TreeNode *r = lcaOf3Nodes(root->right, nodes);
    if (l != NULL && r != NULL)
        return root;
    else
        return l != NULL ? l : r;
}

inline int max(int a, int b)
{
    return a > b ? a : b;
}

int longestPath(struct TreeNode *root, int *longest)
{
    if (root == NULL)
    {
        return 0;
    }
    int len_l = longestPath(root->left, longest);
    int len_r = longestPath(root->right, longest);
    //why can't use one variable instead two?
    //if root->val==l->val and !=r->val then return l->val+1
    //if root->val!=l->val and ==r->val then return r->val+1
    //if root->val==l->val and ==r->val then return max(l->val+1,r->val+1)
    //if root->val!=l->val and !=r->val then return 0
    int r = 0, l = 0;
    if (root->left && root->left->val == root->val)
    {
        l = len_l + 1;
    }
    if (root->right && root->right->val == root->val)
    {
        r = len_r + 1;
    }
    *longest = max(l + r, *longest);
    return max(l, r);
}

int longestUnivaluePath(struct TreeNode *root)
{
    int longest = 0;
    longestPath(root, &longest);
    return longest;
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

    preorderPrint(searchBST(root, 5));
    printf("\n");

    root = newNode(5);
    root->left = newNode(3);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right = newNode(6);
    root->right->right = newNode(7);
    struct TreeNode *after = deleteNode(root, 5);
    preorderPrint(after);
    printf("\n");
    inorderPrint(after);
    printf("\n");

    int preorder1[] = {3, 1, 3, 4, 1, 5};
    int inorder1[] = {3, 1, 3, 1, 4, 5};
    root = buildTree(preorder1, sizeof(preorder1) / sizeof(int), inorder1, sizeof(inorder1) / sizeof(int));
    printf("goodNodes:%d\n", goodNodes(root));

    int preorder2[] = {3, 1, 4};
    int inorder2[] = {1, 3, 4};
    root = buildTree(preorder2, sizeof(preorder2) / sizeof(int), inorder2, sizeof(inorder2) / sizeof(int));
    printf("goodNodes:%d\n", goodNodes(root));

    int preorder3[] = {1, 2, 4, 7, 8, 3, 5, 6, 9, 10};
    int inorder3[] = {7, 4, 8, 2, 1, 5, 3, 9, 6, 10};
    root = buildTree(preorder3, sizeof(preorder3) / sizeof(int), inorder3, sizeof(inorder3) / sizeof(int));
    int nodes0[] = {7, 8, 2};
    printf("lca:%d\n", lcaOf3Nodes(root, nodes0)->val);
    int nodes1[] = {5, 6, 7};
    printf("lca:%d\n", lcaOf3Nodes(root, nodes1)->val);
    int nodes2[] = {4, 7, 8};
    printf("lca:%d\n", lcaOf3Nodes(root, nodes2)->val);
    return 0;
}
