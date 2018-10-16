#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
struct edge{
    ll to,prev;
};
struct SegmentTree{
    ll l,r,maxn,tag,cover;
};
const ll MAXN=2e5+51; 
edge ed[MAXN];
SegmentTree tree[MAXN<<2];
ll last[MAXN],val[MAXN],depth[MAXN],fa[MAXN],size[MAXN],heavy[MAXN];
ll id[MAXN],pre[MAXN],top[MAXN],from[MAXN],to[MAXN],dist[MAXN];
ll tot,nc,ccnt,tx,x,y,z;
string op;
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
inline void addEdge(ll from,ll to)
{
    ed[++tot].prev=last[from];
    ed[tot].to=to;
    last[from]=tot;
}
inline void update(ll node)
{
    tree[node].maxn=max(tree[node<<1].maxn,tree[(node<<1)|1].maxn);
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r,tree[node].cover=-1;
    if(l==r)
    {
        tree[node].maxn=val[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline void spread(ll node)
{
    if(tree[node].cover!=-1)
    {
        tree[node<<1].maxn=tree[node].cover;
        tree[(node<<1)|1].maxn=tree[node].cover;        
        tree[node<<1].cover=tree[node].cover;
        tree[(node<<1)|1].cover=tree[node].cover;
        tree[node<<1].tag=tree[(node<<1)|1].tag=0;
        tree[node].cover=-1;
    }
    if(tree[node].tag)
    {
        tree[node<<1].maxn+=tree[node].tag;
        tree[(node<<1)|1].maxn+=tree[node].tag;
        tree[node<<1].tag+=tree[node].tag;
        tree[(node<<1)|1].tag+=tree[node].tag;
        tree[node].tag=0;
    }
}
inline void change(ll pos,ll val,ll node)
{
    if(tree[node].l==tree[node].r)
    {
        tree[node].maxn=val;
        return;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    spread(node);
    if(pos<=mid)
    {
        change(pos,val,node<<1);
    }
    else
    {
        change(pos,val,(node<<1)|1);
    }
    update(node);
}
inline void cover(ll l,ll r,ll val,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        tree[node].maxn=val;
        tree[node].cover=val;
        tree[node].tag=0;
        return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        cover(l,r,val,node<<1);
    }
    if(r>mid)
    {
        cover(l,r,val,(node<<1)|1);
    }
    update(node);
}
inline void add(ll l,ll r,ll val,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        tree[node].maxn+=val;
        tree[node].tag+=val;
        return;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(l<=mid)
    {
        add(l,r,val,node<<1);
    }
    if(r>mid)
    {
        add(l,r,val,(node<<1)|1);
    }
    update(node);
}
inline ll queryMax(ll l,ll r,ll node) 
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node].maxn;
    }
    spread(node);
    ll mid=(tree[node].l+tree[node].r)>>1,val=-(1<<30);
    if(l<=mid)
    {
        val=max(val,queryMax(l,r,node<<1));
    }
    if(r>mid)
    {
        val=max(val,queryMax(l,r,(node<<1)|1));
    }
    return val;
}
inline void dfs(ll node,ll f,ll dep)
{
    depth[node]=dep,fa[node]=f,size[node]=1;
    ll maxn=-1;
    for(register int i=last[node];i;i=ed[i].prev)
    {
        if(ed[i].to!=f)
        {
            dfs(ed[i].to,node,dep+1);
            size[node]+=size[ed[i].to];
            if(size[ed[i].to]>maxn)
            {
                heavy[node]=ed[i].to,maxn=size[ed[i].to];
            }
        }
    }
}
inline void ddfs(ll node,ll link)
{
    id[node]=++ccnt,val[ccnt]=pre[node],top[node]=link;
    if(!heavy[node])
    {
        return;
    }
    ddfs(heavy[node],link);
    for(register int i=last[node];i;i=ed[i].prev)
    {
        if(ed[i].to!=fa[node]&&ed[i].to!=heavy[node])
        {
            ddfs(ed[i].to,ed[i].to);
        }
    }
}
inline ll queryPathMax(ll x,ll y)
{
    ll ans=-(1<<30);
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
        {
            swap(x,y);
        }
        ans=max(ans,queryMax(id[top[x]],id[x],1));
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
    {
        swap(x,y);
    }
    ans=max(ans,queryMax(id[x]+1,id[y],1));
    return ans;
}
inline void changePoint(ll x,ll y)
{
    change(id[x],y,1);
}
inline void changePath(ll x,ll y,ll val)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
        {
            swap(x,y);
        }
        add(id[top[x]],id[x],val,1);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
    {
        swap(x,y);
    }
    add(id[x]+1,id[y],val,1);
}
inline void coverPath(ll x,ll y,ll val)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
        {
            swap(x,y);
        }
        cover(id[top[x]],id[x],val,1);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
    {
        swap(x,y);
    }
    cover(id[x]+1,id[y],val,1);
}
inline ll lca(ll x,ll y)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
        {
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return depth[x]<depth[y]?x:y;
}
int main()
{
    nc=read();
    for(register int i=0;i<nc-1;i++)
    {
        from[i]=read(),to[i]=read(),dist[i]=read();
        addEdge(from[i],to[i]),addEdge(to[i],from[i]);
    }
    dfs(1,0,1),ddfs(1,1),create(1,nc,1);
    for(register int i=0;i<nc-1;i++)
    {
    	changePoint(depth[from[i]]>depth[to[i]]?from[i]:to[i],dist[i]);
    }
    while(cin>>op,op!="Stop")
    {
    	if(op=="Max")
        {
            x=read(),y=read();
            cout<<queryPathMax(x,y)<<endl;
        }
        if(op=="Change")
        {
            x=read(),y=read();
            tx=depth[from[x-1]]>depth[to[x-1]]?from[x-1]:to[x-1];
    		changePoint(tx,y);
        }
        if(op=="Add")
        {
            x=read(),y=read(),z=read();
            changePath(x,y,z);
        }
        if(op=="Cover")
        {
            x=read(),y=read(),z=read();
            coverPath(x,y,z);
        }
    }
}
