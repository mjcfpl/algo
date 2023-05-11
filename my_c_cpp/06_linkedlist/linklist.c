/*
 * 判断字符串是否为回文： abccba
 * 0. 由字符串生成单向链表
 * 1. 找到中间节点
 * 2. 链表拆成两部分，并将后半部分逆序
 * 3. 前后两部分比较
 * 4. 恢复链表：将后半部分逆序恢复，再合并链表
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct SingleListNode_Tag {
    char val;
    struct SingleListNode_Tag *next;   
} SingleListNode;

void del_list(SingleListNode *lst)
{
    SingleListNode *tmp = NULL;

    while (lst)
    {
        tmp = lst->next;
        free(lst);
        lst = tmp;
    }
}

SingleListNode *creat_list_from_string(const char *str)
{
    SingleListNode head = {0};
    SingleListNode *cur = &head;
    SingleListNode *new_node = NULL;

    if (NULL == str)
    {
        printf("%s(%d): str is NULL\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    while(*str)
    {
        new_node = (SingleListNode *)malloc(sizeof(SingleListNode));
        if (NULL == new_node)
        {
            printf("------%s(%d): malloc failed------\n", __FUNCTION__, __LINE__);
            del_list(head.next);
            return NULL;
        }

        new_node->val = *str;
        new_node->next = NULL;
        cur->next = new_node;
        cur = new_node;

        str++;
    }

    return head.next;
}


void print_list(SingleListNode *head)
{
    char ch = 0;

    if (head) {
        ch = '\n';
    }

    printf("------print begin------\n");

    while(head) {
        printf("%c", head->val);
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

bool check_list_is_huiwen(SingleListNode *lst)
{
    bool ret = true;
    int flag = 0;                           //链表节点个数奇偶标志位，奇数个为1，偶数个为2
    SingleListNode *fast = lst;
    SingleListNode *slow = lst;
    SingleListNode *right_list = NULL;      // 将链表从中间节点拆成两半，代表右边的链表
    SingleListNode *left_node = NULL;       // 左链表中的节点
    SingleListNode *left_end_node = NULL;   // 左链表中最后一个节点；找到中间节点后，若为奇数链，则值为slow；否则为slow之前的节点
    SingleListNode *right_node = NULL;      // 右链表中的节点

    if (NULL == lst || NULL == lst->next)
    {
        return true;
    }

    // 1. 找到中间节点
    while(1)
    {
        if (NULL == fast)
        {
            flag = 2;
        }
        else if (NULL == fast->next)
        {
            flag = 1;
        }

        if (flag)
        {
            break;
        }

        fast = fast->next->next;
        left_end_node = slow;
        slow = slow->next;
    }

    // 2. 链表拆成两部分，并将后半部分逆序
    if (flag == 1)
    {
        left_end_node = slow;       // 链表有奇数个节点，2n+1, 左半部n+1个，右半部n个；slow为中间节点，不参与比较；左链比右链多一个中间节点slow
        right_list = slow->next;    // 奇数链表，右链起点为slow->next
    }
    else
    {
        right_list = slow;          // 偶数链表，右链起点为slow
    }

    reverse_list(&right_list);
    // printf("right_list: \n");
    // print_list(right_list);

    // 前后两部分比较
    left_node = lst;
    right_node = right_list;
    while(1)
    {
        if (NULL == right_node)     // 全部比较完的标志是，右链遍历完，说明两者完全相同
        {
            ret = true;
            break;
        }

        if (left_node->val != right_node->val)
        {
            ret = false;
            break;
        }

        left_node = left_node->next;
        right_node = right_node->next;
    }

    // 4. 恢复链表：将后半部分逆序恢复，再合并链表
    reverse_list(&right_list);
    // printf("right_list: \n");
    // print_list(right_list);

    left_end_node->next = right_list;
    // printf("merged list: \n");
    // print_list(lst);

    return ret;
}

void check_huiwen_string(const char *str)
{
    if (NULL == str || *str == 0)
    {
        printf("str is NULL or empty\n");
        return;
    }

    // 由字符串生成单向链表
    SingleListNode *lst = creat_list_from_string(str);
    if (NULL == lst)
    {
        printf("create list failed\n");
        return;
    }
    // print_list(lst);

    if (true == check_list_is_huiwen(lst))
    {
        printf("%s is huiwen\n", str);
    }
    else
    {
        printf("%s is not huiwen\n", str);
    }

    del_list(lst);
}

void test_huiwen()
{
    char *str = "a";
    check_huiwen_string(str);

    str = "aa";
    check_huiwen_string(str);

    str = "ab";
    check_huiwen_string(str);

    str = "aba";
    check_huiwen_string(str);

    str = "abc";
    check_huiwen_string(str);

    str = "abba";
    check_huiwen_string(str);

    str = "abca";
    check_huiwen_string(str);

    str = "abcba";
    check_huiwen_string(str);

    str = "abcab";
    check_huiwen_string(str);

    str = "abcd1dcba";
    check_huiwen_string(str);
}

int main()
{
    test_huiwen();
    return 0;
}