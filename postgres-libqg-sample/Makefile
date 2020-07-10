#MODULES = samples

#PG_CONFIG = pg_config
#PGXS := $(shell $(PG_CONFIG) --pgxs)
#include $(PGXS)

samples: lib_version.c server_version.c
	gcc -o lib_version.out lib_version.c -I/usr/include/postgresql -lpq -std=gnu99
	gcc -o server_version.out server_version.c -I/usr/include/postgresql -lpq -std=gnu99

