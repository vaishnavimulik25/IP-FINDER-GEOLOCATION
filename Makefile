
CC = gcc

#chmod a+x final

final: main.o sftnode.o schord.o finder.o 
	$(CC) main.o sftnode.o schord.o finder.o -o final -lcurl -lm
#-g flag put before -o and see why this preference is used and how can .o files use -g flag
#put -g -c see why this preference is used
sftnode.o: sftnode.c headers.h
	$(CC) -c -g headers.h sftnode.c -lcurl -lm
schord.o: schord.c headers.h
	$(CC) -c -g headers.h schord.c -lcurl -lm

finder.o: finder.c headers.h
	$(CC)  -c -g headers.h finder.c -lcurl -lm

main.o: main.c headers.h
	$(CC) -c -g headers.h main.c -lcurl -lm
clean: 
	rm *.o
