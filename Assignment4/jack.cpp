#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef long long int ll;

ll stack[1000100],indx[100010];
ll top=-1;
ll minimum[100010],ind[100010];

void push(ll info,ll in)
{
  top++;
  stack[top]=info;
  indx[top]=in;
}
void push2(ll info ,ll in)
{
  top++;
  stack[top]=info;
  ind[top]=in;
}

void pop()
{top--;}

ll smstr(ll array[],ll n,ll window)
{
  ll bottom=0,i;
  push2(array[0],window);
  minimum[0]=array[0];
  for(i=1;i<n;i++)
  {
    minimum[i]=array[i]+stack[bottom];
    while(top>=bottom&&minimum[i]<=stack[top])
      pop();
    push2(minimum[i],i+window);
    if(ind[bottom]==i)
      bottom++;
  }
  return minimum[n-1];
}

int main(void)
{
  long long int p[50010],d[50010];
  long long int n,t;
  long long int i,count=0,tp;
  scanf("%lld %lld",&n,&t);

  for(i=0;i<n-1;i++)
  {
      scanf("%lld",&tp);
      while(stack[top]>tp&&top>=0)
        pop();
      push(tp,i);
  }
  for(i=0;i<=top;i++)
  {
    p[i]=stack[i];
  //  printf("%lld %lld ",p[i],indx[i]);
  }
//  printf("\n");
  count=top+1;
  top=-1;
  d[0]=0;
  d[n-1]=0;
  for(i=1;i<n-1;i++)
    scanf("%lld",&d[i]);

  ll mm=0,max=count,mid;
//  cout<<count;
  while(mm<=max)
{
    mid=(mm+max)/2;
    top=-1;
    tp=smstr(d,n,indx[mid]+1);
    //  cout<<"time = "<<tp<<"\n";
    //  cout<<"window = "<<indx[mid]+1<<"\n";
    // cout<<"mid = "<<mid<<"\n";
    if(tp+n-1<=t)
      max=mid-1;
    else
      mm=mid+1;
  }
  cout<<p[mm]<<"\n";

  return 0;
}
