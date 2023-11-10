practica2.exe: main.o funcionesInsertarDatos.o funcionesMostrarDatos.o funcionesModificarDatos.o
	gcc -o practica2.exe main.o funcionesInsertarDatos.o funcionesMostrarDatos.o funcionesModificarDatos.o -lnsl -lm -lz -lmysqlclient

funcionesModificarDatos.o: funcionesModificarDatos.c
	gcc -c funcionesModificarDatos.c

funcionesMostrarDatos.o: funcionesMostrarDatos.c
	gcc -c funcionesMostrarDatos.c

funcionesInsertarDatos.o: funcionesInsertarDatos.c def.h
	gcc -c funcionesInsertarDatos.c

main.o: main.c def.h
	gcc -c main.c

clean:
	rm *.o
