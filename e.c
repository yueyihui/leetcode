#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
    struct ListNode *child;
};

_Bool hasCycle(struct ListNode *head)
{
    int i = 0;
    struct ListNode *slow = head, *fast = head;
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast == slow)
            return 1;
        else if (i == 3) //3 is slow speed, it could be any number
        {
            slow = slow->next;
            i = 0;
        }
        else
            i++;
    }

    return 0;
}

struct ListNode * newNode(int val)
{
    struct ListNode *n = (struct ListNode *)malloc(sizeof(struct ListNode));
    n->val = val;
    n->next = NULL;
    n->child = NULL;
    return n;
}

struct ListNode *addToList(struct ListNode *head, int val)
{
    if (head == NULL)
    {
        return newNode(val);
    }

    struct ListNode *p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode(val);
    return p->next;
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;
    if (list1->val <= list2->val)
    {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    else
    {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int carry = 0;
    struct ListNode *head = NULL, *p = NULL;
    while (l1 != NULL || l2 != NULL)
    {
        if (p == NULL)
        {
            head = newNode(l1->val + l2->val + carry);
            p = head;
        }
        else if (l1 == NULL)
        {
            p->next = newNode(l2->val + carry);
        }
        else if (l2 == NULL)
        {
            p->next = newNode(l1->val + carry);
        }
        else
        {
            p->next = newNode(l1->val + l2->val + carry);
        }

        if (p->val >= 10)
        {
            p->val -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if (l1 != NULL)
        {
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            l2 = l2->next;
        }
        while (p->next != NULL)
        {
            p = p->next;
        }
    }

    if (carry > 0)
    {
        p->next = newNode(carry);
    }

    return head;
}

void printList(struct ListNode *head)
{
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");
}

struct ListNode *reverse(struct ListNode *head)
{
    printList(head);
    struct ListNode *pre = NULL, *cur = head, *next = NULL;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
        if (cur != NULL)
            head = cur;
    }

    printList(head);
    return head;
}

struct ListNode *reverseBetween(struct ListNode *head, int left, int right)
{
    int pos = 0;
    struct ListNode *p = head;

    struct ListNode *a = NULL;
    while (pos < left)
    {
        if (left - pos == 1)
        {
            a = p;
        }
        p = p->next;
        pos++;
    }
    struct ListNode *sub_head = p;
    a->next = NULL;

    while (pos < right)
    {
        p = p->next;
        pos++;
    }
    struct ListNode *b = p->next;
    p->next = NULL;

    //it lead head to be tail after reverse complete
    struct ListNode *sub_tail = sub_head;
    sub_head = reverse(sub_head);
    a->next = sub_head;
    sub_tail->next = b;

    return head;
}

struct ListNode *removeNth(struct ListNode *head, int *n)
{
    if (head == NULL)
    {
        return NULL;
    }
    struct ListNode *i = removeNth(head->next, n);
    (*n)--;
    if (*n == 0)
    {
        free(head);
        return i;
    }
    else
    {
        head->next = i;
        return head;
    }
}

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    return removeNth(head, &n);
}

struct ListNode *deleteDuplicates(struct ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    struct ListNode *p = deleteDuplicates(head->next);
    if (head->val != p->val)
    {
        head->next = p;
    }
    else
    {
        head->next = p->next;
        free(p);
    }
    return head;
}

//linklist rotation is different with array
//array is value move
//linklist is change tail node as head node
//example:
//1 2 3 4 5 -> 5 1 2 3 4 -> 4 5 1 2 3
struct ListNode *rotateRight(struct ListNode *head, int k)
{
    if (head == NULL)
        return NULL;

    for (int i = 0; i < k; i++)
    {
        struct ListNode *pre = NULL, *cur = head;
        //find last node
        while (cur->next != NULL)
        {
            pre = cur;
            cur = cur->next;
        }
        pre->next = NULL;
        cur->next = head;
        head = cur;
    }
    return head;
}

struct ListNode *get_reversed_tail(struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *end = tail->next;
    struct ListNode *pre = NULL;
    while (head != end)
    {
        struct ListNode *next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return end;
}

//1 2 3 NULL
struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    if (head == NULL)
        return head;

    struct ListNode *sub_head = head, *sub_tail = head;
    for (int i = 0; i < k - 1; i++)
    {
        if (sub_tail->next != NULL)
            sub_tail = sub_tail->next;
        else
            return head;
    }
    //after reverse, head and tail be Swapped
    sub_head->next = reverseKGroup(get_reversed_tail(sub_head, sub_tail), k);
    return sub_tail;
}

struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;

