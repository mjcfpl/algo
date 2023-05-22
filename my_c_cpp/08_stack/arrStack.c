#include <stdio.h>
#include <stdlib.h>

typedef struct ArrStack_tag
{
    int size;
    int top;
    int *arr;
}ArrStack;

ArrStack *ArrStack_create(int size)
{
    ArrStack *stack = (ArrStack *)malloc(sizeof(ArrStack));
    if (NULL == stack)
    {
        printf("------%s(%d): malloc stack failed------\n", __FUNCTION__, __LINE__);
        return NULL;
    }

    stack->arr = (int *)malloc(sizeof(int) * size);
    if (NULL == stack->arr)
    {
        printf("------%s(%d): malloc arr failed------\n", __FUNCTION__, __LINE__);
        free(stack);
        return NULL;
    }

    stack->size = size;
    stack->top = -1;
    return stack;
}

void ArrStack_destroy(ArrStack *stack)
{
    if (stack)
    {
        if (stack->arr)
        {
            free(stack->arr);
        }

        free(stack);
    }
}

int ArrStack_push(ArrStack *stack, int data)
{
    if (stack->top >= stack->size - 1)
    {
        printf("------%s(%d): full------\n", __FUNCTION__, __LINE__);
        return -1;
    }

    stack->arr[++stack->top] = data;
    return 0;
}

int ArrStack_pop(ArrStack *stack, int *data)
{
    if (stack->top <= 0)
    {
        printf("------%s(%d): empty------\n", __FUNCTION__, __LINE__);
        return -1;
    }

    *data = stack->arr[stack->top--];
    return 0;
}

void ArrStack_print(ArrStack *stack)
{
    int i = 0;
    for (i = 0; i <= stack->top; i++)
    {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}


void test_ArrStack()
{
    int data;
    ArrStack *stack = ArrStack_create(10);
    ArrStack_push(stack, 2);
    ArrStack_push(stack, 1);
    ArrStack_push(stack, 3);
    ArrStack_push(stack, 6);
    ArrStack_push(stack, 5);
    ArrStack_print(stack);

    ArrStack_pop(stack, &data);
    printf("%d\n", data);
    ArrStack_print(stack);

    ArrStack_destroy(stack);
}

int main()
{
    test_ArrStack();

    return 0;
}