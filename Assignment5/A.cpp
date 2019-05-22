#include<stdio.h>
#include<iostream>
#include<vector>
#include<array>
#include<algorithm>

typedef long long int lli;
using namespace std;

vector<lli> level(6000000);
vector<int> gande(6000000);
vector<int> total(6000000);
vector <pair<lli,lli> > adjlist[6000000];
vector <int> status[6000000];
int visit[1000000];
lli tt;
lli power(lli a,lli b,lli mod)
{
    lli p = 1;
    while(b>0)
    {
        if(b%2==1) p=(p*a)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return p;
}

lli actual(lli x,lli mod)
{
  lli ans1,ans;
  ans1=power(x,x,mod-1);
  ans=power(x,ans1,mod);
  return ans;
}

void dfs(lli node)
{
    lli st;
    if(visit[node]==1)
      return;
    lli i;
    visit[node]=1;
    if(gande.at(node)==0)
    { tt--;
      gande.at(node)=1;}
    // if(tt==0)
    //   return;
//    cout<<"node = "<<node<<"\n";
    for(i=0;i<adjlist[node].size();i++)
    {
      lli tmp=adjlist[node][i].second;
  //    cout<<"node = "<<node<<" tmp = "<<tmp<<" status= "<<status[node].at(i)<<"\n";
  //    cin>>st;
      // if(tt==0)
      //   return;
      if(status[node].at(i)!=1&&visit[tmp]!=1)
      {
        status[node].at(i)=1;
      //  cout<<"node = "<<node<<" tmp = "<<tmp<<"\n";
    //    cout<<status[node].at(i);
        total.at(i)++;
    //    tt--;
        dfs(tmp);
      }
    }
    visit[node]=0;
  //  cout<<"\n";
    return;
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  lli i,n;
  lli tmp1,tmp2,tmp3;
  vector <pair<lli,lli> > v;
  vector <pair<lli,lli> > sv;
  cin>>n;
  tt=n;
  for(i=0;i<n-1;i++)
  {
    cin>>tmp1>>tmp2>>tmp3;
    //First of pair is weight
    //Second of pair is neighbour
    adjlist[tmp1].push_back(make_pair(tmp3,tmp2));
    adjlist[tmp2].push_back(make_pair(tmp3,tmp1));
    status[tmp1].push_back(0);
    status[tmp2].push_back(0);
  }
  for(i=1;i<=n;i++)
    sort(adjlist[i].begin(),adjlist[i].end());

  // for(i=1;i<=n;i++)
  // {
  //   lli siz=adjlist[i].size();
  //   cout<<i<<"\n";
  //   for(lli j=0;j<siz;j++)
  //     cout<<adjlist[i][j].second<<" ";
  //   cout<<"\n\n";
  // }
  for(i=1;i<=n;i++)
  {
    lli j;
    lli siz=adjlist[i].size();
    if(tt==0)
      break;
        for(j=0;j<siz;j++)
          {
            if(tt==0)
              break;
            if((j+1<siz&&(adjlist[i][j].first==adjlist[i][j+1].first)))
            {
            //    cout<<"Starting "<<i<<" on "<<adjlist[i][j].second;
              //  vector <int>visit(n+10);
                visit[i]=1;
                status[i].at(j)=1;
                dfs(adjlist[i][j].second);
                visit[i]=0;
            }
            else if(j>0&&(adjlist[i][j].first==adjlist[i][j-1].first))
            {
            //  cout<<"Starting "<<i<<" on "<<adjlist[i][j].second;
          //    vector <int>visit(n+10);
              visit[i]=1;
              status[i].at(j)=1;
              dfs(adjlist[i][j].second);
              visit[i]=0;
            }
        //    cout<<"Y\n";
          }
    }

    // for(i=1;i<=n;i++)
    // {
    //   lli siz=adjlist[i].size();
    //   cout<<i<<"\n";
    //   for(lli j=0;j<siz;j++)
    //     cout<<status[i].at(j)<<" ";
    //   cout<<"\n";
    // }

  lli cnt=0;
  for(i=1;i<=n;i++)
  {
  //  cout<<gande.at(i)<<"\n";
    if(gande.at(i)==0)
      cnt++;
  }
  lli tmp=cnt;
  //cout<<cnt<<"\n";

//  cout<<tmp<<"\n";
    //cout<<tt;
  if(cnt!=0)
    cnt=actual(cnt,1000000007);
  cout<<cnt<<"\n";
  return 0;
}
