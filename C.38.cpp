#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 反转字符串
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// 大数加法
char* add(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;
    char *result = (char*)malloc(sizeof(char) * (maxLen + 2)); // +2 for possible carry and '\0'
    if (!result) return NULL; // 分配内存失败

    reverse(num1);
    reverse(num2);

    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int digit1 = i < len1 ? num1[i] - '0' : 0;
        int digit2 = i < len2 ? num2[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        result[i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        result[maxLen] = carry + '0';
        result[maxLen + 1] = '\0';
    } else {
        result[maxLen] = '\0';
    }

    reverse(result);
    reverse(num1);
    reverse(num2);

    return result;
}

// 大数减法（假设 num1 >= num2）
char* subtract(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char *result = (char*)malloc(sizeof(char) * (len1 + 1));
    if (!result) return NULL; // 分配内存失败

    reverse(num1);
    reverse(num2);

    for (int i = 0; i < len2; i++) {
        if (num1[i] < num2[i]) {
            num1[i] += 10;
            num1[i+1]--;
        }
        result[i] = (num1[i] - num2[i]) + '0';
    }

    for (int i = len2; i < len1; i++) {
        if (num1[i] < '0') {
            num1[i] += 10;
            num1[i+1]--;
        }
        result[i] = num1[i];
    }

    reverse(result);
    reverse(num1);
    reverse(num2);

    // 移除前导零
    int start = strlen(result) - 1;
    while (start >= 0 && result[start] == '0') {
        start--;
    }
    if (start < 0) {
        result[0] = '0';
        result[1] = '\0';
    } else if (start < (len1 - 1)) {
        result[start + 1] = '\0';
    }

    return result;
}

// 大数乘法
char* multiply(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    char *result = (char*)calloc(len1 + len2, sizeof(char)); // 初始化为0
    if (!result) return NULL; // 分配内存失败

    reverse(num1);
    reverse(num2);

    for (int i = 0; i < len1; i++) {
        int carry = 0;
        for (int j = 0; j < len2; j++) {
            int sum = (num1[i] - '0') * (num2[j] - '0') + (result[i + j] - '0') + carry;
            result[i + j] = (sum % 10) + '0';
            carry = sum / 10;
        }
        if (carry > 0) {
            result[i + len2] += carry;
        }
    }

    reverse(result);

    // 移除前导零
    int start = strlen(result) - 1;
    while (start >= 0 && result[start] == '0') {
        start--;
    }
    if (start < 0) {
        free(result);
        return strdup("0");
    }
    result[start + 1] = '\0';

    reverse(num1);
    reverse(num2);

    return result;
}

int main() {
    char num1[] = "12345678901234567890";
    char num2[] = "98765432109876543210";
    
    char *sum = add(num1, num2);
    printf("和: %s\n", sum);
    free(sum);

    char *diff;
    if (strlen(num1) > strlen(num2) || (strlen(num1) == strlen(num2) && strcmp(num1, num2) >= 0)) {
        diff = subtract(num1, num2);
        printf("差: %s\n", diff);
    } else {
        diff = subtract(num2, num1);
        printf("差: -%s\n", diff);
    }
    free(diff);

    char *prod = multiply(num1, num2);
    printf("积: %s\n", prod);
    free(prod);

    return 0;
}

