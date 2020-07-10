#MODULES = samples

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

all: sample.c funcs.c
	gcc -fPIC -c sample.c -I /usr/include/postgresql/11/server -std=gnu99 -o bin/sample.o
	gcc -shared -o bin/sample.so bin/sample.o
	gcc -fPIC -c funcs.c -I /usr/include/postgresql/11/server -std=gnu99 -o bin/funcs.o
	gcc -shared -o bin/funcs.so bin/funcs.o

