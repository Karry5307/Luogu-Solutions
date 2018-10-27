#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=1e6+51;
struct SegmentTree{
    ll l,r,ls,rs,sum;
};
SegmentTree tree[MAXN<<5];
ll cnt,ccnt,tot,ver,op,x,y;
ll root[MAXN],num[MAXN];
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
inline void update(ll node)
{
    tree[node].sum=tree[tree[node].ls].sum+tree[tree[node].rs].sum;
}
inline void create(ll l,ll r,ll &node)
{
    node=++tot;
    tree[node].l=l,tree[node].r=r;
    if(l==r)
    {
        tree[node].sum=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,tree[node].ls);
    create(mid+1,r,tree[node].rs);
    //update(node);
}
inline ll change(ll pos,ll val,ll node)
{
    ll cur=++tot;
    tree[cur].l=tree[node].l,tree[cur].r=tree[node].r;
    tree[cur].ls=tree[node].ls,tree[cur].rs=tree[node].rs;
    if(tree[node].l==tree[node].r)
    {
        tree[cur].sum=val;
        return cur;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(pos<=mid)
    {
        tree[cur].ls=change(pos,val,tree[node].ls);
    }
    else
    {
        tree[cur].rs=change(pos,val,tree[node].rs);
    }
    //update(cur);
    return cur;
}
inline ll query(ll pos,ll node)
{
    if(tree[node].l==tree[node].r)
    {
        return tree[node].sum;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(pos<=mid)
    {
        return query(pos,tree[node].ls);
    }
    else
    {
        return query(pos,tree[node].rs);
    }
}
int main()
{
    cnt=read(),ccnt=read();
    for(register int i=1;i<=cnt;i++)
    {
        num[i]=read();
    }
    create(1,cnt,root[0]);
    for(register int i=1;i<=ccnt;i++)
    {
        ver=read(),op=read();
        if(op==1)
        {
            x=read(),y=read();
            root[i]=change(x,y,root[ver]);
        }
        else
        {
            x=read();
            printf("%d\n",query(x,root[ver]));
            root[i]=root[ver];
        }
    }
} 
