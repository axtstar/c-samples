# postgresql server programming interface

## prerequire

linux
> sudo apt-get install postgresql
> sudo apt-get install postgresql-common
> sudo apt install postgresql-server-dev-all
> sudo apt install postgresql-server-dev-10
> sudo apt-get install libpq-dev
> sudo apt-get install libc6


> sudo apt-get install mecab
> sudo apt install libmecab-dev
> 

osx
> brew install postgresql@11


## add postgresql repos

> sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt/ bionic-pgdg main" > /etc/apt/sources.list.d/postgresql.list'
> wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
> 
> sudo apt clean
> sudo apt update
> sudo apt upgrade

> sudo apt install postgresql-11

## build

> make

> sudo make install



[Comile and Link](https://www.postgresql.jp/document/11/html/xfunc-c.html#DFUNC)

copy so file to the folder which is indicated by the below command
> pg_config --pkglibdir

create function

```sql
CREATE FUNCTION execq(text, integer) RETURNS int8
    AS 'filename'
    LANGUAGE C STRICT;
```

```
SELECT execq('CREATE TABLE a (x integer)', 0)
```
https://www.postgresql.jp/document/11/html/spi-examples.html


```
CREATE FUNCTION add_one(integer) RETURNS integer
     AS 'funcs', 'add_one'
     LANGUAGE C STRICT;

-- SQL関数名"add_one"のオーバーロードに注意
CREATE FUNCTION add_one(double precision) RETURNS double precision
     AS 'funcs', 'add_one_float8'
     LANGUAGE C STRICT;

CREATE FUNCTION makepoint(point, point) RETURNS point
     AS 'funcs', 'makepoint'
     LANGUAGE C STRICT;

CREATE FUNCTION copytext(text) RETURNS text
     AS 'funcs', 'copytext'
     LANGUAGE C STRICT;

CREATE FUNCTION concat_text(text, text) RETURNS text
     AS 'funcs', 'concat_text'
     LANGUAGE C STRICT;

```

## docker

> docker-compose up -d

> psql -h 127.0.0.1 -d postgres -U postgres
(type postgres)

> postgres=#   CREATE FUNCTION mecab(text) RETURNS text 
     AS 'mecab_simple', 'mecab'
     LANGUAGE C STRICT;

> postgres=# select mecab('すもももももももものうち');

## rust

> cargo bindgen

> bindgen -o src/bindings.rs ./src/wrapper.h -- -I /usr/include/ 

↓いらなさそう↓
> -xc++ -Wno-ignored-attributes -emit-llvm -c

## psql

> cargo pgx connect pg11 postgres


> cargo pgx 