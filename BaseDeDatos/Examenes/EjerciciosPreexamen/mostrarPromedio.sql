DELIMITER $$

DROP PROCEDURE IF EXISTS mostrarPromedio$$

CREATE PROCEDURE mostrarPromedio(IN nombreAlumno VARCHAR(25), OUT promedio DECIMAL(4,2))

BEGIN

    DECLARE nom VARCHAR(25);
    DECLARE salida INT;
    DECLARE curAlumno CURSOR FOR SELECT nombre, AVG(calificacion) AS prom FROM resultados_semestrales GROUP BY nombre ORDER BY prom DESC;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET salida = 1;

    OPEN curAlumno;

    FETCH curAlumno INTO nom, promedio;

    IF nom != nombreAlumno THEN

        recorrer: WHILE nom != nombreAlumno DO

            IF salida = 1 THEN
                SET promedio = NULL;
                LEAVE recorrer;
            END IF;
            FETCH curAlumno INTO nom, promedio;

        END WHILE recorrer;

    END IF;

    CLOSE curAlumno;

END$$

DELIMITER ;

