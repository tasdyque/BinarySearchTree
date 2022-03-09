#pragma once
#include "BSTree.h"
#include <iostream>
using namespace std;

/// <summary>
/// BSTreeNode constructor
/// 
/// precondition: node is uninitialized
/// postcondition: node is initialized with arguments
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="nodeDataItem"></param>
/// <param name="leftPtr"></param>
/// <param name="rightPtr"></param>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	this->dataItem = nodeDataItem;
	this->dataItem.setKey(nodeDataItem.getKey());
	this->left = leftPtr;
	this->right = rightPtr;
}

/// <summary>
/// BSTreeNode copy constructor
/// 
/// precondition: node is uninitialized
/// postcondition: node is initialized with data from another node
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="other"></param>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const BSTreeNode& other)
{
	this->dataItem.setKey(other.dataItem.getKey());
	this->left = other.left;
	this->right = other.right;
}

/// <summary>
/// BSTree default constructor
/// 
/// precondition: root is uninitialized
/// postcondition: root is set to NULL
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
{
	root = NULL;
}

/// <summary>
/// BSTree copy constructor
/// 
/// precondition: root is uninitialized
/// postcondition: root is set to argument object root
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="other"></param>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{
	this->root = other.root;
}


/// <summary>
/// Assignment operator overload
/// 
/// precondition: root is not equal to the argument object
/// postcondition: root is equal to the argument object
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="other"></param>
/// <returns></returns>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator= (const BSTree<DataType, KeyType>& other)
{
	this->root = other.root;
}


/// <summary>
/// Helper to the BSTree destructor, deallocates the memory in the tree. Uses in-order recursive traversal
/// 
/// precondition: Tree has nodes
/// postcondition: Nodes in the tree are all deleted, and pointers are deallocated
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="ptr"></param>
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::destructorHelper(BSTreeNode*& ptr)
{

	if (ptr != NULL)
	{
		destructorHelper(ptr->left);
		destructorHelper(ptr->right);
		delete ptr;
	}

}


/// <summary>
/// BSTree Destructor, calls to the helper to deallcoate the memory
/// 
/// precondition: Tree has nodes
/// postcondition: Nodes in the tree are all deleted, and pointers are deallocated
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree()
{
	destructorHelper(root);
}


/// <summary>
/// Insert function adds a node with specified key. Uses in-order traversal
/// 
/// precondition: Node is not created
/// postcondition: Node is created and initialized, data item is set to specified value
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="newDataItem"></param>
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{

	bool set = false;

	if (this->root == NULL)
	{
		this->root = new BSTreeNode(newDataItem, NULL, NULL);
		

	}
	else
	{

		BSTreeNode* tempPtr = root;
		while (set == false)
		{
			if (newDataItem.getKey() < tempPtr->dataItem.getKey())
			{
				if (tempPtr->left != NULL)
				{
					tempPtr = tempPtr->left;
				}
				else
				{

					tempPtr->left = new BSTreeNode(newDataItem, NULL, NULL);
					set = true;
				}
			}
			else if (newDataItem.getKey() > tempPtr->dataItem.getKey())
			{
				if (tempPtr->right != NULL)
				{
					tempPtr = tempPtr->right;
				}
				else
				{
					tempPtr->right = new BSTreeNode(newDataItem, NULL, NULL);
					set = true;
				}

			}
			else if (newDataItem.getKey() == tempPtr->dataItem.getKey())
			{
				tempPtr->dataItem.setKey(newDataItem.getKey());
			}
			
		}
	}



}


/// <summary>
/// retrieve function searches the tree for a value and returns true if found. false if not found. 
/// Uses in-order traversal
/// </summary>
/// 
/// precondition: key is not found
/// postcondition: key is found and true is returned or it is not found and false is returned
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="searchKey"></param>
/// <param name="searchDataItem"></param>
/// <returns></returns>
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem)
{
	BSTreeNode* tempPtr = this->root;

	while (tempPtr != NULL)
	{
		if (searchKey < tempPtr->dataItem.getKey())
		{
			tempPtr = tempPtr->left;
		}
		else if (searchKey > tempPtr->dataItem.getKey())
		{
			tempPtr = tempPtr->right;
		}
		else if (searchKey == tempPtr->dataItem.getKey())
		{
			return true;
		}

	}
	return false;
}

