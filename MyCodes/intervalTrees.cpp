#include <iostream>
#define INT_MIN -100000009

using namespace std;

// Structure of an interval
struct Interval{
  int low;
  int high;
};
typedef struct Interval Interval;

// Definition of Binary Search Tree Node
struct BSTNode{
  BSTNode* parent;
  BSTNode* leftChild;
  BSTNode* rightChild;
  Interval key;
  int maxRightHigh;   // To store the maximum value of high in it's right subtree
  int maxLeftHigh;   // To store the maximum value of high in it's left subtree
};
typedef struct BSTNode BSTNode;

// Check if a BSTNode is a leaf
bool isLeaf(BSTNode* node){
  if(node->leftChild == NULL && node->rightChild == NULL){
    return 1;
  }
  return 0;
}

// check if two intervals overlap
bool checkOverlap(Interval i1, Interval i2){
  if( (i1.high < i2.low) || (i1.low > i2.high) ){
    return 0;
  }
  return 1;
}

// Custom max function of 3 arguments
int customMax(int a, int b , int c){
  return max(max(a,b),c);
}

// Delete a node in BST
void deleteInBST(BSTNode** root, BSTNode* toDelete){
  if(toDelete->leftChild == NULL){
    if(toDelete->parent == NULL){
      *root = toDelete->rightChild;
      if(*root)
        (*root)->parent = NULL;
    }
    else if(toDelete == toDelete->parent->leftChild){
      toDelete->parent->leftChild = toDelete->rightChild;
      if(toDelete->rightChild)
        toDelete->rightChild->parent = toDelete->parent;
      BSTNode* tempParent = toDelete->parent;
      free(toDelete);
      while(tempParent!=NULL){

        if(tempParent->leftChild){
          tempParent->maxLeftHigh = customMax(tempParent->leftChild->maxLeftHigh, tempParent->leftChild->maxRightHigh, (tempParent->leftChild->key).high);
        }
        else{
          tempParent->maxLeftHigh = INT_MIN;
        }

        if(tempParent->rightChild){
          tempParent->maxRightHigh = customMax(tempParent->rightChild->maxLeftHigh, tempParent->rightChild->maxRightHigh, (tempParent->rightChild->key).high);
        }
        else{
          tempParent->maxRightHigh = INT_MIN;
        }
        tempParent=tempParent->parent;
      }
    }
    else{
      toDelete->parent->rightChild = toDelete->rightChild;
      if(toDelete->rightChild)
        toDelete->rightChild->parent = toDelete->parent;
      BSTNode* tempParent = toDelete->parent;
      free(toDelete);
      while(tempParent!=NULL){

        if(tempParent->leftChild){
          tempParent->maxLeftHigh = customMax(tempParent->leftChild->maxLeftHigh, tempParent->leftChild->maxRightHigh, (tempParent->leftChild->key).high);
        }
        else{
          tempParent->maxLeftHigh = INT_MIN;
        }

        if(tempParent->rightChild){
          tempParent->maxRightHigh = customMax(tempParent->rightChild->maxLeftHigh, tempParent->rightChild->maxRightHigh, (tempParent->rightChild->key).high);
        }
        else{
          tempParent->maxRightHigh = INT_MIN;
        }
        tempParent=tempParent->parent;
      }
    }
  }
  else if(toDelete->rightChild == NULL){
    if(toDelete->parent == NULL){
      *root = toDelete->leftChild;
      (*root)->parent = NULL;
    }
    else if(toDelete == toDelete->parent->leftChild){
      toDelete->parent->leftChild = toDelete->leftChild;
      toDelete->leftChild->parent = toDelete->parent;
      BSTNode* tempParent = toDelete->parent;
      free(toDelete);
      while(tempParent!=NULL){

        if(tempParent->leftChild){
          tempParent->maxLeftHigh = customMax(tempParent->leftChild->maxLeftHigh, tempParent->leftChild->maxRightHigh, (tempParent->leftChild->key).high);
        }
        else{
          tempParent->maxLeftHigh = INT_MIN;
        }

        if(tempParent->rightChild){
          tempParent->maxRightHigh = customMax(tempParent->rightChild->maxLeftHigh, tempParent->rightChild->maxRightHigh, (tempParent->rightChild->key).high);
        }
        else{
          tempParent->maxRightHigh = INT_MIN;
        }
        tempParent=tempParent->parent;
      }
    }
    else{
      toDelete->parent->rightChild = toDelete->leftChild;
      toDelete->leftChild->parent = toDelete->parent;
      BSTNode* tempParent = toDelete->parent;
      free(toDelete);
      while(tempParent!=NULL){

        if(tempParent->leftChild){
          tempParent->maxLeftHigh = customMax(tempParent->leftChild->maxLeftHigh, tempParent->leftChild->maxRightHigh, (tempParent->leftChild->key).high);
        }
        else{
          tempParent->maxLeftHigh = INT_MIN;
        }

        if(tempParent->rightChild){
          tempParent->maxRightHigh = customMax(tempParent->rightChild->maxLeftHigh, tempParent->rightChild->maxRightHigh, (tempParent->rightChild->key).high);
        }
        else{
          tempParent->maxRightHigh = INT_MIN;
        }
        tempParent=tempParent->parent;
      }
    }
  }
  else{
    BSTNode* nextDelete = toDelete->rightChild;
    while(nextDelete->leftChild){
      nextDelete = nextDelete->leftChild;
    }
    toDelete->key = nextDelete->key ;
    deleteInBST(root, nextDelete);
  }
}

