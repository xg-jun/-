#include<stdio.h>
#include<string.h>
char * baoli(char * s){
    int N = strlen(s), start = 0, len = 0;  // N �ַ������ȣ� start �Ӵ���ʼλ�ã� len �Ӵ�����
    for (int i = 0; i < N; i++) {   // �������ȵĻ����Ӵ�
        int left = i - 1, right = i + 1;
        while (left >= 0 && right < N && s[left] == s[right]){
            left--; right++;            // �� i Ϊ���ģ����������죬ֱ�������������
        }                               // left+1 ~ right-1 ��Ϊ��iΪ���ĵ��������Ӵ�
        if (right - left - 1 > len) {   // ���������򱣴���Ӵ���Ϣ
            start = left + 1;
            len = right - left - 1;
        }
    }
    for (int i = 0; i < N; i++) {   // ż�����ȵĻ����Ӵ�
        int left = i, right = i + 1;    // �� i+0.5 Ϊ���ģ�����������
        while (left >=0 && right < N && s[left] == s[right]) {
            left--, right++;
        }
        if (right - left - 1 > len) {
            start = left + 1;
            len = right - left - 1;
        }
    }
    s[start + len] = '\0';      // ԭ���޸ķ���
    return s + start;
}

char * mana(char * s){
    if(strlen(s)==0||strlen(s)==1) return s;
    int i,start,left,right,count,len;
    start = len =0;
    for(i=0;s[i]!='\0';i+=count){
        count = 1;
        left=i-1;
        right = i+1;
        while(s[right]!='\0'&&s[i]==s[right]){ //�����ظ��ַ���
            right++;
            count++;
        }
        while(left>=0 && s[right]!='\0' && s[left] == s[right]){
            left--;
            right++;
        }
        if(right-left-1>len){
            start = left+1;
            len = right-left-1;
        }
    }
    s[start + len] = '\0';      // ԭ���޸ķ���
    return s + start;
}

int main()
{
	char s1[1000];
	char *s2;
	scanf("%s",s1);
	s2=mana(s1);
	printf("%s",s2);
	return 0;
}
