// Write your program here

#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;


struct HuffmanNode{
    char c;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode(int freq, char c = '\0'){
        this->c = c;
        this->freq = freq;
    }
};

struct node{
    HuffmanNode *huffmanNode;
    node* next;
    node(HuffmanNode *&huffmanNode){
        this->huffmanNode = huffmanNode;
        next = nullptr;
    }
};

class PrioQueue{
private:
  node* top;
  int size;
public:
  PrioQueue(){
    top = nullptr;
    size = 0;
  }

  void push(HuffmanNode*& huffmanNode){
    node* n = new node(huffmanNode);
    size++;
    if(top == nullptr)
      top = n;

    else{
      node* curr = top;
      node* temp = nullptr;
      while(curr != nullptr && huffmanNode->freq >= curr->huffmanNode->freq){
        temp = curr;
        curr = curr->next;
      }
      //end of list
      if(curr == nullptr){
        temp->next = n;
      }

      //inserting at the beginning
      else if(curr == top){
        n->next = top;
        top = n;
      }
      //inserting at the middle of the list
      else{
        temp->next = n;
        n->next = curr;
      }

    }
  }

    HuffmanNode* getTop(){
        return top->huffmanNode;
    }

    int pop(){
        size--;
        node* curr= top;
        top = top->next;
        return curr->huffmanNode->freq;
      }
    int getSize(){
        return size;
    }
};



struct HuffmanNodeComparison
{
   bool operator()( const HuffmanNode* a, const HuffmanNode* b ) const
   {
    return a->freq > b->freq;
   }
};

void print_leaf_nodes(HuffmanNode* root, string &code){
    if(root == nullptr){
        return;
    }

    if(root->left == nullptr && root->right == nullptr){
        cout << "Symbol: " << root->c <<
        ", Frequency: " << root->freq <<
        ", Code: " << code;
        return;
    }
    if(root->left){
        code.append(1, '0');
        print_leaf_nodes(root->left, code);
    }

    if(root->right){
        code.append(1, '1');
        print_leaf_nodes(root->right, code);
    }
}

int main(){

    ifstream input;
    string line;

    //HuffmanTree tree;
    char c;
    int freq;

    //priority_queue<HuffmanNode*, vector<HuffmanNode*>, HuffmanNodeComparison> q;
    PrioQueue q;
    input.open("input.txt");

    while(input >> c >> freq){
        HuffmanNode *node = new HuffmanNode(freq, c);
        cout << "Added: " << node->freq << endl;
        q.push(node);
    }

    cout << "Top: " << q.getTop()->freq << endl;
    int x = 0;
    while(q.getSize() > 1){

        HuffmanNode *leftNode = q.getTop();
        cout << "Popped: " << leftNode->freq << endl;
        q.pop();

        HuffmanNode *rightNode = q.getTop();
        cout << "Popped: " << rightNode->freq << endl;
        q.pop();

        HuffmanNode *root = new HuffmanNode(leftNode->freq + rightNode->freq);
        root->left = leftNode;
        cout << "root->left->freq: " << root->left->freq << endl;
        root->right = rightNode;
        cout << "root->right->freq: " << root->right->freq << endl;
        q.push(root);
        //cout << "q.top-directaccess " << root->left->freq << endl;
        cout << "q.top-indirectaccess " << q.getTop()->left->freq << endl;
        x++;

    }
    //cout << "root: " << q.getTop()->c << (q.getTop()->freq);
}
