/**
 * @file main.c
 *
 * @brief Programa en C que permite llevar a cabo la operación completa de un sistema de base de datos, el cual
 *         incluye el llenado de la información para poder desplegarla. El programa se divide en los siguientes menús: 
 *             a) Ingresar Datos: La opción de ingresar los datos de los usuarios, empleados (ajustadores y operadores), vehículos, siniestros
 *                                ubicaciones y la actividad de los ajustadores durante la jornada. 
 *             b) Modificar Datos: La opción de modificar los datos de los usuarios, empleados (ajustadores y operadores), vehículos, siniestros
 *                                 ubicaciones y la actividad de los ajustadores durante la jornada.
 *             c) Desplegar Datos: Despliega los datos mediante un menú de opciones que el usuario que maneja el programa puede consultar. Los datos solicitados son los siguientes:
 *                 1) Usuarios que menos usan el sistema.
 *                 2) Ajustadores que más siniestros atienden.
 *                 3) Ajustadores que menos siniestros han atendido.
 *                 4) Lista de todos los ajustadores que están registrados en el sistema.
 *                 5) Lista de los siniestros de un ajustador en particular.
 *                 6) Lista de todos los ajustadores que manejaron un vehículo en un periodo de tiempo determinado.
 *                 7) Lista de las colonias en donde más siniestros ocurren.
 *                 8) Periodo del día (mañana, tarde o noche) en donde más siniestros ocurren.
 *                 9) Número de siniestros en un periodo de tiempo determinado.
 *                 10) Nombre del ajustador que manejó un vehículo en un periodo de tiempo determinado.
 *                 11) La última posición de un ajustador en particular
 *                 12) Lista de todos los vehículos que manejó un ajustador en un periodo de tiempo determinado
 *             d) Salir: Esta opción es para salir del programa.
 *
 *
 * @author Programa elaborado por: Diego Bravo Pérez y Javier Lachica y Sánchez  
 *
 * @date Fecha de elaboración del programa: 2 de Noviembre del 2023
 *
 * @date Última Actualización: 9 de Noviembre del 2023
 *
 */


#include "def.h"

/**
 * @brief Menú principal del programa
 */

int main(int argc, char *argv[])
{
  unsigned int bandera;
  char opcion;
  bandera = 0;

  char *server = "localhost";
  char *user = "msc22dbp";
  char *passwd = "227019";
  char *db = "msc22dbp";

  MYSQL mysql;


  if(argc != 2)
    {
      fputs("Usage: practica2.exe <dataBase>\n", stderr);
    }

  else
    {
      mysql_init(&mysql); // Prepara la conexion al servidor de bases de datos

       // Se conecta al servidor de base de datos y verifica que no haya error
      if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
          fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&mysql));
          exit(1);
      }

      // Se conecta a la base de datos deseada
      if( mysql_select_db(&mysql,argv[1]) ){
          fprintf(stderr, "Error selecting database: Error: %s\n", mysql_error(&mysql));
          exit(1);
      }
    
      else
      {
        system("clear");
        fprintf(stdout, "¡¡¡Connection succed!!!\n\n");
      }

      // Despliega el menú principal
      while(bandera == 0)
      {
        printf("---- Práctica 2: Aseguradora ------\n\n");
        printf("\t-> a) Insertar datos nuevos\n\t-> b) Modificar datos ingresados\n\t-> c) Consultar Información\n\t-> d) Salir\n\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);

        switch(opcion)
        {
          case 'A':
          system("clear");
          menuInsertarDatos(mysql);
          break;

          case 'a':
          system("clear");
          menuInsertarDatos(mysql);
          break;

          case 'b':
          system("clear");
          break;

          case 'B':
          system("clear");
          break;

          case 'c':
          system("clear");
          
          break;

          case 'C':
          system("clear");
          
          break;

          case 'D':
          system("clear");
          bandera = 1;
          break;

          case 'd':
          system("clear");
          bandera = 1;
          break;

          default:
          system("clear");
          printf("Ingrese una opción correcta.\n\n");
          break;
        }
      }
      
      mysql_close(&mysql);
    }
  
  return 0;
}

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