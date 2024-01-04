#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

bool isValidOutSequence(char* sequence, char* charSet) {
    int len = strlen(sequence);  // ���г���
    int charSetLen = strlen(charSet);  // �ַ�������
    int stack[MAX_SIZE];  // ģ��ջ
    int top = -1;  // ջ��ָ��

    int i, j = 0;
    for (i = 0; i < len; i++) {
        // ���ַ������е��ַ����ַ����е��ַ����бȽ�
        for (j = 0; j < charSetLen; j++) {
            if (sequence[i] == charSet[j]) {
                break;
            }
        }
        if (j == charSetLen) {
            // ����ַ������ַ����У���ֱ�ӷ���false
            return false;
        }

        // ģ��ջ�ĳ�ջ����
        while (top >= 0 && stack[top] == sequence[i]) {
            top--;
        }

        // ģ��ջ����ջ����
        if (top < MAX_SIZE - 1) {
            stack[++top] = sequence[i];
        } else {
            // ջ����������false
            return 0;
        }
    }

    // �ж�ջ�Ƿ�Ϊ��
    return 1;
}

int main() {
    char sequence[MAX_SIZE];
    char charSet[] = "abcde";

    printf("���������У�");
    scanf("%s", sequence);

    if (isValidOutSequence(sequence, charSet)==1) {
        printf("�ǺϷ��ĳ�ջ���С�\n");
    } else {
        printf("���ǺϷ��ĳ�ջ���С�\n");
    }

    return 0;
}

