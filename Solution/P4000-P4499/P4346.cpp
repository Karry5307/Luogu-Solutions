#include<bits/stdc++.h>
using namespace std;
typedef int ll;
map<string,char>mp;
ll cur,length,pos,res;
string calc;
string str[11]={
    "xxxxxx...xx...xx...xx...xx...xxxxxx",
    "....x....x....x....x....x....x....x",
    "xxxxx....x....xxxxxxx....x....xxxxx",
    "xxxxx....x....xxxxxx....x....xxxxxx",
    "x...xx...xx...xxxxxx....x....x....x",
    "xxxxxx....x....xxxxx....x....xxxxxx",
    "xxxxxx....x....xxxxxx...xx...xxxxxx",
    "xxxxx....x....x....x....x....x....x",
    "xxxxxx...xx...xxxxxxx...xx...xxxxxx",
    "xxxxxx...xx...xxxxxx....x....xxxxxx",
    ".......x....x..xxxxx..x....x......."
},val[10],temp[20];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll toInt(string str)
{
    ll res=0;
    for(register int i=0;i<str.length();i++)
    {
        res=(res<<3)+(res<<1)+(str[i]-'0');
    }
    return res;
}
inline string toString(ll num)
{
    string str;
    while(num)
    {
        str=(char)(num%10+'0')+str;
        num/=10;
    }
    return str;
}
int main()
{
    for(register int i=0;i<11;i++)
    {
        mp[str[i]]=i==10?'+':i+'0';
    }
    for(register int i=0;i<7;i++)
    {
        cin>>val[i];
    }
    length=(val[0].length()+1)/6;
    for(register int i=0;i<7;i++)
    {
        cur=0;
        while(val[i].length()!=0)
        {
            for(register int j=0;j<5;j++)
            {
                temp[cur]+=val[i][j];
            }
            val[i].erase(0,6);
            cur++;
        }
    }
    for(register int i=0;i<length;i++)
    {
        calc+=mp[temp[i]];
        if(mp[temp[i]]=='+')
        {
            pos=i;
        }
    }
    res=toInt(calc.substr(0,pos))+toInt(calc.substr(pos+1)),calc=toString(res);
    for(register int i=0;i<35;i+=5)
    {
        for(register int j=0;j<calc.length();j++)
        {
            res=calc[j]-'0';
            printf("%c%c%c",str[res][i],str[res][i+1],str[res][i+2]);
            printf("%c%c",str[res][i+3],str[res][i+4]);
            if(j!=calc.length()-1)
            {
                putchar('.');
            }
        }
        puts("");
    }
}