    struct ListNode *i = sortList(head->next);
    if (i != NULL && head->val > i->val)
    {
        head->next = i->next;
        i->next = sortList(head);
        return i;
    }
    else
    {
        head->next = i;
        return head;
    }
}

struct ListNode *deleteMiddle(struct ListNode *head)
{
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    struct ListNode *pre = NULL;
    int i = 0;
    while (fast != NULL)
    {
        fast = fast->next;
        if (i == 1)
        {
            pre = slow;
            slow = slow->next;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    printf("mid val %d\n", slow->val);
    printf("pre val %d\n", pre->val);
    pre->next = slow->next;
    return slow;
}

struct ListNode *insert(struct ListNode *head, struct ListNode *n)
{
    if (head == NULL)
        return n;
    if (n == NULL)
        return head;
    if (head->val <= n->val)
    {
        head->next = insert(head->next, n);
        return head;
    }
    else
    {
        n->next = insert(head, n->next);
        return n;
    }
}

struct ListNode *flattenLinkedList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;

    struct ListNode *a = head->next;
    head->next = NULL;
    struct ListNode *ar = flattenLinkedList(a);

    struct ListNode *b = head->child;
    head->child = NULL;
    struct ListNode *br = flattenLinkedList(b);
    return insert(insert(ar, br), head);
}

struct ListNode *split(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head, *pre = NULL;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            fast = fast->next;
            pre = slow;
            slow = slow->next;
        }
    }
    if (pre)
    {
        pre->next = NULL;
    }
    return slow;
}

struct ListNode *mergeSort(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;
    struct ListNode *half = split(head);
    return insert(mergeSort(head), mergeSort(half));
}

