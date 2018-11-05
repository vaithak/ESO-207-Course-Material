#include<iostream>
#define MAX_SIZE 10000

using namespace std;

struct Node{
    int c1,c2,c3;
    int l1,l2,l3;
};

typedef struct Node Node;

Node* createNode(int c1,int c2,int c3,int l1,int l2,int l3){
    Node* temp = new Node;
    temp->c1=c1;
    temp->c2=c2;
    temp->c3=c3;
    temp->l1=l1;
    temp->l2=l2;
    temp->l3=l3;
}

int countMinSteps(Node* source, Node* destination){
    Node* queue[MAX_SIZE];
    int queueStart=0;
    int queueEnd=0;
    queue[queueEnd]=source;
    currSize++;
    int level=0;
    while(currSize!=0){

        if(checkEqual(source))
    }

}

int main(int argc, char const *argv[])
{
    int t;
    cin>>t;
    while(t--){
        int l1,l2,l3;
        cin>>l1>>l2>>l3;
        int s1,s2,s3;
        cin>>s1>>s2>>s3;
        Node* source = createNode(s1,s2,s3,l1,l2,l3);
        int q;
        cin>>q;
        while(q--){
            int r1,r2,r3;
            cin>>r1>>r2>>r3;
            Node* destination = createNode(r1,r2,r3,l1,l2,l3);
            int minSteps = countMinSteps(source, destination);
            if(minSteps==-1)
                cout<<"IMPOSSIBLE"<<endl;
            else
                cout<<minSteps<<endl;
        }
    }
    return 0;
}
