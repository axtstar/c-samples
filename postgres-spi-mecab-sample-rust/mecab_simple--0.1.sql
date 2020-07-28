CREATE FUNCTION mecab(text) RETURNS text
     AS 'mecab_simple', 'mecab'
     LANGUAGE C STRICT;