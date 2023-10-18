DELIMITER $$

DROP PROCEDURE IF EXISTS cantidadPresidentes$$

CREATE PROCEDURE cantidadPresidentes(IN nombreEstado VARCHAR(15), OUT estadoNacimiento VARCHAR(15), OUT cantidadNacidos INT)

BEGIN

 DECLARE curEstado CURSOR FOR SELECT estado, COUNT(id) AS cantidad FROM presidentes GROUP BY estado;

 OPEN curEstado;

 FETCH curEstado INTO estadoNacimiento, cantidadNacidos; --Se obtiene el primer dato de la tabla--

 IF estadoNacimiento != nombreEstado THEN		 --Si no se cumple esta condición, entonces hará el while --
 
  datos: WHILE estadoNacimiento != nombreEstado DO
  
   FETCH curEstado INTO estadoNacimiento, cantidadNacidos;
   
  END WHILE datos;
  
 END IF;

 CLOSE curEstado;
 
END $$

DELIMITER ;

