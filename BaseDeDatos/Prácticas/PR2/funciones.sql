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

--- PROCEDIMIENTO QUE VERIFICA SI LAS HORAS INGRESADAS ESTÁN EN ÓRDEN CORRECTO

DROP PROCEDURE IF EXISTS validarRango;

DELIMITER $

CREATE PROCEDURE validarRango(IN tiempo1 TIME, IN tiempo2 TIME, OUT validacion INT)

BEGIN
    IF tiempo1 > tiempo2 THEN
        SET validacion = 1;
    ELSE
        SET validacion = 0;
    END IF;
END$

DELIMITER ;


--- PROCEDIMIENTO QUE VERIFICA SI LA HORA INGRESADA PERMANECE EN ALGUNO DE LOS RANGOS ---

DROP PROCEDURE IF EXISTS validarHora2;

DELIMITER $
CREATE PROCEDURE validarHora2(IN dato TIME, IN dato2 DATE, OUT validacion INT)

BEGIN
    DECLARE horain, horafin TIME;
    DECLARE curs CURSOR FOR SELECT hora_inicio, hora_fin FROM pr1_A_V WHERE fecha = dato2 AND hora_inicio <= dato AND hora_fin >= dato;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET validacion = 0;

    OPEN curs;
    SET validacion = 1;
    FETCH curs INTO horain, horafin;
    IF horain > dato OR horafin < dato THEN
        SET validacion = 0;
        WHILE horain IS NOT NULL OR validacion != 1 DO
            IF horain <= dato AND horafin >= dato THEN 
                SET validacion = 1;
            ELSE
                FETCH curs INTO horain, horafin;
                SET validacion = 0;
            END IF;
        END WHILE;
    END IF;
        
    CLOSE curs;
END$

DELIMITER ;