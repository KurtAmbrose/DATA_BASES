#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    unsigned int i = 0;
    char     buffer[1024];
    unsigned int num_fields;

    char *server = "localhost";
    char *user = "msc22dbp";
    char *passwd = "227019";
    char *db = "msc22dbp";

    char nombre[10];
    char apellido[10];
    char fecha[11];

    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;


    if( argc != 3 ){
      fputs("Usage: mysql <dataBase> <\"nombre del presidente\">\n", stderr);
      return 1;
    }

    mysql_init(&mysql); // Prepara la conexion al servidor de bases de datos

    // Se conecta al servidor de base de datos y verifica que no haya error
    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){
      fprintf(stderr, "Failed to connect to database: Error: %s\n",mysql_error(&mysql));
      return(0);
    }

    // Se conecta a la base de datos deseada
    if( mysql_select_db(&mysql,argv[1]) ){
        fprintf(stderr,"Error selecting database: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }

    // Ejecuta el query
    sprintf(buffer, "SELECT nombre, ap_paterno, ap_materno, ciudad, estado, nacimiento FROM presidentes WHERE nombre LIKE '%%%s%%';", argv[2]);
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
    system("clear");
    
    while( (row = mysql_fetch_row(res)) ){
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ ){
	  if(row[i] != NULL){
            printf("|%s\n",row[i]);
	  }
	  else{
	    printf(" \n");
	  }
        }
        fputc('\n',stdout);
    }

    mysql_free_result(res);
    
    // cierra la conexion con al servidor
    mysql_close(&mysql);

    return 0;
}
