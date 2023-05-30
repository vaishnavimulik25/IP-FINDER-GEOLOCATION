#include<stdio.h>
#include<stdlib.h>
#include"headers.h"

void makeschordcircle(sftnode** pointer,int nodeId,char * IP){
	
	if(pointer[0] == NULL){
		sftnode* node = initializeNode(nodeId,IP);//check this TODO
		pointer[0] = node;
	}
	else{
		sftnode* node = initializeNode(nodeId,IP);
		pointer[nodeId] = node;
		node->predecessor = pointer[nodeId-1];
	}

	
}

sftnode* initializeNode(int nodeId,char* IP)
{
	sftnode* node=(sftnode*)malloc(sizeof(sftnode));
	if(!node)
		return NULL;
	node->nodeId = nodeId;
	node->IP = (char*)malloc(sizeof(char)*12);
	node->IP = IP;
	node->predecessor=NULL;
	node->tree=NULL;
	//for splay tree
	node->left = NULL;
	node->right = NULL;
	node->data = 0;
	return node;
}
//for each node we have to call this function along with its last modified node
void joinSchordNetwork(sftnode* node,sftnode** pointer)
{


	node->tree=initializeFingertable(pointer,node);

	
}

//for creating fingertable for one node
sft* initializeFingertable(sftnode** pointer,sftnode* node)
{
	sft* tree = NULL;
	tree = constructsft(node,pointer);


	return tree;
}





int isBetween(int value,int end,int start){

	if(start<=end){
		if(value>=start && value<=end)
			return 1;
	}
	else{
		if(value<=start && value>=end)
			return 1;
	}
	return 0;
}

//perform lookup 
char* lookupipaddress(sftnode** pointer,int nodeId,int data){
	
		for(int i=0; i<m; i++){
			
			if(isBetween(nodeId,pointer[i]->tree->max,pointer[i]->tree->min)){
					//assuming that pointer[i] contains nodeId wala node in its splay tree
					sftnode* node =searchnodeByIp(pointer[i]->tree,nodeId,data);
					if(node){
						char* str = (char*)malloc(sizeof(char)*12);
						str	=node->IP;
						return str;
					}
			}
		}
}










