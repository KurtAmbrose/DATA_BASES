.DEFAULT_GOAL := all

all: practica2.exe clean

.PHONY: clean

practica2.exe: main.o funcionesInsertarDatos.o funcionesMostrarDatos.o funcionesModificarDatos.o funcionesConsultarInfo.o
	gcc -o practica2.exe main.o funcionesInsertarDatos.o funcionesMostrarDatos.o funcionesModificarDatos.o funcionesConsultarInfo.o -lnsl -lm -lz -lmysqlclient

funcionesConsultarInfo.o: funcionesConsultarInfo.c
	gcc -c funcionesConsultarInfo.c

funcionesModificarDatos.o: funcionesModificarDatos.c
	gcc -c funcionesModificarDatos.c

funcionesMostrarDatos.o: funcionesMostrarDatos.c
	gcc -c funcionesMostrarDatos.c

funcionesInsertarDatos.o: funcionesInsertarDatos.c def.h
	gcc -c funcionesInsertarDatos.c

main.o: main.c def.h
	gcc -c main.c

clean:
	rm -f *.o *~
