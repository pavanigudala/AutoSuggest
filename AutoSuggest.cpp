#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ALPHA_SIZE 26
struct node{
    bool isEOW;
    node *next[ALPHA_SIZE];
};
node *createNode(){
    node *nn=(node *)malloc(sizeof(node));
    nn->isEOW=false;
    for(int i=0;i<ALPHA_SIZE;i++)
        nn->next[i]=NULL;
    return nn;
}
void insertWord(node *root,char str[])
{
    node *temp=root;
    for(int i=0;str[i];i++)
    {
        int idx=str[i]-'a';
        if(temp->next[idx]==NULL)
                temp->next[idx]=createNode();
        temp=temp->next[idx];
    }
    temp->isEOW=true;
}
bool isWordExist(node *root,char str[])
{
    node *temp=root;
    for(int i=0;str[i];i++)
    {
        int idx=str[i]-'a';
        if(temp->next[idx]==NULL)
            return false;
        temp=temp->next[idx];
    }
    return temp->isEOW;
}
char path[100];
void printWords(node *root,int pi)
{
    if(root->isEOW==true)
        printf("%s\n",path);
    for(int i=0;i<ALPHA_SIZE;i++)
    {
        if(root->next[i]!=NULL)
        {
            path[pi]=i+'a';
            path[pi+1]='\0';
            printWords(root->next[i],pi+1);
        }
    }
}
void autoSuggest(node *root,char pre[])
{
    node *temp=root;
    for(int i=0;pre[i];i++)
    {
        int idx=pre[i]-'a';
        if(temp->next[idx]==NULL)
        {
            cout<<"no word exists with the given prefix\n";
            return;
        }
        temp=temp->next[idx];
    }
    strcpy(path,pre);
    printWords(temp,strlen(pre));
}
int showMenu()
{
    int c;
    cout<<"menu"<<"\n";
    cout<<"===="<<"\n";
    cout<<"1.insert word"<<"\n";
    cout<<"2.auto suggest words"<<"\n";
    cout<<"3.print all words"<<"\n";
    cout<<"4.is word exits"<<"\n";
    cout<<"5.exit"<<"\n";
    cout<<"\n";
    cout<<"enter your choice: ";
    cin>>c;
    return c;
}
void fill(node *root)
{
    FILE *fp=fopen("c:\\words\\dict.txt","r");
    if(fp)
    {
       char str[100];
       while(!feof(fp))
       {
           fscanf(fp,"%s",str);
           insertWord(root,str);
       }
       fclose(fp);
    }
    else
        printf("file not found");
}

int main()
{
    node *root=createNode();
    fill(root);
    char str[100];
    while(true)
    {
        int ch=showMenu();
        switch(ch)
        {
        case 1:
            printf("enter a word: ");
            scanf("%s", str);
            insertWord(root,str);
            break;
        case 2:
            printf("enter prefix of words: ");
            scanf("%s",str);
            autoSuggest(root,str);
            break;
        case 3:
            printWords(root,0);
            break;
        case 4:
            printf("enter a word to search:");
            scanf("%s",str);
            if(isWordExist(root,str))
                cout<<"found\n";
            else
                cout<<"not found\n";
            break;
        case 5:
            return 0;
        default:
            cout<<"bad choice!! try again.\n";
        }
    }
    return 0;
}
