#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef long long int ll;

#define mod 1000000007

using namespace std;

ll ind[100100],arr[100100];
ll seg_tree[600100];
ll min_arr[100100],max_arr[100100],newind[100100];
ll newarr[100100];
ll duplicate[100100];
ll status=0;

void mergecnt(long long int arr[],long long int q[],long long int l,long long int mid,long long int r)
{
  //first arr is from l to mid(inclusive)
  //second arr is from mid+1to r(inclusive)
  long long int tmp[r-l+2],tmp2[r-l+2];
  long long int ptr1=l,ptr2=mid+1,cnt=0;
  while(cnt<r-l+1)
  {
  //  printf("ptr1 = %d\tptr2 = %d\n",ptr1,ptr2);
    if(ptr1==mid+1)
      {
        while(ptr2<r+1)
        {
          tmp2[cnt]=q[ptr2];
          tmp[cnt++]=arr[ptr2++];
        }
      }
    else if(ptr2==r+1)
      {
        while(ptr1<mid+1)
        {
          tmp2[cnt]=q[ptr1];
          tmp[cnt++]=arr[ptr1++];
        }
      }
    else if(arr[ptr1]<arr[ptr2])
    {
      tmp2[cnt]=q[ptr1];
      tmp[cnt++]=arr[ptr1++];
    }
    else if(arr[ptr2]<arr[ptr1])
    {
      tmp2[cnt]=q[ptr2];
      tmp[cnt++]=arr[ptr2++];
    }
    else if(arr[ptr1]==arr[ptr2])
    {
      if(q[ptr1]<q[ptr2])
      {
        tmp2[cnt]=q[ptr1];
        tmp[cnt]=arr[ptr1];
        cnt++;ptr1++;
      }
      else if(q[ptr1]>=q[ptr2])
      {
        tmp2[cnt]=q[ptr2];
        tmp[cnt]=arr[ptr2];
        cnt++;ptr2++;
      }
    }
  }
  for(long long int i=0;i<cnt;i++)
  {
    q[l]=tmp2[i];
    arr[l++]=tmp[i];
  }
}

void dividecnt(long long int arr[],long long int q[],long long int l,long long int r)
{
  //here l and r are inclusive
  long long int mid=(l+r)/2;
  if(l<r)
  {
    dividecnt(arr,q,l,mid);
    dividecnt(arr,q,mid+1,r);
    mergecnt(arr,q,l,mid,r);
  }
}

ll query(ll seg_tree[],ll start,ll end,ll qs,ll qe,ll ptr)
{
  if(start>end||qs>end||qe<start)
    return 0;
  if(qs<=start&&qe>=end)
    return seg_tree[ptr]%mod;
  ll mid=(start+end)/2;
//f  cout<<"hello\n";
  return (query(seg_tree,start,mid,qs,qe,2*ptr+1)%mod+query(seg_tree,mid+1,end,qs,qe,2*ptr+2)%mod)%mod;
}


//Note That segtree has 0 based indexing
ll val,indx,n;
ll insert_seg(ll seg_tree[],ll ptr,ll start,ll end)
{
  if(start>end)
    return 0;
  if(start==end)
  {
    seg_tree[ptr]=(1+query(seg_tree,0,n-1,0,indx-1,0)%mod)%mod;
    if(status==0)
      min_arr[indx]=seg_tree[ptr]%mod;
    else
      max_arr[n-indx-1]=seg_tree[ptr]%mod;
    return seg_tree[ptr];
  }
  ll mid=(start+end)/2;
  if(indx>mid)
    seg_tree[ptr]=(seg_tree[2*ptr+1]%mod+insert_seg(seg_tree,2*ptr+2,mid+1,end)%mod)%mod;
  else
    seg_tree[ptr]=(seg_tree[2*ptr+2]%mod+insert_seg(seg_tree,2*ptr+1,start,mid)%mod)%mod;
  return seg_tree[ptr]%mod;
}




int main(void)
{
  ll i;
  scanf("%lld",&n);
  for(i=0;i<n;i++)
    {
      scanf("%lld",&arr[i]);
      ind[i]=i;
      newarr[n-i-1]=arr[i];
      newind[n-i-1]=n-i-1;
    }
  dividecnt(arr,ind,0,n-1);
  status=0;


//THIS PART IS FOR INCREASING SEQUENCE
  for(i=0;i<n;i++)
  {
    indx=ind[i];
    val=arr[i];
    insert_seg(seg_tree,0,0,n-1);
  }
//  cout<<seg_tree[0]<<"\n";
  for(i=0;i<=4*n;i++)
    seg_tree[i]=0;
  status=1;


//THIS PART IS FOR DECREASING SEQUENCE
  dividecnt(newarr,newind,0,n-1);
  for(i=0;i<n;i++)
  {
    indx=newind[i];
    val=newarr[i];
    insert_seg(seg_tree,0,0,n-1);
  }
  ll ans=0;
/*  for(i=0;i<n;i++)
    {
      cout<<min_arr[i]<<"  ";
    }
    cout<<"\n";*/

  ll sum=0;


  for(i=n-1;i>=0;i--)
  {
    duplicate[ind[i]]=(max_arr[ind[i]]%mod-sum%mod)%mod;
    if(arr[i]==arr[i-1])
      sum=(sum%mod+max_arr[ind[i]]%mod)%mod;
    else
      sum=0;
/*    cout<<"Sum : "<<sum<<"\n";
    cout<<max_arr[ind[i]]<<"  "<<arr[i]<<" "<<duplicate[i]<<"\n";*/
  }


/*  for(i=0;i<n;i++)
    cout<<max_arr[i]<<" ";
    cout<<"\n";
  for(i=0;i<n;i++)
    cout<<duplicate[i]<<" ";*/
  for(i=0;i<n;i++)
    ans=(ans%mod+((duplicate[i]%mod*min_arr[i]%mod)%mod)%mod)%mod;
//cout<<"\n";
  cout<<ans%mod<<"\n";
  return 0;
}
