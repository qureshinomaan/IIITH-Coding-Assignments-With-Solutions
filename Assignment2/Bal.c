#include<stdio.h>

char stack[1000010];
int top=-1;

void push(char a)
{
  top++;
  stack[top]=a;
}

void pop()
{
  top--;
}

int main(void)
{
  long long int n,i;
  long long int count=0;
  char string[1000010];
  scanf("%lld",&n);
  scanf("%s",string);
  if(n%2==1)
    printf("-1\n");
  else
  {
    for(i=0;i<n;i++)
    {
      if(string[i]=='A')
      {
        push(string[i]);
      }
      else if(string[i]=='C')
      {
        if(stack[top]=='A')
          pop();
        else
          push(string[i]);
      }
    }
    for(i=0;i<=top;i+=2)
    {
      if(stack[i]=='A'&&stack[i+1]=='A')
        count++;
      else if(stack[i]=='C'&&stack[i+1]=='C')
        count++;
      else
        count+=2;
    }
    printf("%lld\n",count);
  }
  return 0;
}
if(string[i]<stack[top])
{
  ans[ansvar]=string[i];
  ansvar++;
  i++;
}
else
{
  ans[ansvar]=stack[top];
  ansvar++;
  pop();
}
