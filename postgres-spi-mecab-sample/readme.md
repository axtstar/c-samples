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

with args(use mecab_new2)
```
CREATE FUNCTION mecab_args(text, text) RETURNS text
     AS 'mecab_simple', 'mecab_args'
     LANGUAGE C STRICT;
```
> select mecab('すもももももももものうち');

nbest
```
CREATE FUNCTION mecab_nbest(text,integer) RETURNS text
     AS 'mecab_simple', 'mecab_nbest'
     LANGUAGE C STRICT;
```
> select mecab_nbest('すもももももももものうち', 3);

dictionary info
```
CREATE FUNCTION mecab_dic_info(text) RETURNS text
     AS 'mecab_simple', 'mecab_dic_info'
     LANGUAGE C STRICT;
```
> select mecab_dic_info();

mecab version
```
CREATE FUNCTION mecab_version_info() RETURNS text
     AS 'mecab_simple', 'mecab_version_info'
     LANGUAGE C STRICT;
```

> select mecab_version_info();