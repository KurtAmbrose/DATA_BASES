/**
 * @file funcionesMostrarDatos.c
 * 
 * @brief Este archivo contiene las funciones que muestran algunos datos de las tablas pertenecientes a la base de datos.
 *        Estos sirven más que nada para auxiliar a algunas funciones externas que involucren la alteración de algunos registros
 *        o propiamente de la insersiones de nuevos registros.
 *          
 *        El archivo contiene las siguientes funciones:
 *          -> Mostrar Ajustadores
 *          -> Mostrar vehículos
 *          -> Mostrar Usuarios
 *          -> Mostrar operadores
 *          -> Mostrar siniestros
 *          -> Mostrar colonias
 * 
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * 
 * @date Fecha de creación del archivo: 7 de Noviembre del 2023
 * 
 * @date Última Actualización: 9 de Noviembre del 2023
*/


#include "def.h"

//  PROCEDIMIENTOS GENERALES QUE MUESTRAN REGISTROS DE LA BASE DE DATOS.

/**
 * @brief Procedimiento que despliega los datos de la tabla de los ajustadores
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 7/11/2023
*/

extern void mostrarAjustadores(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT idAjustador, CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---AJUSTADORES REGISTRADOS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra la tabla de los vehículos registrados
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 7/11/2023
*/

extern void mostrarVehiculos(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT idVehiculo, modelo FROM pr1_vehiculos;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---VEHÍCULOS REGISTRADOS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);

}

/**
 * @brief Procedimiento que muestra los usuarios registrados en la base de datos
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 9/11/2023
*/

extern void mostrarUsuarios(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT idUsuario, CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_usuarios;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---USUARIOS REGISTRADOS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra las colonias registradas en la base de datos
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 9/11/2023
*/

extern void mostrarColonias(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT colonia FROM pr1_colonias;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---COLONIAS REGISTRADAS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra a los operadores registrados en la base de datos
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 9/11/2023
*/

extern void mostrarOperadores(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT idOperador, CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) FROM pr1_operadores;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---OPERADORES REGISTRADOS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra los siniestros registrados en la base de datos
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 9/11/2023
*/

extern void mostrarSiniestros(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    // Ejecuta el query
    sprintf(buffer, "SELECT idSiniestro, fecha, hora FROM pr1_siniestros;");
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---SINIESTROS REGISTRADOS----\n\n");
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
              printf("|%s\n",row[i]);
            }
            else
            {
              printf(" \n");
            }
        }
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}