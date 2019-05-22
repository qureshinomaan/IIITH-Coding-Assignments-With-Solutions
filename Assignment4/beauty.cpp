#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

long long int level=1;

struct node{

  struct node* arr[5];
  int end;
  int level;
  int total;
};

node* newnode()
{
  node *tmp=new node;
  for(int i=0;i<5;i++)
    tmp->arr[i]=NULL;
  tmp->end=0;
  return tmp;
}

void insert(node *root,char a[])
{
  node *tmp=root;
  int i,index;
  int len=strlen(a);
  for(i=0;i<len;i++)
  {
    index=a[i]-97;
    if(tmp->arr[index]==NULL)
      tmp->arr[index]=newnode();
    tmp=tmp->arr[index];
  }
  if(tmp->end>=0)
    tmp->end++;
}

long long int status=0;

void search(node *root,char a[])
{
  node *tmp=root;
  int len=strlen(a);
  int index,i;
  char str[1600];

  for(i=0;i<len;i++)
  {
    strcpy(str,a);
    index=a[i]-97;

    if(a[i]!='?')
    {
      if(tmp->arr[index]==NULL)
        return;
      tmp=tmp->arr[index];
    }
    else
    {
      char dodo='a';
      for(int j=0;j<5;j++)
      {
        str[i]=dodo;
    //    printf("%s\n",str);
        search(tmp,&str[i]);
        dodo++;
      }
      char tempstr[1600],tempstr2[1600];
  //    printf("%c",a[i+1]);
      search(tmp,&a[i+1]);
      return;
    }
  }
  if(tmp!=NULL&&tmp->end>0&&tmp->level<level)
    {
      tmp->level=level;
    //  printf("%s\n",a);
      status+=tmp->end;
    }
}

int main(void)
{
  long long int n,i;
  char str[1600];
  node *head=newnode();
  scanf("%lld",&n);
  for(i=0;i<n;i++)
    {
      scanf("%s",str);
      insert(head,str);
    }
  scanf("%lld",&n);
  for(i=0;i<n;i++)
  {
    status=0;
    scanf("%s",str);
    search(head,str);
    printf("%lld\n",status);
    level++;
  }
  return 0;
}
