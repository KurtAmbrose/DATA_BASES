/**
 * @file funcionesModificarDatos.c
 * 
 * @brief Este archivo contiene el submenú de la opción "Modificar datos", las opciones disponibles son las siguientes:
 *          1) Modificar usuario: lo que se puede modificar de aquí es:
 *              -> Nombre
 *              -> Apellidos
 *              -> celular
 *              -> contraseña
 *              -> correo
 *          2) Ajustadores: lo que se puede modificar de aquí es:
 *              -> Nombre
 *              -> Apellidos
 *              -> Celular
 *              -> Correo
 *              -> Contraseña
 *          3) Colonias: lo que se puede modificar de aquí es:
 *              -> colonia
 *              -> alcaldía
 *              -> Código postal
 *          4) Vehículos: Lo que se puede modificar de aquí es:
 *              -> Modelo
 *              -> Ubicación actual
 *          5) Actividad de los ajustadores: lo que se puede modificar de aquí es:
 *              -> Hora de inicio de la jornada
 *              -> Hora final de la jornada
 *              -> fecha
 *              -> El ajustador 
 *              -> el vehículo que utilizó
 *              -> Kilometraje
 *          6) Operadores: lo que se puede modificar de aquí es:
 *              -> Nombre
 *              -> Apellidos
 *              -> teléfono
 *          7) Siniestros: lo que se puede modificar de aquí es:
 *              -> fecha en la que ocurrió el siniestro
 *              -> hora en la que ocurrió el siniestro
 *              -> el ajustador que estuvo en el sinietro
 *              -> el usuario que sufrió el siniestro
 *              -> la colonia donde ocurrió el siniestro
 *          8) Llamadas: Lo que se puede modificar de aquí es:
 *              -> Siniestro
 *              -> Operador que atendió la llamada
 * 
 *      Por otro lado, también permite que se puedan borrar elementos de la base de datos que no sean deseados.
 * 
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * 
 * @date Fecha de creación: 10 de Noviembre del 2023
 * 
 * @date Última modificación: 10 de Noviembre del 2023
*/

#include "def.h"

/**
 * @brief Procedimiento que muestra el submenú de la opción "Modificar Datos"
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 10/11/2023
*/

extern void menuModificarDatos(MYSQL mysql)
{
    char buffer[MAX];
    unsigned int opcion, bandera;
    opcion = 0;
    bandera = 0;
    strcpy(buffer, "\0");


    while(bandera == 0)
    {
        printf("---Modificar datos existentes---\n\n");
        printf("\t-> 1) Usuarios\n\t-> 2) Ajustadores\n\t-> 3) Operadores\n\t-> 4) Siniestros\n\t-> 5) Llamadas\n\t-> 6) Vehículos\n\t-> 7) Colonias\n\t-> 8) Actividad de los Ajustadores\n\t-> 9) Regresar\n\n");
        printf("Ingresa una opción que quieras realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            system("clear");
    
            break;

            case 2:
            system("clear");
            
            break;

            case 3:
            system("clear");
        
            break;

            case 4:
            system("clear");
            
            break;

            case 5:
            system("clear");
            break;

            case 6:
            system("clear");
        
            break;

            case 7:
            system("clear");
    
            break;

            case 8:
            system("clear");
            break;

            case 9:
            bandera = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingrese una opción correcta.\n\n");
            break;
        }
    }
}