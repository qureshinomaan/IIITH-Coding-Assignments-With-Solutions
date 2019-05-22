#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long int lli ;

vector<lli> adjlist[500010];
vector<lli> strength(500010);
vector<int> visited(500010);
vector<lli> level(500010);
vector<lli> st(500010);   //for start time
vector<lli> et(500010);   //for end time
//level starts from 1
lli tme=0;    //tme starts from 1


//1 is for odd, 2 is for even
lli segtree1[1600050],segtree2[1600050];

void dfs(lli node,lli lvl) // pass 1 as level when you apply dfs
{
  if(visited.at(node)==1)
    return ;
  //cout<<"node = "<<node<<" start time = "<<tme+1<<endl;
  visited.at(node)=1;

  tme++;
  st.at(node)=tme;

  level.at(node)=lvl;

  for(lli i=0;i<adjlist[node].size();i++)
  {
    lli tmp=adjlist[node].at(i);
    dfs(tmp,lvl+1);
  }
//  visited.at(node)=0;
  tme++;
  et.at(node)=tme;
//  cout<<"node = "<<node<<" end time = "<<tme<<endl;
  return;
}

//segtree is 1 based indexed
void buildseg(lli segtree[],lli array[],lli start,lli end,lli node)
{
  if(start>end)
    return;
  if(start==end)
  {
    segtree[node]=array[start];
    return;
  }
  lli mid =(start+end)/2;
  buildseg(segtree,array,start,mid,2*node);
  buildseg(segtree,array,mid+1,end,2*node+1);
  segtree[node]=segtree[2*node]+segtree[2*node+1];
  return;
}

lli query(lli start,lli end,lli l,lli r,lli node,lli segtree[])
{
  //l and r are the query variable
  if(start>r||end<l||start>end)
    return 0;
  if(start>=l&&end<=r)
    return segtree[node];
  lli mid=(start+end)/2;
  return query(start,mid,l,r,2*node,segtree)+query(mid+1,end,l,r,2*node+1,segtree);
}

lli update(lli segtree[],lli pos,lli start,lli end,lli val,lli node)
{
  if(start>end)
    return 0;
  if(start==end)
  {
    segtree[node]+=val;
    return segtree[node];
  }
  lli mid=(start+end)/2;
  if(pos<=mid)
      segtree[node]=segtree[2*node+1]+update(segtree,pos,start,mid,val,2*node);
  else
      segtree[node]=segtree[2*node]+update(segtree,pos,mid+1,end,val,2*node+1);

  return segtree[node];
}


int main(void)
{
  lli n,m,i;
  lli tmp1,tmp2;
  cin>>n>>m;
  for(i=1;i<=n;i++)
    cin>>strength[i];
  for(i=1;i<=n-1;i++)
  {
    cin>>tmp1>>tmp2;
    adjlist[tmp1].push_back(tmp2);
    adjlist[tmp2].push_back(tmp1);
  }
  dfs(1,1);
  //cout<<"tme = "<<tme<<endl;
//  cout<<"dfs done successfully!!!\n";
  // for(i=1;i<=2*n;i++)
  //   cout<<odd[i]<<"\n";
  while(m--)
  {
    lli ch;
    cin>>ch;
    if(ch==1){
      lli pos,u;
      cin>>pos>>u;
      if(level.at(pos)%2==1)
      {
         update(segtree1,st.at(pos),1,2*n,u,1);
         update(segtree1,et.at(pos),1,2*n,-1*u,1);
          cout<<"1 ";
          for(i=1;i<=4*n;i++)
           cout<<segtree1[i]<<"   ";
         cout<<endl;
      }
      else{
         update(segtree2,st.at(pos),1,2*n,u,1);
         update(segtree2,et.at(pos),1,2*n,-1*u,1);
          cout<<"2 ";
          for(i=1;i<=4*n;i++)
           cout<<segtree2[i]<<"   ";
         cout<<endl;
       }
      }
    else{
      lli pos;
      cin>>pos;
      // cout<<"query odd "<<query(1,2*n,1,st.at(pos),1,segtree1)<<endl;
      // cout<<"query even "<<query(1,2*n,1,st.at(pos),1,segtree2)<<endl;
      if(level.at(pos)%2==1)
        cout<<strength.at(pos)+query(1,2*n,1,st.at(pos),1,segtree1)-query(1,2*n,1,st.at(pos),1,segtree2)<<endl;
      else
        cout<<strength.at(pos)+query(1,2*n,1,st.at(pos),1,segtree2)-query(1,2*n,1,st.at(pos),1,segtree1)<<endl;
    }
  }
  return 0;
}
