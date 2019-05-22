#include<stdio.h>
#include<iostream>
#include<deque>
#include<vector>
#include<utility>


typedef long long int lli;

using namespace std;

deque <lli>que;
vector<int> adjlist[6000000];
vector<int> revlist[6000000];
vector<int> visited(6000000);
vector<int> vist(6000000);
vector<int> status(6000000);
vector<int> st;

void dfs(lli node)
{
  if(visited.at(node)==1)
    return ;
  lli i;
  visited.at(node)=1;
  for(i=0;i<adjlist[node].size();i++)
  {
    lli tmp=adjlist[node].at(i);
    dfs(tmp);
  }
  que.push_back(node);
}

void dfs2(lli node)
{
  if(vist.at(node)==1)
    return;
  lli i;
  vist.at(node)=1;
  for(i=0;i<revlist[node].size();i++)
  {
    lli tmp=revlist[node].at(i);
  //  cout<<"node = "<<node<<" tmp = "<<tmp<<"\n";
    dfs2(tmp);
  }
  //cout<<"node "<<node<<"\n";
  st.push_back(node);
  // for(i=0;i<st.size();i++)
  //   cout<<"back "<<st.at(i);
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  lli i,n,m;
  lli tmp1,tmp2;
  cin>>n>>m;
  for(i=0;i<m;i++)
  {
    cin>>tmp1>>tmp2;
    adjlist[tmp1].push_back(tmp2);
    revlist[tmp2].push_back(tmp1);
  }
  for(i=1;i<=n;i++)
    dfs(i);
  while(!que.empty())
  {
    //cout<<que.back()<<"\n";
    dfs2(que.back());
    vist.at(que.back())=1;
    // for(lli j=0;j<st.size();j++)
    //   cout<<st.at(j)<<" ";
//    cout<<st.size()<<"\n";
    if(st.size()>2)
      {
        for(lli j=0;j<st.size();j++)
          status.at(st.at(j))=1;
      }
  //  cout<<"\n";
    while(!st.empty())
      st.pop_back();
    que.pop_back();
  }
  for(i=1;i<=n;i++)
    cout<<status.at(i)<<" ";
  return 0;
}
