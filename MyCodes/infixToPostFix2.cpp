#include <iostream>

using namespace std;

bool isOperand(string s)
{
    if(s == ")" || s=="(" || s=="+" || s=="-" || s=="*" || s=="/" || s=="%" || s=="^")
        return false;
    
    return true;
}

bool isOnlyBinaryOperator(string s)
{
    if(s=="+" || s=="*" || s=="/" || s=="%" || s=="^")
        return true;
    
    return false;
}

bool anyOperator(string s)
{
    if(s=="+" || s=="*" || s=="/" || s=="%" || s=="^" || s=="-")
        return true;
    
    return false;
}

bool canBeUnary(string s)
{
    if(s=="-")
        return true;
    
    return false;
}

bool checkValidity(string str[], int end)
{
    int bracketCount=0;
    if(str[0]==")" || isOnlyBinaryOperator(str[0]))
        return false;
    
    if(str[end]=="(" || anyOperator(str[end]))
        return false;
    
    for(int i=0;i<=end;i++)
    {
        if(str[i]=="(")
        {
            bracketCount++;
            if(i!=0 && (str[i-1]==")" || isOperand(str[i-1])) )
                return false; 
                
            if(str[i+1]==")" || isOnlyBinaryOperator(str[i+1]))
                return false;
                
        }
        else if(str[i]==")")
        {
            bracketCount-=1;
            
            if(bracketCount<0)
                return false;
                
            if(i!=end && (str[i+1]=="(" || isOperand(str[i+1])))
                return false;
                
            if(i!=0 && (str[i-1]=="(" || anyOperator(str[i-1]) ) )
                return false;  

        }
        else if(isOnlyBinaryOperator(str[i]))
        {
            if(str[i+1]==")" || isOnlyBinaryOperator(str[i+1]))
                return false;   
            
            if(str[i+1]=="-" && ( anyOperator(str[i-1]) || anyOperator(str[i+2]) ))
                return false;
                
            
        }
        else if(canBeUnary(str[i]))
        {
            if(i==end || isOnlyBinaryOperator(str[i+1]) || str[i+1]==")")
                return false;
        }
        else if(isOperand(str[i]))
        {
            if(i!=0 && (str[i-1]==")" || isOperand(str[i-1]) ))
                return false;
                
            if(i!=end && (str[i+1]=="(" || isOperand(str[i+1]) ))
                return false;
        }
    }
    
    if(bracketCount!=0)
        return false;
    
    return true;
}

bool removeFromStack(string s1, string s2)
{
    if(s1=="~" && !(s2=="~"))
        return false;
    else if(s1=="^" && !(s2=="~"))
        return false;
    else if((s1=="%" || s1=="/") && !(s2=="^" || s2=="%" || s2=="/" || s2=="~"))
        return false;
    else if((s1=="*") && !(s2=="/" || s2=="*" || s2=="%" || s2=="^" || s2=="~"))
        return false;
    else if(s2=="(")
        return false;
        
    return true;
    
}

void convert(string str[], int end)
{
    string stack[10000];
    int stackSize=0;
    string res[10000];
    int len=0;
    for(int i=0;i<=end;i++)
    {
        if(str[i]=="(")
        {
            stack[stackSize]=str[i];
            stackSize++;
        }
        else if(isOperand(str[i]))
        {
            res[len]=str[i];
            len++;
        }
        else if(str[i]==")")
        {
            while(stack[stackSize-1]!="(")
            {
                res[len]=stack[stackSize-1];
                len++;
                stackSize--;
            }
            stackSize--;
        }
        else
        {
            if(str[i] == "-" && (i==0 || str[i-1]=="(" || anyOperator(str[i-1])))
                str[i]="~";
            
            if(stackSize!=0 && removeFromStack(str[i],stack[stackSize-1]))
            {
                while(stackSize!=0 && removeFromStack(str[i],stack[stackSize-1]))
                {
                    res[len]=stack[stackSize-1];
                    len++;
                    stackSize--;
                }
                stack[stackSize]=str[i];
                stackSize++;
            }
            else
            {
                stack[stackSize]=str[i];
                stackSize++;
            }
        }
    }
    
    for(int i=0;i<len;i++)
    {
        cout<<res[i]<<" ";
    }
    
    while(stackSize!=0)
    {
        cout<<stack[stackSize-1]<<" ";
        stackSize--;
    }
    
    cout<<endl;
}

int main()
{
    int t;
    cin>>t;
    char c=getchar();
    while(t--)
    {
        string str[10000];
        int len=0;
        char c;
        
        char s[10000];
        
        scanf("%[^\n]%*c", s);
        string inp=s;
        
        int i=0;
        while(i<inp.length())
        {
            if(inp[i]==' ')
            {
                i++;
            }
            else
            {
                string check ="";
                while(i!=inp.length() && inp[i]!=' ')
                {
                     check = check + inp[i];
                     i++;
                }
                str[len] = check;
                len++;
            }
        }
        
        if(!checkValidity(str,len-1))
        {
            cout<<"INVALID"<<endl;
        }
        else
        {
            convert(str,len-1);
        }
    }
    return 0;
}