// Constructing a new node with given interval value
BSTNode* createNode(BSTNode* parent, Interval val){
  BSTNode* temp = new BSTNode;
  temp->key = val;
  temp->parent = parent;
  temp->leftChild = NULL;
  temp->rightChild = NULL;
  temp->maxRightHigh = INT_MIN;
  temp->maxLeftHigh = INT_MIN;
  return temp;
}

// Declaration of Binary Search Tree Class
class BST {
private:
  bool empty;
public:
  BSTNode* root;
  BST();                                                          // Constructor function for Binary Search Tree
  bool isEmpty();                                                 // check if BST is empty
  void setRoot(Interval val);                                     // set the root of a BST
  BSTNode* findInterval(BSTNode* root, Interval val, bool lowFlag, bool checkOnlyOne);    // Finds and return the pointer to the val Interval if it exists, else return NULL
  void insertNode(BSTNode* root, Interval val, bool lowFlag);          // Function to insert a key in BST
  void deleteNode(BSTNode* root, Interval val, bool lowFlag);          // Function to delete a key in BST
  Interval getMin(BSTNode* root);                        // Function to return minimum interval ranked by key value of intervals
  Interval getMax(BSTNode* root);                        // Function to return maximum interval ranked by key value of intervals
  Interval successor(BSTNode* root, Interval val, bool lowFlag);       // Function to return succesor by key field
  bool isOverlap(BSTNode* root, Interval val);           // Function to check if an interval overlap with any interval in the tree
  void printBSTFromRoot(BSTNode* root);                  // Printing the binary tree -> for debugging purposes
};

