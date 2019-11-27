#ifndef BINARY_SEARCH_TREE_CLASS
#define BINARY_SEARCH_TREE_CLASS
#include <iostream>
#include <cstdlib>
using namespace std;
#ifndef NULL
const int NULL = 0;
#endif  // NULL

#include "treenode.h"

//SOME FUNCTIONS FOR BINARY SEARCH TREE ARE INSPIRED FROM :
//https://gist.github.com/apupeikis/746485/#file-bstree-h;


template <class T>
class BinSTree
{
    private:
        // pointer to tree root
        TreeNode<T> *root;

        // number of elements in the tree
        int size;

        // memory allocation/deallocation
        TreeNode<T>* GetTreeNode(const T& item, TreeNode<T> *lptr, TreeNode<T> *rptr);
        void FreeTreeNode(TreeNode<T> *p);

        // used by copy constructor and assignment operator
        TreeNode<T>* CopyTree(TreeNode<T> *t);

        // used by destructor and assignment operator
        void DeleteTree(TreeNode<T> *t);

    public:
        // locate a node with data item and its parent in tree.
        // used by Delete
        TreeNode<T>* FindNode(const T& item, TreeNode<T>* & parent) const;

        // constructors, destructor
        BinSTree(void);
        BinSTree(const BinSTree<T>& tree);
        ~BinSTree(void);

        // assignment operator
        BinSTree<T>& operator=(const BinSTree<T>& rhs);

        // tree handling methods
        void Insert(const T& item);
        void Delete(const T& item); // TO BE IMPLEMENTED IN PART 2
        int TreeEmpty(void) const;
        int TreeSize(void) const;

        TreeNode<T>* GetRoot(void) const;
};

// allocate a new tree node and return a pointer to it. Similar to GetNode of Linked List.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T>* BinSTree<T>::GetTreeNode(const T& item,TreeNode<T> *lptr,TreeNode<T> *rptr)
{
TreeNode<T> *p;

    p = new TreeNode<T>(item, lptr, rptr);
    if (p == NULL)
    {
        cout << "Memory allocation failure!\n";
        exit(1); //exits with error code
    }
    return p;
}

// delete the storage occupied by a tree node
template <class T>
void BinSTree<T>::FreeTreeNode(TreeNode<T> *p)
{
    delete p;
}

// RECURSIVELY copy tree t and make it the tree stored in the current object.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T>* BinSTree<T>::CopyTree(TreeNode<T> *t)
{
    TreeNode<T> *newlptr, *newrptr, *newNode;

    // if tree branch is  NULL , stop.
    if (t == NULL)
        return NULL;

    // RECURSIVELY copy the left branch of root t and assign its root to newlptr
    if (t->left != NULL)
        newlptr = CopyTree(t->left);
    else
        newlptr = NULL;

    // RECURSIVELY copy the right branch of tree t and assign its root to newrptr
    if (t->right != NULL)
        newrptr = CopyTree(t->right);
    else
        newrptr = NULL;
    // allocate storage for the current root node and assign its data value
    // and pointers to its subtrees. return its pointer
     newNode = GetTreeNode(t->data, newlptr, newrptr);
    return newNode;
}

// delete the tree stored by the current object.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::DeleteTree(TreeNode<T> *t)
{
    // if current root node is not NULL, delete its left subtree,
    // its right subtree and then the node itself
   if(t != NULL)
        {
            DeleteTree(t->left);
            DeleteTree(t->right);
            delete t;
        }

}

// search for data item in the tree. if found, return its node
// address and a pointer to its parent; otherwise, return NULL.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
TreeNode<T> *BinSTree<T>::FindNode(const T& item, TreeNode<T>* & parent) const
{

  TreeNode<T> *q ;
   q = root;
    // the parent of the root is NULL
    parent = NULL;

    // when the tree is not empty
    while(q != NULL)
    {
        // if found, stop
        if (item == q->data)
            break;
        else
        {
            // go left or right accordingly
            if (item > q->data)
            {
                parent = q;
                q = q->right;
            }
            else
            {
                parent = q;
                q = q->left;
            }
        }
    }

    // return pointer to node
    return q;
}

// constructor. initialize root to NULL, size to 0
template <class T>
BinSTree<T>::BinSTree(void): root(NULL), size(0)
{

}

// copy constructor.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>::BinSTree(const BinSTree<T>& tree)
{
    // copy tree to the current object. assign size

    root = CopyTree(tree.root);
    size = tree.size;
}

