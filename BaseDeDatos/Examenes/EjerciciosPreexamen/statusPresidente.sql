DROP PROCEDURE IF EXISTS statusPresidente;

DELIMITER $

CREATE PROCEDURE statusPresidente(IN nom VARCHAR(100), OUT edad INT, OUT mortis DATE, OUT stat VARCHAR(10))

BEGIN

DECLARE salida INT;
DECLARE n VARCHAR(100);
DECLARE fecha1 DATE;
DECLARE curs CURSOR FOR SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nomPresi, nacimiento, muerte FROM presidentes HAVING nomPresi = nom;
DECLARE EXIT HANDLER FOR NOT FOUND SET salida = 1;

OPEN curs;

FETCH curs INTO n, fecha1, mortis;

IF salida = 1 THEN
    SET edad = NULL;
    SET mortis = NULL;
    SET stat = NULL;
END IF;

SET stat = ' ';

IF mortis IS NULL THEN
    SET mortis = CURDATE();
    SET stat = 'Vivo';
END IF;

SET edad = (YEAR(mortis) - YEAR(fecha1)) - IF(RIGHT(mortis, 5) < RIGHT(fecha1, 5), 1, 0);

IF mortis = CURDATE() THEN
    SET mortis = NULL;
END IF;

CLOSE curs;

END$

DELIMITER ;

