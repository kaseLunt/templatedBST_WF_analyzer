/*

Author: Kase Lunt

Date:   7/7/21

Description: This is the header file for a templated binary search tree, including all the associated method templates.

*/

#pragma once
#ifndef TEMPLATEDBST_H
#define TEMPLATEDBST_H

#include <iostream>
#include <array>
#include <string>


// small class which holds the words and a count of number of occurrences of that word
class WordEntry
{
    std::string word;
    int count;

    public:
        WordEntry(std::string inputWord)
        {
            word = inputWord;
            count = 1;
        }
        void increaseCount()
        {
            count++;
        }
        int getCount()
        {
            return count;
        }
        std::string getWord()
        {
            return word;
        }
};


/****************************************************************************************
                                 Templated BST Node CLass
 ****************************************************************************************/

template<typename T>
class BSTNode
{
        T data;
        BSTNode* left;
        BSTNode* right;
    public:
        WordEntry* word;


/***************************************
                Interface
****************************************/
    public:
        // constructor / destructor
        BSTNode( T data );
        ~BSTNode();

        // getters and setters
        T getData();
        BSTNode* getLeft();
        BSTNode* getRight();

        void setData( T data );
        void setLeft( BSTNode* left );
        void setRight( BSTNode* right );
};

/****************************************************************************************
                                 Templated BST Class
 ****************************************************************************************/

template<typename T>
class BST_T
{
    private:
        BSTNode<T>* root;
        int size();
        std::vector<T>* vector;

    
        // private versions of interface methods                     
        BSTNode<T>* insert( T data, BSTNode<T>* root );
        BSTNode<T>* remove( T data, BSTNode<T>* root );
        public:
        BSTNode<T>* find( T data, BSTNode<T>* root );
        bool elementExists( T data, BSTNode<T>* root );

        // helper methods
        BSTNode<T>* findMin( BSTNode<T>* root );
        BSTNode<T>* findMax( BSTNode<T>* root );
    


/***************************************
            Interface methods
****************************************/

    public:
        // constructor / destructor
        BST_T();
        ~BST_T();

        BSTNode<T>* getRoot();
        BSTNode<T>* insert( T data );
        void remove( T data );
        BSTNode<T>* find( T data );
        void empty( BSTNode<T>* root );
      
        
        bool elementExists( T data );
        void inOrder( BSTNode<T>* root );
        std::vector<T>* toArray( BSTNode<T>* root, std::vector<T>* vector );
        std::vector<T>* toArray( BSTNode<T>* root );

};


/****************************************************************************************
                            Node Class method imlementations
 ****************************************************************************************/

// default constructor
template<typename T> BSTNode<T>::BSTNode( T data )
{
    this->data = data;
    this->word = NULL;
    this->left = NULL;
    this->right = NULL;
}

// constructor which executes if parameter is string data
template<> BSTNode<std::string>::BSTNode( std::string data )
{
    this->data = data;
    this->word = new WordEntry(data);
    this->left = NULL;
    this->right = NULL;
}

template<typename T> BSTNode<T>::~BSTNode()
{

}

// getters and setters
template<typename T> T BSTNode<T>::getData()
{
    return this->data;
}


template<typename T> BSTNode<T>* BSTNode<T>::getLeft()
{
    return this->left;
}

template<typename T> BSTNode<T>* BSTNode<T>::getRight()
{
    return this->right;
}

template<typename T> void BSTNode<T>::setData( T data )
{
    this->data = data;
}

template<typename T> void BSTNode<T>::setLeft( BSTNode* left )
{
    this->left = left;
}

template<typename T> void BSTNode<T>::setRight( BSTNode* right )
{
    this->right = right;
}


/****************************************************************************************
                            BST Class method implementations
 ****************************************************************************************/

// constructor
template<typename T> BST_T<T>::BST_T()
{
    root = NULL;
    vector = new std::vector<T>;
}

// destructor
template<typename T> BST_T<T>::~BST_T()
{
    this->empty( this->getRoot() );
    delete vector;
    std::cout << "tree deleted. ";
}

// accessor for private root
template<typename T> BSTNode<T>* BST_T<T>::getRoot()
{
    return this->root;
}

// traverse in order and print the tree
template<typename T> void BST_T<T>::inOrder( BSTNode<T>* root )
{
    if( root == NULL )
    {
        return;
    }
    inOrder( root->getLeft() );
    std::cout << root->getData() << std::endl;
    inOrder( root->getRight() );
}

// traverse post order, delete every node
template<typename T> void BST_T<T>::empty( BSTNode<T>* root )
{
    if( root == NULL )
    {
        return;
    }
    empty( root->getLeft() );
    empty( root->getRight() );
    delete root;
    
}

template<typename T> std::vector<T>* BST_T<T>::toArray( BSTNode<T>* root, std::vector<T>* vector )
{
    if( root == NULL )
    {
        return vector;
    }
    toArray( root->getLeft(), vector );
    vector->push_back( root->getData() );
    toArray( root->getRight(), vector );
    return vector;
}

template<typename T> std::vector<T>* BST_T<T>::toArray( BSTNode<T>* root )
{
    vector = BST_T<T>::toArray( root, vector );
    return vector;
}

