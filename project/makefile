CC = gcc
CFLAGS = -Wall -Wextra

lu: lu_fact.c
	$(CC) $(CFLAGS) -o lu_fact lu_fact.c
	
clean_lu:
	rm -f lu_fact

read: lu_fact_readfile.c
	$(CC) $(CFLAGS) -o lu_fact_readfile lu_fact_readfile.c
	
clean_read:
	rm -f lu_fact_readfile
