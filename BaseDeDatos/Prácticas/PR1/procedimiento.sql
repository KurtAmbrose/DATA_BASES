-- PROCEDIMIENTO QUE RECIBE COMO PARÁMETRO EL NOMBRE DEL AJUSTADOR Y UNA FECHA Y DEVUELVE EL VEHÍCULO QUE MANEJÓ EL AJUSTADOR'

DROP PROCEDURE IF EXISTS mostrarVehiculo;

DELIMITER $

CREATE PROCEDURE mostrarVehiculo(IN nom VARCHAR(100), IN tiempo DATE, OUT model VARCHAR(50))

BEGIN
    DECLARE salida INT;
    DECLARE curs CURSOR FOR SELECT modelo FROM pr1_vista_AjustadoresFechasModelos WHERE nombre_completo LIKE CONCAT('%', nom, '%') AND fecha = tiempo;
    DECLARE EXIT HANDLER FOR NOT FOUND SET salida = 1;

    OPEN curs;

    IF salida = 1 THEN
        SET model = 'No manejó ningún vehículo';
    END IF;

    FETCH curs INTO model;

    WHILE model != NULL DO 
        FETCH curs INTO model;
    END WHILE; 
    
    CLOSE curs;

END$

DELIMITER ;
