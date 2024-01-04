#include <stdio.h>
#include <string.h>
#include <ctype.h>

void geshihua(char *juzi) {
    int len = strlen(juzi);
    int i, j;
    int zishu = 0;
    int konggeshu = 0;

    // 去除开头的空格
    while (isspace(juzi[0])) {
        memmove(juzi, juzi + 1, len--);
    }

    // 去除末尾的空格
    while (isspace(juzi[len - 1])) {
        juzi[--len] = '\0';
    }

    // 去除单词之间多余的空格
    for (i = 0, j = 0; i < len; i++) {
        if (isspace(juzi[i])) {
            konggeshu++;
        } else {
            konggeshu = 0;
        }

        if (konggeshu <= 1) {
            juzi[j++] = juzi[i];
        }
    }
    juzi[j] = '\0';
}

int main() {
    char sentence1[] = "     This is an example sentence.";
    char sentence2[] = "      Hello     world! ";

    printf("原始句子1：%s\n", sentence1);
    geshihua(sentence1);
    printf("格式化后的句子1：%s\n", sentence1);

    printf("原始句子2：%s\n", sentence2);
    geshihua(sentence2);
    printf("格式化后的句子2：%s\n", sentence2);

    return 0;
}