// default insert method ( T data, node pointer )
template<typename T> BSTNode<T>* BST_T<T>::insert( T data, BSTNode<T>* root ) 
{
    if( root == NULL ) // tree is empty
    {
        // create a new node of type T
        root = new BSTNode<T>( data );
        std::cout << "successfully inserted " << data << "\n";
    } 
    else if( data < root->getData() ) // less than goes left
    {
        root->setLeft( insert( data, root->getLeft() ) );
    }
    else if( data > root->getData() )
    {
        root->setRight( insert( data, root->getRight() ) );
    }
    return root;
}

// public insert method, no root in parameter
template<typename T> BSTNode<T>* BST_T<T>::insert( T data )
{
    // call private insert method, pass in and update root
    this->root = BST_T::insert( data, this->root );
    return root;
}



/*********************************** **********************************************/
//


// remove an element from the list, private. returns pointer to root
template<typename T> BSTNode<T>* BST_T<T>::remove( T data, BSTNode<T>* root )
{
    // base case 
    if( root == NULL )
    {
        return root;
    }
    else if( data < root->getData() )
    {
        root->setLeft( remove( data, root->getLeft() ) );
    }
    else if( data > root->getData() )
    {
        root->setRight( remove( data, root->getRight() ) );
    }
    else // we found it
    {
        // case 1 : no child
        if( root->getLeft() == NULL && root->getRight() == NULL)
        {
            delete root;
            root = NULL;
            return root;
        }
        // case 2 : one child
        else if( root->getLeft() == NULL )
        {
            BSTNode<T>* temp = root;
            root = root->getRight();
            delete temp;
        }
        else if( root->getRight() == NULL )
        {
            BSTNode<T>* temp = root;
            root = root->getLeft();
            delete temp;
        }
        // case 3 : two children
        else
        {
            // find the minimum of the right subtree, or inorder successor of target node
            BSTNode<T>* temp = findMin( root->getRight() );
            // set the data in target node = to data in successor
            root->setData( temp->getData() );
            // recursively call remove on right subtree
            root->setRight( BST_T::remove( root->getData(), temp->getRight() ));
        }
    }
    return root;
}

// remove an element from the list, public 
template<typename T> void BST_T<T>::remove( T data )
{   
    // call private remove method, pass in and update root
    this->root = remove( data, this->root );
}



// insert method called when passed a string as data type
template<> BSTNode<std::string>* BST_T<std::string>::insert( std::string data, BSTNode<std::string>* root ) 
{
    if( root == NULL ) // tree is empty
    {
        // create a new node of type string
        root = new BSTNode<std::string>( data );
    } 
    else if( data < root->word->getWord() ) // less than goes left
    {
        root->setLeft( insert( data, root->getLeft() ) );
    }
    else if( data == root->word->getWord() ) // word already exists in tree, increase count
    {
        root->word->increaseCount();
    }
    else if( data > root->word->getWord() )
    {
        root->setRight( insert( data, root->getRight() ) );
    }
    return root;
}

// public insert function, no root parameter needed
template<> BSTNode<std::string>* BST_T<std::string>::insert( std::string data )
{
    root = insert( data, this->getRoot() );
    std::cout << "calling string's insert function \n";
    return root;
} 

// returns true if the target data exists in the tree
template<typename T> bool BST_T<T>::elementExists( T data , BSTNode<T>* root)
{
    if( root == NULL ) // tree is empty
    {
        return false;
    }
    else if( data < root->getData() )
    {
        return elementExists( data, root->getLeft() );
    }
    else if( data == root->getData() )
    {
        return true;
    }
    else
    {
        return elementExists( data, root->getRight() ); 
    }
}

// public elementExists which doesnt require root parameter
template<typename T> bool BST_T<T>::elementExists( T data )
{
    return BST_T::elementExists( data, this->root );
}

 //returns a pointer to the node with matching data, if it exists
template<typename T> BSTNode<T>* BST_T<T>::find( T data , BSTNode<T>* root)
{
    if( root == NULL ) // tree is empty
    {
        return NULL;
    } 
    else if( data < root->getData() && root->getLeft() != NULL ) // if data 
    {
        return find( data, root->getLeft() );
    }
    else if( data == root->getData() ) // found the word
    {
        return root;
    }
    else if( data > root->getData() && root->getRight() != NULL )
    {
        return find( data, root->getRight() );
    }
    return NULL;
}


template<typename T> BSTNode<T>* BST_T<T>::find( T data )
{
    return BST_T::find( data, this->getRoot() );
}

// find minimum item in the tree and return a pointer to it
template<typename T> BSTNode<T>* BST_T<T>::findMin( BSTNode<T>* root )
{
    if( root == NULL )
    {
        return NULL;
    }
    else if( root->getLeft() == NULL )
    {
        return root;
    }
    // search left subtree
    return findMin( root->getLeft() );
}

// find max in the tree and return pointer to it
template<typename T> BSTNode<T>* BST_T<T>::findMax( BSTNode<T>* root )
{
    if( root == NULL )
    {
        return NULL;
    }
    else if( root->getRight() == NULL )
    {
        return root;
    }
    // search left subtree
    return findMin( root->getRight() );
}


#endif