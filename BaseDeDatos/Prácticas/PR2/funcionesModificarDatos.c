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
 * @date Última modificación: 12 de Noviembre del 2023
*/

#include "def.h"

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