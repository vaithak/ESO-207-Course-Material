#include <iostream>

using namespace std;

struct node {
    int num;
    node *next;
};

typedef struct node Node;

Node* createNode(int num){
    Node* tempNode = new Node;
    tempNode->next=NULL;
    tempNode->num=num;
    return tempNode;
}

Node* insertNode(Node* list, int num){
    if(list==NULL){
        list=createNode(num);
    }
    else{
        Node* tempNode = createNode(num);
        tempNode->next=list;
        list = tempNode;
    }
    return list;
}

bool DFS_CHECK_PATH(int x, int y, Node** adjList, bool visited[]){
    if(x==y)
        return true;
        
    visited[x]=true;
    Node* temp = adjList[x];
    while(temp!=NULL){
        // cout<<temp->num<<endl;
        if(visited[temp->num]==false){
            if(DFS_CHECK_PATH(temp->num, y, adjList, visited) == true)
                return true;   
        }
        temp=temp->next;
    }
    return false;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int m,n;
        cin>>m>>n;
        int x[n],y[n];
        
        Node **adjList;
        adjList = new Node*[m+1];
        
        for(int i = 1; i <= m; i++){
            adjList[i] = NULL;
        }
        
        for(int i=0;i<n;i++){
            cin>>x[i]>>y[i];
        }
        
        // for(int i=1;i<=m;i++){
        //     cout<<i<<" ";
        //     Node* temp=adjList[i];
        //     while(temp!=NULL){
        //         cout<<temp->num;
        //         if(temp->next!=NULL)
        //             cout<<"->";
        //         temp=temp->next;
        //     }
        //     cout<<endl;
        // }
        
        int check1, check2;
        cin>>check1>>check2;  // Inputting the edge to delete
        for(int i=0;i<n;i++){
            if((x[i]==check1 && y[i]==check2) || (x[i]==check2 && y[i]==check1))
                continue;
            adjList[x[i]] = insertNode(adjList[x[i]],y[i]);
            adjList[y[i]] = insertNode(adjList[y[i]],x[i]);
        }

        bool visited[m+1];
        for(int i=1;i<=m;i++)
            visited[i]=false;
        if(DFS_CHECK_PATH(check1,check2,adjList,visited) == true){
            cout<<"Not Bridge\n";
        }
        else{
            cout<<"Bridge\n";
        }
    }
    return 0;
}