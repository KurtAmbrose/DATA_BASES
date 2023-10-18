DELIMITER $$

DROP FUNCTION IF EXISTS potencia$$

CREATE FUNCTION potencia(base INT, exponente INT) RETURNS INT
DETERMINISTIC

BEGIN
	DECLARE resultado, contador INT;
	SET resultado=1;
	SET contador=1;

	potencia: LOOP
		SET resultado=resultado*base;
		SET contador=contador+1;
		IF contador > exponente THEN
			LEAVE potencia;
		END IF;

	END LOOP potencia;
	RETURN resultado;
END$$

DELIMITER ;
