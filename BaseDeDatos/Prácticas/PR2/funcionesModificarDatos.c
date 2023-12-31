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
 * @date Última modificación: 16 de Noviembre del 2023
*/

#include "def.h"

/**
 * @brief Procedimiento que borra una colonia cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 16/11/2023
*/

void borrarSiniestro(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    siniestro registro;

    contador = 3;
    validacion = 0;

    while(validacion == 0)
    {
        mostrarSiniestros(buffer, mysql);
        printf("Ingresa el ID del siniestro que quieras borrar: ");
        scanf(" %d", &registro.idSiniestro);

        // Ejecuta el query
        sprintf(buffer, "SELECT idSiniestro FROM pr1_siniestros WHERE idSiniestro = %d;", registro.idSiniestro);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El siniestro no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_siniestros WHERE idSiniestro = %d;", registro.idSiniestro);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
    
}

/**
 * @brief Procedimiento que muestra la información necesaria para realizar de manera correcta la modificación del ajustador, fecha y hora 
 * @param Integer: num_args
 * @param String: buffer[]
 * @param Struct: mysql
 * @param Pointer: *ver
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 14/11/2023
*/

void mostrarTiempoPasoaPaso(char buffer[], MYSQL mysql, int *ver, int num_args, ...)
{
    //mostrarTiempo(char *query, MYSQL mysql, char *fecha, char *hora)
    va_list args;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char **cadena;
    int i;

    cadena = (char **)malloc(sizeof(char **));
    if(cadena == NULL)
    {
        system("clear");
        printf("Memoria insuficiente.\n\n");
        exit(1);
    }

    va_start(args, num_args);

    for (i = 0; i < num_args; i++) {
        *(cadena + i) = va_arg(args, char *);
    }

    va_end(args);

    //if(!hora)
    if(num_args == 1)
    {
        sprintf(buffer, "SELECT idAV, CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno), hora_inicio, hora_fin FROM pr1_A_V LEFT JOIN pr1_ajustadores USING(idAjustador) WHERE fecha = '%s';", cadena[0]);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        
        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        if (mysql_field_count(&mysql) == 0)
        {
            printf("No hay datos existentes.\n\n");
            *ver = 1;
        }

        else
        {
            // Despliega el resultado del query
            printf("---JORNADAS REGISTRADAS EL DÍA %s---\n\n", cadena[0]);
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
        }
        
    }

    else
    {
        sprintf(buffer, "SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno), idAjustador FROM pr1_A_V LEFT JOIN pr1_ajustadores USING(idAjustador) WHERE fecha = '%s' AND hora_inicio <= '%s' AND hora_fin >= '%s';", cadena[0], cadena[1], cadena[1]);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }
        
        // Obtiene el query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        if(mysql_field_count(&mysql) == 0)
        {
            printf("No hay datos existentes\n\n");
            *ver = 1;

        }
        else
        {
            // Despliega el resultado del query
                printf("---JORNADAS REGISTRADAS EL DÍA %s DONDE EXISTE LA HORA %s---\n\n", cadena[0], cadena[1]);
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
        }
    }
        
    mysql_free_result(res);
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un  de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 14/11/2023
*/

void modificarSiniestro(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag, conf;
    MYSQL_RES *res;
    MYSQL_ROW row;
    siniestro registro;
    int verifica;
    char final;
    char ubi[DATOS];
    
    opcion = 0;
    validacion = 0;
    flag = 0;
    conf = 0;
    verifica = 0;

    while(validacion == 0)
    {
        mostrarSiniestros(buffer, mysql);
        printf("Ingresa el ID del siniestro que quieras modificar: ");
        scanf(" %d", &registro.idSiniestro);

        // Ejecuta el query
        sprintf(buffer, "SELECT idSiniestro FROM pr1_siniestros WHERE idSiniestro = %d;", registro.idSiniestro);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El siniestro no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Fecha, Hora y Ajustador\n\t2) Usuario\n\t3) Colonia\n\t4) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            strcpy(registro.fecha, "\0");
            strcpy(registro.hora, "\0");
            system("clear");
            while(flag == 1)
            {
                printf("---¿Cuál de estas opciones?---\n\n");
                printf("\t1) Fecha en la que ocurrió el siniestro\n\t2) Hora en la que ocurrió el siniestro\n\t3) Ajustador que atendió el siniestro\n\t4) Confirmar datos\n\n");
                printf("Ingresa la opción que desee realizar: ");
                scanf(" %d", &opcion);

                switch(opcion)
                {
                    case 1:
                    system("clear");
                    printf("Ingresa la fecha con el formato 'AAAA-MM-DD' (incluyendo los '-'): ");
                    scanf(" %[^\n]", registro.fecha);
                    system("clear");
                    conf = 1;
                    break;

                    case 2:
                    system("clear");
                    if(conf == 0)
                    {
                        system("clear");
                        printf("Debes de ingresar primero la fecha.\n\n");
                    }
                    else
                    {
                        validacion = 0;
                        while(validacion == 0)
                        {
                            mostrarTiempoPasoaPaso(buffer, mysql, &verifica, 1, registro.fecha);
                            printf("Ingresa la hora con el formato 'HH:MM:DD' (incluyendo los ':'): ");
                            scanf(" %[^\n]", registro.hora);

                            // Ejecuta el query
                            sprintf(buffer, "CALL validarHora2('%s', '%s', @val);", registro.hora, registro.fecha);
                            if( mysql_query(&mysql, buffer) ){
                                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                                exit(1);
                            }

                            sprintf(buffer, "SELECT @val;");
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
                                validacion = atoi(row[0]);
                            }
                            
                            if(validacion == 0)
                            {
                                system("clear");
                                printf("La hora no está en el rango.\n\n");
                            }
                        }

                        mysql_free_result(res);
                        system("clear");
                        conf = 2;
                    }
                    break;

                    case 3:
                    system("clear");
                    if(conf == 1 || conf == 0)
                    {
                        printf("Debes de ingresar primero la hora.\n\n");
                    }
                    else
                    {
                        validacion = 0;
                        while(validacion == 0)
                        {
                            mostrarTiempoPasoaPaso(buffer, mysql, &verifica, 2, registro.fecha, registro.hora);
                            if(verifica == 1)
                            {
                                printf("No hay datos existentes, intentelo de nuevo.\n\nPresione \"enter para regresar\" -> ");
                                getchar();
                                getchar();
                                system("clear");
                                validacion = 1;
                                conf = 0;
                            }
                            else
                            {
                                printf("Ingresa el ID del ajustador: ");
                                scanf(" %d", &registro.idAjustador);

                                // Ejecuta el query
                                sprintf(buffer, "SELECT idAjustador FROM pr1_A_V WHERE idAjustador = %d AND fecha = '%s' AND hora_inicio <= '%s' AND hora_fin >= '%s';", registro.idAjustador, registro.fecha, registro.hora, registro.hora);
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
                                    validacion = atoi(row[0]);
                                }
                                
                                if(validacion == 0)
                                {
                                    system("clear");
                                    printf("El ajustador ingresado no trabajó ese día.\n\n");
                                }
                            }

                        }
                        mysql_free_result(res);
                        system("clear");
                        conf=3;
                    }
                    break;

                    case 4:
                    system("clear");
                    if(conf != 3)
                    {
                        printf("No se han ingresado los datos suficientes para realizar la insersión.\n\n");
                    }
                    else
                    {
                        flag = 0;

                        sprintf(buffer, "UPDATE pr1_siniestros SET fecha = '%s' WHERE idSiniestro = %d", registro.fecha, registro.idSiniestro);
                        if( mysql_query(&mysql, buffer) ){
                            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                            exit(1);
                        }
                        else
                        {
                            sprintf(buffer, "UPDATE pr1_siniestros SET hora = '%s' WHERE idSiniestro = %d", registro.hora, registro.idSiniestro);
                            if( mysql_query(&mysql, buffer) ){
                                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                                exit(1);
                            }
                            else
                            {
                                sprintf(buffer, "UPDATE pr1_siniestros SET idAjustador = %d WHERE idSiniestro = %d", registro.idAjustador, registro.idSiniestro);
                                if( mysql_query(&mysql, buffer) ){
                                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                                    exit(1);
                                }
                                else
                                {
                                    system("clear");
                                    printf("¡¡¡Datos actualizados con éxito!!!\n\n");
                                }
                            }
                        }

                    }
                    break;

                    default:
                    system("clear");
                    printf("Ingresa una opción correcta.\n\n");
                    break;

                }
            }
            break;

            case 2:
            system("clear");
            validacion = 0;
            while(validacion == 0)
            {
                mostrarUsuarios(buffer, mysql);
                printf("Ingresa el ID del nuevo usuario que quieras modificar: ");
                scanf(" %d", &registro.idUsuario);
                sprintf(buffer, "SELECT idUsuario FROM pr1_usuarios WHERE idUsuario = %d", registro.idUsuario);
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
                    validacion = atoi(row[0]);
                }
                
                if(validacion == 0)
                {
                    system("clear");
                    printf("El usuario no está registrado.\n\n");
                }
            }
            mysql_free_result(res);
            
            sprintf(buffer, "UPDATE pr1_siniestros SET idUsuario = %d WHERE idSiniestro = %d", registro.idUsuario, registro.idSiniestro);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 3:
            system("clear");
            validacion = 1;
            while(validacion != 0)
            {
                mostrarColonias(buffer, mysql);
                printf("Ingresa el nombre de la colonia: ");
                scanf(" %[^\n]", ubi);

                //Verifica si la colonia está registrada
                sprintf(buffer, "CALL validarColonia('%s', @val);", ubi);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                sprintf(buffer, "SELECT @val;");
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                //Captura el resultado del Query
                if( !(res = mysql_store_result(&mysql)) ){
                    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                    exit(1);
                }

                if ((row = mysql_fetch_row(res))) {
                    validacion = atoi(row[0]);
                }

                if(validacion == 1){
                    system("clear");
                    printf("La colonia no está registrada.\n\n");
                }
            }

            system("clear");
            mysql_free_result(res);

            //Busca el id de la colonia
            sprintf(buffer, "SELECT idColonia FROM pr1_colonias WHERE colonia = '%s';", ubi);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            
            //Captura el resultado del Query
            if( !(res = mysql_store_result(&mysql)) ){
                fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                exit(1);
            }

            if ((row = mysql_fetch_row(res))) {
                registro.idColonia = atoi(row[0]);
            }
            mysql_free_result(res);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_siniestros SET idColonia = %d WHERE idSiniestro = %d;", registro.idColonia, registro.idSiniestro);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else
            {
                system("clear");
                printf("¡¡¡Datos guardados con éxito!!!\n\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que borra una colonia cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Jjavier Lachica Sánchez 
 * @date 14/11/2023
*/

void borrarLlamada(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    siniestro llamada;

    contador = 3;
    validacion = 0;

    while(validacion == 0)
    {
        mostrarLlamadas(buffer, mysql);
        printf("Ingresa el ID de la llamada que quieras borrar: ");
        scanf(" %d", &llamada.idLlamada);

        // Ejecuta el query
        sprintf(buffer, "SELECT idOS FROM pr1_O_S WHERE idOS = %d;", llamada.idLlamada);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("La llamada no está registrada.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_O_S WHERE idOS = %d;", llamada.idLlamada);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un vehículo de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 14/11/2023
*/

void modificarLlamada(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    siniestro llamada;

    opcion = 0;
    validacion = 0;
    flag = 0;

    while(validacion == 0)
    {
        mostrarLlamadas(buffer, mysql);
        printf("Ingresa el ID de la llamada que quieras modificar: ");
        scanf(" %d", &llamada.idLlamada);

        // Ejecuta el query
        sprintf(buffer, "SELECT idOS FROM pr1_O_S WHERE idOS = %d;", llamada.idLlamada);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("La llamada no está registrada.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Operador que atendió la llamada\n\t2) Siniestro atendido\n\t3) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            validacion = 0;
            while(validacion == 0)
            {
                mostrarOperadores(buffer, mysql);
                printf("Ingresa el ID del operador que deseas modificar: ");
                scanf(" %d", &llamada.idOperador);

                //Verifica si la colonia está registrada
                sprintf(buffer, "SELECT idOperador FROM pr1_operadores WHERE idOperador = %d", llamada.idOperador);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                //Captura el resultado del Query
                if( !(res = mysql_store_result(&mysql)) ){
                    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                    exit(1);
                }

                if ((row = mysql_fetch_row(res))) {
                    validacion = atoi(row[0]);
                }

                if(validacion == 0){
                    system("clear");
                    printf("El operador no está registrado.\n\n");
                }
            }

            mysql_free_result(res);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_O_S SET idOperador = %d WHERE idOS = %d;", llamada.idOperador, llamada.idLlamada);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else
            {
                system("clear");
                printf("¡¡¡Datos guardados con éxito!!!\n\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            validacion = 0;
            while(validacion == 0)
            {
                mostrarSiniestros(buffer, mysql);
                printf("Ingresa el ID del siniestro que deseas modificar: ");
                scanf(" %d", &llamada.idSiniestro);

                //Verifica si la colonia está registrada
                sprintf(buffer, "SELECT idSiniestro FROM pr1_O_S WHERE idSiniestro = %d", llamada.idSiniestro);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                //Captura el resultado del Query
                if( !(res = mysql_store_result(&mysql)) ){
                    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                    exit(1);
                }

                if ((row = mysql_fetch_row(res))) {
                    validacion = atoi(row[0]);
                }

                if(validacion == 0){
                    system("clear");
                    printf("El siniestro no está registrado.\n\n");
                }
            }

            mysql_free_result(res);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_O_S SET idSiniestro = %d WHERE idOS = %d;", llamada.idSiniestro, llamada.idLlamada);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else
            {
                system("clear");
                printf("¡¡¡Datos guardados con éxito!!!\n\n\n");
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que borra una colonia cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void borrarActividad(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    actividad jornada;

    contador = 3;
    validacion = 0;

    while(validacion == 0)
    {
        mostrarActividad(buffer, mysql);
        printf("Ingresa el ID de la actividad que quieras borrar: ");
        scanf(" %d", &jornada.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAV FROM pr1_A_V WHERE idAV = %d;", jornada.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("La jornada no está registrada.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_A_V WHERE idAV = %d;", jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un vehículo de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void modificarActividad(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    actividad jornada;

    opcion = 0;
    validacion = 0;
    flag = 0;

    while(validacion == 0)
    {
        mostrarActividad(buffer, mysql);
        printf("Ingresa el ID de la jornada que quieras modificar: ");
        scanf(" %d", &jornada.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAV FROM pr1_A_V WHERE idAV = %d;", jornada.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("La jornada no está registrada.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Hora de inicio y fin\n\t2) Fecha\n\t3) Ajustador\n\t4) Vehículo\n\t5) Kilometraje\n\t6) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            while(validacion != 0)
            {
                printf("Ingresa la hora de inicio con el siguiente formato 'HH:MM:SS' (incluyendo los ':'): ");
                scanf(" %[^\n]", jornada.horaInicio);
                printf("Ingresa la hora de fin con el siguiente formato 'HH:MM:SS' (incluyendo los ':'): ");
                scanf(" %[^\n]", jornada.horaFin);

                // Ejecuta el query
                sprintf(buffer, "CALL validarRango('%s', '%s', @val);", jornada.horaInicio, jornada.horaFin);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                sprintf(buffer, "SELECT @val");
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
                    validacion = atoi(row[0]);
                }
                
                if(validacion != 0)
                {
                    system("clear");
                    printf("La hora de inicio debe de ser menor a la hora fin.\n\n");
                }

            }

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_A_V SET hora_inicio = '%s' WHERE idAV = %d;", jornada.horaInicio, jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                sprintf(buffer, "UPDATE pr1_A_V SET hora_fin = '%s' WHERE idAV = %d;", jornada.horaFin, jornada.id);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }
                else{
                    system("clear");
                    printf("¡¡¡Datos Guardados con éxito!!!\n\n");
                }
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            printf("Ingresa la fecha con el formato 'AAAA-MM-DD' (incluyendo los '-'): ");
            scanf(" %[^\n]", jornada.fecha);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_A_V SET fecha = '%s' WHERE idAV = %d;", jornada.fecha, jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            validacion = 0;
            while(validacion == 0)
            {
                mostrarAjustadores(buffer, mysql);
                printf("Ingresa el ID del ajustador que quieras modificar: ");
                scanf(" %d", &jornada.idAjustador);

                // Ejecuta el query
                sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", jornada.idAjustador);
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
                    validacion = atoi(row[0]);
                }
                
                if(validacion == 0)
                {
                    system("clear");
                    printf("El ajustador no está registrado.\n\n");
                }
            }
            

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_A_V SET idAjustador = %d WHERE idAV = %d;", jornada.idAjustador, jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            validacion = 0;
            while(validacion == 0)
            {
                mostrarVehiculos(buffer, mysql);
                printf("Ingresa el ID del vehículo que quieras modificar: ");
                scanf(" %d", &jornada.idVehiculo);

                // Ejecuta el query
                sprintf(buffer, "SELECT idVehiculo FROM pr1_vehiculos WHERE idVehiculo = %d;", jornada.idVehiculo);
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
                    validacion = atoi(row[0]);
                }
                
                if(validacion == 0)
                {
                    system("clear");
                    printf("El vehículo no está registrado.\n\n");
                }
            }
            

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_A_V SET idVehiculo = %d WHERE idAV = %d;", jornada.idVehiculo, jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 5:
            flag = 1;
            system("clear");
            printf("Ingresa el kilometraje: ");
            scanf(" %d", &jornada.km);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_A_V SET kilometraje = %d WHERE idAV = %d;", jornada.km, jornada.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 6:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que borra una colonia cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void borrarVehiculo(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    vehiculo carro;

    contador = 3;

    while(validacion == 0)
    {
        mostrarVehiculos(buffer, mysql);
        printf("Ingresa el ID del vehículo que quieras borrar: ");
        scanf(" %d", &carro.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idVehiculo FROM pr1_vehiculos WHERE idVehiculo = %d;", carro.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El operador no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_vehiculos WHERE idVehiculo = %d;", carro.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un vehículo de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void modificarVehiculo(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    vehiculo carro;
    char ubi[DATOS];

    opcion = 0;
    flag = 0;
    validacion = 0;

    while(validacion == 0)
    {
        mostrarVehiculos(buffer, mysql);
        printf("Ingresa el ID del vehículo que deseas modificar que quieras modificar: ");
        scanf(" %d", &carro.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idVehiculo FROM pr1_vehiculos WHERE idVehiculo = %d;", carro.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El vehículo no está registrado.\n\n");
        }

        
    }

    system("clear");
    mysql_free_result(res);

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Modelo\n\t2) Ubicación actual\n\t3) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            printf("Ingresa el modelo: ");
            scanf(" %[^\n]", carro.modelo);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_vehiculos SET modelo = '%s' WHERE idVehiculo = %d;", carro.modelo, carro.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            while(validacion != 0)
            {
                mostrarColonias(buffer, mysql);
                printf("Ingresa la colonia en la que está el vehículo: ");
                scanf(" %[^\n]", ubi);

                //Verifica si la colonia está registrada
                sprintf(buffer, "CALL validarColonia('%s', @val);", ubi);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                sprintf(buffer, "SELECT @val;");
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }

                //Captura el resultado del Query
                if( !(res = mysql_store_result(&mysql)) ){
                    fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                    exit(1);
                }

                if ((row = mysql_fetch_row(res))) {
                    validacion = atoi(row[0]);
                }

                if(validacion == 1){
                    system("clear");
                    printf("La colonia no está registrada.\n\n");
                }
            }

            mysql_free_result(res);

            //Busca el id de la colonia
            sprintf(buffer, "SELECT idColonia FROM pr1_colonias WHERE colonia = '%s';", ubi);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            
            //Captura el resultado del Query
            if( !(res = mysql_store_result(&mysql)) ){
                fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
                exit(1);
            }

            if ((row = mysql_fetch_row(res))) {
                carro.idColonia = atoi(row[0]);
            }
            mysql_free_result(res);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_vehiculos SET idColonia = %d WHERE idVehiculo = %d;", carro.idColonia, carro.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else
            {
                system("clear");
                printf("¡¡¡Datos guardados con éxito!!!\n\n\n");
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que borra una colonia cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void borrarColonia(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    colonia col;

    contador = 3;

    while(validacion != 0)
    {
        mostrarColonias(buffer, mysql);
        printf("Ingresa el nombre de la colonia que quieras borrar: ");
        scanf(" %[^\n]", col.nombre);

        //Verifica si la colonia está registrada
        sprintf(buffer, "CALL validarColonia('%s', @val);", col.nombre);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        sprintf(buffer, "SELECT @val;");
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        //Captura el resultado del Query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        if ((row = mysql_fetch_row(res))) {
            validacion = atoi(row[0]);
        }

        if(validacion == 1){
            system("clear");
            printf("La colonia no está registrada.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    //Busca el id de la colonia
    sprintf(buffer, "SELECT idColonia FROM pr1_colonias WHERE colonia = '%s';", col.nombre);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    
    //Captura el resultado del Query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    if ((row = mysql_fetch_row(res))) {
        col.id = atoi(row[0]);
    }
    mysql_free_result(res);

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_colonias WHERE idColonia = %d;", col.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de una colonia de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 13/11/2023
*/

void modificarColonia(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    colonia col;

    opcion = 0;
    flag = 0;

    while(validacion != 0)
    {
        mostrarColonias(buffer, mysql);
        printf("Ingresa el nombre de la colonia que deseas modificar que quieras modificar: ");
        scanf(" %[^\n]", col.nombre);

        //Verifica si la colonia está registrada
        sprintf(buffer, "CALL validarColonia('%s', @val);", col.nombre);
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        sprintf(buffer, "SELECT @val;");
        if( mysql_query(&mysql, buffer) ){
            fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
            exit(1);
        }

        //Captura el resultado del Query
        if( !(res = mysql_store_result(&mysql)) ){
            fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
            exit(1);
        }

        if ((row = mysql_fetch_row(res))) {
            validacion = atoi(row[0]);
        }

        if(validacion == 1){
            system("clear");
            printf("La colonia no está registrada.\n\n");
        }
        
    }

    mysql_free_result(res);
    system("clear");

    //Busca el id de la colonia
    sprintf(buffer, "SELECT idColonia FROM pr1_colonias WHERE colonia = '%s';", col.nombre);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    
    //Captura el resultado del Query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    if ((row = mysql_fetch_row(res))) {
        col.id = atoi(row[0]);
    }
    mysql_free_result(res);

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Nombre\n\t2) Alcaldía\n\t3) Código Postal\n\t4) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            printf("Ingresa el nombre: ");
            scanf(" %[^\n]", col.nombre);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_colonias SET colonia = '%s' WHERE idColonia = %d;", col.nombre, col.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            printf("Ingresa la alcaldía: ");
            scanf(" %[^\n]", col.alcaldia);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_colonias SET alcaldia = '%s' WHERE idColonia = %d;", col.alcaldia, col.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else
            {
                system("clear");
                printf("¡¡¡Datos guardados con éxito!!!\n\n\n");
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            printf("Ingresa el nuevo código postal: ");
            scanf(" %d", &col.cp);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_colonias SET codigo_postal = %d WHERE idColonia = %d;", col.cp, col.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que borra un operador cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void borrarOperador(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona operador;

    validacion = 0;
    contador = 3;

    while(validacion == 0)
    {
        mostrarOperadores(buffer, mysql);
        printf("Ingresa el ID del operador que quieras borrar: ");
        scanf(" %d", &operador.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idOperador FROM pr1_operadores WHERE idOperador = %d;", operador.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El operador no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_operadores WHERE idOperador = %d;", operador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un operador de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void modificarOperador(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona operador;

    opcion = 0;
    validacion = 0;
    flag = 0;

    while(validacion == 0)
    {
        mostrarOperadores(buffer, mysql);
        printf("Ingresa el ID del operador que quieras modificar: ");
        scanf(" %d", &operador.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idOperador FROM pr1_operadores WHERE idOperador = %d;", operador.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El operador no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Nombre\n\t2) Apellidos\n\t3) Teléfono\n\t4) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            printf("Ingresa el nombre: ");
            scanf(" %[^\n]", operador.nombre);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_operadores SET nombre = '%s' WHERE idOperador = %d;", operador.nombre, operador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            printf("Ingresa el apellido paterno: ");
            scanf(" %[^\n]", operador.ap_paterno);
            printf("Ingresa el apellido materno: ");
            scanf(" %[^\n]", operador.ap_materno);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_operadores SET ap_paterno = '%s' WHERE idOperador = %d;", operador.ap_paterno, operador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                sprintf(buffer, "UPDATE pr1_operadores SET ap_materno = '%s' WHERE idOperador = %d;", operador.ap_materno, operador.id);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }
                else{
                    system("clear");
                    printf("¡¡¡Datos actualizados con éxito!!!\n\n");
                } 
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            printf("Ingresa el nuevo número telefónico: ");
            scanf(" %[^\n]", operador.celular);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_operadores SET telefono = '%s' WHERE idOperador = %d;", operador.celular, operador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }

}

/**
 * @brief Procedimiento que borra un ajustador cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void borrarAjustador(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona ajustador;

    validacion = 0;
    contador = 3;

    while(validacion == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("Ingresa el ID del ajustador que quieras borrar: ");
        scanf(" %d", &ajustador.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", ajustador.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El ajustador no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_ajustadores WHERE idAjustador = '%d';", ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un ajustador de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void modificarAjustador(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona ajustador;

    opcion = 0;
    validacion = 0;
    flag = 0;

    while(validacion == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("Ingresa el ID del ajustador que quieras modificar: ");
        scanf(" %d", &ajustador.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", ajustador.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El ajustador no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Nombre\n\t2) Apellidos\n\t3) Celular\n\t4) Correo\n\t5) Contraseña\n\t6) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            printf("Ingresa el nombre: ");
            scanf(" %[^\n]", ajustador.nombre);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_ajustadores SET nombre = '%s' WHERE idAjustador = '%d';", ajustador.nombre, ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            printf("Ingresa el apellido paterno: ");
            scanf(" %[^\n]", ajustador.ap_paterno);
            printf("Ingresa el apellido materno: ");
            scanf(" %[^\n]", ajustador.ap_materno);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_ajustadores SET ap_paterno = '%s' WHERE idAjustador = %d;", ajustador.ap_paterno, ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                sprintf(buffer, "UPDATE pr1_ajustadores SET ap_materno = '%s' WHERE idAjustador = %d;", ajustador.ap_materno, ajustador.id);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }
                else{
                    system("clear");
                    printf("¡¡¡Datos actualizados con éxito!!!\n\n");
                } 
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            printf("Ingresa el nuevo número telefónico: ");
            scanf(" %[^\n]", ajustador.celular);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_ajustadores SET celular = '%s' WHERE idAjustador = '%d';", ajustador.celular, ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            printf("Ingresa el correo nuevo: ");
            scanf(" %[^\n]", ajustador.correo);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_ajustadores SET correo = '%s' WHERE idAjustador = '%d';", ajustador.correo, ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 5:
            flag = 1;
            system("clear");
            printf("Ingresa la contraseña nueva: ");
            scanf(" %[^\n]", ajustador.contrasena);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_ajustadores SET contraseña = '%s' WHERE idAjustador = '%d';", ajustador.contrasena, ajustador.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 6:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }

}

/**
 * @brief Procedimiento que borra un usuario cuando el usuario que usa el programa lo confirme 3 veces
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void borrarUsuario(char buffer[], MYSQL mysql)
{
    int contador;
    unsigned int validacion;
    char confirmacion;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona usuario;

    validacion = 0;
    contador = 3;

    while(validacion == 0)
    {
        mostrarUsuarios(buffer, mysql);
        printf("Ingresa el ID del usuario que quieras borrar: ");
        scanf(" %d", &usuario.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idUsuario FROM pr1_usuarios WHERE idUsuario = %d;", usuario.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El usuario no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(contador > 0)
    {
        printf("¿Estás seguro?\n\n\t[S]í\t[N]o (Confirmación: %d): ", contador);
        scanf(" %c", &confirmacion);
        if(confirmacion == 'S' || confirmacion == 's')
        {
            contador--;
            printf("\n\n");
        }
        else
        {
            contador = 0;
        }
    }

    if(confirmacion == 'S' || confirmacion == 's')
    {
        // Ejecuta el query
            sprintf(buffer, "DELETE FROM pr1_usuarios WHERE idUsuario = '%d';", usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos borrados con éxito!!!\n\n");
            }
    }

    else
    {
        system("clear");
        printf("Procedimiento cancelado.\n\n");
    }
}

/**
 * @brief Procedimiento que despliega un menú para mostrarle a la persona que ocupa el programa las opciones que
 *        puede modificar de un usuario de la base de datos. Una vez que se ingresa la opción a realizar, el programa
 *        solicita los nuevos datos para realizar el cambio.
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 12/11/2023
*/

void modificarUsuario(char buffer[], MYSQL mysql)
{
    unsigned int opcion, validacion, flag;
    MYSQL_RES *res;
    MYSQL_ROW row;
    persona usuario;

    opcion = 0;
    validacion = 0;
    flag = 0;

    while(validacion == 0)
    {
        mostrarUsuarios(buffer, mysql);
        printf("Ingresa el ID del usuario que quieras modificar: ");
        scanf(" %d", &usuario.id);

        // Ejecuta el query
        sprintf(buffer, "SELECT idUsuario FROM pr1_usuarios WHERE idUsuario = %d;", usuario.id);
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
            validacion = atoi(row[0]);
        }
        
        if(validacion == 0)
        {
            system("clear");
            printf("El usuario no está registrado.\n\n");
        }
    }

    mysql_free_result(res);
    system("clear");

    while(flag == 0)
    {
        printf("---¿Qué deseas modificar?---\n\n");
        printf("\t1) Nombre\n\t2) Apellidos\n\t3) Celular\n\t4) Correo\n\t5) Contraseña\n\t6) Regresar\n\n");
        printf("Ingresa la opción que desee realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            flag = 1;
            system("clear");
            printf("Ingresa el nombre: ");
            scanf(" %[^\n]", usuario.nombre);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_usuarios SET nombre = '%s' WHERE idUsuario = '%d';", usuario.nombre, usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 2:
            flag = 1;
            system("clear");
            printf("Ingresa el apellido paterno: ");
            scanf(" %[^\n]", usuario.ap_paterno);
            printf("Ingresa el apellido materno: ");
            scanf(" %[^\n]", usuario.ap_materno);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_usuarios SET ap_paterno = '%s' WHERE idUsuario = %d;", usuario.ap_paterno, usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                sprintf(buffer, "UPDATE pr1_usuarios SET ap_materno = '%s' WHERE idUsuario = %d;", usuario.ap_materno, usuario.id);
                if( mysql_query(&mysql, buffer) ){
                    fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                    exit(1);
                }
                else{
                    system("clear");
                    printf("¡¡¡Datos actualizados con éxito!!!\n\n");
                } 
            }
            break;

            case 3:
            flag = 1;
            system("clear");
            printf("Ingresa el nuevo número telefónico: ");
            scanf(" %[^\n]", usuario.celular);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_usuarios SET celular = '%s' WHERE idUsuario = '%d';", usuario.celular, usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 4:
            flag = 1;
            system("clear");
            printf("Ingresa el correo nuevo: ");
            scanf(" %[^\n]", usuario.correo);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_usuarios SET correo = '%s' WHERE idUsuario = '%d';", usuario.correo, usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 5:
            flag = 1;
            system("clear");
            printf("Ingresa la contraseña nueva: ");
            scanf(" %[^\n]", usuario.contrasena);

            // Ejecuta el query
            sprintf(buffer, "UPDATE pr1_usuarios SET contraseña = '%s' WHERE idUsuario = '%d';", usuario.contrasena, usuario.id);
            if( mysql_query(&mysql, buffer) ){
                fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
                exit(1);
            }
            else{
                system("clear");
                printf("¡¡¡Datos actualizados con éxito!!!\n\n");
            }
            break;

            case 6:
            flag = 1;
            system("clear");
            break;

            default:
            system("clear");
            printf("Ingresa una opción válida\n\n");
            break;
        }
    }
}

/**
 * @brief Procedimiento que muestra el submenú de la opción "Modificar Datos"
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 10/11/2023
*/

extern void menuModificarDatos(MYSQL mysql)
{
    char buffer[MAX];
    unsigned int opcion, bandera, flag;
    char opc;
    opcion = 0;
    bandera = 0;
    strcpy(buffer, "\0");

    while(bandera == 0)
    {
        flag = 0;
        printf("---Modificar datos existentes---\n\n");
        printf("\t-> 1) Usuarios\n\t-> 2) Ajustadores\n\t-> 3) Operadores\n\t-> 4) Siniestros\n\t-> 5) Llamadas\n\t-> 6) Vehículos\n\t-> 7) Colonias\n\t-> 8) Actividad de los Ajustadores\n\t-> 9) Regresar\n\n");
        printf("Ingresa una opción que quieras realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Usuario\t b) Borrar Usuario\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarUsuario(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarUsuario(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarUsuario(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarUsuario(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 2:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Ajustador\t b) Borrar Ajustador\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarAjustador(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarAjustador(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarAjustador(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarAjustador(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 3:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Operador\t b) Borrar Operador\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarOperador(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarOperador(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarOperador(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarOperador(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 4:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar siniestro existente\t b) Borrar siniestro existente\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarSiniestro(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarSiniestro(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarSiniestro(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarSiniestro(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 5:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar registro de llamada\t b) Borrar registro de llamada\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarLlamada(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarLlamada(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarLlamada(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarLlamada(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 6:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Vehículo\t b) Borrar Vehículo\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarVehiculo(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarVehiculo(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarVehiculo(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarVehiculo(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 7:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Colonia\t b) Borrar Colonia\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarColonia(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarColonia(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarColonia(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarColonia(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
            break;

            case 8:
            system("clear");
            while(flag == 0)
            {
                printf("---¿Qué deseas realizar?---\n\n");
                printf(" a) Modificar Actividad\t b) Borrar Actividad\t c) Regresar\n\n");
                printf("Ingresa una opción: ");
                scanf(" %c", &opc);
                switch(opc)
                {
                    case 'A':
                    system("clear");
                    flag = 1;
                    modificarActividad(buffer, mysql);
                    break;

                    case 'a':
                    system("clear");
                    flag = 1;
                    modificarActividad(buffer, mysql);
                    break;

                    case 'B':
                    system("clear");
                    flag = 1;
                    borrarActividad(buffer, mysql);
                    break;

                    case 'b':
                    system("clear");
                    flag = 1;
                    borrarActividad(buffer, mysql);
                    break;

                    case 'c':
                    system("clear");
                    flag = 1;
                    break;

                    case 'C':
                    system("clear");
                    flag = 1;
                    break;

                    default:
                    system("clear");
                    printf("Elige una opción correcta.\n\n");
                    break;                    
                }
            }
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