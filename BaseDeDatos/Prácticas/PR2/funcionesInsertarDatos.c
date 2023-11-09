#include "def.h"

/**
 * @brief Procedimiento que despliega la hornada de un ajustador.
 * @param String: buffer[]
 * @param Struct: mysql
 * @param Unsigned_Integer: idAjustador
 * @param String: hora[]
 * @param Pointer: *val
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 8/11/2023
*/

void mostrarJornada(char buffer[], MYSQL mysql, unsigned int idAjustador, char fecha[], unsigned int *val)
{
    MYSQL_RES *res;
    MYSQL_ROW row, *prueba;
    unsigned int i;

     // Ejecuta el query
    sprintf(buffer, "SELECT hora_inicio, hora_fin FROM pr1_A_V WHERE idAjustador = %d AND fecha = '%s';", idAjustador, fecha);
    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    row = mysql_fetch_row(res);

    // Despliega el resultado del query
    printf("---JORNADA---\n\n");
    if(row != NULL)
    {
        while(i < mysql_num_fields(res))
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
        *val = 1;
    }
    else
    {
        *val = 0;
    }

    mysql_free_result(res);
}

/**
 * @brief Procedimiento que ingresa una un nuev siniestro a la base de datos
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 8/11/2023
*/

void ingresarSiniestroNuevo(char buffer[], MYSQL mysql)
{
    siniestro registro;
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int validacion, bandera;
    char ubi[DATOS];
    validacion = 0;
    bandera = 0;

    while(validacion == 0)
    {
        printf("->Ingresa la fecha con el formato 'AAAA-MM-DD' (incluyendo '-'): ");
        scanf(" %[^\n]", registro.fecha);
        mostrarAjustadores(buffer, mysql);
        printf("->Ingresa el ID del ajustador: ");
        scanf(" %d", &registro.idAjustador);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", registro.idAjustador);
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

        // Despliega la jornada del ajustador según la hora del siniestro para confirmar
        else
        {
           system("clear");
           mostrarJornada(buffer, mysql, registro.idAjustador, registro.fecha, &bandera);

           if(bandera == 0)
            {
                printf("La fecha o el ajustador no coincide con ninguno de los registros de la jornada.\n\nPresione \"enter para regresar\" -> ");
                getchar();
                getchar();
                system("clear");
                validacion = 0;
            }

            else
            {
                while(validacion == 1)
                {
                    printf("\n->Ingresa la hora en la que ocurrió el siniestro con el formato 'HH:MM:SS' (incluyendo los ':'): ");
                    scanf(" %[^\n]", registro.hora);

                    sprintf(buffer, "CALL validarHora('%s', '%s', %d, @val);", registro.hora, registro.fecha, registro.idAjustador);
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
                    
                    if(validacion == 1)
                    {
                        system("clear");
                        printf("La hora no forma parte del rango de la jornada del ajustador.\n\n");
                        mostrarJornada(buffer, mysql, registro.idAjustador, registro.fecha, &bandera);
                    }

                }

            }
        }
        mysql_free_result(res);
    }

    validacion = 0;
    system("clear");

    while(validacion == 0)
    {
        mostrarUsuarios(buffer, mysql);
        printf("->Ingresa el ID usuario que sufrió el siniestro: ");
        scanf(" %d", &registro.idUsuario);

        // Ejecuta el query
        sprintf(buffer, "SELECT idUsuario FROM pr1_usuarios WHERE idUsuario = %d;", registro.idUsuario);
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

    while(validacion != 0)
    {
        mostrarColonias(buffer, mysql);
        printf("->Ingresa la colonia en donde ocurrió el siniestro: ");
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
            printf("La colonia no está registrada.\n");
        }
    }
    mysql_free_result(res);
    system("clear");

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
}

/**
 * @brief Procedimiento que registra una actividad nueva de uno de los ajustadores
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 7/11/2023
*/

