#include<stdio.h>
#include<string.h>

char troy[1010][1010];
int horizontal[1010][1010];
int vertical [1010][1010];

int stack[1000010],indexstack[1000010];
int top=-1;

void pushindex(int info)
{
  top++;
  indexstack[top]=info;

}
void pop()
{
  top--;
}

void print()
{
  int i;
  for(i=top;i>=0;i--)
    printf("%lld --> ",indexstack[i]);
  printf("\n");
}

int front[1000010],last[1000010];
int labques(int *arr,int len)
{
  int area,max=-1,index,i=1,sum;

  front[1]=0;
  last[len-1]=0;
  pushindex(0);
  while(i<=len)
  {
    if(top==0||(arr[i]>arr[indexstack[top]]))
    {
      front[i]=indexstack[top];
      pushindex(i);
      i++;
    }
    else
    {
      pop();
    }
        //print();
  }
  top=0;
  i=len;
  last[len]=len+1;
  pushindex(len+1);
  while(i>0)
  {
    if(top==0||(arr[i]>arr[indexstack[top]]))
    {
      last[i]=indexstack[top];
      pushindex(i);
      i--;
    }
    else
    {
      pop();
    }
    //    print();
  }
/*  for(i=1;i<=len;i++)
    printf("%lld ",last[i]);
  printf("\n");
  for(i=1;i<=len;i++)
    printf("%lld ",front[i]);*/
  for(i=1;i<=len;i++)
  {
    sum=(last[i]-front[i]-1)*arr[i];
    if(sum>max)
      max=sum;
  }
  return max;
}

int main(void)
{
  int i,j;
  int m,n;
  scanf("%d %d",&m,&n);
  char string[10000];
  char tmp;
  for(i=1;i<=m;i++)
  {
    for(j=1;j<=n;j++)
    {
      scanf("%s",string);
      //printf("%s\n",string);
      if(strcmp(string,"E")==0)
        vertical[i][j]=0;
      else
        vertical[i][j]=1;
    }
  }

  for(j=1;j<=n;j++)
  {
    for(i=2;i<=m;i++)
    {
      if(vertical[i][j]>0&&vertical[i-1][j]>0)
        vertical[i][j]=vertical[i-1][j]+1;
      }
  }
/*  printf("horizontal\n");
  for(i=1;i<=m;i++)
  {
    for(j=1;j<=n;j++)
    {
        printf("%d ",horizontal[i][j]);
    }
    printf("\n");
  }*/
/* printf("vertical\n");
  for(i=1;i<=m;i++)
  {
    for(j=1;j<=n;j++)
    {
      printf("%d  ",vertical[i][j]);
    }
    printf("\n");
  }*/

  //Checking horizontally

  int max=-1,sum;
  for(i=1;i<=m;i++)
  {
    sum=0;
    vertical[i][0]=0;
    vertical[i][n+1]=0;
    sum=labques(vertical[i],n);
    if(sum>max)
      max=sum;
  }
  printf("%d\n",max);
  return 0;
}
