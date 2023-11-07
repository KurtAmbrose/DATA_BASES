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
#define TIEMPO 9
#define FECHA 11

/**
 * @brief Declaración de estructuras que se utilizarán en el programa
*/

typedef struct persona
{
    char nombre[DATOS], ap_paterno[DATOS], ap_materno[DATOS], correo[DATOS], contrasena[PWD], celular[CELL];
}persona;

typedef struct colonia
{
    char nombre[DATOS], alcaldia[DATOS];
    unsigned int cp;
}colonia;

typedef struct vehiculo
{
    char modelo[DATOS];
    unsigned int idColonia;
}vehiculo;

typedef struct actividad
{
    char horaInicio[TIEMPO], horaFin[TIEMPO];
    char fecha[FECHA];
    int idAjustador;
    int idVehiculo;
    int km;
}actividad;

/**
 * @brief Declaración de funciones que se usarán en el programa
*/

void menuInsertarDatos(MYSQL mysql);
void ingresarUsuarioNuevo(char buffer[], MYSQL mysql);
void ingresarAjustadorNuevo(char buffer[], MYSQL mysql);
void ingresarOperadorNuevo(char buffer[], MYSQL mysql);
void ingresarVehiculoNuevo(char buffer[], MYSQL mysql);
void ingresarColoniaNueva(char buffer[], MYSQL mysql);
void ingresarActividadReciente(char buffer[], MYSQL mysql);
void mostrarAjustadores(char buffer[], MYSQL mysql);
void mostrarVehiculos(char buffer[], MYSQL mysql);