DELIMITER $$

DROP PROCEDURE IF EXISTS lugarNacimiento$$

CREATE PROCEDURE lugarNacimiento(IN InputNombre VARCHAR(90), OUT OutputLugar VARCHAR(50))

BEGIN

    DECLARE salida INT;
    DECLARE nombrePresi VARCHAR(90);
    DECLARE curPresi CURSOR FOR SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre, CONCAT(ciudad,', ', estado) AS lugar_nacimiento FROM presidentes;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET salida = 1;

    OPEN curPresi;

    FETCH curPresi INTO nombrePresi, OutputLugar;

    IF InputNombre != nombrePresi THEN
        recorrer: WHILE InputNombre != nombrePresi DO

            IF salida = 1 THEN
                SET OutputLugar = NULL;
                LEAVE recorrer;
            END IF;

            FETCH curPresi INTO nombrePresi, OutputLugar;

        END WHILE recorrer;
    END IF;

    CLOSE curPresi;

END$$

DELIMITER ;

