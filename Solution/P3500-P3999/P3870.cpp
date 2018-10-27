#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=1e5+51;
struct SegmentTree{
    ll l,r,sum,tag;
};
SegmentTree tree[MAXN<<2];
ll cnt,ccnt,op,l,r;
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
    tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r;
    if(l==r)
    {
        tree[node].sum=0;
        return;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline void spread(ll node)
{
    ll ls=node<<1,rs=ls|1;
    if(tree[node].tag)
    {
        tree[ls].sum=tree[ls].r-tree[ls].l+1-tree[ls].sum;
        tree[rs].sum=tree[rs].r-tree[rs].l+1-tree[rs].sum;
        tree[ls].tag^=1;
        tree[rs].tag^=1;
        tree[node].tag=0;
    }
}
inline void change(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        tree[node].sum=tree[node].r-tree[node].l+1-tree[node].sum;
        tree[node].tag^=1;
        return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        change(l,r,node<<1);
    }
    if(r>mid)
    {
        change(l,r,(node<<1)|1);
    }
    update(node);
}
inline ll query(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node].sum;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1,res=0;
    if(l<=mid)
    {
        res+=query(l,r,node<<1);
    }
    if(r>mid)
    {
        res+=query(l,r,(node<<1)|1);
    }
    return res;
}
int main()
{
    cnt=read(),ccnt=read();
    create(1,cnt,1);
    for(register int i=0;i<ccnt;i++)
    {
        op=read(),l=read(),r=read();
        if(op)
        {
            printf("%d\n",query(l,r,1));

        }
        else
        {
            change(l,r,1);
        }
    }
}
