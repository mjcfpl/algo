#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t
{
    Node_t *next;
    int data;
} Node;

Node *stack_create()
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("------%s(%d): malloc failed------\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    head->next = NULL;
    return head;
}

void stack_destory(Node *stack)
{
    Node *node = NULL;

    if (stack)
    {
        while(stack->next)
        {
            node = stack->next->next;
            free(stack->next);
            stack->next = node;
        }

        free(stack);
    }
}

int stack_push(Node *stack, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (NULL == node)
    {
        printf("------%s(%d): malloc failed------\n", __FUNCTION__, __LINE__);
        return -1;
    }

    node->data = val;
    node->next = stack->next;
    stack->next = node;
    return 0;
}

int stack_pop(Node *stack, int *val)
{
    if (NULL == stack->next)
    {
        printf("------%s(%d): empty------\n", __FUNCTION__, __LINE__);
        return -1;
    }

    *val = stack->next->data;
    stack->next = stack->next->next;
    return 0;
}

int stack_top(Node *stack, int *val)
{
    if (NULL == stack->next)
    {
        printf("------%s(%d): empty------\n", __FUNCTION__, __LINE__);
        return -1;
    }

    *val = stack->next->data;
    return 0;
}

int get_int_from_string(char **str, int *v)
{
    char *p = *str;
    int val = 0;
    while(1)
    {
        if (*p >= '0' && *p <= '9')
        {
            val = val * 10 + (*p - '0');
            p++;
        }
        else
        {
            *str = p;
            *v = val;
            break;
        }
    }

    return 0;
}

int get_op_pri(char op)
{
    int pri = 1;

    switch (op)
    {
        case '+':
        case '-':
            pri = 1;
            break;
        case '*':
        case '/':
            pri = 2;
            break;
    }

    return pri;
}

int calc(int left, int right, char op)
{
    switch(op)
    {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }

    return 0;
}

int calc_with_stack(char *str)
{
    char *p = str;
    char op1, op2;
    int left = 0;
    int right = 0;
    int data = 0;
    int ret = 0;
    Node *stack1 = stack_create();
    Node *stack2 = stack_create();

    get_int_from_string(&p, &data);

    if (0 == *p)
    {
        stack_destory(stack1);
        stack_destory(stack2);
        return data;
    }

    stack_push(stack1, data);
    stack_push(stack2, *p++);
    get_int_from_string(&p, &data);
    stack_push(stack1, data);

    while (1)
    {
        if (0 == *p)
        {
            while (1)
            {
                stack_pop(stack1, &right);

                ret = stack_pop(stack2, &data);
                if (ret < 0)
                {
                    stack_destory(stack1);
                    stack_destory(stack2);
                    printf("%s = %d\n", str, right);
                    return right;
                }
                op1 = data;

                stack_pop(stack1, &left);
                data = calc(left, right, op1);
                stack_push(stack1, data);
            }
        }

        op2 = *p++;

        while (1)
        {
            ret = stack_top(stack2, &data);
            if (ret < 0)
            {
                stack_push(stack2, op2);
                get_int_from_string(&p, &data);
                stack_push(stack1, data);
                break;
            }

            op1 = data;

            if (get_op_pri(op2) > get_op_pri(op1))
            {
                stack_push(stack2, op2);
                get_int_from_string(&p, &data);
                stack_push(stack1, data);
                break;
            }
            else
            {
                stack_pop(stack1, &right);
                stack_pop(stack1, &left);
                stack_pop(stack2, &data);
                op1 = data;
                data = calc(left, right, op1);
                stack_push(stack1, data);
            }
        }
    }
}

void test_cal()
{
    calc_with_stack("34+13*9+44-12/3");
    calc_with_stack("34+13*9+44-12/3+2");
}

int main()
{
    test_cal();


    return 0;
}