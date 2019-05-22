#include<stdio.h>

long long int count=0;

void merge(long long int arr[],long long int l,long long int r)
{
  long long int mid=(l+r)/2,ptr1,ptr2;
  ptr1=l;
  ptr2=mid+1;
  long long int tmp[r-l+4],cnt=0;
  while(ptr1<mid+1&&ptr2<r+1)
  {
    if(arr[ptr2]<arr[ptr1])
    {
      tmp[cnt++]=arr[ptr2++];
      count+=mid-ptr1+1;
    }
    else
      tmp[cnt++]=arr[ptr1++];
  }
  while(ptr1<mid+1)
    tmp[cnt++]=arr[ptr1++];
  while(ptr2<r+1)
    tmp[cnt++]=arr[ptr2++];
  for(long long int i=0;i<cnt;i++)
    arr[l+i]=tmp[i];
}

void divide(long long int arr[],long long int l,long long int r)
{
  if(r-l>0)
  {
    long long int mid=(l+r)/2;
    divide(arr,l,mid);
    divide(arr,mid+1,r);
    merge(arr,l,r);
  }
}

long long int arr[30010];
int main(void)
{
  int t;
  scanf("%d",&t);
  while(t--)
  {
    count=0;
    long long int n,i;
    scanf("%lld",&n);
    for(i=0;i<n;i++)
      scanf("%lld",&arr[i]);
    divide(arr,0,n-1);
    //printf("%lld\n",count);
    if(count%2==0)
      printf("1\n");
    else
      printf("0\n");
  }
  return 0;
}
