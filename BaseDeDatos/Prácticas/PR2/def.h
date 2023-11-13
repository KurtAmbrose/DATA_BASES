/**
 * @brief Declaración de bibliotecas que se van a usar 
*/

#include <stdio.h>
#include <stdio_ext.h>
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
    unsigned int id;
}persona;

typedef struct colonia
{
    char nombre[DATOS], alcaldia[DATOS];
    unsigned int cp, id;
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
    unsigned int idAjustador;
    unsigned int idVehiculo;
    unsigned int km;
}actividad;

typedef struct siniestro
{
    char fecha[FECHA], hora[TIEMPO];
    unsigned int idAjustador, idUsuario, idColonia, idSiniestro, idOperador;
}siniestro;

/**
 * @brief Declaración de funciones que se usarán en el programa
*/


// Funciones del archivo funcionesInsertarDatos.c
extern void menuInsertarDatos(MYSQL mysql);
void ingresarUsuarioNuevo(char buffer[], MYSQL mysql);
void ingresarAjustadorNuevo(char buffer[], MYSQL mysql);
void ingresarOperadorNuevo(char buffer[], MYSQL mysql);
void ingresarVehiculoNuevo(char buffer[], MYSQL mysql);
void ingresarColoniaNueva(char buffer[], MYSQL mysql);
void ingresarActividadReciente(char buffer[], MYSQL mysql);
void ingresarSiniestroNuevo(char buffer[], MYSQL mysql);
void mostrarJornada(char buffer[], MYSQL mysql, unsigned int idAjustador, char fecha[], unsigned int *val);
void registrarLlamada(char buffer[], MYSQL mysql);

// Funciones del archivo funcionesMostrarDatos.c
extern void mostrarAjustadores(char buffer[], MYSQL mysql);
extern void mostrarVehiculos(char buffer[], MYSQL mysql);
extern void mostrarUsuarios(char buffer[], MYSQL mysql);
extern void mostrarColonias(char buffer[], MYSQL mysql);
extern void mostrarOperadores(char buffer[], MYSQL mysql);
extern void mostrarSiniestros(char buffer[], MYSQL mysql);

// Funciones del archivo funcionesModificarDatos.c
extern void menuModificarDatos(MYSQL mysql);
void modificarUsuario(char buffer[], MYSQL mysql);
void borrarUsuario(char buffer[], MYSQL mysql);
void modificarAjustador(char buffer[], MYSQL mysql);
void borrarAjustador(char buffer[], MYSQL mysql);
void modificarOperador(char buffer[], MYSQL mysql);
void borrarOperador(char buffer[], MYSQL mysql);
void modificarColonia(char buffer[], MYSQL mysql);
void borrarColonia(char buffer[], MYSQL mysql);