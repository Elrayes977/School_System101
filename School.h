#include"tree.h"
#ifndef _LIST_H
#define _LIST_H


/*******Shared Macros*****/


/*******user defined data types*****/
typedef u32 sEntry;



typedef struct myNode{

   // sEntry classNum;
   //tree *subjects;
    sEntry ID;
    sEntry *Adress;
  //  sEntry *ID;
    sEntry * phoneNumber;
    sEntry *dateOfBirth;
    sEntry * Name;
  //  f32 marks;
    struct myNode *pNext;
    struct myNode *pPrev;
   // struct myNode *leftPtr;
    //struct myNode *rightPtr;
    f32 mark;
}sNode;

typedef struct myList{
   sNode *pHead;
   sNode *pTail;
   u32 StudentsNumbers;
}List;

typedef enum mystate{FALSE ,TRUE}State_Type;

/*******non static fns prototypes*****/
State_Type createList(List * Ps);
State_Type freeList(List * Ps);

void Main_Menu();
State_Type New_Student(List* Ps,sEntry ID,sEntry * name,sEntry * Adress,sEntry * dateOfBirth,sEntry * phoneNumber);
State_Type Delete_Student(List * Ps,sEntry e);
State_Type Student_List(List* Ps);
State_Type searchStudent(List * Ps,sEntry e, sNode **ppn);
State_Type Student_Edit(List * Ps,sEntry e,sNode *pn);
State_Type Rank_Student(List * Ps,tree* ptr);
State_Type Student_Score(List *Ps,tree **ptr);
#endif // _LIST_H


