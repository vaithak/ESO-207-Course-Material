#include<iostream>
#include<queue>

using namespace std;

struct Node{
    int c1,c2,c3;
    int l1,l2,l3;
    int level;
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
    return temp;
}

bool checkEqual(Node node1, Node node2){
    return (node1.c1 == node2.c1 && node1.c2 == node2.c2 && node1.c3 == node2.c3);
}

void adjNodes(Node source, Node arr[], bool visited[105][105][105], int &size){
    Node temp;
    temp.level = source.level+1;
    temp.l1=source.l1;
    temp.l2=source.l2;
    temp.l3=source.l3;
    if(source.c1 != 0){
        temp.c1=0;
        temp.c2=source.c2;
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c2=min(source.c2+source.c1, source.l2);
        temp.c1=source.c1 - (temp.c2 - source.c2);
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c3=min(source.c3+source.c1, source.l3);
        temp.c1=source.c1 - (temp.c3 - source.c3);
        temp.c2=source.c2;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

    }
    if(source.c2 != 0){
        temp.c2=0;
        temp.c1=source.c1;
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c1=min(source.c2+source.c1, source.l1);
        temp.c2=source.c2 - (temp.c1 - source.c1);
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c3=min(source.c3+source.c2, source.l3);
        temp.c2=source.c2 - (temp.c3 - source.c3);
        temp.c1=source.c1;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

    }
    if(source.c3 != 0){
        temp.c3=0;
        temp.c2=source.c2;
        temp.c1=source.c1;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c2=min(source.c2+source.c3, source.l2);
        temp.c3=source.c3 - (temp.c2 - source.c2);
        temp.c1=source.c1;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }

        temp.c1=min(source.c3+source.c1, source.l1);
        temp.c3=source.c3 - (temp.c1 - source.c1);
        temp.c2=source.c2;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
            visited[temp.c1][temp.c2][temp.c3]=1;
        }
    }
}

int countMinSteps(Node source, Node destination){
    bool visited[105][105][105];

    for(int i=0;i<105;i++){
        for(int j=0;j<105;j++){
            for(int k=0;k<105;k++){
                visited[i][j][k]=0;
            }
        }
    }

    queue<Node> qu;
    source.level=1;
    qu.push(source);
    visited[source.c1][source.c2][source.c3]=1;
    while(!qu.empty()){
        Node currNode = qu.front();
        qu.pop();
        Node arr[9];
        int size=0;
        adjNodes(currNode, arr, visited, size);
        for(int i=0;i<size;i++){
            if(checkEqual(arr[i], destination))
                return arr[i].level;
            else
                qu.push(arr[i]);
        }
    }
    return -1;
}

bool isPossible(Node source, Node destination){
    if(destination.c1!=0 && destination.c1!=destination.l1 && destination.c2!=0 && destination.c2!=destination.l2 && destination.c3!=0 && destination.c3!=destination.l3)
        return 0;

    if(source.c1>source.l1 || destination.c1>destination.l1 || source.c2>source.l2 || destination.c2>destination.l2 || source.c3>source.l3 || destination.c3 > destination.l3)
        return 0;

    return  ( (source.c1 + source.c2 + source.c3) >= (destination.c1 + destination.c2 + destination.c3) ) ;
}

int main(int argc, char const *argv[]){
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
            if(checkEqual(*source, *destination)){
                cout<<1<<endl;
                continue;
            }
            if(isPossible(*source, *destination)){
                int temp = countMinSteps(*source, *destination);
                if(temp==-1){
                    cout<<"IMPOSSIBLE "<<endl;
                }
                else
                    cout<<temp<<endl;
            }
            else
                cout<<"IMPOSSIBLE "<<endl;
            free(destination);
        }
        free(source);
    }
    return 0;
}
