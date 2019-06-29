/*
*  A. Rana Yozgatli
*  21000132
*  Section 2
*  CS342: Operating Systems
*  Homework 1
*  
*  diff.c
*  Parameters: inputFileName1, inputFileName2, outputFileName
*  outputFile = inputFile1 - inputFile2
*  The output file is sorted in ascending order.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node definition for the list
struct wordNode
{
	char word[256];
	struct wordNode *next;
};

// function prototypes
void fileToList( FILE *theFile, struct wordNode *root);
void difference( struct wordNode *root1, struct wordNode *root2);
void listToFile( struct wordNode *theRoot, FILE *outFile);

// ze main
int main( int argc, char *argv[] )
{
	FILE *input1;
	FILE *input2;
	FILE *output;
	struct wordNode *listRoot1;
	struct wordNode *listRoot2;
	
	// check the input count
	if( argc != 4)
	{
		printf( "2 input, 1 output file names are expected!\n");
		return 0;
	}
	// open and check the files
	input1 = fopen( argv[1], "r");
	input2 = fopen( argv[2], "r");
	output = fopen( argv[3], "w");
	if( input1 == NULL || input2 == NULL || output == NULL)
	{
		printf( "An error occurred while opening the file.\n");
		return 0;
	}
	// allocate memory for roots
	listRoot1 = malloc( sizeof( struct wordNode));
	listRoot1 -> next = 0;
	listRoot2 = malloc( sizeof( struct wordNode));
	listRoot2 -> next = 0;
	// read files
	fileToList( input1, listRoot1);
	fclose( input1);
	fileToList( input2, listRoot2);
	fclose( input2);
	// take the difference
	difference( listRoot1, listRoot2);
	// write the difference into the output file
	listToFile( listRoot1, output);
	fclose( output);
	// the end
	printf( "Done!");
	return 0;
}

// ze functions
void fileToList( FILE *inFile, struct wordNode *root)
{
	struct wordNode *cur;
	struct wordNode *newNode;
	char theWord[256];
	char temp[256];
	int order;
	while(1)
	{
		// read the line
		fgets( theWord, 256, inFile);
		if( feof(inFile))
		{
			// reached the end of file
			break;
		}
		// create the word node
		newNode = malloc( sizeof( struct wordNode));
		newNode -> next = 0;
		strcpy( newNode -> word, theWord);
		// first word
		if( root -> next == NULL)
		{
			root -> next = newNode;
		}
		// find the appropriate place for the node and add the node
		else
		{
			cur = root;
			while( cur -> next != NULL)
			{
				strcpy( temp, cur -> next -> word);
				order = strcmp(theWord, temp);
				if( order < 0)
				{
					// theWord < curWord : add the node
					newNode -> next = cur -> next;
					cur -> next = newNode;
					break;
				}
				else if( order > 0)
				{
					// theWord > curWord : keep looking
					cur = cur -> next;
				}
				else
				{
					// theWord = curWord : dan dan dann
					printf( "Not so unique..\n");
					break;
				}
			}
			if( cur -> next == NULL)
			{
				cur -> next = newNode;
			}
		}
		
	}
}

void difference( struct wordNode *root1, struct wordNode *root2)
{
	// list1 = list1 - list2
	struct wordNode *cur1 = root1;
	struct wordNode *cur2 = root2;
	char temp1[256];
	char temp2[256];
	int order;
	struct wordNode *temp;
	while( cur1 -> next != NULL || cur2 -> next != NULL)
	{
		strcpy( temp1, cur1 -> next -> word);
		strcpy( temp2, cur2 -> next -> word);
		order = strcmp( temp1, temp2);
		if( order < 0)
		{
			// cur1word < cur2word : keep looking
			cur1 = cur1 -> next;
		}
		else if( order > 0)
		{
			// cur1word > cur2word : keep looking
			cur2 = cur2 -> next;
		}
		else
		{
			// cur1word = cur2word : gotcha!
			temp = cur1 -> next;
			cur1 -> next = cur1 -> next -> next;
			free(temp);
		}
	}
}

void listToFile( struct wordNode *theRoot, FILE *outFile)
{
	struct wordNode *cur = theRoot -> next;
	int control;
	char theWord[256];
	while( cur != NULL)
	{
		strcpy( theWord, cur -> word);
		control = fputs( theWord, outFile);
		if( control < 0)
		{
			printf( "An error occurred while writing into the output file.\n");
			return;
		}
		control = fputs( "\n", outFile);
		if( control < 0)
		{
			printf( "An error occurred while writing into the output file.\n");
			return;
		}
		cur = cur -> next;
	}
	
}

