#include "def.h"

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
    printf("Ingresa el nombre: ");
    scanf(" %[^\n]", usuario.nombre);
    printf("Ingresa el apellido paterno: ");
    scanf(" %[^\n]", usuario.ap_paterno);
    printf("Ingresa el apellido materno: ");
    scanf(" %[^\n]", usuario.ap_materno);
    printf("Ingresa el contraseña: ");
    scanf(" %[^\n]", usuario.contrasena);
    printf("Ingresa el correo: ");
    scanf(" %[^\n]", usuario.correo);
    printf("Ingresa el celular: ");
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
            break;

            case 3:
            break;

            case 4:
            break;

            case 5: 
            break;

            case 6:
            break;

            case 7:
            break;

            case 8:
            bandera = 1;
            break;

            default:
            system("clear");
            printf("Ingrese una opción correcta.\n\n");
            break;
        }
    }
}