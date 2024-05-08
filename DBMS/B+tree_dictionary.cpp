#include<bits/stdc++.h>
using namespace std;

int numPointers, numkeys; //numkeys= numPointers-1
int jumps= 0; //the number of hops needed to find a word

struct Node
{
int numCurrentKeys;
Node *parent, *next;
Node **nodePointers; // array of node pointers
bool isLeaf;
string *words, *meanings; // array of words and their meanings
};

Node *root;

Node *createNewNode() // creates a new node 
{
    Node *newNode = new Node();
    newNode-> numCurrentKeys=0;
    newNode-> parent= nullptr;
    newNode-> next = nullptr;
    newNode-> nodePointers= new Node *[numPointers +1]; //
    for(int i=0; i<numPointers; i++)
    {
        newNode->nodePointers[i]= nullptr; //initializing node pointers as null
    }

    newNode->isLeaf= true;
    newNode->words= new string [numkeys+1];
    newNode-> meanings= new string [numkeys+1];

    return newNode;
}

void updateRootNode(Node *node, Node* leftChild, Node* rightChild, string word) // creating a new root by splitting the existing root in two as left child and right child
{
    node= createNewNode();
    node-> isLeaf= false;
    node-> words[0]= word;
    node->numCurrentKeys++;
    node->nodePointers[0]= leftChild;
    node-> nodePointers[1]= rightChild;
    leftChild-> parent= node;
    rightChild-> parent= node;
    root =  node;
}

Node *searchInsertionNode(Node *node, string word) //searching the correct node to insert a new value
{
    while(!node-> isLeaf)
    {
        int i;
        for(i=0; i<node->numCurrentKeys; i++)
        {
            if(word < node->words[i]) break;
        }
        node= node->nodePointers[i];
        jumps++;
    }
    return node;
}

void mergeWithParent(Node *parent, Node *rightChild, string word)
{
    int parent_keyIndex= parent-> numCurrentKeys-1;

    while(parent_keyIndex > -1)
    {
        if(parent->words[parent_keyIndex] <= word)
        break;
        else{ //right shifting existing key to make space if the new key is smaller
            parent->words[parent_keyIndex+1]= parent->words[parent_keyIndex];
            parent->nodePointers[parent_keyIndex+2]= parent->nodePointers[parent_keyIndex+1];
        }
        parent_keyIndex--;
    }

    // inserting the new key at the right position
    parent->words[parent_keyIndex+1]= word;
    parent->nodePointers[parent_keyIndex+2]= rightChild;
    parent->numCurrentKeys++;
}

void shiftUp(Node *parent, Node* leftChild, Node *rightChild, string word)
{
    if(parent == nullptr)
    {
        updateRootNode(parent, leftChild, rightChild, word);
        return;
    }

    rightChild->parent= parent;
    mergeWithParent(parent, rightChild, word);

    if(parent->numCurrentKeys == numPointers) // overflow
    {
        // overflow -> have to split parent node
        Node *splitNode= createNewNode();
        splitNode->isLeaf= false; // intermediate node

        int totalKeys= parent->numCurrentKeys, splitNode_index=0;
        for(int i= totalKeys-(numPointers/2); i<numPointers; i++)
        {
            splitNode->words[splitNode_index]= parent->words[i];

            if(splitNode_index==0) // inserting the left pointer for the new intermediate node
            {
                splitNode->nodePointers[0]= parent->nodePointers[i];
                splitNode->nodePointers[0]->parent= splitNode;
            }

            // inserting the right nodes
            splitNode->nodePointers[splitNode_index+1]= parent->nodePointers[i+1];
            splitNode->nodePointers[splitNode_index+1]->parent= splitNode;
            splitNode_index++;
        }
        splitNode->numCurrentKeys = totalKeys/2;
        parent -> numCurrentKeys -= (totalKeys/2);
        shiftUp(parent->parent, parent, splitNode, parent->words[parent->numCurrentKeys-1]);
    }
}

void insertNewWord(string word, string meaning)
{
    Node *insertionNode= searchInsertionNode(root, word);
    int keyIndex= insertionNode->numCurrentKeys-1;

    while(keyIndex > -1)
    {
        if(word < insertionNode->words[keyIndex])
        {
            insertionNode->words[keyIndex+1]= insertionNode->words[keyIndex]; // right shiting the keys greater than word
            insertionNode->meanings[keyIndex+1]= insertionNode->meanings[keyIndex];
        }
        else break;
        keyIndex--;
    }

    insertionNode->words[keyIndex+1]= word;
    insertionNode->meanings[keyIndex+1]= meaning;
    insertionNode->numCurrentKeys++;

    if(insertionNode-> numCurrentKeys == numPointers) // = numkeys+1
    {
        Node *splitNode= createNewNode(); // creating a new node to split the original node in two
        int totalKeys= insertionNode->numCurrentKeys, splitNode_index=0; // replace totalkeys with keyIndex
        for(int i= totalKeys- (numPointers/2); i<numPointers; i++) // at this point numPointers = numCurrentKeys
        {
            splitNode->words[splitNode_index]= insertionNode->words[i];
            splitNode->meanings[splitNode_index]= insertionNode->meanings[i];
            splitNode_index++;
        }

        splitNode->numCurrentKeys = numPointers/2;
        insertionNode->numCurrentKeys -= (numPointers/2);

        splitNode->next = insertionNode->next;
        insertionNode->next= splitNode;
        shiftUp(insertionNode->parent, insertionNode, splitNode, word); //balancing with the parent node 
    }
}

bool buildTree()
{
    string word, meaning;
    root= createNewNode();

    ifstream file;
    file.open("dictionary.txt");

    if(!file)
    {
        cout << "Failed to open file" << endl;
        return false;
    }

    else{
        while( file >> word)
        {
            getline(file, meaning);
            insertNewWord(word, meaning);
        }

        file.close();
    }
    
    cout << "read successfully" << endl;
    return true;
}

void search_word_meaning()
{
  //  bool flag= true;
    while(true)
    {
        cout << "Enter x to terminate" << endl;
        cout << "Enter a word: ";
        string word;
        cin >> word;

        for(int i=0; i<word.size(); i++)
        {
            word[i]= tolower(word[i]);
        }

        if(word == "x")
        {
            cout << "Terminated successfully!" << endl;
            return;
        }

        jumps=0;

        Node *leaf= searchInsertionNode(root, word);
        int i;

        for(i=0; i<leaf->numCurrentKeys; i++)
        {
            if(leaf->words[i]== word) break;
        }

        if(i== leaf->numCurrentKeys) 
            cout << "Sorry! No such word found!" << endl;
        else
            cout << endl << word << " -" << leaf->meanings[i] << endl << endl;
        cout << "Number of hops= " << jumps << endl << endl;
    }
}

int main()
{
    cout << "Enter the number of pointers: ";
    cin >> numPointers;
    numkeys = numPointers-1;

    if(buildTree()) cout << "Tree has been built successfully!" << endl << endl;
    else 
    {
        cout << "Failed to built the tree" << endl;
        exit(1);
    }

    search_word_meaning();
    return 0;
}