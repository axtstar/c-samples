CREATE FUNCTION execq(text) RETURNS int8
 AS 'execq_sample', 'execq'
 LANGUAGE C STRICT
;