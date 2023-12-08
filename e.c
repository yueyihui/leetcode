#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
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
    n->val=val;
    n->next = NULL;
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

//L1:1 2 3 10 11 NULL
//L2:4 15 NULL
//when 3->next=merge(3->next,4), 3->next= want to L2 as return
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
    return 0;
}