// Main function
int main(){
    int t;
    cin>>t;
    while(t--){
        BST* lowT = new BST;  // for mantaining bst prop by lo field
        BST* highT = new BST; // for mantaining bst prop by hi field
        int q;
        cin>>q;
        while(q--){
          string inp;
          cin>>inp;

          if(inp[0]=='+'){
            Interval val;
            cin>>val.low;
            cin>>val.high;

            if(lowT->isEmpty()){
              lowT->setRoot(val);
              highT->setRoot(val);
            }
            else{
              lowT->insertNode(lowT->root, val, 1);
              highT->insertNode(highT->root, val, 0);
            }
            // lowT->printBSTFromRoot(lowT->root);
            // highT->printBSTFromRoot(highT->root);
          }
          else if(inp[0]=='-'){
            Interval val;
            cin>>val.low;
            cin>>val.high;
            if(!(lowT->isEmpty())){
              lowT->deleteNode(lowT->root, val, 1);
              highT->deleteNode(highT->root, val, 0);
            }
          }
          else if(inp=="min"){
              if(lowT->isEmpty()){
                  continue;
              }
            Interval res = lowT->getMin(lowT->root);
            cout<<"["<<res.low<<" "<<res.high<<"]"<<endl;
          }
          else if(inp=="max"){
              if(highT->isEmpty()){
                  continue;
              }
            Interval res = highT->getMax(highT->root);
            cout<<"["<<res.low<<" "<<res.high<<"]"<<endl;
          }
          else if(inp=="lsucc"){
            Interval val;
            cin>>val.low;
            cin>>val.high;
            Interval res = lowT->successor(lowT->root, val, 1);
            if(res.low == INT_MIN){
              cout<<"INVALID\n";
            }
            else{
              cout<<"["<<res.low<<" "<<res.high<<"]"<<endl;
            }
          }
          else if(inp=="hsucc"){
            Interval val;
            cin>>val.low;
            cin>>val.high;
            Interval res = highT->successor(highT->root, val, 0);
            if(res.high == INT_MIN){
              cout<<"INVALID\n";
            }
            else{
              cout<<"["<<res.low<<" "<<res.high<<"]"<<endl;
            }
          }
          else if(inp=="overlap"){
            Interval val;
            cin>>val.low;
            cin>>val.high;
            cout<<lowT->isOverlap(lowT->root, val)<<endl;
          }
        }
    }
    return 0;
}

// Definition of BST's member functions
// Constructor of BST class
BST::BST(){
  this->empty = true;
  this->root = NULL;
}

// check if BST is empty
bool BST::isEmpty(){
  if(this->root == NULL){
    this->empty = true;
  }
  else
    this->empty = false;
  return this->empty;
}

// set the root of a BST
void BST::setRoot(Interval val){
  if(this->isEmpty()){
    this->root = createNode(NULL, val);
    this->empty = false;
  }
}

// Function to insert a key in BST
void BST::insertNode(BSTNode* root, Interval val, bool lowFlag){
  if(lowFlag){
    if(isLeaf(root)){
      if(val.low < (root->key).low){
        root->leftChild = createNode(root, val);
        root->maxLeftHigh = val.high;
      }
      else{
        root->rightChild = createNode(root, val);
        root->maxRightHigh = val.high;
      }
    }
    else{
      if(val.low < (root->key).low){
        if(root->leftChild != NULL){
            insertNode(root->leftChild, val, lowFlag);
            root->maxLeftHigh = max(max(root->leftChild->maxLeftHigh,root->leftChild->maxRightHigh), (root->leftChild->key).high) ;
        }
        else{
            root->leftChild = createNode(root, val);
            root->maxLeftHigh = (root->leftChild->key).high;
        }
      }
      else{
        if(root->rightChild != NULL){
            insertNode(root->rightChild, val, lowFlag);
            root->maxRightHigh = max(max(root->rightChild->maxLeftHigh,root->rightChild->maxRightHigh), (root->rightChild->key).high) ;
        }
        else{
          root->rightChild = createNode(root, val);
          root->maxRightHigh = (root->rightChild->key).high;
        }
      }
    }
  }
  else{
    if(isLeaf(root)){
      if(val.high < (root->key).high){
        root->leftChild = createNode(root, val);
        root->maxLeftHigh = val.high;
      }
      else{
        root->rightChild = createNode(root, val);
        root->maxRightHigh = val.high;
      }
    }
    else{
      if(val.high < (root->key).high){
        if(root->leftChild != NULL){
            insertNode(root->leftChild, val, lowFlag);
            root->maxLeftHigh = max(max(root->leftChild->maxLeftHigh,root->leftChild->maxRightHigh), (root->leftChild->key).high) ;
        }
        else{
            root->leftChild = createNode(root, val);
            root->maxLeftHigh = (root->leftChild->key).high;
        }
      }
      else{
        if(root->rightChild != NULL){
            insertNode(root->rightChild, val, lowFlag);
            root->maxRightHigh = max(max(root->rightChild->maxLeftHigh,root->rightChild->maxRightHigh), (root->rightChild->key).high) ;
        }
        else{
          root->rightChild = createNode(root, val);
          root->maxRightHigh = (root->rightChild->key).high;
        }
      }
    }
  }
}

