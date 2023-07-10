#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "Config.h"
#include "Tree.h"
#include "School.h"



/******* static fns prototypes*****/
static State_Type isEmpty(List * Ps);


/*******************************/
void Main_Menu()
{
    typedef enum {NEW_STUDENT=1,PRINT,SEARCH,DELETE,EDIT,DELETE_ALL,SCORES,RANK,EXIT}menu_type;
    tree * s=NULL;//to pass to tree
    List s1;
    //List *S;
    createList(&s1);
    sEntry e1=0;//ID
    sNode *pn;
    sNode S;
    u8 name[TEXT_SIZE];
  //  u8 ID[20];
    u8 Adress[TEXT_SIZE];
    u8 dateB[TEXT_SIZE];
    u8 phone[TEXT_SIZE];
    u8 temp=0;

    u8 choice;

    do{

        printf("|=================================================|\n");
        printf("|__________________ MAIN MENU_____________________|\n");
        printf("|=================================================|\n");
        printf("WELCOME TO THE SCHOOL SYSTEM:\nplease choose from these optins:\n");
        printf("Enter the number:\n[1]NEW_STUDENT\n[2]PRINT THE LIST\n[3]SEARCH\n[4]DELETE\n[5]EDIT\n[6]DELET_ALL\n[7]SCORES\n[8]RANKS\n[9]EXIT\n");
        scanf("%d",&choice);
        while(getchar() != '\n');// to clear the buffer the scanf puts the enter in the stack,
        switch(choice)
        {
            case NEW_STUDENT:
                printf("Please Enter STUDENT ID: ");
                //scanf("%d",&e1);
                 if(scanf("%d", &e1) != 1){

                    printf("Error - END.\nPlease use only numbers\n"); //to prvent using charecters
                    break;
                    }

                while(temp==e1)
                    {
                        printf("ID already Used Please Try again");
                        scanf("%d",&e1);
                    }
                    temp=e1;
                while(getchar() != '\n');

                printf("PLEASE ENTER STUDENT'S NAME:\n");
                gets(name);
                printf("PLEASE ENTER STUDENT'S Adress:\n");
                gets(Adress);
                printf("please enter students Date of birth:\n");
                gets(dateB);
                printf("please enter students phone number:\n");
                gets(phone);
                New_Student(&s1,e1,name,Adress,dateB,phone);
                break;
            case PRINT:
                Student_List(&s1);
             break;
            case SEARCH:
                printf("please enter search ID: ");
                scanf("%d",&e1);
                searchStudent(&s1,e1,&pn);
                if(pn == NULL)
                    printf("Not Found\n");
                    else{
                        printf("Found\n");
                        printf("ID = %d \t Name=%s \n",pn->ID,pn->Name);
                    }
                break;
            case DELETE:
                printf("please enter ID of the student you wish to delete: ");
                scanf("%d",&e1);
                Delete_Student(&s1,e1);
                break;
                case EDIT:
                printf("please enter ID of the student you wish to EDIT: ");
                scanf("%d",&e1);
               Student_Edit(&s1,e1,&pn);
                break;
                case DELETE_ALL:
                    freeList(&s1);
                    printf("All Students DELETED\n");
                break;
                case SCORES:
                    Student_Score(&s1,&s);
                break;
                case RANK:
                  Rank_Student(&s1,s);
                break;
            case EXIT:
                printf("END OF THE PROGRAM SEE YOU LATER\n");
                break;
            default:
             printf("you entered wrong number ");


        }//end switch






    }while(choice != EXIT);


}
/*******************************/
State_Type createList(List * Ps)
{
   State_Type Local_state = FALSE;

   if(Ps == NULL)
   {
       printf("Null Pointer\n");
       Local_state = FALSE;
   }
   else
   {
      // initialize List object
      Ps->pHead = NULL;
      Ps->pTail = NULL;
      Ps->StudentsNumbers = 0;
 //printf("tes3 passed\n");
      Local_state = TRUE;
   }
   return Local_state;
}
/*********************************/
State_Type New_Student(List* Ps,sEntry ID,sEntry * name,sEntry * Adress,sEntry * dateOfBirth,sEntry * phoneNumber)
{
    State_Type Local_state = FALSE;
    if(Ps == NULL)
    {
       printf("Null Pointer\n");
       Local_state = FALSE;
    }
    else
    {
       // step 1 : allocate location for the class
      sNode* pn =(sNode*)malloc(sizeof(sNode));
       //allocate locations for the
        u8 * Np=(u8 *)malloc(TEXT_SIZE*sizeof(u8));
         // u8 * IDp=(u8 *)malloc(20*sizeof(u8));
          u8 * Adp=(u8 *)malloc(TEXT_SIZE*sizeof(u8));
          u8 * bdp=(u8 *)malloc(TEXT_SIZE*sizeof(u8));
          u8 * Php=(u8 *)malloc(TEXT_SIZE*sizeof(u8));
      if(pn == NULL&&Np==NULL&&Adp==NULL&&bdp==NULL&&Php==NULL)
      {
          printf("Memory is Full\n");
          Local_state = FALSE;
      }
      else // heap is working fine
      {

          // step 2 : initialize Node members
            strcpy(Np,name);
            strcpy(Adp,Adress);
            strcpy(bdp,dateOfBirth);
            strcpy(Php,phoneNumber);
          pn->ID=ID;//classN is the number of the class
          pn->Name=Np;
//          pn->ID=IDp;
          pn->Adress=Adp;
          pn->dateOfBirth=bdp;
          pn->phoneNumber=Php;
        //  pn->marks=0;
          pn->pNext = NULL;
          pn->pPrev = NULL;


          // increment number of students
          Ps->StudentsNumbers++;
          // step3 : insert Node in List
        //  printf("tes1 passed\n");
          if(isEmpty(Ps))
          {
              Ps->pHead = Ps->pTail = pn;
            //  printf("tes2 passed\n");
          }
          else  // list is Not Empty
          {
              // search for right place to insert node
              //search for the firs letter alphabetics
             sNode * temp = Ps->pHead;  // initialization

             while(temp != NULL &&(strcmp(temp->Name,name)<=0))// condition
             {
                 temp = temp->pNext; // update
                  //printf("ZZZZZZZ\n");
             }

             // after tail
             if(temp == NULL)
             {
                 Ps->pTail->pNext = pn;
                 pn->pPrev = Ps->pTail;
                 Ps->pTail = pn;
                printf("after Tail\n");
             }
             else if(temp == Ps->pHead)// before head
             {
                 Ps->pHead->pPrev = pn;
                 pn->pNext = Ps->pHead;
                 Ps->pHead = pn;
                 printf("before head\n");
             }
             else{ // in the middle
                temp->pPrev->pNext  = pn;
                pn->pNext = temp;
                pn->pPrev = temp->pPrev;
                temp->pPrev = pn;
                 printf("after head\n");
             }
          }// list is not empty
          Local_state = TRUE;
#if(ENABLE_DEBUGGING == ENABLE)
    printf("%s is the  inserted student \n",name);
#endif
      }// else heap is working fine
    }// else Ps!= NULL

  return Local_state;
}

