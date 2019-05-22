#include<stdio.h>

void merge(long long int arr[],long long int l,long long int r)
{
  //l and r included
  //l to mid
  //mid+1 to r
  long long int temp[r-l+9];
  long long int mid=(r+l)/2 ,ptr1=l,ptr2=mid+1;
  long long int len1=mid-l+1,len2=r-mid,cnt=0;
  while(ptr1<mid+1&&ptr2<r+1)
  {
    if(arr[ptr1]<=arr[ptr2])
    {
      temp[cnt++]=arr[ptr1++];
    }
    else if(arr[ptr1]>arr[ptr2])
    {
      temp[cnt++]=arr[ptr2++];
    }
  }
  while(ptr1<mid+1)
  {
    temp[cnt++]=arr[ptr1++];
  }
  while(ptr2<r+1)
  {
    temp[cnt++]=arr[ptr2++];
  }
  for(long long int i=0;i<r-l+1;i++)
    arr[i+l]=temp[i];
}

void msort(long long int arr[],long long int l,long long int r)
{
  if(r-l>0)
  {
    long long int mid=(r+l)/2;
    msort(arr,l,mid);
    msort(arr,mid+1,r);
    merge(arr,l,r);
  }
}

long long int arr[100000];
int main(void)
{
  int t;
  scanf("%d",&t);
  while(t--)
  {
    long long int n,i;
    scanf("%lld",&n);
    for(i=0;i<n;i++)
      scanf("%lld",&arr[i]);
    msort(arr,0,n-1);
    printf("%lld ",arr[0]);
    for(i=1;i<n;i+=2)
      {
        if(i+1<n)
        {
          printf("%lld ",arr[i+1]);
          printf("%lld ",arr[i]);
        }
        else
          printf("%lld",arr[i]);
      }
      printf("\n");
  }
  return 0;
}
