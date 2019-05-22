#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node{
	struct node *left,*right;
	long long int info;
	long long int l,r;
};

long long int sum=0;

long long int dif,mdif=11000101,answer=-1,good=0;

struct node *newnode(long long int info,long long int l)
{
	struct node *temp= (struct node*)(malloc(sizeof(struct node)));
	temp->info=info;
	temp->right=NULL;
	temp->left=NULL;
	temp->l=0;
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
			head->left=insert(head->left,info,l);
		}
	return head;
}

void inorder(struct node *head)
{
	if(head==NULL)
		return;
	inorder(head->left);
	printf("%lld ",head->info);
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

long long int mn(long long int a,long long int b)
{
	if(a<b)
		return a;
	return b;
}

void calTax(struct node*head,long long int a)
{
	if(head==NULL)
		return;
	long long int sm=(good+head->l)/10 + (sum-good-head->l)/2,ns;
//	inorder(head);
//	printf("%lld %lld\n",head->info,sm);
	if(sm>=a)
	{
		good+=head->l;
		answer=head->info;
		good+=head->info;
		if(head->right!=NULL)
		calTax(head->right,a);
	}
	else
	{
		if(head->left!=NULL)
		calTax(head->left,a);
	}
}

int main(void)
{
	long long int info,n,i;
	char string[2];
	long long int count=0;
	struct node*head=NULL;
	scanf("%lld\n",&n);
	while(1)
	{
		scanf("%s ",string);
		scanf("%lld",&info);
		if(strcmp(string,"H")==0)
		{
			sum+=info;
			head=insert(head,info,0);
		}
		else if(strcmp(string,"F")==0)
		{
			sum-=info;
			head=del(head,info);
		}
		else
		{
			count++;
			good=0;
			answer=-1;
			if(sum/10 >= info)
				printf("1000000000\n");
			else if(sum/2 < info)
				printf("Alert!\n");
			else
			{
				calTax(head,info);
				printf("%lld\n",answer);
			}
		}
		if(count==n)
			break;
	}
	return 0;
}