/***************************************************/
State_Type searchStudent(List * Ps,sEntry e, sNode **ppn)
{
  State_Type Local_state = FALSE;
    if(Ps == NULL)
    {
       printf("Null Pointer\n");
       Local_state = FALSE;
    }
    else
    {
         sNode * temp = Ps->pHead;
         while(temp != NULL && temp->ID != e )
         {
           temp =  temp->pNext;
         }

        *ppn = temp;
          Local_state = TRUE;
    }
   return Local_state;
}
/***************************************************/
State_Type Delete_Student(List * Ps,sEntry e)
{
    State_Type Local_state = FALSE;
    if(Ps == NULL)
    {
       printf("Null Pointer\n");
       Local_state = FALSE;
    }
    else
    {
        if(isEmpty(Ps))
        {
            printf("List is Empty\n");
            Local_state = FALSE;
        }
        else
        {
            sNode *pn;
            searchStudent(Ps ,e,&pn);

            if(pn == NULL) // Not found
            {
                printf("ID %d can not be found\n",e);
            }
            else // found
            {
                free(pn->Name);
                 free(pn->Adress);
                  free(pn->dateOfBirth);
                   free(pn->phoneNumber);
               if(Ps->pHead == Ps->pTail) // only one Node
               {
                  free(Ps->pHead);// free
                  Ps->pHead = Ps->pTail = NULL;
                  Ps->StudentsNumbers = 0;
               }
               else if(pn == Ps->pHead) // found and it is head
               {
                    //pl->pHead = pl->pHead->pNext;
                    // assign new head
                    Ps->pHead = pn->pNext;
                    // make new head prev  equal to NULL
                    Ps->pHead->pPrev = NULL;
                    // delete old head stored in pn
                    free(pn);
                    // decrement size
                    Ps->StudentsNumbers--;
               }
               else if(pn == Ps->pTail)
               {
                   // assign new Tail
                  Ps->pTail = pn->pPrev;
                   // make new tail next  equal to NULL
                  Ps->pTail->pNext = NULL;
                  // delete old head stored in pn
                   free(pn);
                  // decrement size
                  Ps->StudentsNumbers--;
               }
               else // middle
               {
                  pn->pNext->pPrev = pn->pPrev;
                  pn->pPrev->pNext = pn->pNext;
                  Ps->StudentsNumbers--;
                  free(pn);
               }
               Local_state = TRUE;
               printf("Student %s Is deleted\n",pn->Name);
            }// else found
        }// else not empty
    }// not NULL pinter
    return Local_state;
}
/***************************************************/

