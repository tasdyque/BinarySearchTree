
#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

template < typename DataType, class KeyType >    // DataType : tree data item
class BSTree                                     // KeyType : key field
{
public:

    /// <summary>
    /// Default Constructor
    /// </summary>
    BSTree();                    

    /// <summary>
    /// Copy Constructor
    /// </summary>
    /// <param name="other"></param>
    BSTree(const BSTree<DataType, KeyType>& other);   

    /// <summary>
    /// Overload assignment operator
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    BSTree& operator= (const BSTree<DataType, KeyType>& other);


   
    ~BSTree();

    /// <summary>
    /// Inserts a node into the tree with specified data item
    /// </summary>
    /// <param name="newDataItem"></param>
    void insert(const DataType& newDataItem);  

    /// <summary>
    /// Retrieves a data item in the tree with spcified key
    /// </summary>
    /// <param name="searchKey"></param>
    /// <param name="searchDataItem"></param>
    /// <returns></returns>
    bool retrieve(const KeyType& searchKey, DataType& searchDataItem);
  

    /// <summary>
    /// Removes a node in the tree with given data item
    /// </summary>
    /// <param name="deleteKey"></param>
    /// <returns></returns>
    bool remove(const KeyType& deleteKey);           


    /// <summary>
    /// Outputs all keys in the tree
    /// </summary>
    void writeKeys();                           

    /// <summary>
    /// Clears the tree
    /// </summary>
    void clear();                                


    /// <summary>
    /// Check if tree is empty
    /// </summary>
    /// <returns></returns>
    bool isEmpty() const;                        
    

    /// <summary>
    /// Outputs the tree structure
    /// </summary>
    void showStructure() const;

    /// <summary>
    /// Function returns height of the tree
    /// </summary>
    /// <returns></returns>
    int getHeight();                     

    /// <summary>
    /// Function returns count of the number of nodes in the tree
    /// </summary>
    /// <returns></returns>
    int getCount();	  



protected:

    /// <summary>
    /// Inner class: facilitator for the BSTree class
    /// </summary>
    class BSTreeNode                  
    {
    public:

        /// <summary>
        /// BSTreeNode Constructor
        /// </summary>
        /// <param name="nodeDataItem"></param>
        /// <param name="leftPtr"></param>
        /// <param name="rightPtr"></param>
        BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr);

        /// <summary>
        /// BSTreeNode Copy Constructor
        /// </summary>
        /// <param name="other"></param>
        BSTreeNode(const BSTreeNode& other);  

        /// <summary>
        /// BSTreeNode data member, data Item for the node
        /// </summary>
        DataType dataItem;    

        /// <summary>
        /// Data Items for the BSTreeNode, pointers to the left and right children of the Node
        /// </summary>
        BSTreeNode* left,    
                  * right;   
    };

    
    /// <summary>
    /// Recursive Helper function to help the showStructure function
    /// </summary>
    /// <param name="currentNode"></param>
    /// <param name="level"></param>
    void showHelper(BSTreeNode* currentNode, int level) const;

    /// <summary>
    /// Recursive Helper function to help the destructor
    /// </summary>
    /// <param name="currentNode"></param>
    void destructorHelper(BSTreeNode*& currentNode);

    /// <summary>
    /// Recursive Helper function to help the writeKeys function
    /// </summary>
    /// <param name="currentNode"></param>
    void writeKeysHelper(BSTreeNode* currentNode);

    /// <summary>
    /// Recursive Helper function to help the remove function
    /// </summary>
    /// <param name="currentNode"></param>
    /// <param name="deleteKey"></param>
    /// <returns></returns>
    bool removeHelper(BSTreeNode*& currentNode, const KeyType& deleteKey);


    /// <summary>
    /// Recursive Helper function to help the clear function
    /// </summary>
    /// <param name="rootNode"></param>
    void clearHelper(BSTreeNode*& rootNode);


    /// <summary>
    /// Recursive Helper function to help the getCount function
    /// </summary>
    /// <param name="currentNode"></param>
    /// <returns></returns>
    int getCountHelper(BSTreeNode* currentNode);

    /// <summary>
    /// recursive helper for the getHeight function
    /// </summary>
    /// <param name="currentNode"></param>
    /// <returns></returns>
    int getHeightHelper(BSTreeNode* currentNode);

    /// <summary>
    /// Recursive helper for the getHeightHelper function that finds the max height
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    int maxHeightHelper(int left, int right);

    /// <summary>
    /// Data memeber of BSTree Class, pointer to the root node 
    /// </summary>
    BSTreeNode* root;   
};

#endif	// define BSTREE_H