struct ListNode *firstNode(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        if (fast == slow)
        {
            slow = head;
            while (fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;
}

struct ListNode *removeLoop(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head;
    struct ListNode *pre = NULL;
    while (fast)
    {
        pre = fast;
        fast = fast->next;
        if (fast)
        {
            pre = fast;
            fast = fast->next;
            slow = slow->next;
        }
        if (fast == slow)
        {
            slow = head;
            while (fast != slow)
            {
                pre = fast;
                fast = fast->next;
                slow = slow->next;
            }
            pre->next = NULL;
            return head;
        }
    }
    return head;
}

struct ListNode *reverse1(struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *saved = tail->next;
    struct ListNode *pre = NULL;
    while (head != saved)
    {
        struct ListNode *cur = head;
        head = head->next;
        cur->next = pre;
        pre = cur;
    }
    return saved;
}

struct ListNode *getListAfterReverseOperation(struct ListNode *head, int n, int b[])
{
    if (head == NULL)
        return NULL;
    if (n == 0)
        return head;
    if (*b == 0)
        return getListAfterReverseOperation(head, n - 1, b + 1);

    struct ListNode *l = head, *r = head;
    for (int i = 1; i < b[0]; i++)
    {
        if (r->next)
        {
            r = r->next;
        }
        else
            break;
    }
    l->next = getListAfterReverseOperation(reverse1(l, r), n - 1, b + 1);
    return r;
}

struct ListNode* sortLL(struct ListNode* head)
{
    int count[3] = {0};
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        count[i->val]++;
    }

    int p = 0;
    struct ListNode *i = head;
    while (i != NULL)
    {
        if (count[p] == 0)
            p++;
        else
        {
            i->val = p;
            i = i->next;
            count[p]--;
        }
    }
    return head;
}

int main(int argc, char *argv[])
{
    struct ListNode *head = addToList(NULL, 0);
    addToList(head, 1);
    addToList(head, 2);
    addToList(head, 3);
    struct ListNode *tail = addToList(head, 4);
    tail->next = head;
    printf("hasCycle:%u\n", hasCycle(head));

    struct ListNode *head1 = addToList(NULL, 0);
    addToList(head1, 2);
    addToList(head1, 4);
    addToList(head1, 5);
    struct ListNode *head2 = addToList(NULL, -1);
    addToList(head2, 1);
    addToList(head2, 3);
    addToList(head2, 9);
    struct ListNode *merge = mergeTwoLists(head1, head2);
    printf("mergeTwoLists:");
    for (struct ListNode *i = merge; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");


    //410
    struct ListNode *add = addToList(NULL, 0);
    addToList(add, 1);
    addToList(add, 4);
    //13
    struct ListNode *added = addToList(NULL, 3);
    addToList(added, 1);

    struct ListNode *r = addTwoNumbers(add, added);
    for (struct ListNode *i = r; i != NULL; i = i->next)
    {
        printf("%d ",i->val);
    }
    printf("\n");

    struct ListNode *rb = addToList(NULL, 0);
    addToList(rb, 1);
    addToList(rb, 2);
    addToList(rb, 3);
    addToList(rb, 4);
    addToList(rb, 5);
    addToList(rb, 6);
    addToList(rb, 7);
    rb = reverseBetween(rb, 2, 7);
    printList(rb);

    rb = addToList(NULL, 0);
    addToList(rb, 1);
    addToList(rb, 2);
    addToList(rb, 3);
    addToList(rb, 4);
    addToList(rb, 5);
    addToList(rb, 6);
    addToList(rb, 7);
    struct ListNode *rm = removeNthFromEnd(rb, 2);
    printf("remove from end:");
    printList(rm);

    rb = addToList(NULL, 0);
    addToList(rb, 1);
    addToList(rb, 1);
    addToList(rb, 1);
    addToList(rb, 2);
    addToList(rb, 2);
    addToList(rb, 3);
    addToList(rb, 4);
    addToList(rb, 4);
    printf("before:");
    printList(rb);
    deleteDuplicates(rb);
    printf("after:");
    printList(rb);

    rb = addToList(NULL, 0);
    addToList(rb, 1);
    addToList(rb, 2);
    addToList(rb, 3);
    addToList(rb, 4);
    addToList(rb, 5);
    printf("before rotate:");
    printList(rb);
    rb = rotateRight(rb, 3);
    printf("after rotate:");
    printList(rb);


    rb = addToList(NULL, 0);
    addToList(rb, 1);
    addToList(rb, 2);
    addToList(rb, 3);
    addToList(rb, 4);
    addToList(rb, 5);
    printf("before rotate:");
    printList(rb);
    rb = reverseKGroup(rb, 2);
    printf("after rotate:");
    printList(rb);


    head = addToList(NULL, -1);
    addToList(head, 11);
    addToList(head, 34);
    addToList(head, 5);
    addToList(head, 1);
    addToList(head, 82);
    addToList(head, 4);
    addToList(head, 0);
    addToList(head, 10);
    addToList(head, 11);
    addToList(head, 20);
    addToList(head, -5);
    addToList(head, -15);
    addToList(head, 15);
    head = sortList(head);
    printList(head);

    head = newNode(0);
    tail = addToList(head, 1);
    for (int i = 2; i < 25; i++)
    {
        tail = addToList(tail, i);
    }
    printf("original: ");
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");
    deleteMiddle(head);
    printf("after deleteMiddle: ");
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");

    head = addToList(NULL, 1);
    head->child = newNode(11);
    head->child->child = newNode(3);
    head->child->child->child = newNode(4);
    head->child->child->child->child = newNode(19);
    tail = addToList(head, 5);
    tail->child = newNode(82);
    tail->child->child = newNode(10);
    tail = addToList(tail, 22);
    tail->child = newNode(1);
    tail->child->child = newNode(14);
    tail = addToList(tail, 16);
    tail = addToList(tail, 6);
    tail->child = newNode(45);
    flattenLinkedList(head);
    printf("flattenLinkedList: ");
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");

    head = newNode(51);
    tail = addToList(head, 42);
    tail = addToList(tail, 14);
    tail = addToList(tail, 4);
    tail = addToList(tail, 24);
    head = mergeSort(head);
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");

    head = newNode(0);
    tail = addToList(head, 1);
    tail = addToList(tail, 2);
    tail = addToList(tail, 3);
    tail = addToList(tail, 4);
    tail->next = head->next;
    printf("first cycle: %d\n", firstNode(head)->val);

    head = newNode(2);
    tail = addToList(head, 1);
    tail = addToList(tail, 0);
    tail = addToList(tail, 0);
    tail = addToList(tail, 1);
    tail = addToList(tail, 2);
    tail = addToList(tail, 2);
    tail = addToList(tail, 0);
    tail = addToList(tail, 1);
    tail = addToList(tail, 1);
    tail = addToList(tail, 1);
    tail = addToList(tail, 0);
    printf("[0,2] linked list, sort:");
    sortLL(head);
    for (struct ListNode *i = head; i != NULL; i = i->next)
    {
        printf("%d ", i->val);
    }
    printf("\n");

    return 0;
}