// Printing the binary tree -> for debugging purposes
void BST::printBSTFromRoot(BSTNode* root){
  if(root == NULL){
    return ;
  }
  cout<<(root->key).low<<","<<(root->key).high<<"-"<<(root->maxRightHigh);
  cout<<endl;
  printBSTFromRoot(root->leftChild);
  printBSTFromRoot(root->rightChild);
  cout<<endl;
}

// Function to return minimum interval ranked by lower value of intervals
Interval BST::getMin(BSTNode* root){
  if(root->leftChild == NULL){
    return root->key;
  }
  return getMin(root->leftChild);
}

// Function to return maximum interval ranked by key value of intervals
Interval BST::getMax(BSTNode* root){
  if(root->rightChild == NULL){
    return root->key;
  }
  return getMax(root->rightChild);
}

// Finds and return the pointer to the val Interval if it exists, else return NULL
BSTNode* BST::findInterval(BSTNode* root, Interval val, bool lowFlag,  bool checkOnlyOne){
  if(root == NULL){
    return NULL;    // Not found the interval
  }
  if(lowFlag){
    if(val.low < (root->key).low){
      return findInterval(root->leftChild, val, lowFlag, checkOnlyOne);
    }
    else if(val.low > (root->key).low){
      return findInterval(root->rightChild, val, lowFlag, checkOnlyOne);
    }
    else{

      if(checkOnlyOne){
          return root;
      }

      if(val.high == (root->key).high){
        return root;
      }
      else{
        return NULL;  // Not found the interval
      }
    }
  }
  else{
    if(val.high < (root->key).high){
      return findInterval(root->leftChild, val, lowFlag, checkOnlyOne);
    }
    else if(val.high > (root->key).high){
      return findInterval(root->rightChild, val, lowFlag, checkOnlyOne);
    }
    else{
      if(checkOnlyOne){
          return root;
      }

      if(val.low == (root->key).low){
        return root;
      }
      else{
        return NULL;  // Not found the interval
      }
    }
  }
}

// Function to return succesor by key field
Interval BST::successor(BSTNode* root, Interval val, bool lowFlag){
  BSTNode* temp = findInterval(root, val, lowFlag, 1);
  if(temp==NULL){
    Interval res;
    res.low = INT_MIN;
    res.high = INT_MIN;
    return res;
  }
  if((temp->rightChild)!=NULL){
    return getMin(temp->rightChild);
  }
  else{
    BSTNode* tempParent = temp->parent;
    while(((tempParent!=NULL) && (tempParent->rightChild!=NULL)) && (tempParent->rightChild == temp)){
      temp = tempParent;
      tempParent = temp->parent;
    }
    if(tempParent == NULL){
      Interval res;
      res.low = INT_MIN;
      res.high = INT_MIN;
      return res;
    }
    return tempParent->key;
  }
}

// Function to check if an interval overlap with any interval in the tree
bool BST::isOverlap(BSTNode* root, Interval val){
  while (root!=NULL && !(checkOverlap(root->key, val))){
    if(root->leftChild){
      int leftMax = max(max(root->leftChild->maxLeftHigh , root->leftChild->maxRightHigh), (root->leftChild->key).high);
      if(leftMax >= val.low)
        root = root->leftChild;
      else
        root=root->rightChild;
    }
    else{
      root=root->rightChild;
    }
  }
  if(root==NULL){
    return 0;
  }
  return 1;
}

void BST::deleteNode(BSTNode* root, Interval val, bool lowFlag){
  BSTNode* temp = findInterval(root, val, lowFlag, 0);
  if(temp){
    deleteInBST(&(this->root), temp);
  }
}
