#include <stdio.h>
#include <stdlib.h> 
int merge(int arr[], int temp[], int left, int mid, int right) {
    int i, j, k;
    int inversions = 0;

    i = left; // 左子数组的起始索引
    j = mid; // 右子数组的起始索引
    k = left; // 合并后的数组的起始索引

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += (mid - i); // 统计逆序对的数量
        }
    }

    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

int mergeSort(int arr[], int temp[], int left, int right) {
    int mid, inversions = 0;

    if (right > left) {
        mid = (left + right) / 2;
        inversions += mergeSort(arr, temp, left, mid);
        inversions += mergeSort(arr, temp, mid + 1, right);
        inversions += merge(arr, temp, left, mid + 1, right);
    }

    return inversions;
}

int minSteps(int arr[], int n) {
    int *temp = (int *)malloc(sizeof(int) * n);
    int inversions = mergeSort(arr, temp, 0, n - 1);
    free(temp);
    return inversions;
}

int main() {
    int n, i;
    printf("请输入排列的长度 N：");
    scanf("%d", &n);

    int arr[n];
    printf("请输入随机排列：");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int steps = minSteps(arr, n);
    printf("最少的变换步数为：%d\n", steps);

    return 0;
}

