/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BINARY SEARCH TREE
 *
 * Features:
 * 1. Expected search time is O(nlogn).
 * 2. Data should be !!!SHUFFLED!!! first before tree creation.
 * 3. First initialize the value of the root (pointer to the 
 *    structure treeNode) with NULL. eg:
 *    treeNode *root = NULL
 *
 * http://en.wikipedia.org/wiki/Binary_search_tree
 *
 ******************************************************************************/

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stdlib.h>
#include <stdint.h>

/**
 * binary search tree definiton.
 */
typedef struct treeNode
{
	int32_t data;	// data
	struct treeNode *left;	// left child
	struct treeNode *right;	// right child
} treeNode;

/**
 * search he minimal element in the binary search tree.
 */
static inline treeNode * 
bst_find_min(treeNode *node)
{
	if(node==NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if(node->left) /* Go to the left sub tree to find the min element */
		return bst_find_min(node->left);
	else 
		return node;
}

/**
 * search the maximal element in the binary search tree.
 */
static inline treeNode * 
bst_find_max(treeNode *node)
{
	if(node==NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if(node->right) /* Go to the left sub tree to find the min element */
		bst_find_max(node->right);
	else 
		return node;
}

/**
 * insert a new data into the binary search tree.
 */
static treeNode * 
bst_insert(treeNode *node,int data)
{
	if (node==NULL)
	{
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp -> data = data;
		temp -> left = temp -> right = NULL;
		return temp;
	}

	if(data >(node->data))
	{
		node->right = bst_insert(node->right,data);
	}
	else if(data < (node->data))
	{
		node->left = bst_insert(node->left,data);
	}
	/* Else there is nothing to do as the data is already in the tree. */
	return node;
}

#endif //
