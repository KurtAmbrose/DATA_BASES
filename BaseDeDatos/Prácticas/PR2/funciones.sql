-- PROCEDIMIENTO QUE AYUDA A VALIDAR SI UN DATO EXISTE ---

DROP PROCEDURE IF EXISTS validarColonia;

DELIMITER $

CREATE PROCEDURE validarColonia(IN dato VARCHAR(50), OUT validacion INT)

BEGIN
    DECLARE id, salida INT;
    DECLARE cur CURSOR FOR SELECT idColonia FROM pr1_colonias WHERE colonia = dato;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET salida = 1;

    OPEN cur;
    FETCH cur INTO id;

    IF salida = 1 THEN
        SET validacion = 1;
    ELSE
        SET validacion = 0;
    END IF;
END$

DELIMITER ;
