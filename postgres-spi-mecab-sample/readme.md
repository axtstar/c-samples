# postgresql server programming interface sample

## docker build

> docker build -t postgres-mecab .

## run postgres with mecab_simple module

> docker-compose up -d

## execute mecab_simple

> psql -h 127.0.0.1 -d postgres -U postgres
(type postgres)

> postgres=# CREATE FUNCTION mecab(text) RETURNS text \
     AS 'mecab_simple', 'mecab' \
     LANGUAGE C STRICT;

> postgres=# select mecab('すもももももももものうち');

result:
```
                       mecab
---------------------------------------------------
 すもも  名詞,一般,*,*,*,*,すもも,スモモ,スモモ   +
 も      助詞,係助詞,*,*,*,*,も,モ,モ             +
 もも    名詞,一般,*,*,*,*,もも,モモ,モモ         +
 も      助詞,係助詞,*,*,*,*,も,モ,モ             +
 もも    名詞,一般,*,*,*,*,もも,モモ,モモ         +
 の      助詞,連体化,*,*,*,*,の,ノ,ノ             +
 うち    名詞,非自立,副詞可能,*,*,*,うち,ウチ,ウチ+
 EOS                                              +

(1 row)
```

```
CREATE FUNCTION mecab(text) RETURNS text
     AS 'mecab_simple', 'mecab'
     LANGUAGE C STRICT;
```

dictionary info
```
CREATE FUNCTION mecab_dic_info(text) RETURNS text
     AS 'mecab_simple', 'mecab_dic_info'
     LANGUAGE C STRICT;
```