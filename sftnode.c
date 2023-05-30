#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"headers.h"

//function to construct sft for a node
sft* constructsft(sftnode* node,sftnode** pointer){

	//initialise sft with empty splay tree
	sft* sft1 = (sft*)malloc(sizeof(sft));
	if(!sft1)
		return NULL;

	sft1->splaytreeroot = NULL;

	//called this after making schord circle
	for(int i = 0;i < M;i++){
		int successorId = (node->nodeId + (1<<i))%(1<<M);
		sftnode* successor = pointer[successorId];
		insertintoSplayTree(sft1,successor);
	}

	return sft1;
}

//function to perform splay tree insertion operation
void insertintoSplayTree(sft* sft,sftnode* node){

	if(sft->splaytreeroot == NULL){
		sft->splaytreeroot = node;
		node->left = NULL;
		node->right = NULL;
		sft->count++;
		sft->min = node->nodeId;
		sft->max = node->nodeId;
		return;
	}

	sftnode* current = sft->splaytreeroot;

	while(current != NULL){
		if(node->nodeId<current->nodeId){
			if(current->left == NULL){
				current->left = node;
				node->left = NULL;
				node->right = NULL;
				splay(sft,current->left);
				sft->count++;
				sft->max = node->nodeId;
				return;
			}
			else
				current = current->left;
		}	
		else{
			if(current->right == NULL){
				current->right = node;
				node->left = NULL;
				node->right = NULL;
				splay(sft,current->right); //for making newly added node as root node
				sft->count++;
				sft->max = node->nodeId;
				return;
			}
			else
				current = current->right;
		}
	}
}

//function to perform splaying operation in splaytree
void splay(sft* sft1,sftnode* node){
	while(node!=sft1->splaytreeroot){
		sftnode* parent = getParent(sft1->splaytreeroot ,node);
		sftnode* grandparent = getParent(sft1->splaytreeroot ,parent);

		if(grandparent == NULL && parent != NULL){
			//zig rotation
			if(node == parent->left){
				rotateRight(sft1,parent);
				sft1->splaytreeroot=node;
			}
			else{
				rotateLeft(sft1,parent);
				sft1->splaytreeroot=node;
			}
		}
		else if(parent!= NULL && grandparent != NULL){
			//zig-zag or zig-zig rotation
			if(node == parent->left && parent == grandparent->left){
				rotateRight(sft1,grandparent);
				rotateRight(sft1,parent);
				sft1->splaytreeroot=node;
			}
			else if(node == parent->right && parent == grandparent->right){
				rotateLeft(sft1,grandparent);
				rotateLeft(sft1,parent);
				sft1->splaytreeroot=node;
			}
			else if(node == parent->right && parent == grandparent->left){
				rotateLeft(sft1,parent);
				rotateRight(sft1,grandparent);
				sft1->splaytreeroot=node;
			}
			else{
				rotateRight(sft1,parent);
				rotateLeft(sft1,grandparent);
				sft1->splaytreeroot=node;
			}
		}
	}
}

//function to perform left rotation in splaytree
void rotateLeft(sft *t, sftnode *x)//ll rotation in avl
{
	sftnode* p = x;
	sftnode* q = p->left;
	sftnode* r = NULL;
	//handled r case
	if(q && q->right)
		r = q->right;
	sftnode* ap = getParent(t->splaytreeroot,p);

	if(ap != NULL && ap->left == p)
		ap->left = q;
	else if(ap!=NULL && ap->right == p)
		ap->right = q;
	if(q)
		q->right = p;
//	p->parent = q;
//	if(ap)
//		q->parent = ap;
//	else if(!ap)
//		q->parent = NULL;

	if(r){
		p->left = r;
//		r->parent = p;
	}
	if(!r)
		p->left = NULL;
	return;
}

//function to perform right rotation in splay tree
void rotateRight(sft *t, sftnode *x)//rr rotation
{
	sftnode* p = x;
	sftnode* q = p->right;
	sftnode* r = NULL;
	if(q && q->left)
		r = q->left;
	sftnode* ap = getParent(t->splaytreeroot,p);

	if(ap!=NULL && ap->left == p)
		ap->left = q;
	else if(ap!=NULL && ap->right == p)
		ap->right = q;
	if(q)
		q->left = p;
	//p->parent = q;
	if(r){
		p->right = r;
	//	r->parent = p;
	}
	if(!r)
		p->right = NULL;
//	if(ap)
//		q->parent = ap;
//	else if(!ap)
//		q->parent = NULL;
	return;
}
//used in splay operation
sftnode* getParent(sftnode* root,sftnode* node){
	

	//empty tree
	if(root==NULL || root==node)
		return NULL;
	sftnode* parent=NULL;
	sftnode* current=root;

	while(current!=NULL)
	{
		if(current->nodeId==node->nodeId)
			return parent;
		else if(current->nodeId>node->nodeId){
			parent=current;
			current=current->left;
		}
		else{
			parent=current;
			current=current->right;
		}

	}

	return NULL;
}

//function for search operation in SFT

sftnode* searchnodeByIp(sft* sft1,int nodeId,int data)
{
	//splay root node to top before starting search
	splay(sft1,sft1->splaytreeroot);

	sftnode* current=sft1->splaytreeroot;
	while(current!=NULL)
	{
		if(nodeId == current->nodeId )
		{
			splay(sft1,current);
			//splay found node to root
			current->data = data;
			return current;
		}
		else if(current->nodeId > nodeId )
		{
			if(current->left==NULL)
				break;

			splay(sft1,current->left);
			//splay left child to node
			current=current->left;
		}
		else{
			if(current->right==NULL)
				break;

			splay(sft1,current->right);
			current=current->right;
		}

	}

	return NULL;
}




