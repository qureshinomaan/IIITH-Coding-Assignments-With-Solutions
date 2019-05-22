#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node{
	struct node *left,*right;
	long long int info;
	long long int l,r;
  long long int total;
};

long long int sum=0,max=-1000000000000;
long long int good2=0,k,t;
long long int array[300000];
long long int dif,mdif=11000101,answer=-1,good=0,elements=0;

struct node *newnode(long long int info,long long int l)
{
	struct node *temp= (struct node*)(malloc(sizeof(struct node)));
	temp->info=info;
	temp->right=NULL;
	temp->left=NULL;
	temp->l=0;
  temp->total=0;
	return temp;
}

struct node* insert(struct node *head,long long int info,long long int l)
{
	if(head==NULL)
		return newnode(info,l);
	if(info>head->info)
		{
			head->right=insert(head->right,info,l);
		}
	else
		{
			head->l+=info;
      head->total++;
			head->left=insert(head->left,info,l);
		}
	return head;
}

void inorder(struct node *head)
{
	if(head==NULL)
		return;
	inorder(head->left);
	printf("[ %lld, %lld, %lld ]",head->info,head->l,head->total);
	inorder(head->right);
}

struct node *del(struct node *head,long long int info)
{
	if(head==NULL)
		return head;

	if(info>head->info)
		{
			head->right=del(head->right,info);
			return head;
		}
	else if(info<head->info)
		{
			head->l-=info;
      head->total--;
			head->left=del(head->left,info);
			return head;
		}

	if(head->right==NULL && head->left==NULL)
		return NULL;
	if(head->right==NULL)
		return head->left;
	if(head->left==NULL)
		return head->right;

	struct node *tmp=(struct node*)malloc(sizeof(struct node));
	// struct node *parent=(struct node*)malloc(sizeof(struct node));
	tmp=head->right;
	while(tmp->left!=NULL)
	{
		// parent=tmp;
		tmp=tmp->left;
	}
	// parent=head->right;
	if(tmp->left==NULL)
		{
			head->info=tmp->info;
			head->right=del(head->right, tmp->info);
		}
	// else{
	// 	while(tmp->left!=NULL)
	// 	{
	// 		parent=tmp;
	// 		tmp=tmp->left;
	// 	}
	// 	head->info=tmp->info;
	// 	parent->left=tmp->right;
	// }
	return head;
}

void calTax(struct node*head)
{
	if(head==NULL)
		return;
//	printf("%lld %lld\n",head->total,sum);
  if(t-good-head->total==k)
  {
    answer=sum-good2-head->l;
    return;
  }
	else if(t-good-head->total<k)
	{
		return calTax(head->left);
	}
	else
	{
		good+=(head->total+1);
		good2+=(head->l+head->info);
		return calTax(head->right);
	}

}

int main(void)
{
  struct node*head=NULL;
  long long int n,i;

  scanf("%lld",&n);
  scanf("%lld",&t);
  scanf("%lld",&k);
  for(i=0;i<n;i++)
  { scanf("%lld",&array[i]);}
  for(i=0;i<t;i++)
    {
      sum+=array[i];
      head=insert(head,array[i],0);
    }
  calTax(head);
	if(answer>max)
		max=answer;
  for(i=t;i<n;i++)
  {
    sum+=array[i];
    sum-=array[i-t];
    head=del(head,array[i-t]);
    head=insert(head,array[i],0);
    // inorder(head);
    // printf("\n");
    answer=0;
    good=0;
    good2=0;
    calTax(head);
	//	printf("%lld\n",max);
    if(answer>max)
      max=answer;
  }
//  printf("\n");
 	printf("%lld\n",max);

  return 0;
}
