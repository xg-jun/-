#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

bool isValidOutSequence(char* sequence, char* charSet) {
    int len = strlen(sequence);  // 序列长度
    int charSetLen = strlen(charSet);  // 字符集长度
    int stack[MAX_SIZE];  // 模拟栈
    int top = -1;  // 栈顶指针

    int i, j = 0;
    for (i = 0; i < len; i++) {
        // 将字符序列中的字符与字符集中的字符进行比较
        for (j = 0; j < charSetLen; j++) {
            if (sequence[i] == charSet[j]) {
                break;
            }
        }
        if (j == charSetLen) {
            // 如果字符不在字符集中，则直接返回false
            return false;
        }

        // 模拟栈的出栈操作
        while (top >= 0 && stack[top] == sequence[i]) {
            top--;
        }

        // 模拟栈的入栈操作
        if (top < MAX_SIZE - 1) {
            stack[++top] = sequence[i];
        } else {
            // 栈已满，返回false
            return 0;
        }
    }

    // 判断栈是否为空
    return 1;
}

int main() {
    char sequence[MAX_SIZE];
    char charSet[] = "abcde";

    printf("请输入序列：");
    scanf("%s", sequence);

    if (isValidOutSequence(sequence, charSet)==1) {
        printf("是合法的出栈序列。\n");
    } else {
        printf("不是合法的出栈序列。\n");
    }

    return 0;
}

