DELIMITER $$
DROP FUNCTION IF EXISTS factorial2$$

CREATE FUNCTION factorial2(num INT) RETURNS INT
DETERMINISTIC

BEGIN
    DECLARE factorial, i INT;
    SET factorial = 1;
    SET i = 1;
    IF num < 1 THEN
        SET factorial = 0;
    ELSE
        resultado: LOOP
            SET factorial = factorial * i;
            SET i = i + 1;
            IF i > num THEN
                LEAVE resultado;
            END IF;
        END LOOP resultado;
    END IF;
    RETURN factorial;
END$$
DELIMITER ;