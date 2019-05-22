#include<stdio.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

typedef long long int ll;
ll mod = 1000000007;
ll len;

struct seg_tree{
  ll total;
  ll prefix[12];
  ll postfix[12];
  ll string_sum;
};

seg_tree segment[600020];


ll pwer(ll num,ll raise)
{
  ll ans=1;
  while(raise>0)
  {
    if(raise%2==1)
      ans=(ans*num)%mod;
    raise=raise/2;
    num=(num*num)%mod;
  }
  return ans;
}

seg_tree newnode()
{
  seg_tree tmp;
  tmp.total=0;
  tmp.string_sum=0;
  for(ll i=0;i<9;i++)
  {
    tmp.prefix[i]=0;
    tmp.postfix[i]=0;
  }
  return tmp;
}

void build_seg(ll array[],ll start,ll end,ll ptr)
{
  if(start>end)
    return;
  if(start==end)
  {
    ll x=array[start];
    if(x%9==0)
      segment[ptr].total=1;
    else
      segment[ptr].total=0;

    for(ll i=0;i<9;i++)
    {
      segment[ptr].postfix[i]=0;
      segment[ptr].prefix[i]=0;
    }
    segment[ptr].postfix[x%9]=1;
    segment[ptr].prefix[x%9]=1;
    segment[ptr].string_sum=x%9;
     // cout<<ptr<<"\n";
     // cout<<array[start]<<"\n";
     // cout<<segment[ptr].total<<"\n\n";
    return;
  }
  ll mid=(start+end)/2;
  build_seg(array,start,mid,2*ptr);
  build_seg(array,mid+1,end,2*ptr+1);
  for(ll i=0;i<9;i++)
    {
      segment[ptr].postfix[i]=segment[2*ptr+1].postfix[i];
      segment[ptr].prefix[i]=segment[2*ptr].prefix[i];
    }
  segment[ptr].total=segment[2*ptr].total+segment[2*ptr+1].total;
  segment[ptr].string_sum=(segment[2*ptr].string_sum+segment[2*ptr+1].string_sum)%9;

  for(ll i=0;i<9;i++)
  {
    if(segment[2*ptr].string_sum==i)
    {
      for(ll j=0;j<9;j++)
        segment[ptr].prefix[j]+=segment[2*ptr+1].prefix[(9-i+j)%9];
    }
    if(segment[2*ptr+1].string_sum==i)
    {
      for(ll j=0;j<9;j++)
        segment[ptr].postfix[j]+=segment[2*ptr].postfix[(9-i+j)%9];
    }
  }
  // cout<<"ptr = "<<ptr<<"\n";
  // cout<<"segment[ptr].total = "<<segment[ptr].total<<"\n";
  for(ll i=0;i<9;i++)
    {
      segment[ptr].total+=segment[2*ptr].postfix[i]*segment[2*ptr+1].prefix[(9-i)%9];
  //    printf("i = %lld post = %lld pre = %lld\n",i,segment[2*ptr].postfix[i], segment[2*ptr+1].prefix[(9-i)%9]);
    }

//  cout<<"ptr = "<<ptr<<"segment = "<<segment[ptr].total<<"\n";

}

seg_tree setvalue(seg_tree left, seg_tree right)
{
  seg_tree temp;
  temp.total=left.total+right.total;
  temp.string_sum=(left.string_sum+right.string_sum)%9;
  for(ll i=0;i<9;i++)
  {
    temp.prefix[i]=left.prefix[i];
    temp.postfix[i]=right.postfix[i];
  }
  for(ll i=0;i<9;i++)
  {
    if(left.string_sum%9==i)
    {
      for(ll j=0;j<9;j++)
        temp.prefix[j]=temp.prefix[j]+right.prefix[(9-i+j)%9];
    }
    if(right.string_sum%9==i)
    {
      for(ll j=0;j<9;j++)
        temp.postfix[j]=temp.postfix[j]+left.postfix[(9-i+j)%9];
    }
  }
  for(ll i=0;i<9;i++)
    temp.total=temp.total+left.postfix[i]*right.prefix[(9-i)%9];
  return temp;
}

