#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>

using namespace std;

typedef long long int lli ;

vector<pair<lli,lli> > adjlist[1000000];
vector <int> why[1000000];
vector<int> visited(4000000);
vector<lli> paths(4000000);
vector<int> vis(4000000);
vector<int> done(4000000);
vector<int> status(4000000);
vector<lli> weight(4000000);
vector<lli> sm;
lli sho[5000000][2];

int ins(lli array[][2],lli val,lli node)
{
  //array of 0 contains the smallest element
  //array[1] contains the second smallest element
  if(val>array[node][1])
    return 0;
  if(val<array[node][0])
  {
    array[node][1]=array[node][0];
    array[node][0]=val;
    return 1;
  }
  array[node][1]=val;
  return 1;
}


int main(void)
{
  lli n,m,k,i;
  lli tmp1,tmp2,tmp3;
  priority_queue<pair<lli,lli>,vector<pair<lli,lli> >,greater<pair<lli,lli > > > pq;
  cin>>n>>m>>k;
  cout<<"anna hello world\n ";
  for(i=0;i<m;i++)
  {
    cin>>tmp1>>tmp2>>tmp3;
    adjlist[tmp1].push_back(make_pair(tmp2,tmp3));
    why[tmp1].push_back(0);
    adjlist[tmp2].push_back(make_pair(tmp1,tmp3));
    why[tmp2].push_back(0);
  }
  for(i=0;i<300000;i++)
  {
    sho[i][0]=10000000000000000;
    sho[i][1]=10000000000000000;
  }
  for(i=0;i<k;i++)
  {
    cin>>tmp1;
    status.at(tmp1)=1;
    paths.at(tmp1)=0;
    done.at(tmp1)=1;
  }
  for(i=0;i<n;i++)
  {
    if(status.at(i)==1)
    {
      for(lli j=0;j<adjlist[i].size();j++)
      {
        lli tmp=adjlist[i][j].first;
        lli wgh=adjlist[i][j].second;
        paths.at(tmp)++;
        lli x=ins(sho,wgh,tmp);
        if(paths.at(tmp)>=2&&tmp!=0&&status.at(tmp)!=1&&x)
          pq.push(make_pair(sho[tmp][1],tmp));
      }
    }
  }

  if(n==1||status.at(0)==1)
  {
    cout<<0<<endl;
    return 0;
  }
  while(!pq.empty())
  {
    pair <lli ,lli> p= pq.top();
    pq.pop();
    lli node=p.second;
    lli curr=p.first;
    if(!done.at(node)&&curr==sho[node][1])
    {
      done.at(node)=1;
      for(i=0;i<adjlist[node].size();i++)
      {
        lli tmp=adjlist[node][i].first;
        lli wgh=adjlist[node][i].second;
    //    cout<<"node = "<<node<<" tmp = "<<tmp<<" done = "<<done.at(tmp)<<" wgh = "<<curr<<endl;
        if(!done.at(tmp))
        {
          lli x=ins(sho,wgh+curr,tmp);
          // cout<<"paths = "<<paths.at(tmp)<<" ";
          // cout<<"node = "<<node<<" tmp = "<<tmp<<" weight = "<<wgh+curr<<endl;
          paths.at(tmp)++;
          if(tmp!=0&&x==1&&paths.at(tmp)>=2)
            {pq.push(make_pair(sho[tmp][1],tmp));}
          }
      }
    }
  }
  // for(i=0;i<n;i++)
  //   cout<<"paths = " <<paths.at(i)<<endl;
  if(sho[0][1]<10000000000000000)
    cout<<sho[0][1]<<endl;
  else
    cout<<-1<<endl;
  return 0;
}
