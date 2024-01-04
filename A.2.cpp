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
struct EDGE //拉链法
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
    //线性探测法
    while (user1[k].phone != 0 && user1[k].phone != x) //找到没使用过的或者已经存在的就返回
    {
        k++;
    }
    return k;
}
int hash_2(ll x)
{
    int k = (int)(sqrt(x) / 10000) % mod;
    //平方探测法 以k为mid 向两端 按照 1 -1 2 -2 4 -4的方式查找
    int t = k, d = 1;
    while (user2[t].phone != 0 && user2[t].phone != x) //找到没使用过的或者已经存在的 就返回
    {
        t = k + d;
        if (t < 0 || t > mod) //溢出
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
    while (num) //第三种哈希函数
    {
        sum += num % 10;
        num /= 10;
    }
    // 拉链法 相当sum 和 x之间建边  不会出现冲突
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
    while (num) //第三种哈希函数
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
            cout << "哈希函数3 查询到该用户" << endl;
            cout << "phone: " << edge[i].phone << " name: " << edge[i].name << " dress: " << edge[i].dress << endl;
            break;
        }
    }
    if (!f)
        cout << "哈希函数3 无法查询到该用户" << endl;
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
            cout << "无法找到合适的空间" << endl;
        }
        else 
        {
        	user2[k].phone = phon;
        	user2[k].dress = dres;
       	 	user2[k].name = na;
		}
  
        hash_3(phon, na, dres);
    }
    for (int i = 1; i <= 2; i++) //每次询问
    {
        ll ph; //每次输入电话进行查询
        cin >> ph;
        int k = hash_1(ph);
        if (user1[k].phone == 0)
        {
            cout << "哈希函数1 没找到该用户" << endl;
        }
        else
        {
            cout << "哈希函数1 查询到该用户" << endl;
            cout << "phone: " << ph << " name: " << user1[k].name << " dress: " << user1[k].dress << endl;
        }
        k = hash_2(ph);
        if (user2[k].phone == 0)
        {
            cout << "哈希函数2 没找到该用户" << endl;
        }
        else
        {
            cout << "哈希函数2 查询到该用户" << endl;
            cout << "phone: " << ph << " name: " << user2[k].name << " dress: " << user2[k].dress << endl;
        }
        find_hash_3(ph);
    	cout << "---------------------" << endl;
	}
}
