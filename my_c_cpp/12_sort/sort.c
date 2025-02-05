/**
 * 归并排序
 * 快排
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/**
 * 有哨兵实现
 * 假定所有元素小于 MAX_INT
*/
#define MAX_INT 0x7FFFFFFF
void merge_guard(int *arr, int left, int right)
{
    int mid = (left + right) / 2;
    int i = 0;
    int j = 0;
    int k = left;
    int left_cnt = (mid - left + 2);    // 多分配一个，在最后存放哨兵
    int right_cnt = (right - mid + 1);  // 多分配一个，在最后存放哨兵

    if (NULL == arr || left >= right)
    {
        return;
    }

    int *arr_left = (int *)malloc(sizeof(int) * left_cnt);
    if (NULL == arr_left)
    {
        printf("------%s(%d): malloc arr_left failed ------\n", __FUNCTION__, __LINE__);
        return;
    }

    int *arr_right = (int *)malloc(sizeof(int) * right_cnt);
    if (NULL == arr_right)
    {
        printf("------%s(%d): malloc arr_right failed ------\n", __FUNCTION__, __LINE__);
        return;
    }

    memcpy(arr_left, &arr[left], (left_cnt - 1) * sizeof(int));
    arr_left[left_cnt - 1] = MAX_INT;
    memcpy(arr_right, &arr[mid + 1], (right_cnt - 1) * sizeof(int));
    arr_right[right_cnt - 1] = MAX_INT;

    while (!(i == left_cnt - 1 && j == right_cnt - 1))
    {
        if (arr_left[i] <= arr_right[j])
        {
            arr[k++] = arr_left[i++];
        }
        else
        {
            arr[k++] = arr_right[j++];
        }
    }

    free(arr_left);
    free(arr_right);
}


/**
 * 无哨兵实现
 * 将2个有序序列合并
 * arr[left, right]分为2部分，arr[left, mid]和arr[mid+1, right]
*/
void merge(int *arr, int left, int right)
{
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    int k = 0;
    int begin = 0;
    int end = 0;

    if (NULL == arr || left >= right)
    {
        return;
    }

    int *arr2 = (int *)malloc(sizeof(int) * (right - left + 1));
    if (NULL == arr2)
    {
        printf("------%s(%d): malloc failed ------\n", __FUNCTION__, __LINE__);
        return;
    }

    // 1. 合并2个子序列，合并完成后，其中1个子序列完全合入，另1个子序列没有完全合入
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            arr2[k++] = arr[i++];
        }
        else
        {
            arr2[k++] = arr[j++];
        }
    }

    // 2. 将未完全合入的子序列，将剩余部分合入
    begin = i;
    end = mid;
    if (i > mid)
    {
        begin = j;
        end = right;
    }

    for (i = begin; i <= end; i++)
    {
        arr2[k++] = arr[i];
    }

    // 3. 将合并后的arr2反向合入arr
    i = left;
    k = 0;
    while(i <= right)
    {
        arr[i++] = arr2[k++];
    }

    free(arr2);
    arr2 = NULL;
}

void merge_sort_c(int *arr, int left, int right)
{
    int mid = (left + right) / 2;

    if (NULL == arr || left >= right)
    {
        return;
    }

    merge_sort_c(arr, left, mid);
    merge_sort_c(arr, mid + 1, right);
    // merge(arr, left, right);
    merge_guard(arr, left, right);
}

void merge_sort(int *arr, int cnt)
{
    merge_sort_c(arr, 0, cnt - 1);
    print_arr(arr, cnt);
}

void test_merge_sort()
{
    int arr[] = {3, 2, 7, 6, 2, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);

    // merge_sort(arr, 0);
    // merge_sort(arr, 1);
    // merge_sort(arr, 2);
    // merge_sort(arr, 3);
    // merge_sort(arr, 4);
    merge_sort(arr, 5);
    // merge_sort(arr, 6);
}

void swap(int *v1, int *v2)
{
    int tmp = 0;
    tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

int partition(int *arr, int left, int right)
{
    int i = left;   // i为arr的索引，i的左侧都不大于arr[right]
    int j = left;
    int tmp = 0;

    for (j = left; j < right; j++)  // 使用j遍历right左侧节点，将不大于arr[right]的节点交换到i的左侧
    {
        if (arr[j] <= arr[right])
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[right]); // 循环结束后，[left, right-1]范围不大于arr[right]的都已放到i的左侧；i就是arr[right]应该放的位置
    return i;
}

/**
 * 取一个元素为分割点，小于它的放在左边，大于它的放在右边
*/
void quick_sort_c(int *arr, int left, int right)
{
    int pos = 0;

    if (NULL == arr || left >= right)
    {
        return;
    }

    pos = partition(arr, left, right);
    quick_sort_c(arr, left, pos - 1);
    quick_sort_c(arr, pos + 1, right);
}

void quick_sort(int *arr, int cnt)
{
    quick_sort_c(arr, 0, cnt - 1);
    print_arr(arr, cnt);
}

void test_quick_sort()
{
    int arr[] = {3, 2, 7, 6, 2, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);

    // quick_sort(arr, 0);
    // quick_sort(arr, 1);
    // quick_sort(arr, 2);
    // quick_sort(arr, 3);
    // quick_sort(arr, 4);
    // quick_sort(arr, 5);
    quick_sort(arr, 6);
}


void find_k_min(int *arr, int cnt, int k)
{
    int pos = 0;
    int begin = 0;
    int end = cnt - 1;

    if (NULL == arr || cnt < k)
    {
        printf("------%s(%d): invalid args------\n", __FUNCTION__, __LINE__);
        return;
    }

    while(1)
    {
        pos = partition(arr, begin, end);
        if (pos == k - 1)
        {
            printf("k min = %d\n", arr[pos]);
            break;
        }
        else if (pos > k - 1)
        {
            end = pos - 1;
        }
        else
        {
            begin = pos + 1;
        }
    }
}

// 假定数组的元素各不相同
void test_find_k_min()
{
    int arr[] = {3, 2, 7, 6, 8};
    int cnt = sizeof(arr) / sizeof(arr[0]);

    find_k_min(arr, cnt, 3);

}

int main()
{
    // test_merge_sort();
    // test_quick_sort();
    test_find_k_min();
    return 0;
}
