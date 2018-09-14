#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string inp;
        long double arr[100000];
        int curr = -1;
        int flag=0;
        while(cin>>inp)
        {
            if(inp=="+" || inp=="-" || inp=="*" || inp=="/" || inp=="^" || inp=="%" || inp=="~")
            {
                if(curr < 1 && inp!="~")
                {
                    flag=1;
                    break;
                }
                else if(curr < 0)
                {
                    flag=1;
                    break;
                }
                long double num1 = arr[curr-1];
                long double num2 = arr[curr];
                curr=curr-1;
                if(inp=="+")
                {
                    arr[curr]=num1+num2;
                }
                else if(inp=="-")
                {
                    arr[curr]=num1-num2;
                }
                else if(inp == "*")
                {
                    arr[curr]=num1*num2;
                }
                else if(inp=="^")
                {
                    arr[curr] = pow(num1,num2);
                }
                else if(inp=="%")
                {
                    arr[curr]=(int)num1%(int)num2;
                }
                else if(inp == "/")
                {
                    arr[curr]=num1/num2;
                }
                else if(inp == "~")
                {
                    curr++;
                    arr[curr]=(-1)*num2;
                }
            }
            else
            {
               curr++;
               arr[curr]=(long double)stoll(inp);
            }
            char c = getchar();
            if(c==' ')
                continue;
                
            if(c=='\n')
                break;
        }
        if(curr!=0 || flag)
            cout<<"INVALID"<<endl;
        else
            cout<<(int)(arr[curr])<<endl;
    }
    return 0;
}