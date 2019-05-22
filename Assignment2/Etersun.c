#include<stdio.h>

long long int arr[1000010];
long long int stack[1000010];
long long int ind[1000010];
long long int minimum[1000010];
long long int top=0,bottom=0;
long long int currentcount;

//This is for the bottom of the stack.
void push(long long int info)
{
  top++;
  stack[top]=info;
}

void pop()
{
  top--;
}

int main(void)
{
  long long int i,n,k;
  scanf("%lld %lld",&n,&k);
  for(i=1;i<=n;i++)
  {
    scanf("%lld",&arr[i]);
  }
  if(n==1)
  {
    printf("%lld\n",arr[1]);
    return 0;
  }
  if(k>=n)
  {
    printf("%lld\n",arr[1]+arr[n]);
    return 0;
  }
  i=2;
  long long int curr=arr[1];
  push(arr[1]);
  minimum[1]=arr[1];
  ind[top]=1+k;
  bottom=1;
  while(i<=n)
  {
    minimum[i]=arr[i]+curr;
    if(arr[i]+curr>=stack[top])
    {
      push(arr[i]+curr);
      ind[top]=i+k;
    }
    else
    {
      while(top>0&&arr[i]+curr<stack[top])
        pop();
      push(arr[i]+curr);
      ind[top]=i+k;
    }
    if(i==ind[bottom])
    {
      bottom++;
      curr=stack[bottom];
    }
    i++;
  }
//  for(i=1;i<=n;i++)
  //  printf("%lld ",minimum[i]);
  printf("%lld\n",minimum[n]);
  return 0;
}