/// <summary>
/// remove function Helper, deletes a node, searches tree using in-order recursive traversal
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="currentNode"></param>
/// <param name="deleteKey"></param>
/// <returns></returns>
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& currentNode, const KeyType& deleteKey)
{

	if (currentNode == NULL)
	{
		return false;
	}

	if (deleteKey == currentNode->dataItem.getKey())
	{
		if (currentNode->left == NULL && currentNode->right == NULL) /// no child
		{
			delete currentNode;
			currentNode = NULL;
			return true;
		}
		else if (currentNode->left != NULL && currentNode->right == NULL) ///one child
		{
			BSTreeNode* tempNode = currentNode;
			currentNode = currentNode->left;
			delete tempNode;
			return true;
		}
		else if (currentNode->right != NULL && currentNode->left == NULL)
		{
			BSTreeNode* tempNode = currentNode;
			currentNode = currentNode->right;
			delete tempNode;
			return true;
		}
		else if (currentNode->right != NULL && currentNode->left != NULL) ///two children
		{
			BSTreeNode* leftptr;
			BSTreeNode* rightptr;
			rightptr = currentNode->right;
			leftptr = currentNode->left;

		}
		else
		{
			return false;
		}
	}
	else
	{
		if (removeHelper(currentNode->left, deleteKey))
		{
			return true;
		}
		else
		{
			if (removeHelper(currentNode->right, deleteKey))
			{
				return true;

			}
			else
			{
				return false;
			}
		}


	}
	return false;
}

/// <summary>
/// remove function, calls to the helper, deletes a node, returns true if successful
/// </summary>
/// 
/// precondition: node is in the tree
/// postcondition: node is deleted from the tree or false is returned if not found
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="deleteKey"></param>
/// <returns></returns>
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	if (removeHelper(root, deleteKey))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Write Keys helper uses in order recursive traversal to output the keys
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="currentNode"></param>
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* currentNode)

{

	if (currentNode != NULL)
	{
		writeKeysHelper(currentNode->left);
		cout << currentNode->dataItem.getKey() << " ";
		writeKeysHelper(currentNode->right);
	}
	else
	{
		cout << " ";
	}

}


/// <summary>
/// Calls to the helper, inputs root and outputs all keys
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys()
{
	writeKeysHelper(root);
}


/// <summary>
/// function shows the structure of the tree using reverse in order traversal
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showStructure() const
{
	if (root == NULL)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

/// <summary>
/// recursive helper to the showstructure function
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="p"></param>
/// <param name="level"></param>
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode* p, int level) const

{
	int j;   // Loop counter

	if (p != NULL)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)    // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();   // Output key
		if ((p->left != NULL) &&           // Output "connector"
			(p->right != NULL))
			cout << "<";
		else if (p->right != NULL)
			cout << "/";
		else if (p->left != NULL)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}

/// <summary>
/// clear function deallocates all memory in the tree
/// 
/// precondition: tree has nodes
/// postcondition: all Nodes are deleted
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clear()
//Calls the recursive clearHelper function that clears the tree
{
	clearHelper(root);
	root = NULL;
}

/// <summary>
/// clear function Helper deallocates all memory in the tree, uses recursive in order traversal
/// 
/// precondition: tree has nodes
/// postcondition: all Nodes are deleted
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& currentNode)
//clears the tree
{
	if (currentNode != NULL)
	{
		clearHelper(currentNode->left);
		clearHelper(currentNode->right);
		delete currentNode;
	}
}


/// <summary>
/// checks if the tree is empty, returns true if it is
/// </summary>
/// 
/// 
/// precondition: tree is either empty or not empty
/// postcondition: true is returned if tree is not empty, false is returned if it is
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <returns></returns>
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
//function that displays if the tree is empty by checking the root node
{
	if (root == NULL)
		return true;
	else
		return false;
}

/// <summary>
/// Helper to the getcount function, counts the nodes using recursive in order traversal
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="currentNode"></param>
/// <returns></returns>
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* currentNode) 
{
	int count = 0;
	if (currentNode != NULL)
	{
		count = getCountHelper(currentNode->left) + getCountHelper(currentNode->right) + 1;
	}
	else
	{
		return 0;
	}

	return count;
}

/// <summary>
/// Counts the nodes in the tree
/// </summary>
/// 
/// 
/// precondition: count is 0
/// postcondition: count is equal to the number of nodes in the tree
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="currentNode"></param>
/// <returns></returns>
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCount()
{
	return getCountHelper(root);
	
}


/// <summary>
/// helper to the getHeightHelper that returns the max value between subtree levels
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="left"></param>
/// <param name="right"></param>
/// <returns></returns>
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::maxHeightHelper(int left, int right)
{
	if (left > right)
	{
		return left;
	}
	else if (left < right)
	{
		return right;
	}
	else if (left == right)
	{
		return left;
	}
	else
	{
		return 0;
	}
}


/// <summary>
/// Helper to the getHeight function that returns the number of levels in the tree
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <param name="currentNode"></param>
/// <returns></returns>
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* currentNode)
{
	if (currentNode == NULL)
	{
		return 0;
	}
	else
	{
		return maxHeightHelper(getHeightHelper(currentNode->left), getHeightHelper(currentNode->right)) + 1;
	}
}

/// <summary>
/// returns the number of levels in the tree
/// 
/// precondition: tree level is 0
/// postcondition: tree level is equal to number of levels in the BSTree
/// </summary>
/// <typeparam name="DataType"></typeparam>
/// <typeparam name="KeyType"></typeparam>
/// <returns></returns>
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeight() 
{
	return getHeightHelper(root);

}