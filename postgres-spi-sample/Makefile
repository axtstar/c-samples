#MODULES = samples

OSNAME=${shell uname -s}
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

ifeq ($(OSNAME),Linux)
	SHARED_OPTS=-shared
	POSTGRES_INCLUDE_OPTS=/usr/include/postgresql/11/server
	MEMCAB_INCLUDE_OPTS=/usr/include
else
	SHARED_OPTS=-bundle -flat_namespace -undefined suppress
	POSTGRES_INCLUDE_OPTS=/usr/local/Cellar/postgresql/12.3_4/include/postgresql/server/
	MEMCAB_INCLUDE_OPTS=/usr/local/Cellar/mecab/0.996/include
endif


all: sample.c funcs.c
	$(shell mkdir -p bin)
	gcc -fPIC -c sample.c -I ${POSTGRES_INCLUDE_OPTS} -std=gnu99 -o bin/sample.o
	gcc ${SHARED_OPTS} -o bin/sample.so bin/sample.o
	gcc -fPIC -c funcs.c -I ${POSTGRES_INCLUDE_OPTS} -std=gnu99 -o bin/funcs.o
	gcc ${SHARED_OPTS} -o bin/funcs.so bin/funcs.o
	gcc \
        `mecab-config --cflags` \
        mecab_sample.c -o bin/mecab_sample \
        `mecab-config --libs`
	gcc -fPIC -c \
        `mecab-config --cflags` \
        mecab_simple.c -o bin/mecab_simple.o \
        -I ${POSTGRES_INCLUDE_OPTS} \
        `mecab-config --libs`
	gcc ${SHARED_OPTS} -o bin/mecab_simple.so bin/mecab_simple.o
