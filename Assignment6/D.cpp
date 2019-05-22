
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>

using namespace std;

typedef long long int lli ;
vector<pair<lli,lli> > adjlist[1000010];
vector<lli> visited(1000010);

//middle is the guessed element

int main(void)
{
  lli n,m,k,i;
  lli tmp1,tmp2,tmp3;
  vector <lli> weight;
  priority_queue<pair<lli,lli >,vector<pair<lli,lli > >,greater<pair<lli,lli > > > pq;
  priority_queue<pair<lli,lli >,vector<pair<lli,lli > >,greater<pair<lli,lli> > > pq2;
  cin>>n>>m>>k;
  for(i=0;i<m;i++)
  {
    cin>>tmp1>>tmp2>>tmp3;
    adjlist[tmp1].push_back(make_pair(tmp2,tmp3));
    adjlist[tmp2].push_back(make_pair(tmp1,tmp3));
  }
  visited.at(1)=1;
  for(i=0;i<adjlist[1].size();i++)
  {
    lli tmp=adjlist[1][i].first;
    lli wgh=adjlist[1][i].second;
    pq.push(make_pair(wgh,tmp));
  }
  while(!pq.empty())
  {
    pair<lli,lli > p=pq.top();
    pq.pop();
    lli node=p.second;
    lli curr=p.first;
    if(!visited.at(node))
    {
      visited.at(node)=1;
      weight.push_back(p.first);
      for(i=0;i<adjlist[node].size();i++)
      {
        lli tmp=adjlist[node][i].first;
        lli wgh=adjlist[node][i].second;
        if(visited.at(tmp)!=1)
          pq.push(make_pair(wgh,tmp));
      }
    }
  }
  if(n-1>k)
    {
      cout<<-1<<endl;
      return 0;
    }
  if(n==1)
  {
    cout<<0<<endl;
    return 0;
  }
  for(i=1;i<=n;i++)
  {
    if(visited.at(i)!=1)
      {cout<<-1<<endl;
        return 0;}
  }
  lli sum=0,ans=0;
  sort(weight.begin(),weight.end());

  // for(i=0;i<weight.size();i++)
  // {
  //   cout<<"wgh = "<<weight.at(i)<<endl;
  // }

  for(i=weight.size()-1;i>=0;i--)
    sum+=weight.at(i);
  for(i=weight.size()-1;i>=0;i--)
  {
    if(sum>k)
    {
      sum=sum-weight.at(i)+1;
      ans++;
    }
  }
  cout<<ans<<endl;
  return 0;
}
