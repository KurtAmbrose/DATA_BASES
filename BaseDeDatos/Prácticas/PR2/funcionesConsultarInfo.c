/**
 * @file funcionesConsultarInfo.o
 * 
 * @brief Este archivo contiene las funciones relacioandas al submenú de consultar información. 
 *        Es capaz de mostrar un submenú con los siguientes puntos:
 *              1) Usuarios que menos usan el sistema
 *              2) Ajustadores y siniestros
 *                  a) Ajustadores que más siniestros atienden
 *                  b) Ajustadores que menos siniestros atienden
 *              3) Lista de Ajustadores registrados en el sistema
 *              4) Lista de siniestros de un ajustador en particular
 *              5) Lista de ajustadores que manejaron un vehículo en un periodo de tiempo
 *              6) Lista de colonias donde más siniestros ocurren
 *              7) Periodo del día donde más siniestros ocurren
 *              8) Cantidad de siniestros que ocurren en cierto periodo de tiempo
 *              9) Nombre del ajustador/es que manejó un vehículo en un periódo de tiempo determinado
 *              10) Última poición de un ajustador en particular
 *              11) Lista de vehículos que manejó un ajustador en un tiempo específico
 *              12) Vehículo que manejó un ajustador en un tiempo determinado
 * 
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * 
 * @date Fecha de elaboración del archivo: 16 de Noviembre del 2023
 *
 * @date Última Actualización: 17 de Noviembre del 2023
*/

#include "def.h"

/**
 * @brief Procedimiento que despliega los vehículos que manejó un siniestro en una hora específica
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 17/11/2023
*/

void mostrarListaVehiculosManejoAjustadorEnTiempoFijo(char buffer[], MYSQL mysql)
{
    char nombre[DATOS], fecha[FECHA];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int validar, id, i, j;

    validar = 0;
    j = 1;

    printf("Ingresa la fecha en el formato 'AAAA-MM-DD' (incluyendo los '-'): ");
    scanf(" %[^\n]", fecha);

    system("clear");

    while(validar == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("Ingresa el ID del ajustador: ");
        scanf(" %d", &id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", id);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        // Despliega el resultado del ID
        if ((row = mysql_fetch_row(res))) {
            validar = atoi(row[0]);
        }
        
        if(validar == 0)
        {
            system("clear");
            printf("El ajustador no está registrado.\n\n");
        }
        mysql_free_result(res);
    }

    system("clear");

    // Ejecuta el query
    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) FROM pr1_ajustadores WHERE idAjustador = %d;", id);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del ID
    if ((row = mysql_fetch_row(res))) {
        strcpy(nombre, row[0]);
    }

    mysql_free_result(res);

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre, modelo FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) WHERE fecha = '%s' HAVING nombre = '%s';", fecha, nombre);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del ID
    printf("---LISTA DE VEHÍCULOS QUE MANEJÓ EL AJUSTADOR %s EL DÍA %s---\n\n", nombre, fecha);
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        printf("-> Vehículo #%d\n", j);
        for( i=0 ; i < mysql_num_fields(res); i++ )
        {
            if(row[i] != NULL)
            {
                if(strcmp(row[i], nombre) != 0)
                {
                    printf("|%s\n",row[i]);
                }
            }
            else
            {
              printf(" \n");
            }
        }
        j++;
        fputc('\n',stdout);
    }

    mysql_free_result(res);     
}

