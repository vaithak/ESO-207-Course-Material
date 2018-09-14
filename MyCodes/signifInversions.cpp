#include <iostream>

using namespace std;

long long int signifInversion(int a[],int n)
{
    if(n<=1)
        return 0;
    
    int lSize = (n+1)/2;
    int left[lSize];
    for(int i=0;i<lSize;i++)
    {
        left[i]=a[i];
    }
    
    int rSize = (n)/2;
    int right[rSize];
    for(int i=0;i<rSize;i++)
    {
        right[i]=a[i+lSize];
    }
    
    long long int count=signifInversion(left,lSize);
    count = count + signifInversion(right,rSize);
    
    int pos=0,i=0,j=0;
    while(pos<n)
    {
        if(i==lSize)
            break;
        
        if(j==rSize)
            break;
        
        if(left[i]<right[j])
        {
            a[pos]=left[i];
            i++;
        }
        else
        {
            a[pos]=right[j];
            j++;
        }
        
        pos++;
    }
    
    while(i!=lSize)
    {
        a[pos]=left[i];
        i++;
        pos++;
    }
    
    while(j!=rSize)
    {
        a[pos]=right[j];
        j++;
        pos++;
    }
    
    int tempPos=0,tempI=0,tempJ=0;
    while(tempPos < n)
    {
        if(tempI==lSize)
            break;
        
        if(tempJ==rSize)
            break;
        
        if(left[tempI]<=2*right[tempJ])
        {
            tempI++;
        }
        else
        {
            count=count+(lSize - tempI);
            tempJ++;
        }
        
        tempPos++;
    }
    
    return count;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        long long int ans = signifInversion(a,n);
        cout<<ans<<endl;
    }
    return 0;
}