void ingresarActividadReciente(char buffer[], MYSQL mysql)
{
    actividad nuevoRegistro;
    unsigned int validacion;
    MYSQL_RES *res;
    MYSQL_ROW row;

    validacion = 0;

    while(validacion == 0)
    {
        mostrarAjustadores(buffer, mysql);
        printf("->Ingresa el ID del ajustador: ");
        scanf(" %d", &nuevoRegistro.idAjustador);

        // Ejecuta el query
        sprintf(buffer, "SELECT idAjustador FROM pr1_ajustadores WHERE idAjustador = %d;", nuevoRegistro.idAjustador);
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
    validacion = 0;

    while(validacion == 0)
    {
        mostrarVehiculos(buffer, mysql);
        printf("->Ingresa el ID del vehículo: ");
        scanf(" %d", &nuevoRegistro.idVehiculo);

         // Ejecuta el query
        sprintf(buffer, "SELECT idVehiculo FROM pr1_vehiculos WHERE idVehiculo = %d;", nuevoRegistro.idVehiculo);
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
    mysql_free_result(res);
    system("clear");
    validacion = 0;

    printf("->Ingresa la fecha con el formato 'AAAA-MM-DD' (incluyendo '-'): ");
    scanf(" %[^\n]", nuevoRegistro.fecha);
    printf("->Ingresa la hora de inicio con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", nuevoRegistro.horaInicio);
    printf("->Ingresa la hora en la que acabó la jornada con el formato 'HH:MM:SS' (incluyendo los ':'): ");
    scanf(" %[^\n]", nuevoRegistro.horaFin);
    printf("->Ingresa el kilometraje: ");
    scanf(" %d", &nuevoRegistro.km);
    system("clear");

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_A_V(hora_inicio, hora_fin, fecha, idAjustador, idVehiculo, kilometraje) VALUES ('%s', '%s', '%s', %d, %d, %d);", nuevoRegistro.horaInicio, nuevoRegistro.horaFin, nuevoRegistro.fecha, nuevoRegistro.idAjustador, nuevoRegistro.idVehiculo, nuevoRegistro.km);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }

}

/**
 * @brief Procedimiento que ingresa una colonia nueva
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 6/11/2023
*/

void ingresarColoniaNueva(char buffer[], MYSQL mysql)
{
    colonia ubicacion;

    system("clear");
    printf("->Ingresa el nombre de la colonia: ");
    scanf(" %[^\n]", ubicacion.nombre);
    printf("->Ingresa el nombre de la alcaldía a la cual pertenece la colonia: ");
    scanf(" %[^\n]", ubicacion.alcaldia);
    printf("->Ingresa el código postal: ");
    scanf(" %d", &ubicacion.cp);
    system("clear");

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_colonias(colonia, alcaldia, codigo_postal) VALUES ('%s', '%s', %d);", ubicacion.nombre, ubicacion.alcaldia, ubicacion.cp);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }
}


/**
 * @brief Procedimiento que ingresa un vehículo nuevo
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 7/11/2023
*/

void ingresarVehiculoNuevo(char buffer[], MYSQL mysql)
{
    vehiculo automovil;
    char ubicacion_actual[DATOS];
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int validacion;

    system("clear");
    printf("->Ingresa el modelo del vehículo: ");
    scanf(" %[^\n]", automovil.modelo);
    while(validacion != 0){
        system("clear");
        mostrarColonias(buffer, mysql);
        printf("\n->Ingresa la colonia en la que está actualmente: ");
        scanf(" %[^\n]", ubicacion_actual);

        //Verifica si la colonia está registrada
        sprintf(buffer, "CALL validarColonia('%s', @val);", ubicacion_actual);
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
            printf("La colonia no está registrada.\n");
        }
    }
    mysql_free_result(res);
    system("clear");

    //Busca el id de la colonia
    sprintf(buffer, "SELECT idColonia FROM pr1_colonias WHERE colonia = '%s';", ubicacion_actual);
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
        automovil.idColonia = atoi(row[0]);
    }
    mysql_free_result(res);

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_vehiculos(modelo, idColonia) VALUES ('%s', %d);", automovil.modelo, automovil.idColonia);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }

}

/**
 * @brief Procedimiento que ingresa un operador nuevo
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 6/11/2023
*/

void ingresarOperadorNuevo(char buffer[], MYSQL mysql)
{
    persona operador;

    system("clear");
    printf("->Ingresa el nombre: ");
    scanf(" %[^\n]", operador.nombre);
    printf("->Ingresa el apellido paterno: ");
    scanf(" %[^\n]", operador.ap_paterno);
    printf("->Ingresa el apellido materno: ");
    scanf(" %[^\n]", operador.ap_materno);
    printf("->Ingresa el teléfono: ");
    scanf(" %[^\n]", operador.celular);
    system("clear");

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_operadores(nombre, ap_paterno, ap_materno, telefono) VALUES ('%s', '%s', '%s', '%s');", operador.nombre, operador.ap_paterno, operador.ap_materno, operador.celular);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }
}

