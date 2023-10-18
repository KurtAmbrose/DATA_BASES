DROP PROCEDURE IF EXISTS nacio_en_anio;

CREATE PROCEDURE nacio_en_anio (anio_nacimiento INT)

SELECT nombre, ap_paterno, nacimiento, muerte FROM presidentes WHERE YEAR(nacimiento) = anio_nacimiento;
