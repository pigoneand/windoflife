#include <iostream>
using namespace std;

// 原串
char S[2000000];

// 模式串
char T[2000000];

int last[2000000];
int next[2000000];
int modelen;

void deal_next(char * s,int & len)
{
     int i,j,k;
     int now;
     
     //calc last[j]
     last[1]=0;
     len=1;
     
     while (s[len+1]!='\0')
     {
           len++;
           j=len;
           now=j-1;
         while (now >0)
         {
               if (s[j]==s[last[now]+1]) 
               { last[j]=last[now]+1; break; }
               now=last[now];
         }
         if (now ==0) last[j]=0;
         next[j]=last[j-1]+1;
     }
     
     next[1]=0;
     next[len+1]=last[len]+1;
     
}

int kmp(char * s,int len,char * t,int modelen)
{
     int i=1,j=1;
     while (i<=len && j<=modelen)
     {
           if (j==0 || s[i]==t[j])
           { i++;j++; }
           else j=next[j];
     }
     if (j>modelen) return i-modelen;
     else return -1;
}

// 计算字符串出现的次数
int kmp2(char * s,int len,char * t,int modelen)
{
     int i=1,j=1;
     int ans=0;
     while (s[i]!='\0')
     {
           if (j==0 || s[i]==t[j])
           { i++;j++; }
           else j=next[j];
           
           if (j>modelen) 
           {
               ans++;
               j=next[j];
           }   
     }
     return ans;
}

int main()
{
    int cases;
    int lenS,lenT;
    cin>>cases;
    cin.getline(S,10,'\n');
    
    while (cases--)
    {
          scanf("%s",T+1);
          scanf("%s",S+1);

              deal_next(T,lenT);
    
              cout<<kmp2(S,lenS,T,lenT)<<endl;
          
    }

    return 0;
}