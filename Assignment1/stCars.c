#include<stdio.h>

long long int arr[1000000];
long long int tmp[1000000];
int main(void)
{
  int t;
  scanf("%d",&t);
  while(t--)
  {
    long long int n,i;
    scanf("%lld",&n);
    arr[0]=0;
    arr[n+1]=1000000000000;
    for(i=1;i<=n;i++)
      scanf("%lld",&arr[i]);
    long long int start,end,flag=0,assign=0;
    long long int sc,ec;//start comparision and end comparision
    //for calcuating tmp
    for(i=1;i<=n+1;i++)
    {
      tmp[i]=arr[i]-arr[i-1];
    }
    assign=0;
    for(i=1;i<=n+1;i++)
    {
      if(flag==0)
      {
        if(tmp[i]==0)
          {
            start=i-1;
            sc=i-2;
            while(tmp[i]==0&&i<=n)
              i++;
            if(tmp[i]<0)
            {
              assign=1;
              flag=1;
            }
          }
        else if(tmp[i]<0)
        {
          start=i-1;
          sc=i-2;
          flag=1;
          assign=1;
        }
      }
      else if(flag==1)
      {
        if(tmp[i]>0)
        {
            end=i-1;
            ec=i;
            flag=2;
        }
      }
      else if(flag==2)
        {
          if(tmp[i]<0)
          {
            flag=3;
            break;
          }
        }
    }

/*    printf("Start =%lld \n End = %lld",start,end);
    printf("sc = %lld\nec =%lld",sc,ec); */
    if(flag==2)
    {
      if(arr[sc]<=arr[end]&&arr[start]<=arr[ec])
      {
        printf("%lld %lld\n",start,end);
      }
      else
        printf("NotPossible\n");
    }
    else
      printf("NotPossible\n");
  }

  return 0;
}
