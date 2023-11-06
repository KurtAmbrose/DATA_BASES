practica2.exe: main.o funcionesInsertarDatos.o
	gcc -o practica2.exe main.o funcionesInsertarDatos.o -lnsl -lm -lz -lmysqlclient


funcionesInsertarDatos.o: funcionesInsertarDatos.c def.h
	gcc -c funcionesInsertarDatos.c

main.o: main.c def.h
	gcc -c main.c

clean:
	rm*.o
