DELIMITER $$

DROP PROCEDURE IF EXISTS mejorPromedio$$

CREATE PROCEDURE mejorPromedio(OUT mayorProm DECIMAL(4,2), OUT mejorAlumno VARCHAR(50))

BEGIN

 DECLARE curMejorAlum CURSOR FOR SELECT nombre, AVG(calificacion) AS promedio FROM resultados_semestrales GROUP BY nombre ORDER BY promedio DESC;

 OPEN curMejorAlum;

 FETCH curMejorAlum INTO mejorAlumno, mayorProm;

 CLOSE curMejorAlum;

END $$

DELIMITER ;
