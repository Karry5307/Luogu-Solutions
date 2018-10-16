#include<bits/stdc++.h>
using namespace std;
typedef int ll;
struct Node{
    string name;
    ll status;
};
Node teacher[3],student[5];
map<string,ll>mp;
vector<string>vec,op;
ll cnt,valid,val,ccnt;
ll gg[5];
string comm,str;
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
inline vector<string> split(string str,char delim)
{
    vector<string>vec;
    string temp;
    for(register int i=0;i<str.length();i++)
    {
        if(str[i]==delim)
        {
            vec.push_back(temp);
            temp="";
        }
        else
        {
            temp+=str[i];
        }
    }
    vec.push_back(temp);
    return vec;
}
int main()
{
    cnt=read();
    for(register int i=0;i<3;i++)
    {
        cin>>teacher[i].name,mp[teacher[i].name]=i+1;
    }
    for(register int i=0;i<5;i++)
    {
        cin>>student[i].name,mp[student[i].name]=i+4;
    }
    cin.ignore(INT_MAX,'\n');
    for(register int i=0;i<cnt;i++)
    {
        getline(cin,comm);
        valid=0,vec=split(comm,' '),val=mp[vec[0]];
        if(vec.size()==2&&vec[1]=="came!"&&val>0&&val<4&&!teacher[val].status)
        {
            teacher[val].status=1,valid=1;
            for(register int i=0;i<5;i++)
            {
                if(student[i].status)
                {
                    gg[i]=1;
                }
            }
        }
        if(vec.size()==2&&vec[1]=="left!"&&val>0&&val<4&&teacher[val].status)
        {
            teacher[val].status=0,valid=1;
        }
        if(vec.size()==4&&val>3)
        {
            str=vec[1]+" "+vec[2]+" "+vec[3];
            if(str=="started playing games!"&&!student[val-4].status)
            {
                student[val-4].status=1,valid=1;
                for(register int i=0;i<3;i++)
                {
                    if(teacher[i].status)
                    {
                        gg[val-4]=1;
                    }
                }
            }
            if(str=="stopped playing games!"&&student[val-4].status)
            {
                student[val-4].status=0,valid=1;
            }
        }
    }
    for(register int i=0;i<5;i++)
    {
        if(gg[i])
        {
            op.push_back(student[i].name);
            ccnt++;
        }
    }
    sort(op.begin(),op.end());
    for(register int i=0;i<op.size();i++)
    {
        cout<<op[i]<<" ";
    }
    if(ccnt)
    {
        putchar('\n');
    }
    if(!ccnt)
    {
        if(cnt<=20)
        {
            puts("b");
        }
        else
        {
            puts("How Good Oiers Are!");
        }
    }
    if(ccnt==5)
    {
        puts("How Bad Oiers Are!");
    }
}
