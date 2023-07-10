#ifndef _TREE_H_
#define _TREE_H_
//#include "School.h"
/* self-referential structure */
typedef struct Treelis
{
    struct Treelis *leftPtr;
    struct Treelis *rightPtr;
    f32 mark;
    u8 * Name;
    u8 ID;
}tree;

 //typedef struct treeNode TreeNode; /* synonym for struct treeNode */
 //typedef TreeNode* TreeNodePtr; /* synonym for TreeNode* */ /* TreeNodePtr <=> struct treeNode*  */

 /* prototypes */
    void insertNode( tree **treePtr, f32 value,tree * name,u8 ID);// change
    void inOrder( tree* treePtr );
// void preOrder( TreeNodePtr treePtr );
 //void postOrder( TreeNodePtr treePtr );


// TreeNodePtr minValueNode(TreeNodePtr node);
 //TreeNodePtr deleteNode(TreeNodePtr root, int key);



#endif // _TREE_H_
