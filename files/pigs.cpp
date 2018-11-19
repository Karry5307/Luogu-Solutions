//Luogu P2482
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
struct Pig{
	vector<char>cards;
	ll blood,cardsNum;
	bool didKill,hasZhuge;
	string identity;
	Pig()
	{
		this->cardsNum=this->blood=4; 
	}
	inline ll findFirst(char target)
	{
		for(register int i=0;i<cardsNum;i++)
		{
			if(cards[i]==target)
			{
				return i;
			}
		}
		return -1;
	}
	inline void debug()
	{
		printf("%d %d ",cardsNum,blood);
		cout<<identity<<" ";
		for(register int i=0;i<cardsNum;i++)
		{
			printf("%c ",cards[i]);
		}
		puts("");
	}
};
struct Pile{
	deque<char>cards;
	inline void get(Pig &p,ll cnt)
	{
		p.cardsNum+=cnt;
		for(register int i=0;i<cnt;i++)
		{
			p.cards.push_back(cards.front());
			cards.pop_front();
		}
	}
	inline void debug()
	{
		for(register int i=0;i<cards.size();i++)
		{
			printf("%c ",cards[i]);	
		} 
		puts("");
	}
};
Pig pig[11];
Pile pile;
ll cnt,ccnt,live,turn;
char ch;
ll check[11];
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
inline void debugAll()
{
	for(register int i=1;i<=cnt;i++)
	{
		pig[i].debug();
	}
	pile.debug();
}
inline ll calcNext(ll cur)
{
	while(!pig[++cur].blood);
	return cur;
}
inline bool respondDefend(Pig &p)
{
	ll pos=p.findFirst('D');
	if(pos!=-1)
	{
		p.cards.erase(p.cards.begin()+pos),p.cardsNum--;
		return 1;
	}
	return 0;
}
inline bool respondPeach(Pig &p)
{
	ll pos=p.findFirst('P');
	if(pos!=-1&&p.blood)
	{
		p.cards.erase(p.cards.begin()+pos),p.cardsNum--;
		return 1;
	}
	return 0;
}
inline void doKill(Pig &p,ll cur,ll pos)
{
	ll nxt;
	if(p.identity!="FP")
	{
		nxt=calcNext(cur);
		if(pig[nxt].identity=="FP")
		{
			if(!respondDefend(pig[nxt]))
			{
				pig[nxt].blood--;
			}
			p.cards.erase(p.cards.begin()+pos),p.cardsNum--;
		}
	}
	else
	{
		nxt=calcNext(cur);
		if(pig[nxt].identity=="MP"||check[nxt]==3)
		{
			if(!respondDefend(pig[nxt]))
			{
				pig[nxt].blood--;
			}
			p.cards.erase(p.cards.begin()+pos),p.cardsNum--;
		}
	}
}
inline void doPeach(Pig &p,ll pos)
{
	p.blood+=(p.blood!=4);
	p.cards.erase(p.cards.begin()+pos),p.cardsNum--;
}
int main()
{
	cnt=live=read(),ccnt=read();
	for(register int i=1;i<=cnt;i++)
	{
		cin>>pig[i].identity;
		for(register int j=0;j<4;j++)
		{
			cin>>ch;
			pig[i].cards.push_back(ch);
		}
	}
	for(register int i=0;i<ccnt;i++)
	{
		cin>>ch;
		pile.cards.push_back(ch);
	}
	for(;;)
	{
		if(live==1)
		{
			break;
		}
		turn++,turn=turn>cnt?1:turn;
	}
}
