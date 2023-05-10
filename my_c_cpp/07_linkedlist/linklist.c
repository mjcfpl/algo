/**
 * 1) 单链表反转
 * 2) 链表中环的检测
 * 3) 两个有序的链表合并
 * 4) 删除链表倒数第 n 个结点
 * 5) 求链表的中间结点
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct SingleListNode_Tag {
    int val;
    struct SingleListNode_Tag *next;   
} SingleListNode;

void inster_node(SingleListNode **head, int data)
{
    SingleListNode *new_node = (SingleListNode *)malloc(sizeof(SingleListNode));
    new_node->val = data;
    new_node->next = *head;
    *head = new_node;
}

void print_list(SingleListNode *head)
{
    char ch = 0;

    if (head) {
        ch = '\n';
    }

    printf("------print begin------\n");

    while(head) {
        printf("%d ", head->val);
        head = head->next;
    }

    putchar(ch);
    printf("------print end------\n\n");
}

void reverse_list(SingleListNode **list)
{
    SingleListNode *cur = *list;
    SingleListNode *pre = NULL;
    SingleListNode *next = NULL;

    while (cur) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next; 
    }

    *list = pre;
}

void test_reverse()
{
    SingleListNode *head = NULL;
    inster_node(&head, 3);
    inster_node(&head, 8);
    inster_node(&head, 5);
    inster_node(&head, 1);
    inster_node(&head, 2);
    print_list(head);

    reverse_list(&head);
    print_list(head);
}

bool check_circle_exist(SingleListNode *head)
{
    bool ret = false;
    SingleListNode *fast = head;
    SingleListNode *slow = head;

    if (!head || !head->next)   //节点数<=1
    {
        return ret;
    }

    if (head->next == head)     //首节点自环
    {
        return true;
    }

    //节点数 >= 2
    while(1)
    {
        // fast前进2步
        fast = fast->next;
        if (!fast)
        {
            return false;
        }

        fast = fast->next;
        if (!fast)
        {
            return false;
        }
        
        if (fast == slow)
        {
            ret = true;
            break;
        }

        // slow前进1步
        slow = slow->next;
        if (fast == slow)
        {
            ret = true;
            break;
        }
    }

    if (ret == true)
    {
        printf("find circle, data=%d\n", fast->val);
    }

    return ret;
}

void test_check_circle()
{
    SingleListNode *head = NULL;
    SingleListNode *tmp, *tmp2;
    inster_node(&head, 3);
    tmp = head;
    inster_node(&head, 8);
    inster_node(&head, 5);
    inster_node(&head, 1);
    tmp2 = head;
    inster_node(&head, 2);
    tmp->next = tmp2;

    if (check_circle_exist(head) == true)
    {
        printf("circle exist\n");
    }
    else
    {
        printf("circle not exist\n");
    }
}

#if 0   //v1，子函数
// /* 由调用者保证 lst1/lst2/lst *lst1/*lst2/*lst 不为NULL */
void merge_smaller_node(SingleListNode **lst1, SingleListNode **lst2, SingleListNode **lst)
{
    if ((*lst1)->val <= (*lst2)->val)
    {
        (*lst)->next = (*lst1);
        (*lst) = *lst1;
        *lst1 = (*lst1)->next;
    }
    else
    {
        (*lst)->next = (*lst2);
        (*lst) = *lst2;
        *lst2 = (*lst2)->next;
    }
}

SingleListNode *merge_sorted_list(SingleListNode *lst1, SingleListNode *lst2)
{
    SingleListNode head = {0};
    SingleListNode *cur = &head;
    SingleListNode *smaller = NULL;

    if (!lst1)
    {
        return lst2;
    }

    if (!lst2)
    {
        return lst1;
    }

    // 两个链表都不为空
    while(1)
    {
        merge_smaller_node(&lst1, &lst2, &cur);

        if (!lst1)
        {
            cur->next = lst2;
            break;
        }
        
        if (!lst2)
        {
            cur->next = lst1;
            break;
        }        
    }

    return head.next;
}
#endif

