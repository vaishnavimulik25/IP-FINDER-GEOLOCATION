
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include<time.h>

#define M 10
#define m 100

typedef struct {
    char* data;
    size_t size;
} CurlResponse;

typedef struct sftnode{
	int nodeId; //for insertion in splay tree
	char* IP;
	int data;
	struct sftnode* predecessor;	//for splaytree predecessor
	struct sft* tree;
	struct sftnode* left;	//for schord circle
	struct sftnode* right;
}sftnode;



typedef struct sft{
	struct sftnode* splaytreeroot;
	int count;
	int max;
	int min;
}sft;


void makeschordcircle(sftnode** pointer,int nodeId,char * IP);

sftnode* initializeNode(int nodeId,char *IP);
void joinSchordNetwork(sftnode* node,sftnode** pointer);
sft* initializeFingertable(sftnode** pointer,sftnode* node);
int isBetween(int value,int start,int end);


size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
void fetch_geolocation(char* ipAddress);
sft* constructsft(sftnode* node,sftnode** pointer);
void insertintoSplayTree(sft* sft1,sftnode* node);
void splay(sft* sft1,sftnode* node);
void rotateRight(sft* sft1,sftnode* node);
void rotateLeft(sft* sft1,sftnode* node);
char* lookupipaddress(sftnode** pointer,int nodeId,int data);
sftnode* getParent(sftnode* root,sftnode* node);
sftnode* searchnodeByIp(sft* sft1,int nodeId,int data);
