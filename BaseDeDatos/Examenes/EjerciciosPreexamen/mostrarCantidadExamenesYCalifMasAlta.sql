DROP PROCEDURE IF EXISTS mostrarCantidadExamenesYCalifMasAlta;

DELIMITER $

CREATE PROCEDURE mostrarCantidadExamenesYCalifMasAlta(IN nom VARCHAR(25), OUT canExamenes INT, OUT calificacionMayor DECIMAL(4,2))

BEGIN

DECLARE nomAlu, nomAlu2 VARCHAR(25);  -- DECLARACIÓN DE VARIABLES --
DECLARE salida INT;
DECLARE mayor DECIMAL(4,2);

DECLARE cursAlumno CURSOR FOR SELECT nombre, COUNT(idExamen) AS cantidad_examenes FROM ej1_resultados LEFT JOIN ej1_alumno USING(idAlumno) GROUP BY nombre;  -- DECLARACIÓN DE CURSORES, UNO RECORRERÁ LOS ALUMNOS Y EL OTRO LOS RESULTADOS HASTA ENCONTRAR EL MÁS GRANDE --
DECLARE cursExamen CURSOR FOR SELECT nombre, calificacion FROM ej1_resultados LEFT JOIN ej1_alumno USING(idAlumno);
DECLARE EXIT HANDLER FOR NOT FOUND SET salida = 1;

OPEN cursAlumno;
OPEN cursExamen;

FETCH cursAlumno INTO nomAlu, canExamenes; -- SE ASIGNAN VALORES A LOS VARIABLES QUE SE UTILIZARÁN --
FETCH cursExamen INTO nomAlu2, mayor;

IF nomAlu != nom THEN  -- SE BUSCA SI EL ALUMNO EXISTE DENTRO DE LA BASE DE DATOS --

    recorrer3: WHILE nomAlu != nom DO
        IF salida = 1 THEN
            SET canExamenes = 0;
            SET mayor = NULL;
            LEAVE recorrer3;
        END IF;

        FETCH cursAlumno INTO nomAlu, canExamenes;

    END WHILE recorrer3;

END IF;


IF nomAlu != nomAlu2 THEN -- SI LOS NOMBRES NO COINCIDEN, VA A BUSCAR EN TODA LA TABLA DE LOS EXAMENES HASTA QUE COINCIDAN --
    recorrer1: WHILE nomAlu != nomAlu2 DO
        FETCH cursExamen INTO nomAlu2, mayor;
    END WHILE recorrer1;
END IF;

SET calificacionMayor = mayor;

recorrer2: WHILE nomAlu2 = nomAlu DO  -- AQUI BUSCARÁ LA CALIFICACIÓN MAYOR DE LAS QUE TIENE EL ALUMNO --
    IF calificacionMayor < mayor THEN
        SET calificacionMayor = mayor;
    END IF;
    FETCH cursExamen INTO nomAlu2, mayor;
END WHILE recorrer2;

END$

DELIMITER ;

