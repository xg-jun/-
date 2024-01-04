#include <stdio.h>

double findMedianSortedArrays(int nums1[], int nums2[], int length) {
    int totalLength = 2 * length;
    int merged[totalLength];
    int i = 0, j = 0, k = 0;

    while (i < length && j < length) {
        if (nums1[i] <= nums2[j]) {
            merged[k++] = nums1[i++];
        } else {
            merged[k++] = nums2[j++];
        }
    }

    while (i < length) {
        merged[k++] = nums1[i++];
    }

    while (j < length) {
        merged[k++] = nums2[j++];
    }

    if (totalLength % 2 == 0) {
        return (merged[totalLength / 2 - 1] + merged[totalLength / 2]) / 2.0;
    } else {
        return merged[totalLength / 2];
    }
}

int main() {
    int nums1[] = {1, 3, 5, 7, 9};
    int nums2[] = {2, 4, 6, 8, 10};
    int length = sizeof(nums1) / sizeof(nums1[0]);
    double median = findMedianSortedArrays(nums1, nums2, length);
    printf("中位数: %.1lf\n", median);

    int nums3[] = {11, 13, 15, 17, 19};
    int nums4[] = {2, 4, 6, 8, 20};
    double median2 = findMedianSortedArrays(nums3, nums4, length);
    printf("中位数: %.1lf\n", median2);

    return 0;
}

