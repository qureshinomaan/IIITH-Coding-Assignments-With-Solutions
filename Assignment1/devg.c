#include<stdio.h>


long long int intern[20010][2];
long long int paper[20010][2];
int main(void)
{
  int t;
  scanf("%d",&t);
  while(t--)
  {
    long long int n,m;
    long long int lpaper=-1,lintern=-1;
    long long int ans=0;
    long long int i;
    scanf("%lld",&n);
    for(i=0;i<n;i++)
    {
      scanf("%lld%lld",&intern[i][0],&intern[i][1]);
      if(intern[i][0]>lintern)
        lintern=intern[i][0];
    }
    scanf("%lld",&m);
    for(i=0;i<m;i++)
    {
      scanf("%lld%lld",&paper[i][0],&paper[i][1]);
      if(paper[i][0]>lpaper)
        lpaper=paper[i][0];
    }
    for(i=0;i<n;i++)
    {
      if(intern[i][1]<lpaper)
      {
        if(lpaper-intern[i][1]>ans)
          ans=lpaper-intern[i][1];
      }
    }
    for(i=0;i<m;i++)
    {
      if(paper[i][1]<lintern)
      {
        if(lintern-paper[i][1]>ans)
          ans=lintern-paper[i][1];
      }
    }
  //  printf("lintern = %lld\n",lintern);
  //  printf("lpaper = %lld\n",lpaper);
    printf("%lld\n",ans);
  }
  return 0;
}