seg_tree query(ll start, ll end, ll l,ll r,ll ptr)
{
  //here start is for which will change
  //l and r are for query
  ll mid=(start+end)/2;
  if(start>r||start>end||end<l)
  {
    seg_tree tmp=newnode();
    return tmp;
  }
  if(l<=start&&r>=end)
    return segment[ptr];
  if(r<=mid)
      return query(start,mid,l,r,2*ptr);
  if(l>mid)
      return query(mid+1,end,l,r,2*ptr+1);
  seg_tree left,right,middle;
  left=query(start,mid,l,r,2*ptr);
  right=query(mid+1,end,l,r,2*ptr+1);
  return setvalue(left,right);
}

void update(ll array[],ll start,ll end,ll ptr,ll ind,ll value)
{
  if(ind>end||ind<start||start>end)
    return;
  if(start==end)
  {
    ll x=value%9;
    segment[ptr].postfix[x]=1;
    segment[ptr].prefix[x]=1;
    segment[ptr].string_sum=x;
    if(x%9==0)
      segment[ptr].total=1;
    else
      segment[ptr].total=0;
    for(ll i=1;i<9;i++)
    {
      segment[ptr].postfix[(x+i)%9]=0;
      segment[ptr].prefix[(x+i)%9]=0;
    }
    return;
  }
  ll mid=(start+end)/2;
  if(ind<=mid) update(array,start,mid,2*ptr,ind,value);
  else update(array,mid+1,end,2*ptr+1,ind,value);
  // for(ll i=0;i<9;i++)
  //   cout<<" ptr = "<<2*ptr<<" pre = "<<segment[2*ptr].prefix[i] <<" post = "<<segment[2*ptr].postfix[i]<<"\n";
  // for(ll i=0;i<9;i++)
  //   cout<<" ptr = "<<2*ptr+1<<" pre = "<<segment[2*ptr+1].prefix[i] <<" post = "<<segment[2*ptr+1].postfix[i]<<"\n";
  for(ll i=0;i<9;i++)
  {
    segment[ptr].prefix[i]=segment[2*ptr].prefix[i];
    segment[ptr].postfix[i]=segment[2*ptr+1].postfix[i];
  }
  segment[ptr].total=segment[2*ptr].total+segment[2*ptr+1].total;
  segment[ptr].string_sum=(segment[2*ptr].string_sum+segment[2*ptr+1].string_sum)%9;
  for(ll i=0;i<9;i++)
  {
    if(segment[2*ptr].string_sum%9==i)
    {
      for(ll j=0;j<9;j++)
        segment[ptr].prefix[j]=segment[ptr].prefix[j]+segment[2*ptr+1].prefix[(9-i+j)%9];
    }
    if(segment[2*ptr+1].string_sum%9==i)
    {
      for(ll j=0;j<9;j++)
        segment[ptr].postfix[j]=segment[ptr].postfix[j]+segment[2*ptr].postfix[(9-i+j)%9];
    }
  }
//  cout<<segment[ptr].total<<"\n\n\n";
  for(ll i=0;i<9;i++)
  {
    segment[ptr].total=segment[ptr].total+segment[2*ptr].postfix[i]*segment[2*ptr+1].prefix[(9-i)%9];
//    cout<<segment[ptr].total<<" ";
//    cout<<segment[2*ptr].postfix[i]*segment[2*ptr+1].prefix[(9-i)%9]<<"\n";
  }
}

int main(void)
{
  ll array[200030];
  char str[200030];
  ll n,i,q;
  scanf("%lld %lld",&n,&q);
  scanf("%s",str);
  len=strlen(str);
  for(i=0;i<len;i++)
  {  array[i]=str[i]-48;
  }
  build_seg(array,0,n-1,1);
  ll good;
  ll ch,tmp1,tmp2,ans;
  seg_tree temp;
  ll ind,value;
//  cout<<segment[1].total<<"\n";
  for(i=0;i<q;i++)
  {
    scanf("%lld %lld %lld",&ch,&ind,&value);
    if(ch==1)
    {
      // scanf("%lld %lld",&ind,&value);
      ind-=1;
      array[ind] = value;
      update(array,0,n-1,1,ind,value);
    }
    if(ch==2)
    {
      // scanf("%lld %lld",&tmp1,&tmp2);
      len=value-ind+1;
      ll poww=((len*(len+1))/2)%mod;
      good=pwer(poww,mod-2);
    //  cout<<len<<"\n";
    //  cout<<good<<"\n";
      temp=query(0,n-1,ind-1,value-1,1);
      //cout<<temp.total;
      ans=((good%mod)*(temp.total%mod))%mod;
      cout<<ans<<"\n";
    //   cout<<ans<<"\n";
    }
  }

  return 0;
}
