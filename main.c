#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"headers.h"


int main()
{
	printf("\n\n\n");
	printf("******************************************************************************************************************************************\n");
	printf("\n\n");//p2p networkch asatate ka bagh write something powerfull
	printf("*                                                       WELCOME TO P2P NETWORK FOR                                                      *\n");
	printf("\n\n");
	printf("*                                          MESSAGING NUMERICAL CODES TO 100 NODES IN OUR NETWORK                                        *\n");
	printf("\n\n");
	printf("*                                       WHICH WOULD DETECT THE LOCATION OF MALLICIOUS ACTOR'S LOCATION                                   *\n");
	printf("\n\n");
	printf("*                         If you want to send any numerical code from your Id to your friend's Id Please be our Guest:)                  *\n");
	printf("\n\n");
	printf("******************************************************************************************************************************************\n");
	printf("\n\n");	



	FILE *fp = fopen("ip.txt","r");
	//make pointer to  schordcircle

	sftnode** schordcirclepointer = NULL;
	schordcirclepointer = (sftnode**)malloc(sizeof(sftnode*)*m);

	//make schordcircle
	for(int i =0 ;i<m;i++){
		char* str1 = (char*)malloc(sizeof(char));
		fscanf(fp,"%s",str1);
		makeschordcircle(schordcirclepointer,i,str1);
	}
	schordcirclepointer[0]->predecessor = schordcirclepointer[m-1];

	fclose(fp);
	//jounschordNetwork//predessor-left;

	for(int i =0 ;i<m;i++){
		joinSchordNetwork(schordcirclepointer[i],schordcirclepointer );
	}

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

	while(1){
		int a,b,data;//data TODO

		//ask for lookup sender's and receiver's id,data
		printf("Enter Sender's Node ID value(positive integer)\n");
		scanf("%d",&a);
		printf("\n");
		printf("Enter Receiver's Node ID value(positive integer)\n");
		scanf("%d",&b);
		printf("\n");
		printf("Enter data to be send(positive integer)\n");//for data TODO
		scanf("%d",&data);
		printf("\n");

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

		//lookup
		clock_t start,end;
		char* ip1 = lookupipaddress(schordcirclepointer,a,0);//TODO
		start = clock();
		char* ip2 = lookupipaddress(schordcirclepointer,b,data);
		end = clock();


		//call fetchgeolocation;
		printf("sender's IP Address %s\n\n",ip1);
		printf("receiver's IP Address %s\n\n",ip2);

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

		if(ip1 && ip2){
			printf("\n");
			printf("Data is successfully send\n\n");

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

			printf("\n");
			printf("Time Required for searching Receiver's node %fsec\n",((double)(end - start))/CLOCKS_PER_SEC);
			printf("\n");

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

			printf("Geolocation of Sender Node: \n\n");
			fetch_geolocation(ip1);

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

			printf("\n");

			printf("Geolocation of Receiver Node: \n\n");
			fetch_geolocation(ip2);

			printf("\n");

			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
		}

		else
			printf("Please enter numerical values for nodeId");
		//free memory for other responses 
//		free(ip1);
//		free(ip2);
	}

	free(schordcirclepointer);

	return 0;
}


