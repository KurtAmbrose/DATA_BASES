mysql.out: mysqlEjemplo.o
	gcc -o mysql.out mysqlEjemplo.o -lnsl -lm -lz -lmysqlclient

mysqlEjemplo.o: mysqlEjemplo.c
	gcc -c mysqlEjemplo.c

clean:
	rm*.o
