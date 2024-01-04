#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���������ǰ׺��LCP������
void computeLCPArray(char *pattern, int m, int *lcp) {
    int len = 0;
    int i = 1;
    lcp[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lcp[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lcp[len - 1];
            } else {
                lcp[i] = 0;
                i++;
            }
        }
    }
}
// KMP�㷨���Ľ��汾��
int KMP(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // ���������ǰ׺��LCP������
    int *lcp = (int *)malloc(sizeof(int) * m);
    computeLCPArray(pattern, m, lcp);

    int i = 0, j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            free(lcp);
            return i - j;  // �Ӵ���Ŀ�괮�е�λ��
        }

        if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lcp[j - 1];
            else
                i++;
        }
    }

    free(lcp);
    return -1;  // �Ӵ�����Ŀ�괮��
}


int main() {
	
    char text[100];
    char pattern[100];
    printf("������Ŀ�괮��\n");
	gets(text);
	printf("�������Ӵ���\n");
	gets(pattern);

    int result = KMP(text, pattern);

    if (result != -1) {
        printf("�Ӵ���Ŀ�괮�е�λ�ã�%d\n", result);
    } else {
        printf("�Ӵ�����Ŀ�괮��\n");
    }

    return 0;
}

