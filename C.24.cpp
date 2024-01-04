#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 构建最长公共前缀（LCP）数组
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
// KMP算法（改进版本）
int KMP(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // 构建最长公共前缀（LCP）数组
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
            return i - j;  // 子串在目标串中的位置
        }

        if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lcp[j - 1];
            else
                i++;
        }
    }

    free(lcp);
    return -1;  // 子串不在目标串中
}


int main() {
	
    char text[100];
    char pattern[100];
    printf("请输入目标串：\n");
	gets(text);
	printf("请输入子串：\n");
	gets(pattern);

    int result = KMP(text, pattern);

    if (result != -1) {
        printf("子串在目标串中的位置：%d\n", result);
    } else {
        printf("子串不在目标串中\n");
    }

    return 0;
}

