DELIMITER $$

DROP PROCEDURE IF EXISTS mostrarFaltas$$

CREATE PROCEDURE mostrarFaltas(IN nombreAlumno VARCHAR(25), OUT cantidadFaltas INT)

BEGIN

    DECLARE nom VARCHAR(25);
    DECLARE salida INT;
    DECLARE curAlumno CURSOR FOR SELECT nombre, COUNT(idAusencia) AS cantidad FROM ej1_alumno LEFT JOIN ej1_ausencias USING(idAlumno) GROUP BY nombre ORDER BY cantidad DESC;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET salida = 1;

    OPEN curAlumno;

    FETCH curAlumno INTO nom, cantidadFaltas;

    IF nom != nombreAlumno THEN

        recorrer: WHILE nom != nombreAlumno DO

            IF salida = 1 THEN
                SET cantidadFaltas = NULL;
                LEAVE recorrer;
            END IF;
            FETCH curAlumno INTO nom, cantidadFaltas;

        END WHILE recorrer;

    END IF;

    CLOSE curAlumno;

END$$

DELIMITER ;

