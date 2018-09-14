#include <iostream>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        
        if(m==0)
            continue;
            
        int s[m][2];
        for(int i=0;i<m;i++)
        {
            cin>>s[i][0];
            s[i][1]=0;
        }
        
        int minStack[m];
        minStack[m-1]=s[m-1][0];
        
        for(int i=m-2;i>=0;i--)
        {
            if(s[i][0]<=minStack[i+1])
            {
                minStack[i]=s[i][0];
            }
            else
            {
                minStack[i]=minStack[i+1];
            }
        }
        
        int res[m],k=0;
        for(int i=0;i<m;i++)
        {
            if(s[i][0]==minStack[i])
            {
                res[k]=s[i][0];
                s[i][1]=1;
                k++;
                int j=i-1;
                while(j>=0 && i<m-1 && s[j][1]==0 && s[j][0]<=minStack[i+1])
                {
                    res[k]=s[j][0];
                    k++;
                    s[j][1]=1;
                    j--;
                }
            }
        }
        
        for(int i=m-1;i>=0;i--)
        {
            if(s[i][1]==0)
            {
                res[k]=s[i][0];
                k++;
            }
        }
        
        for(int i=0;i<m;i++)
        {
            cout<<"v"<<res[i];
        }
        cout<<endl;
    }
    return 0;
}

