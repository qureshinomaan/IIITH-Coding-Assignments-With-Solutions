#include<stdio.h>
#include<iostream>
#include<deque>
#include<vector>
#include<utility>


typedef long long int lli;

using namespace std;

vector<lli> level(6000000);
vector<lli> visited(6000000);
vector <pair<lli,lli> > v[6000000];
int main(void)
{
  lli i;
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  deque <lli>que;
  lli n,m,p;
  lli tmp1,tmp2,tmp3;
  lli src,dst;
  cin>>n>>m>>p;
  for(i=0;i<m;i++)
  {
    cin>>tmp1>>tmp2>>tmp3;
    v[tmp1].push_back(make_pair(tmp2,tmp3));
    v[tmp2].push_back(make_pair(tmp1,tmp3));
  }
  for(i=0;i<=n;i++)
  {  level.at(i)=1000000000000;
  //  cout<<level.at(i);
  }
  cin>>src>>dst;
  //level.at(dst)=-1;
  level.at(src)=0;
  //BFS starts here
  que.push_back(src);
  visited.at(src)=1;
  while(!que.empty())
  {
    lli ele=que.front();
    lli curr=level.at(ele);
    que.pop_front();
    for(i=0;i<v[ele].size();i++)
    {
      lli adj=v[ele][i].first;
    //  cout<<"ele = "<<ele<<" curr = "<<level.at(adj)<<"\n";
      lli wgh=v[ele][i].second;
    //  cout<<"level of "<<adj<<" is "<<curr<<"\n";
          if(wgh==1)
            {
              if(level.at(adj)>curr)
              {
            //    cout<<"level of "<<adj<<" is "<<curr<<"\n";
                level.at(adj)=curr;
               que.push_front(adj);
             }
            }
          else
          {
            if(level.at(adj)>curr+1)
            {
            //  cout<<"level of "<<adj<<" is "<<curr+1<<"\n";
              level.at(adj)=curr+1;
              que.push_back(adj);
            }
          }
    }
  }
   // for(i=1;i<=n;i++)
   //   cout<<level.at(i)<<"\n";

  if(level[dst]!=1000000000000)
    cout<<p*level.at(dst);
  else
    cout<<"-1";

  return 0;
}
