#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/**
 * @brief Declaración de constantes
*/

#define MAX 1024
#define DATOS 50
#define PWD 12
#define CELL 30

typedef struct persona
{
    char nombre[DATOS], ap_paterno[DATOS], ap_materno[DATOS], correo[DATOS], contrasena[PWD], celular[CELL];
}persona;

/**
 * @brief Declaración de funciones que se usarán en el programa
*/

void menuInsertarDatos(MYSQL mysql);
void ingresarUsuarioNuevo(char buffer[], MYSQL mysql);