#include<stdio.h>
#include<string.h>
void MtoC(char m[50],char k[10],char c[50])
{
   int m1[50],k1[10],c1[50],i,j;
   for(i=0;i<strlen(k);i++)
      k1[i]=k[i]-'a';
   for(j=0;j<strlen(m);j++)
   {
      m1[j]=m[j]-'a';
      c1[j]=(m1[j]+k1[j%strlen(k)])%26;
      c[j]=c1[j]+'a';
      printf("%c------%c\n",m[j],c[j]);
   }
}
void CtoM(char c[50],char k[10],char m[50])
{
   int m1[50],k1[10],c1[50],i,j;
   for(i=0;i<strlen(k);i++)
      k1[i]=k[i]-'a';
   for(j=0;j<strlen(m);j++)
   {
      c1[j]=c[j]-'a';
      m1[j]=(c1[j]-k1[j%strlen(k)]+26)%26;
      m[j]=m1[j]+'a';
      printf("%c------%c\n",c[j],m[j]);
   }
}
int main(void)
{
  int i,j;
  char m[50], k[10], c[50],t[50];
  printf("输入明文：");
        gets(t);
        j=0;
        for(i=0;t[i]!='\0';i++){
        if(t[i]<='Z'&&t[i]>='A'){
        m[j]=t[i]+32;
        j++;
        }
        else if(t[i]<='z'&&t[i]>='a'){
        m[j]=t[i];
        j++;
        }
           }
    m[j]='\0';

  printf("输入密钥：");
  scanf("%s",k);
  printf("明文转换为密文：n");
  MtoC(m,k,c);
  printf("密文转换为明文：n");
  CtoM(c,k,m);
}