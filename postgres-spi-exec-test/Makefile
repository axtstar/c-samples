MODULE_big = execq_sample
OBJS = execq.o
PGFILEDESC = "execq_simple - mecab simple test"

SHLIB_LINK = -lmecab

EXTENSION = execq
DATA = execq_simple--0.1.sql

PG_CONFIG = pg_config

PGXS := $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)

override PG_CXXFLAGS += -std=c++11 -O3

SHARED_OPTS=-shared
POSTGRES_INCLUDE_OPTS=/usr/include/postgresql/12/server
MEMCAB_INCLUDE_OPTS=/usr/include

# XXX: PostgreSQL below 11 does not automatically add -fPIC or equivalent to C++
# flags when building a shared library, have to do it here explicitely.
ifeq ($(shell test $(VERSION_NUM) -lt 110000; echo $$?), 0)
	override CXXFLAGS += $(CFLAGS_SL)
endif

COMPILE.cxx.bc = $(CLANG) -xc++ -Wno-ignored-attributes $(BITCODE_CXXFLAGS) $(CPPFLAGS) -emit-llvm -c

%.bc : %.c
	$(COMPILE.cxx.bc) $(CXXFLAGS) $(CPPFLAGS)  -o $@ $<