State_Type Student_List(List* Ps)
{
   State_Type Local_state = FALSE;
   if(Ps == NULL)
   {
       printf("Null Pointer\n");
       Local_state = FALSE;
   }
   else // not Null pointer
   {
       if(isEmpty(Ps))
       {
           printf("List is Empty, can not print anything\n");
            Local_state = FALSE;
       }
       else // List not Empty
       {
           sNode*temp;
          for(temp = Ps->pHead ; temp != NULL; temp = temp->pNext )
          {printf("=========\t========\t==================\t============\t================\n");
           printf("Name:%s  \t  ID:%d \t Date of birth:%s \t Address:%s \t phone number:%s\n",temp->Name,temp->ID,temp->dateOfBirth,temp->Adress,temp->phoneNumber);
            printf("=========\t========\t==================\t============\t================\n");
          }
          Local_state = TRUE;
       }// else Not Empty

   }// else NULL pointer
   return Local_state;
}

/***************************************************/
State_Type Student_Edit(List * Ps,sEntry e,sNode *pn)

{

 //sEntry e1=0;
    //sNode *pn;
    u8 name[TEXT_SIZE];
    u8 ID;
    u8 Adress[TEXT_SIZE];
    u8 dateB[TEXT_SIZE];
    u8 phone[TEXT_SIZE];
     State_Type Local_state = FALSE;
    if(Ps == NULL)
    {
       printf("Null Pointer\n");
       Local_state = FALSE;
    }
    else
    {
        if(isEmpty(Ps))
        {
            printf("List is Empty\n");
            Local_state = FALSE;
        }
        else
        {
            //sNode *pn;
            searchStudent(Ps ,e,&pn);
            if(pn == NULL) // Not found
            {
                printf("ID %d can not be found\n",e);
            }
            else // found
            { u8 choice;
                typedef enum {EDIT_NAME=1,EDIT_ID,EDIT_BIRTH,EDIT_PHONE,EXIT}menu_type;
                do{
                printf("If you want to Edit the student( %s ) proceed\n",pn->Name);
                printf("Enter the number:\n[1]EDIT_NAME\n[2]EDIT_ID\n[3]EDIT_BIRTH\n[4]EDIT_PHONE\n[5]GO BACK\n");
                scanf("%d",&choice);
                while(getchar() != '\n');// to clear the buffer the scanf puts the enter in the stack,
                switch(choice)
                {
                case EDIT_NAME:
                printf("Enter the new name:\n ");
                gets(name);
                strcpy(pn->Name,name);
                break;
                case EDIT_ID:
                printf("please enter student'ss New ID\n");
                scanf("%d",&ID);
                while(getchar() != '\n');
                pn->ID=ID;
                break;
                case EDIT_BIRTH:
                printf("please enter students NEW Date of birth\n");
                gets(dateB);
                strcpy(pn->dateOfBirth,dateB);
                break;
                case EDIT_PHONE:
                 printf("please enter students phone number\n");
                gets(phone);
                strcpy(pn->phoneNumber,phone);
                break;

                case EXIT:
                printf("Back to The Main Menu\n");
                break;
                default:
                printf("you entered wrong number ");


                }//end switch

                }while(choice != EXIT);

               Local_state = TRUE;
            }// else found
        }// else not empty
    }// not NULL pinter
    return Local_state;
}
/************************************************/
State_Type Rank_Student(List*Ps,tree *ptr)
{
  State_Type Local_state = FALSE;
   if(Ps == NULL)
   {
       printf("Null Pointer\n");
       Local_state = FALSE;
   }
else {

    if(isEmpty(Ps))
       {
           printf("List is Empty, can not print anything\n");
            Local_state = FALSE;
       }

    else
        {
           // ptr=NULL;

        inOrder(ptr);
        }


}


}
/************************************************/
State_Type Student_Score(List *Ps, tree ** ptr)
{
    State_Type Local_state = FALSE;
   if(Ps == NULL)
   {
       printf("Null Pointer\n");
       Local_state = FALSE;
   }
   else // not Null pointer
   {
       if(isEmpty(Ps))
       {
           printf("List is Empty, can not print anything\n");
            Local_state = FALSE;
       }
       else // List not Empty
       { f32 marks;
           sNode*temp;
           u8 ID;
          // ptr=NULL;
          for(temp = Ps->pHead ; temp != NULL; temp = temp->pNext )
          {
           printf("Please Enter the score of Name:%s  \t ID:%d \n Score In computer Scince is:",temp->Name,temp->ID);
           scanf("%f",&marks);
           temp->mark=marks;
           u8 *name=temp->Name;
           u8 ID=temp->ID;

           insertNode( ptr, marks,name,ID);
          }
          Local_state = TRUE;
       }// else Not Empty

   }// else NULL pointer
   return Local_state;



}

/************************************************/
State_Type freeList(List * Ps)
{
     State_Type Local_state = FALSE;
   if(Ps == NULL)
   {
       printf("Null Pointer\n");
       Local_state = FALSE;
   }
   else // not Null pointer
   {
        sNode *temp = Ps->pHead;
   while(temp != NULL)
   {
       temp = temp->pNext;
       free(Ps->pHead);
       Ps->pHead = temp;

      }
       Ps->pTail = NULL;
       Ps->StudentsNumbers = 0;
        Local_state = TRUE;
   }
}
/***************************************************/
static State_Type isEmpty(List * Ps)
{
     State_Type Local_state = FALSE;
     if(Ps == NULL)
     {
         printf("Null Pointer\n");
         Local_state = FALSE;
     }
     else
     {
        if(Ps->pHead == NULL )
        {
            Local_state = TRUE;
        }
        else
        {
            Local_state = FALSE;
        }
     }// else pl == NULL
    return Local_state;
}
/***************************************************/
