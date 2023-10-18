DELIMITER $$

DROP PROCEDURE IF EXISTS fechaNacimiento$$

CREATE PROCEDURE fechaNacimiento(IN InputNombre VARCHAR(90), OUT fechaNacimiento DATE)

BEGIN
    DECLARE salida INT;
    DECLARE nombrePresi VARCHAR(100);
    DECLARE curPresi CURSOR FOR SELECT nombre, nacimiento FROM PresidentesNacimiento;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET salida = 1;   

    OPEN curPresi;

    FETCH curPresi INTO nombrePresi, fechaNacimiento; -- SE LE ASIGNA EL NOMBRE DEL PRESIDENTE DE LA PRIMERA FILA DE LA LISTA A LAS VARIABLES DE VALIDACIÓN Y LA QUE VA A DEVOLVER --

    IF nombrePresi != InputNombre THEN   
                                                    -- SE RECORRE LA LISTA EN CASO DE QUE EL NOMBRE DE ENTRADA NO COINCIDA CON EL PRIMER NOMBRE DEL PRIMER RENGLÓN DE LA TABLA --
        recorrer: WHILE nombrePresi != InputNombre DO

            IF salida = 1 THEN
                SET fechaNacimiento = NULL; 
                LEAVE recorrer;
            END IF;

             FETCH curPresi INTO nombrePresi, fechaNacimiento;

        END WHILE recorrer;

    END IF;

    CLOSE curPresi;

END$$

DELIMITER ;
