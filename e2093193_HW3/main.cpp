#include <iostream>
#include "treenode.h"
#include "bstree.h"
using namespace std;

//SOME FUNCTIONS FOR BINARY SEARCH TREE ARE INSPIRED FROM :
//https://gist.github.com/apupeikis/746485/#file-bstree-h;

int main()
{
   BinSTree<int> MyTree;
TreeNode<int> * TreeP1, * TreeP2;
MyTree.Insert(90);
MyTree.Insert(150);
MyTree.Insert(180);
MyTree.Insert(75);
MyTree.Insert(100);
MyTree.Insert(120);
MyTree.Insert(130);
MyTree.Insert(110);
MyTree.Insert(40);
MyTree.Delete(150);
TreeP1=MyTree.FindNode(180,TreeP2);

cout<<TreeP2->data;


}
