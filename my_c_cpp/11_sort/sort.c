#include <stdio.h>

void print_arr(int *arr, int cnt);
void bubble_sort(int * arr, int cnt);
void test_bubble_sort();


void print_arr(int *arr, int cnt)
{
    int i = 0;

    printf("arr: ");
    for (i = 0; i < cnt; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int * arr, int cnt)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
    bool flag = false;

    if (NULL == arr || cnt <= 1)
    {
        return;
    }

    // i表示第几次遍历；cnt=2时，遍历次数为1，cnt=3时，遍历次数为2，所以遍历总次数为 cnt-1；所以i的取值范围是[1, cnt-1]
    for (i = 1; i < cnt; i++)
    {
        flag = false;  //表示本次遍历是否有数据交换；

        // 对于第i次遍历，要比较的索引范围是[0, cnt - i]；
        // j表示元素的过引；
        // 每次比较arr[j] & arr[j+1]，所以j的取值范围是[0, cnt-i)
        for (j = 0; j < cnt - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                flag = true;
            }
        }
        
        if (flag == false)  //本次遍历没有数据交换，说明全部已为有序状态，排序完成
        {
            break;
        }
    }
}

void test_bubble_sort()
{
    int arr[] = {3, 2, 7, 2, 6, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, cnt);
    print_arr(arr, cnt);
}

/**
 * 序列分为左右两部分，左边是有序部分，右边是无序部分
 * 每次取无序部分第一个数，把这个数插到左边正确的位置上
 */
void insert_sort(int * arr, int cnt)
{
    int i = 0; 
    int j = 0;
    int val = 0;

    if (NULL == arr || cnt <= 1)
    {
        return;
    }

    // 初始有序部分是arr[0]，无序部分是arr[1] ~ arr[cnt - 1]
    for (i = 1; i < cnt; i++)   // i表示遍历无序部分，取值范围是[1, cnt)
    {
        val = arr[i];   // 无序部分首元素

        // 对于第i次遍历，无序元素是a[i]
        // j表示有序元素的索引，取值范围是[0, i - 1]
        // 查找插入位置 && 挪动大于 无序元素 的有序元素
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] > val)   //当前元素大于无序元素，将当前元素往后移1个位置
            {
                arr[j + 1] = arr[j];
            }
            else
            {       
                // 当前元素不大于无序元素，arr[j + 1]处为无序元素的插入点；结束本次遍历
                break;  
            }            
        }

        // 循环退出有2种情况：1. 遇到有无素不大于无序元素；2. 所有元素都大于无序元素（j==-1）
        arr[j + 1] = val;       
    }
}

void test_insert_sort()
{
    int arr[] = {3, 2, 7, 6, 2, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);
    insert_sort(arr, cnt);
    print_arr(arr, cnt);
}

/**
 * 选择排序每次会从未排序区间中找到最小的元素，将其放到已排序区间的末尾。
 */
void select_sort(int * arr, int cnt)
{
    int i = 0;
    int j = 0;
    int min_index = 0;
    int val = 0;

    if (NULL == arr || cnt <= 1)
    {
        return;
    }

    for (i = 0; i < cnt - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < cnt; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }

        if (min_index != i)
        {
            val = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = val;
        }
    }
}

void test_select_sort()
{
    int arr[] = {3, 2, 7, 6, 2, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);
    select_sort(arr, cnt);
    print_arr(arr, cnt);
}

int main()
{
    // test_bubble_sort();
    // test_insert_sort();
    test_select_sort();

    return 0;
}

