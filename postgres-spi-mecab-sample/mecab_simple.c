#include <mecab.h>
#include <stdio.h>
#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "utils/geo_decls.h"

int fileWrite(const char *path, const char *content );

#define CHECK(eval) if (! eval) { \
    fprintf (stderr, "Exception:%s\n", mecab_strerror (mecab)); \
    mecab_destroy(mecab); \
    return -1; }

PG_MODULE_MAGIC;

/* 可変長の参照渡し */

PG_FUNCTION_INFO_V1(mecab);

Datum
mecab(PG_FUNCTION_ARGS)
{
    text     *t = PG_GETARG_TEXT_PP(0); // input value
    text     *destination; // for return value

    char *input=t->vl_dat;
    int size; // return value size

    // mecab
    mecab_t *mecab;
    const char *result;

    // Create tagger object
    mecab = mecab_new(1, &input);
    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_sparse_tostr(mecab, input);
    CHECK(result)

    fileWrite("/tmp/mecab_simple.txt", result); //for debug

    size = strlen(result);

    destination = (text *) palloc(VARHDRSZ + size);
    SET_VARSIZE(destination, VARHDRSZ + size);
    memcpy(destination->vl_dat, result, size);

    mecab_destroy(mecab);

    PG_RETURN_TEXT_P(destination);
}

int fileWrite(const char *path, const char *content ) {
  FILE *outputfile;

  outputfile = fopen(path, "w");
  if (outputfile == NULL) {
    return 0; //nothing to do if fail
  }
  fprintf(outputfile, "%s", content);

  fclose(outputfile);
  return 0;
}
