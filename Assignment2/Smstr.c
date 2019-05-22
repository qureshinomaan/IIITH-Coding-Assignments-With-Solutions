#include<stdio.h>
#include<string.h>

char stack[1000010];
long long int top=-1;

void push(char a)
{
  top++;
  stack[top]=a;
}

void pop()
{
  top--;
}
void print()
{
  for(int i=top;i>=0;i--)
    printf("%c-->",stack[i]);
  printf("\n");
}

long long int pos[30][1000010];
int main(void)
{
  long long int n;
  long long int lpos[30];       //This array is for last pos of a character
  long long int mpos[30];
  long long int count[30];      //This array is for counting how many times an element has occured
  for(int j=0;j<30;j++)
  {
    mpos[j]=-1;
    lpos[j]=-1;
    count[j]=0;
  }
  long long int len,i;
  long long int mincount=0;
  char string[1000010];
  char ans[1000010];
  char curr='a';
  long long int ansvar=0;
//  scanf("%lld",&n);
  scanf("%s",string);
  len=strlen(string);
  for(i=0;i<len;i++)
  {
    int tmp=string[i];
    pos[tmp-97][count[tmp-97]]=i;
    lpos[tmp-97]=i;
    count[tmp-97]++;
    if(mpos[tmp-97]==-1)
      mpos[tmp-97]=i;
  }
  i=0;//For iterating through string
  int loopcount=0;


  //This is the main loop
  while(1)
  {
    long long int tmp=curr;//just defining the value of current
    if((tmp-97)>25||i==len)   //breaking conditions
      break;
    else if(lpos[tmp-97]==-1||count[tmp-97]==0)   //This else if tells if all the element of the smallest charcter are covered
    {
      curr++;
      mincount=0;
    }
    else if(top>=0&&stack[top]==curr)             //this else if covers something
    {
      while(top>=0&&stack[top]==curr)
      {
        ans[ansvar]=stack[top];
        ansvar++;
        count[tmp-97]--;
        pop();
        if(pos[tmp-97][mincount]==mpos[tmp-97]&&count[tmp-97]>0)
        {
          mincount++;
          mpos[tmp-97]=pos[tmp-97][mincount];
        }
      }
    }
    else if(string[i]==curr)
    {
      ans[ansvar]=string[i];
      mincount++;
      count[tmp-97]--;
      if(count[tmp-97]>0)
      {
        mpos[tmp-97]=pos[tmp-97][mincount];
      }
      ansvar++;
      i++;
    }
    else if(mpos[tmp-97]>i)
    {
      push(string[i]);
      i++;
    }
    else if(mpos[tmp-97]<i<lpos[tmp-97])
    {
      if(string[i]<stack[top]||top<0)
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
    }
    else if(i>lpos[tmp-97])
    {
      if(string[i]<stack[top]||top<0)
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
    }
  //  print();
  }
  while(top>=0)
  {
    ans[ansvar]=stack[top];
    pop();
    ansvar++;
  }
  printf("%s",ans);
  return 0;
}
