MODULE_big = execq_sample
OBJS = execq.o
PGFILEDESC = "execq_simple - mecab simple test"

EXTENSION = execq
DATA = execq_simple--0.1.sql

PG_CONFIG = pg_config

PGXS := $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)

override PG_CXXFLAGS += -std=c++11 -O3

SHARED_OPTS=-shared
POSTGRES_INCLUDE_OPTS=/usr/include/postgresql/12/server
MEMCAB_INCLUDE_OPTS=/usr/include

all:
	gcc -fPIC -c execq.c -I${POSTGRES_INCLUDE_OPTS} -o execq.o -emit-llvm -c
	gcc -shared -o execq_sample.so execq.o

