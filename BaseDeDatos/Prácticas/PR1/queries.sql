-- USUARIOS QUE MENOS USAN EL SISTEMA --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_usuarios LEFT JOIN pr1_siniestros USING(idUsuario) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_usuarios LEFT JOIN pr1_siniestros USING(idUsuario) GROUP BY nombre ORDER BY COUNT(idSiniestro) ASC LIMIT 1);

-- AJUSTADORES QUE MÁS SINIETROS ATIENDEN --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre ORDER BY COUNT(idSiniestro) DESC LIMIT 1);

-- AJUSTADORES QUE MENOS SINIESTROS ATIENDEN --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) GROUP BY nombre ORDER BY COUNT(idSiniestro) ASC LIMIT 1);

-- LISTA DE AJUSTADORES REGISTRADOS EN EL SISTEMA --

SELECT idAjustador, CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores;

-- LISTA DE SINIESTROS DE UN AJUSTADOR EN PARTICULAR --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno, ' ') AS nombre, idSiniestro FROM pr1_ajustadores LEFT JOIN pr1_siniestros USING(idAjustador) HAVING nombre LIKE '%Vera%';

-- LISTA DE AJUSTADORES QUE MANEJARON UN VEHÍCULO EN UN PERIODO DE TIEMPO --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) WHERE hora_inicio > '17:00:00' AND hora_fin < '21:00:00';

-- LISTA DE COLONIAS DONDE MÁS SINIESTROS OCURREN --

SELECT colonia FROM pr1_colonias LEFT JOIN pr1_siniestros USING(idColonia) GROUP BY colonia HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_colonias LEFT JOIN pr1_siniestros USING(idColonia) GROUP BY colonia ORDER BY COUNT(idSiniestro) DESC LIMIT 1);

-- PERIODO DEL DÍA DONDE MÁS SINIESTROS OCURREN --

SELECT periodoDia(hora) AS periodo FROM pr1_siniestros GROUP BY periodo HAVING COUNT(idSiniestro) = (SELECT COUNT(idSiniestro) FROM pr1_siniestros GROUP BY periodoDia(hora) ORDER BY COUNT(idSiniestro) DESC LIMIT 1);

-- CANTIDAD DE SINIESTROS QUE OCURREN EN CIERTO PERIODO DE TIEMPO --

SELECT COUNT(idSiniestro) AS cantidad_siniestros FROM pr1_siniestros WHERE hora > '11:00:00' AND hora < '19:00:00';

-- NOMBRE DEL AJUSTADOR (O AJUSTADORES) QUE MANEJÓ UN VEHÍCULO EN UN PERIODO DE TIEMPO DETERMINADO --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) WHERE hora_inicio  > '10:00:00' AND hora_fin < '14:00:00';

-- ÚLTIMA POSICIÓN DE UN AJUSTADOR EN PARTICULAR --

SELECT CONCAT(nombre, ' ', ap_paterno, ' ', ap_materno) AS nombre, colonia FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) LEFT JOIN pr1_colonias USING(idColonia) WHERE fecha = '2023-11-03';

-- LISTA DE VEHÍCULOS QUE MANEJÓ UN AJUSTADOR EN UN TIEMPO EN ESPECÍFICO --

SELECT modelo FROM pr1_ajustadores LEFT JOIN pr1_A_V USING(idAjustador) LEFT JOIN pr1_vehiculos USING(idVehiculo) WHERE nombre LIKE 'Leonardo' AND ap_paterno = 'Park' AND ap_materno = 'Morales' AND fecha = '2023-09-15';



-- FUNCIÓN PARA MOSTRAR PERIODO DEL DÍA --


DROP FUNCTION IF EXISTS periodoDia;

DELIMITER $

CREATE FUNCTION periodoDia(tiempo TIME) RETURNS VARCHAR(15)
DETERMINISTIC

BEGIN
DECLARE periodo VARCHAR(15);
DECLARE laHora INT;
	
SET laHora = HOUR(tiempo);

IF laHora >= 6 AND laHora <= 11 THEN
SET periodo = 'MAÑANA';
ELSEIF laHora >= 12 AND laHora <= 18 THEN
SET periodo = 'TARDE';
ELSEIF laHora >= 19 AND laHora <= 23 THEN
SET periodo = 'NOCHE';
ELSE
SET periodo = 'MADRUGADA';
END IF;
RETURN periodo;
END$

DELIMITER ;

