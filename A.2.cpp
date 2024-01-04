#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod = 13;
struct node
{
    ll phone;
    string name;
    string dress;
};
struct EDGE //������
{
    int next;
    ll phone;
    string name;
    string dress;
};
EDGE edge[1000];
int head[1000];
int idx;
node user1[100];
node user2[100];
int hash_1(ll x)
{
    int k = x % mod; 
    //����̽�ⷨ
    while (user1[k].phone != 0 && user1[k].phone != x) //�ҵ�ûʹ�ù��Ļ����Ѿ����ڵľͷ���
    {
        k++;
    }
    return k;
}
int hash_2(ll x)
{
    int k = (int)(sqrt(x) / 10000) % mod;
    //ƽ��̽�ⷨ ��kΪmid ������ ���� 1 -1 2 -2 4 -4�ķ�ʽ����
    int t = k, d = 1;
    while (user2[t].phone != 0 && user2[t].phone != x) //�ҵ�ûʹ�ù��Ļ����Ѿ����ڵ� �ͷ���
    {
        t = k + d;
        if (t < 0 || t > mod) //���
        {
            break;
        }
        if (d > 0)
            d *= -1;
        else
        {
            d = d * -1 * 2;
        }
    }
    return t;
}
int hash_3(ll x, string na, string dres)
{
    ll sum = 0;
    ll num = x;
    while (num) //�����ֹ�ϣ����
    {
        sum += num % 10;
        num /= 10;
    }
    // ������ �൱sum �� x֮�佨��  ������ֳ�ͻ
    edge[++idx].next = head[sum];
    edge[idx].name = na;
    edge[idx].phone = x;
    edge[idx].dress = dres;
    head[sum] = idx;
}
void find_hash_3(ll ph)
{
    ll sum = 0;
    ll num = ph;
    while (num) //�����ֹ�ϣ����
    {
        sum += num % 10;
        num /= 10;
    } 
    int f = 0;
    for (int i = head[sum]; i; i = edge[i].next)
    {
        if (edge[i].phone == ph)
        {
            f = 1;
            cout << "��ϣ����3 ��ѯ�����û�" << endl;
            cout << "phone: " << edge[i].phone << " name: " << edge[i].name << " dress: " << edge[i].dress << endl;
            break;
        }
    }
    if (!f)
        cout << "��ϣ����3 �޷���ѯ�����û�" << endl;
}
int main()
{
    for (int i = 1; i <= 3; i++)
    {
        ll phon;
        string na, dres;
        cin >> phon >> na >> dres;
        int k = hash_1(phon);
        user1[k].phone = phon;
        user1[k].dress = dres;
        user1[k].name = na;
        k = hash_2(phon);
        if (k > mod || k < 0)
        {
            cout << "�޷��ҵ����ʵĿռ�" << endl;
        }
        else 
        {
        	user2[k].phone = phon;
        	user2[k].dress = dres;
       	 	user2[k].name = na;
		}
  
        hash_3(phon, na, dres);
    }
    for (int i = 1; i <= 2; i++) //ÿ��ѯ��
    {
        ll ph; //ÿ������绰���в�ѯ
        cin >> ph;
        int k = hash_1(ph);
        if (user1[k].phone == 0)
        {
            cout << "��ϣ����1 û�ҵ����û�" << endl;
        }
        else
        {
            cout << "��ϣ����1 ��ѯ�����û�" << endl;
            cout << "phone: " << ph << " name: " << user1[k].name << " dress: " << user1[k].dress << endl;
        }
        k = hash_2(ph);
        if (user2[k].phone == 0)
        {
            cout << "��ϣ����2 û�ҵ����û�" << endl;
        }
        else
        {
            cout << "��ϣ����2 ��ѯ�����û�" << endl;
            cout << "phone: " << ph << " name: " << user2[k].name << " dress: " << user2[k].dress << endl;
        }
        find_hash_3(ph);
    	cout << "---------------------" << endl;
	}
}
