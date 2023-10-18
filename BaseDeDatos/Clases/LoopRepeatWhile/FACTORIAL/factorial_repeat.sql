DELIMITER $$
DROP FUNCTION IF EXISTS factorial$$

CREATE FUNCTION factorial(num INT) RETURNS INT 
DETERMINISTIC

BEGIN
    DECLARE resultado, contador INT;
    SET resultado = 1;
    SET contador = 1;
    IF num < 1 THEN 
        SET resultado = 0;
    ELSE
        REPEAT
            SET resultado = resultado * contador;
            SET contador = contador + 1;
            UNTIL contador > num
        END REPEAT;
    END IF;
    RETURN resultado;
END$$
DELIMITER ;