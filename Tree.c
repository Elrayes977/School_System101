#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "Config.h"
#include "School.h"
#include "Tree.h"




void insertNode( tree **treePtr , f32 value, tree * name,u8 ID)
 {

	 /* if tree is empty */
	 if ( *treePtr == NULL ) {
		 *treePtr =(tree*) malloc( sizeof( tree ) );
        u8 * N=(u8*) malloc( 20*sizeof( u8 ) );
        strcpy(N,name);
		 /* if memory was allocated then assign data */
		 if ( *treePtr != NULL ) {
			 ( *treePtr )->ID = ID;
			 ( *treePtr )->Name = N;
			  ( *treePtr )->mark = value;
			 ( *treePtr )->leftPtr = NULL;
			 ( *treePtr )->rightPtr = NULL;
		 } /* end if */
		 else {
		     printf( "%d not inserted. No memory available.\n", value );
		 } /* end else */
	 } /* end if */
	 else { /* tree is not empty */

		/* data to insert is less than data in current node */
		if ( value > ( *treePtr )->mark ) {
			insertNode( &( ( *treePtr )->leftPtr ), value ,name,ID);
		} /* end if */
		/* data to insert is greater than data in current node */
		else if ( value < ( *treePtr )->mark ) {
			insertNode( &( ( *treePtr )->rightPtr ), value,name,ID );
		} /* end else if */
		else { /* duplicate data value ignored */
 			printf( "dup" );
 		} /* end else */
 	} /* end else */
 } /* end function insertNode */




/* begin inorder traversal of tree */
 void inOrder( tree *treePtr ) // Left -> Root ->Right
 {

	/* if tree is not empty then traverse */
	if ( treePtr != NULL ) {
	inOrder( treePtr->leftPtr );
	printf( "The Score of %s wit ID=%d is %f\n",treePtr->Name,treePtr->ID ,treePtr->mark );
	inOrder( treePtr->rightPtr );
	//treePtr->pNext;
	} /* end if */
/*else{
    printf("NULL Pointer\n");
}*/
}



/* end function inOrder */