/**
 * @brief Procedimiento que muestra la última posición o la posición actual de un ajustador en particular
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarUltimaPosicionDeAjustador(char buffer[], MYSQL mysql)
{
    char nombre[DATOS];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int validar, id;

    validar = 0;

    while(validar == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("Ingresa el ID del ajustador: ");
        scanf(" %d", &id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", id);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        // Despliega el resultado del ID
        if ((row = mysql_fetch_row(res))) {
            validar = atoi(row[0]);
        }
        
        if(validar == 0)
        {
            system("clear");
            printf("El ajustador no está registrado.\n\n");
        }
        mysql_free_result(res);
    }

    system("clear");

    // Ejecuta el query
    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) FROM pr1_ajustadores WHERE idAjustador = %d;", id);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del ID
    if ((row = mysql_fetch_row(res))) {
        strcpy(nombre, row[0]);
    }

    mysql_free_result(res);    

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre, colonia FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) LEFT JOIN pr1_colonias USING(idColonia) HAVING nombre = '%s';", nombre);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del ID
    row = mysql_fetch_row(res);
    printf("---POSICIÓN ACTUAL DEL AJUSTADOR: %s---\n\n", nombre);
    printf("|%s\n\n", row[1]);

    mysql_free_result(res); 

}

/**
 * @brief Procedimiento que muestra los ajustadores que manejaron en un rango de tiempo específico
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarAjustadoresManejaronUnVehiculoEnTiempoFijo(char buffer[], MYSQL mysql)
{
    char horaIn[TIEMPO], horaFin[TIEMPO];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i, j;

    j = 1;

    printf("Ingresa la hora del inicio con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", horaIn);
    printf("Ingresa la hora del fin con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", horaFin);
    system("clear");

    sprintf(buffer, "SELECT DISTINCT(CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno)) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) WHERE hora_inicio  >= '%s' AND hora_fin <= '%s';", horaIn, horaFin);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---AJUSTADORES QUE MANEJARON ENTRE LAS %s Y LAS %s----\n\n", horaIn, horaFin);
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        printf("-> Ajustador #%d\n", j);
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
        j++;
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra la cantidad de siniestros que ocurren en cierto periodo de tiempo
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarCantidadDeSiniestrosEnTiempo(char buffer[], MYSQL mysql)
{
    char horaIn[TIEMPO], horaFin[TIEMPO];
    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("Ingresa la hora del inicio con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", horaIn);
    printf("Ingresa la hora del fin con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", horaFin);
    system("clear");

    sprintf(buffer, "SELECT COUNT(idSiniestro) AS cantidad_siniestros FROM pr1_siniestros WHERE hora >= '%s' AND hora <= '%s';", horaIn, horaFin);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---CANTIDAD DE SINIESTROS QUE OCURRIERON ENTRE LAS %s Y LAS %s---\n\n", horaIn, horaFin);

    // Despliega el resultado
    row = mysql_fetch_row(res);

    printf("| Número de sinietros: %d\n\n", atoi(row[0]));

}

/**
 * @brief Procedimiento que muestra el periódo del día donde más siniestros ocurren
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarPeriodoDiaDondeMasSiniestrosPasan(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    sprintf(buffer, "SELECT periodoDia(hora) AS periodo FROM pr1_siniestros GROUP BY periodo HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_siniestros GROUP BY periodoDia(hora) ORDER BY COUNT(idSiniestro) DESC LIMIT 1);");
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---PERIODO DEL DÍA DONDE MÁS SINIESTROS OCURREN----\n\n");

    // Despliega el resultado
    row = mysql_fetch_row(res);
    printf("|%s\n\n", row[0]);
    
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que muestra una lista de las colonias donde más siniestros ocurren (o puede ser sólo una)
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarColoniasDondeMasSiniestrosPasan(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    sprintf(buffer, "SELECT colonia FROM pr1_colonias LEFT JOIN pr1_siniestros USING(idColonia) GROUP BY colonia HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_colonias LEFT JOIN pr1_siniestros USING(idColonia) GROUP BY colonia ORDER BY COUNT(idSiniestro) DESC LIMIT 1);");
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---LISTA DE COLONIAS DONDE MÁS SINIESTROS OCURREN----\n\n");
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
 * @brief Procedimiento que muestra la lista de los ajustadores que manejaron un vehículo en un tiempo específico
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarListaDeAjustadoresManejaronVehiculoEnUnTiempo(char buffer[], MYSQL mysql)
{
    char hora[TIEMPO];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i, j;

    j = 1;

    printf("Ingresa la hora con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", hora);

    sprintf(buffer, "SELECT DISTINCT(CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno)) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) WHERE hora_inicio <= '%s' AND hora_fin >= '%s';", hora, hora);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---LISTA DE AJUSTADORES QUE MANEJARON UN VEHÍCULO A LAS %s----\n\n", hora);
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        printf("-> Ajustador #%d\n", j);

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
        j++;
        fputc('\n',stdout);
    }
    mysql_free_result(res);

}

/**
 * @brief Procedimiento que muestra la lista de los siniestros atendidos por un ajustador en particular
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarSiniestrosDeUnAjustador(char buffer[], MYSQL mysql)
{
    char ajustador[DATOS];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i, j, validar, id;

    validar = 0;
    j = 1;


    while(validar == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("Ingresa el ID del ajustador: ");
        scanf(" %d", &id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", id);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }
        
        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        // Despliega el resultado del ID
        if ((row = mysql_fetch_row(res))) {
            validar = atoi(row[0]);
        }
        
        if(validar == 0)
        {
            system("clear");
            printf("El ajustador no está registrado.\n\n");
        }
    }
    mysql_free_result(res);
    system("clear");

    // Busca el nombre del ajustador
    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) FROM pr1_ajustadores WHERE idAjustador = %d;", id);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del ID
    if ((row = mysql_fetch_row(res))) {
       strcpy(ajustador, row[0]);
    }

    mysql_free_result(res);

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno, ' ') AS nombre, idSiniestro FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) HAVING nombre LIKE '%%%s%%';", ajustador);
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("----LISTA DE SINIESTROS DEL AJUSTADOR: %s----\n\n", ajustador);
    while( (row = mysql_fetch_row(res)) )
    {
        i = 0;

        printf("-> Siniestro #%d\n", j);

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
        j++;
        fputc('\n',stdout);
    }
    mysql_free_result(res);
}


/**
 * @brief Procedimiento que muestra los ajustadores que menos siniestros atienden
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarAjustadoresMenosSiniestrosAtienden(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre ORDER BY COUNT(idSiniestro) ASC LIMIT 1);");
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---AJUSTADORES QUE MENOS SINIESTROS ATIENDEN----\n\n");
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
 * @brief Procedimiento que muestra el ajustador que más siniestros atienden
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarAjustadoresMasSiniestrosAtienden(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre ORDER BY COUNT(idSiniestro) DESC LIMIT 1);");
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---AJUSTADORES QUE MÁS SINIESTROS ATIENDEN----\n\n");
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
 * @brief Procedimiento que muestra los usuarios que menos usan el sistema
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void mostrarUsuariosMenosUsan(char buffer[], MYSQL mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;

    sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_usuarios LEFT JOIN pr1_siniestros USING(idUsuario) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_usuarios LEFT JOIN pr1_siniestros USING(idUsuario) GROUP BY nombre ORDER BY COUNT(idSiniestro) ASC LIMIT 1);");
    if( mysql_query(&mysql, buffer) ){
    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
    exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Despliega el resultado del query
    printf("---USUARIOS QUE MENOS USAN EL SISTEMA----\n\n");
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
 * @brief Procedimiento que despliega el submenú de Consultar Información
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

extern void menuConsultarInfo(MYSQL mysql)
{
    char buffer[MAX];
    unsigned int opcion, bandera, flag;

    opcion = 0;
    bandera = 0;
    strcpy(buffer, "\0");

    sprintf(buffer, "set sql_mode = ' ';");

    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    while(bandera == 0)
    {
        printf("---Consultar datos nuevos---\n\n\n");
        printf("\t-> 1) Usuarios que menos usan el sistema\n\n\t-> 2) Ajustadores y siniestros\n\n\t-> 3) Lista de ajustadores registrados en el sistema\n\n\t-> 4) Lista de siniestro de un ajustador en particular\n\n");
        printf("\t-> 5) Lista de ajustadores que manejaron un vehículo en un periodo de tiempo\n\n\t-> 6) Lista de colonias donde más siniestros ocurren\n\n\t-> 7) Periodo del día donde más siniestros ocurren\n\n\t-> 8) Cantidad de siniestros que ocurren en cierto periodo de tiempo\n\n");
        printf("\t-> 9) Nombre del ajustador/es que manejó un vehículo en un periódo de tiempo determinado\n\n\t-> 10) Última poición de un ajustador en particular\n\n\t-> 11) Lista de vehículos que manejó un ajustador en un tiempo específico\n\n\t-> 12) Regresar\n\n\n");
        printf("Ingresa una opción: ");
        scanf(" %d", &opcion);

        switch(opcion)
        {
            case 1:
            system("clear");
            mostrarUsuariosMenosUsan(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 2:
            system("clear");
            flag = 0;
            while(flag == 0)
            {
                printf("---¿Cuál opción?---\n\n");
                printf("\t-> 1) Ajustadores que más siniestros atienden\n\t-> 2) Ajustadores que menos siniestros atienden\n\t-> 3) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %d", &opcion);
                switch(opcion)
                {
                    case 1:
                    system("clear");
                    mostrarAjustadoresMasSiniestrosAtienden(buffer, mysql);
                    __fpurge(stdin);
                    printf("Presiona \"enter\" para continuar -> ");
                    getchar();
                    system("clear");
                    break;

                    case 2:
                    system("clear");
                    mostrarAjustadoresMenosSiniestrosAtienden(buffer, mysql);
                    __fpurge(stdin);
                    printf("Presiona \"enter\" para continuar -> ");
                    getchar();
                    system("clear");
                    break;

                    case 3:
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Selecciona una opción correcta.\n\n");
                    break;
                }
            }
            break;

            case 3:
            system("clear");
            mostrarAjustadores(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 4:
            system("clear");
            mostrarSiniestrosDeUnAjustador(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 5:
            system("clear");
            mostrarListaDeAjustadoresManejaronVehiculoEnUnTiempo(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 6:
            system("clear");
            mostrarColoniasDondeMasSiniestrosPasan(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 7:
            system("clear");
            mostrarPeriodoDiaDondeMasSiniestrosPasan(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 8:
            system("clear");
            mostrarCantidadDeSiniestrosEnTiempo(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 9:
            system("clear");
            mostrarAjustadoresManejaronUnVehiculoEnTiempoFijo(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 10:
            system("clear");
            mostrarUltimaPosicionDeAjustador(buffer, mysql);
            __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 11:
            system("clear");
            mostrarListaVehiculosManejoAjustadorEnTiempoFijo(buffer, mysql);
             __fpurge(stdin);
            printf("Presiona \"enter\" para continuar -> ");
            getchar();
            system("clear");
            break;

            case 12:
            system("clear");
            bandera = 1;
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida.\n\n");
            break;
        }
    }
}