/**
 * @brief Procedimiento que ingresa un ajustador nuevo
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 6/11/2023
*/

void ingresarAjustadorNuevo(char buffer[], MYSQL mysql)
{
    persona ajustador;

    system("clear");
    printf("->Ingresa el nombre: ");
    scanf(" %[^\n]", ajustador.nombre);
    printf("->Ingresa el apellido paterno: ");
    scanf(" %[^\n]", ajustador.ap_paterno);
    printf("->Ingresa el apellido materno: ");
    scanf(" %[^\n]", ajustador.ap_materno);
    printf("->Ingresa el contraseña: ");
    scanf(" %[^\n]", ajustador.contrasena);
    printf("->Ingresa el correo: ");
    scanf(" %[^\n]", ajustador.correo);
    printf("->Ingresa el celular: ");
    scanf(" %[^\n]", ajustador.celular);
    system("clear");

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_ajustadores(nombre, ap_paterno, ap_materno, celular, correo, contraseña) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');", ajustador.nombre, ajustador.ap_paterno, ajustador.ap_materno, ajustador.celular, ajustador.correo, ajustador.contrasena);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }
}

/**
 * @brief Procedimiento que ingresa un usuario nuevo
 * @param String: buffer[]
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 6/11/2023
*/

void ingresarUsuarioNuevo(char buffer[], MYSQL mysql)
{
    persona usuario;
    
    system("clear");
    printf("->Ingresa el nombre: ");
    scanf(" %[^\n]", usuario.nombre);
    printf("->Ingresa el apellido paterno: ");
    scanf(" %[^\n]", usuario.ap_paterno);
    printf("->Ingresa el apellido materno: ");
    scanf(" %[^\n]", usuario.ap_materno);
    printf("->Ingresa el contraseña: ");
    scanf(" %[^\n]", usuario.contrasena);
    printf("->Ingresa el correo: ");
    scanf(" %[^\n]", usuario.correo);
    printf("->Ingresa el celular: ");
    scanf(" %[^\n]", usuario.celular);
    system("clear");

    // Ejecuta el query
    sprintf(buffer, "INSERT INTO pr1_usuarios(nombre, ap_paterno, ap_materno, celular, contraseña, correo) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');", usuario.nombre, usuario.ap_paterno, usuario.ap_materno, usuario.celular, usuario.contrasena, usuario.correo);
    if( mysql_query(&mysql, buffer) ){
        fprintf(stderr,"Error processing query \"%s\" \nError: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }
    else{
        printf("¡¡¡Datos guardados con éxito!!!\n\n");
    }
    
}

/**
 * @brief Procedimiento que despliega el submenú de la opción de Insertar Datos nuevos
 * @param Struct: mysql
 * @author Diego Bravo Pérez y Javier Lachica y Sánchez
 * @date 6/11/2023
 * 
*/

extern void menuInsertarDatos(MYSQL mysql)
{
    char buffer[MAX];
    unsigned int opcion, bandera;
    opcion = 0;
    bandera = 0;
    strcpy(buffer, "\0");


    while(bandera == 0)
    {
        printf("---Insertar datos nuevos---\n\n");
        printf("\t-> 1) Usuarios\n\t-> 2) Ajustadores\n\t-> 3) Operadores\n\t-> 4) Siniestros\n\t-> 5) Vehículos\n\t-> 6) Colonias\n\t-> 7) Actividad de los Ajustadores\n\t-> 8) Regresar\n\n");
        printf("Ingresa una opción que quieras realizar: ");
        scanf(" %d", &opcion);
        switch(opcion)
        {
            case 1:
            system("clear");
            ingresarUsuarioNuevo(buffer, mysql);
            break;

            case 2:
            system("clear");
            ingresarAjustadorNuevo(buffer, mysql);
            break;

            case 3:
            system("clear");
            ingresarOperadorNuevo(buffer, mysql);
            break;

            case 4:
            system("clear");
            ingresarSiniestroNuevo(buffer, mysql);
            break;

            case 5:
            system("clear");
            ingresarVehiculoNuevo(buffer, mysql);
            break;

            case 6:
            system("clear");
            ingresarColoniaNueva(buffer, mysql);
            break;

            case 7:
            system("clear");
            ingresarActividadReciente(buffer, mysql);
            break;

            case 8:
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