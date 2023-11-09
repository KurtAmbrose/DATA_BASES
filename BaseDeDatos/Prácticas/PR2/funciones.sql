--- PROCEDIMIENTO QUE AYUDA A VALIDAR SI UN DATO EXISTE ---

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

--- PROCEDIMIENTO QUE VALIDA SI LA HORA ES PARTE DEL RANGO DE LA JORNADA DEL AJUSTADOR ---

DROP PROCEDURE IF EXISTS validarHora;

DELIMITER $
CREATE PROCEDURE validarHora(IN dato TIME, IN dato2 DATE, IN dato3 INT, OUT validacion INT)

BEGIN
    DECLARE horain, horafin TIME;
    DECLARE curs CURSOR FOR SELECT hora_inicio, hora_fin FROM pr1_A_V WHERE idAjustador = dato3 AND fecha = dato2;

    OPEN curs;
    FETCH curs INTO horain, horafin;

    IF dato >= horain AND dato <= horafin THEN
        SET validacion = 2;
    ELSE
        SET validacion = 1;
    END IF;
    CLOSE curs;
END$

DELIMITER ;
