DELIMITER $$
DROP FUNCTION IF EXISTS factorial3$$ 

CREATE FUNCTION factorial3(num INT) RETURNS INT
DETERMINISTIC

BEGIN
    DECLARE factorial, contador INT;
    SET factorial = 1;
    SET contador = 1;

    resultado: WHILE contador <                                                                                                                                                                                                                                      num DO
        SET factorial= factorial * contador;
        SET contador = contador + 1;
    END WHILE resultado;
    RETURN factorial;
END$$
DELIMITER ;