DELIMITER $$

DROP PROCEDURE IF EXISTS mesCantidad$$

CREATE PROCEDURE mesCantidad(IN InputMes VARCHAR(15), OUT cantidadPresis INT)

BEGIN

    DECLARE salida INT;
    DECLARE mesNacimiento VARCHAR(15);
    DECLARE curPresi CURSOR FOR SELECT MONTHNAME(nacimiento) AS mes, COUNT(id) AS cantidad FROM presidentes GROUP BY mes ORDER BY cantidad DESC;
    DECLARE CONTINUE HANDLER FOR NOT FOUND
        SET salida = 1;

    OPEN curPresi;

    FETCH curPresi INTO mesNacimiento, cantidadPresis; -- SE TOMA EL PRIMER VALOR DE LA TABLA --

    IF mesNacimiento = 'May' THEN                      -- VALIDACIÓN PARA PODER CAMBIAR EL IDIOMA DEL MES, SEGURO SE PUEDE REALIZAR CON UN CASE, PERO SALIÓ ASÍ XD --
        SET mesNacimiento = 'Mayo';
    ELSEIF mesNacimiento = 'August' THEN
        SET mesNacimiento = 'Agosto';
    ELSEIF mesNacimiento = 'January' THEN
        SET mesNacimiento = 'Enero';
    ELSEIF mesNacimiento = 'February' THEN
        SET mesNacimiento = 'Febrero';
    ELSEIF mesNacimiento = 'March' THEN
        SET mesNacimiento = 'Mayo';
    ELSEIF mesNacimiento = 'April' THEN
        SET mesNacimiento = 'Abril';
    ELSEIF mesNacimiento = 'June' THEN
        SET mesNacimiento = 'Junio';
    ELSEIF mesNacimiento = 'July' THEN
        SET mesNacimiento = 'Julio';
    ELSEIF mesNacimiento = 'September' THEN
        SET mesNacimiento = 'Septiembre';
    ELSEIF mesNacimiento = 'October' THEN 
        SET mesNacimiento = 'Octubre';
    ELSEIF mesNacimiento = 'November' THEN
        SET mesNacimiento = 'Noviembre';    
    ELSE 
        SET mesNacimiento = 'Diciembre';
    END IF;

    IF mesNacimiento != InputMes THEN              -- VALIDACIÓN PARA SABER SI EL PRIMER ELEMENTO QUE SE TOMÓ NO ERA EL MISMO QUE EL PARÁMETRO DE ENTRADA --
        
        recorrer: WHILE mesNacimiento != InputMes DO    -- RECORRE LA TABLA HASTA ENCONTRAR EL DATO QUE COINCIDA CON EL PARÁMETRO DE ENTRADA

            IF salida = 1 THEN
                SET cantidadPresis = 0;
                LEAVE recorrer;
            END IF;

            FETCH curPresi INTO mesNacimiento, cantidadPresis;

            IF mesNacimiento = 'May' THEN           -- VALIDACIÓN PARA PODER CAMBIAR EL IDIOMA DEL MES, SEGURO SE PUEDE REALIZAR CON UN CASE, PERO SALIÓ ASÍ XD --
                SET mesNacimiento = 'Mayo';
            ELSEIF mesNacimiento = 'August' THEN
                SET mesNacimiento = 'Agosto';
            ELSEIF mesNacimiento = 'January' THEN
                SET mesNacimiento = 'Enero';
            ELSEIF mesNacimiento = 'February' THEN
                SET mesNacimiento = 'Febrero';
            ELSEIF mesNacimiento = 'March' THEN
                SET mesNacimiento = 'Mayo';
            ELSEIF mesNacimiento = 'April' THEN
                SET mesNacimiento = 'Abril';
            ELSEIF mesNacimiento = 'June' THEN
                SET mesNacimiento = 'Junio';
            ELSEIF mesNacimiento = 'July' THEN
                SET mesNacimiento = 'Julio';
            ELSEIF mesNacimiento = 'September' THEN
                SET mesNacimiento = 'Septiembre';
            ELSEIF mesNacimiento = 'October' THEN 
                SET mesNacimiento = 'Octubre';
            ELSEIF mesNacimiento = 'November' THEN
                SET mesNacimiento = 'Noviembre';
        
            ELSE 
                SET mesNacimiento = 'Diciembre';
            END IF;

        END WHILE recorrer;
    
    END IF;

    CLOSE curPresi;

END$$

DELIMITER ;

