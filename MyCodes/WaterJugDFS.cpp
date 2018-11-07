#include<iostream>
#define MAX_SIZE 10000

using namespace std;

struct Node{
    int c1,c2,c3;
    int l1,l2,l3;
    int level=0;
};

template <typename T>
class queue
{
public:
    queue();
    void push(T num);
    T front();
    int size();
    void pop();
    bool empty();
private:
    int front;
    int end;
    int maxSize;
    T arr[MAX_SIZE];
};

template <typename T>
queue<T>::queue()
{
    maxSize = MAX_SIZE;
    end=-1;
    front=-1;
}

template <typename T>
int queue<T>::size(){
    if(front==-1)
        return 0;
    
    if(front > end)
        return maxSize - (front-end-1);

    if(end>=front)
        return end-front+1;
}

template <typename T>
bool queue<T>::empty(){
    if(front==-1)
        return 1;
    return 0;
}

template <typename T>
void queue<T>::push(T num){
    if( ((end+1)%maxSize) !=front ){
        if(end==-1){
            end=0;
            front=0;
        }
        else{
            end=(end+1)%maxSize;
        }
        arr[end]=num;
    }
}

template <typename T>
T queue<T>::front(){
    if(front==-1)
        return -1;
    return arr[front];
}

template <typename T>
void queue<T>::pop(){
    if(front!=-1)
        front=(front+1)%maxSize;
}

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

bool checkEqual(Node* node1, Node* node2){
    return (node1->c1 == node2->c1 && node1->c2 == node2->c2 && node1->c3 == node2->c3);
}

void adjNodes(Node source, Node arr[], bool visited[100][100][100], int &size);{
    Node temp;
    size=0;
    if(source->c1 != 0){
        temp.c1=0;
        temp.c2=source.c2;
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c2=min(source.c2+source.c1, source.l2);
        temp.c1=source.c1 - (temp.c2 - source.c2);
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c3=min(source.c3+source.c1, source.l3);
        temp.c1=source.c1 - (temp.c3 - source.c1);
        temp.c2=source.c2;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

    }
    if(source.c2 != 0){
        temp.c2=0;
        temp.c1=source.c1;
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c1=min(source.c2+source.c1, source.l1);
        temp.c2=source.c2 - (temp.c1 - source.c1);
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c3=min(source.c3+source.c2, source.l3);
        temp.c2=source.c2 - (temp.c3 - source.c2);
        temp.c1=source.c1;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

    }
    if(source.c3 != 0){
        temp.c1=0;
        temp.c2=source.c2;
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c2=min(source.c2+source.c1, source.l2);
        temp.c1=source.c1 - (temp.c2 - source.c2);
        temp.c3=source.c3;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }

        temp.c3=min(source.c3+source.c1, source.l3);
        temp.c1=source.c1 - (temp.c3 - source.c1);
        temp.c2=source.c2;
        if(visited[temp.c1][temp.c2][temp.c3]==0){
            arr[size]=temp;
            size++;
        }
    }
}

int countMinSteps(Node* source, Node* destination){
    bool visited[100][100][100]={0};

    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            for(int k=0;k<100;k++){
                visited[i][j][k]=0;
            }
        }
    }

    queue<Node*> qu;
    qu.push(source);
    visited[source->c1][source->c2][source->c3]=1;
    if(checkEqual(arr[i], *destination))
        return 0;

    while(!qu.empty()){
        Node* currNode = qu.front();
        qu.pop();
        Node arr[9];
        int size;
        
        adjNodes(*currNode, arr, visited, size);
        for(int i=0;i<size;i++){
            if(checkEqual(arr[i], *destination))
                return arr[i].level;
            else{
                qu.push(&(arr[i]));
                visited[arr[i].c1][arr[i].c2][arr[i].c3]=1;
            }
        }
    }
}

bool isPossible(Node source, Node destination){
    int flag = ( (source.c1 + source.c2 + source.c3) >= (destination.c1 + destination.c2 + destination.c3) ) ;
    if( gcd(gcd(source->c1, source->c2), source->c3) == gcd(gcd(destination->c1, destination->c2), destination->c3) ){
        return flag;
    }
    else{
        return 0;
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
            if(isPossible(*source, *destination))
                cout<<countMinSteps(source, destination)<<endl;
            else
                cout<<"IMPOSSIBLE"<<endl;
            free(destination);
        }
    }
    return 0;
}