// destructor
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>::~BinSTree(void)
{
 DeleteTree(root);
}

// assignment operator.
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
BinSTree<T>& BinSTree<T>::operator= (const BinSTree<T>& rhs)
{
    // can't copy a tree to itself
    if (this == &rhs)
        return *this;
    // Delete current tree. copy new tree into current object
    DeleteTree();
    root = CopyTree(rhs.root);

    // set the tree size
    size = rhs.size;

    // return reference to current object
    return *this;
}

// insert item into the search tree
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::Insert(const T& item)
{
    // t is current node in traversal, parent the previous node
    TreeNode<T> *q , *parent, *newNode;
    q = root;
    parent = NULL;
    // Search for the point of insertion by searching for the item in the tree.
    // Terminate on on empty subtree, insertion is at the leaf position.
 while(q != NULL)
    {
        // If item is greater than the parent go left, if the item is smaller than the parent go right
        if (item > q->data)
        {
            parent = q;
            q = q->right;
        }
        else
        {
            parent = q;
            q = q->left;
        }
    }
    // create the new leaf node and insert. Special case: Insertion can be at the root node.
    newNode = GetTreeNode(item,NULL,NULL);
    if (parent == NULL)
        root = newNode;
    // if the parent is smaller than item, insert at left
    else if (item > parent->data)
        parent->right = newNode;
    else
        // if the parent is greater than item, insert at right
        parent->left = newNode;
    // Update the state of the tree object
    size++;
}
// if item is in the tree, delete it. PART 2
// COMPLETE THE MISSING PARTS according to the provided comments.
template <class T>
void BinSTree<T>::Delete(const T& item)
{
    // DNodePtr = pointer to node D that is deleted
    // PNodePtr = pointer to parent P of node D
    // RNodePtr = pointer to node R that replaces D
    TreeNode<T> *DNodePtr, *PNodePtr, *RNodePtr;
    // search for a node containing data value item. obtain its
    // node address and that of its parent
    if ((DNodePtr = FindNode (item, PNodePtr)) == NULL)
        return;
    // If D has a NULL pointer, the
    // replacement node is the one on the other branch
    if (DNodePtr->left == NULL)
        RNodePtr = DNodePtr->right;
    else if (DNodePtr->right == NULL)
        RNodePtr = DNodePtr->left;
    // Both pointers of DNodePtr are non-NULL.
    else
    {
        // Find and unlink replacement node for D.
        // Starting on the left branch of node D,
        // find node whose data value is the largest of all
        // nodes whose values are less than the value in D.
        // Unlink the node from the tree.
        // PofRNodePtr = pointer to parent of replacement node
        TreeNode<T> *PofRNodePtr;
        PofRNodePtr = DNodePtr;
        // first possible replacement is left child of D
        RNodePtr = DNodePtr->left;
        // descend down right subtree of the left child of D,
        // keeping a record of current node and its parent.
        // when we stop, we have found the replacement
        while(RNodePtr->right != NULL)
        {
            PofRNodePtr = RNodePtr;
            RNodePtr = RNodePtr->right;
        }
        if (PofRNodePtr == DNodePtr)
            // left child of deleted node is the replacement.
            // assign right subtree of D to R
            RNodePtr->right = DNodePtr->right;
        else
        {
            // we moved at least one node down a right branch
            // delete replacement node from tree by assigning
            // its left branch to its parent
            PofRNodePtr->right = RNodePtr->left;
            // put replacement node in place of DNodePtr.
            RNodePtr->left = DNodePtr->left;
            RNodePtr->right = DNodePtr->right;
        }
    }
    // complete the link to the parent node.
    // deleting the root node. assign new root
    if (PNodePtr == NULL)
        root = RNodePtr;
    // attach R to the correct branch of P
    else if (PNodePtr->data > DNodePtr->data)
        PNodePtr->left = RNodePtr;
    else
        PNodePtr->right = RNodePtr;
    // delete the node from memory and decrement list size
    FreeTreeNode(DNodePtr);
    size--;

}

// indicate whether the tree is empty
template <class T>
int BinSTree<T>::TreeEmpty(void) const
{
    return root == NULL;
}

// return the number of data items in the tree
template <class T>
int BinSTree<T>::TreeSize(void) const
{
    return size;
}

// return the address of the root node.
template <class T>
TreeNode<T> *BinSTree<T>::GetRoot(void) const
{
    return root;
}

#endif  // BINARY_SEARCH_TREE_CLASS
