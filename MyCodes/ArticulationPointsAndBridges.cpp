#include <iostream>

using namespace std;

struct node {
    int num;
    node *next;
};

typedef struct node Node;

Node* createNode(long int num){
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

bool bridge[10000][10000];
long int tim;
void ARTICULATING_POINTS(int u, Node** adjList, bool visited[], bool AP[],int parent[], int low[], int disc[]){
    visited[u]=true;
    tim++;
    low[u]=tim;
    disc[u]=tim;
    int subtree=0;
    
    Node* temp = adjList[u];
    while(temp!=NULL)
    {
        int v = temp->num;
        // cout<<v<<"hi"<<endl;
        if(visited[v]==false)
        {
            subtree++;
            parent[v]=u;
            ARTICULATING_POINTS(v, adjList, visited, AP, parent, low, disc);
            
            low[u]=min(low[u],low[v]);  
            if( (parent[u]!=-1) && ( low[v]>=disc[u] ) ){
                AP[u]=true;
            }
            else if( (parent[u]==-1) && (subtree>1))
                AP[u]=true;
                
            // if(low[v]>disc[u]){
            //     bridge[u][v]=true;
            //     bridge[v][u]=true;
            // }
        }
        else if(v!=parent[u])
        {
            low[u]=min(low[u],disc[v]);
        }
        temp=temp->next;
    }
}

void BRIDGES(int u, Node** adjList, bool visited[], int parent[], int low[], int disc[]){
    visited[u]=true;
    tim++;
    low[u]=tim;
    disc[u]=tim;
    int subtree=0;
    
    Node* temp = adjList[u];
    while(temp!=NULL)
    {
        int v = temp->num;
        if(visited[v]==false)
        {
            subtree++;
            parent[v]=u;
            BRIDGES(v, adjList, visited, parent, low, disc);
            
            low[u]=min(low[u],low[v]);  
            if(low[v]>disc[u]){
                bridge[u][v]=true;
                bridge[v][u]=true;
            }
        }
        else if(v!=parent[u])
        {
            low[u]=min(low[u],disc[v]);
        }
        temp=temp->next;
    }
}

int main(){
        long int m,n;
        cin>>m>>n;
        if(m==0){
            cout<<"EMPTY";
            return 0;
        }
        tim=0;
        Node **adjList;
        adjList = new Node*[m];
        
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                bridge[i][j]=false;
            }
        }
        
        for(long int i = 0 ;i < m; i++){
            adjList[i] = NULL;
        }
        
        long int x,y;
        for(int i=0;i<n;i++){
            cin>>x>>y;
            adjList[x] = insertNode(adjList[x],y);
            adjList[y] = insertNode(adjList[y],x);
        }
        
        // for(int i=0;i<m;i++){
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
    
        bool visited[m];
        bool AP[m];
        int low[m];
        int parent[m];
        int disc[m];
        for(int i=0;i<m;i++){
            visited[i]=false;
            AP[i]=false;
            low[i]=0;
            parent[i]=-1;
            disc[i]=0;
        }
    
        for(int i=0;i<m;i++){
            if(visited[i]==false){
                ARTICULATING_POINTS(i, adjList, visited, AP, parent, low, disc);
            }
        }
        
        // cout<<low[0]<<" "<<disc[1]<<endl;
        int flag=0;
        for(int i=0;i<m;i++){
            if(AP[i]==true)
            {
                flag=1;
                cout<<i<<" ";
            }
        }
        if(!flag){
            cout<<"EMPTY";   
        }
        cout<<endl;
         for(int i=0;i<m;i++){
            visited[i]=false;
            low[i]=0;
            parent[i]=-1;
            disc[i]=0;
        }
        // flag=0;
        BRIDGES(0, adjList, visited, parent, low, disc);
        for(int i=0;i<m;i++){
            for(int j=i;j<m;j++){
                if(bridge[i][j]==true){
                    cout<<i<<" "<<j<<endl;
                    // flag=1;
                }
            }
        }   
        

    return 0;
}