#if 0   // v2: 不调子函数
SingleListNode *merge_sorted_list(SingleListNode *lst1, SingleListNode *lst2)
{
    SingleListNode head = {0};
    SingleListNode *cur = &head;
    SingleListNode *smaller = NULL;

    if (!lst1)
    {
        return lst2;
    }

    if (!lst2)
    {
        return lst1;
    }

    while (1)
    {
        if (lst1->val <= lst2->val)
        {
            cur->next = lst1;
            cur = lst1;
            lst1 = lst1->next;

            if (!lst1)
            {
                cur->next = lst2;
                break;
            }
        }
        else
        {
            cur->next = lst2;
            cur = lst2;
            lst2 = lst2->next;

            if (!lst2)
            {
                cur->next = lst1;
                break;
            }
        }
    }

    return head.next;
}
#endif

// v3: 统一处理
SingleListNode *merge_sorted_list(SingleListNode *lst1, SingleListNode *lst2)
{
    SingleListNode head = {0};      // 哨兵节点
    SingleListNode *cur = &head;

    while (1)
    {
        if (!lst1)
        {
            cur->next = lst2;
            break;
        }

        if (!lst2)
        {
            cur->next = lst1;
            break;
        }

        if (lst1->val <= lst2->val)
        {
            cur->next = lst1;
            cur = lst1;
            lst1 = lst1->next;
        }
        else
        {
            cur->next = lst2;
            cur = lst2;
            lst2 = lst2->next;
        }
    }

    return head.next;
}

void test_merge_sorted_list()
{
    SingleListNode *lst = NULL;
    SingleListNode *lst1 = NULL;
    SingleListNode *lst2 = NULL;


    // lst1
    inster_node(&lst1, 9);
    inster_node(&lst1, 7);
    inster_node(&lst1, 5);
    inster_node(&lst1, 3);
    inster_node(&lst1, 1);
    print_list(lst1);

    // lst2
    inster_node(&lst2, 6);
    inster_node(&lst2, 5);
    inster_node(&lst2, 4);
    inster_node(&lst2, 3);
    inster_node(&lst2, 2);
    print_list(lst2);

    lst = merge_sorted_list(lst1, lst2);
    print_list(lst);
}

SingleListNode *del_back_index(SingleListNode *lst, int index)
{
    int i = 0;
    SingleListNode head = {0, lst};     // 哨兵节点
    SingleListNode *fast = &head;
    SingleListNode *slow = &head;
    SingleListNode *node = NULL;

    if (index <= 0 || !lst)
    {
        return lst;
    }

    // fast先从前入后遍历index个节点
    for (i = 0; i < index; i++)
    {
        fast = fast->next;
        if (!fast)
        {
            break;
        }
    }

    if (i < index)
    {
        printf("i=%d < index=%d\n", i, index);  // lst节点数量i，未达到index个
        return lst;
    }

    while (1)
    {
        if (fast->next == NULL)     // fast->next为空时，slow->next为要删除的节点
        {
            node = slow->next;
            slow->next = node->next;
            free(node);
            node = NULL;
            break;
        }

        fast = fast->next;
        slow = slow->next;
    }

    return head.next;
}

void test_del_back_index()
{
    SingleListNode *head = NULL;
    inster_node(&head, 3);
    inster_node(&head, 8);
    inster_node(&head, 5);
    inster_node(&head, 1);
    inster_node(&head, 2);
    print_list(head);

    head = del_back_index(head, 4);
    print_list(head);
}

SingleListNode *get_middle_node(SingleListNode *lst)
{
    SingleListNode *fast = lst;
    SingleListNode *slow = lst;

    while (1)
    {
        if (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        else
        {
            return slow;
        }
        
    }
}

/* 哨兵 边界 举例 指针不丢 快慢指针 */
void test_get_middle_node()
{
    SingleListNode *head = NULL;
    SingleListNode *mid = NULL;

    // inster_node(&head, 3);
    inster_node(&head, 8);
    inster_node(&head, 5);
    inster_node(&head, 1);
    inster_node(&head, 2);
    print_list(head);

    mid = get_middle_node(head);
    if (NULL != mid)
    {
        printf("mid value: %d\n", mid->val);
    }
    else
    {
        printf("NULL\n");
    }
}

/* 哨兵 边界 举例 指针不丢 快慢指针 */
int main()
{
    // test_reverse();
    // test_check_circle();
    // test_merge_sorted_list();
    // test_del_back_index();
    test_get_middle_node();


    return 0;
}