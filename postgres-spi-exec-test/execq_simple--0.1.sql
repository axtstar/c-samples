CREATE FUNCTION execq(text, integer) RETURNS int8
 AS 'execq_sample', 'execq'
 LANGUAGE C STRICT
;