#include <mecab.h>
#include <stdio.h>
#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "utils/geo_decls.h"
#include <locale.h>



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
    setlocale(LC_CTYPE, "C.UTF-8");

    text     *t = PG_GETARG_TEXT_PP(0);
    char *input=t->vl_dat;

    // mecab
    mecab_t *mecab;
    const mecab_node_t *node;
    const char *result;
    int i;
    size_t len;

    // Create tagger object
    mecab = mecab_new(1, &input);
    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_sparse_tostr(mecab, input);
    CHECK(result)

    /*

     * VARSIZEは、そのヘッダのVARHDRSZまたはVARHDRSZ_SHORTを引いた
     * 構造体の総長をバイト数で表したものです。
     * 完全な長さのヘッダと合わせたコピーを作成します。
     */

    // for  debug
    FILE *outputfile;         // 出力ストリーム

    int size = strlen(result);
    outputfile = fopen("/tmp/d.txt", "w");
    fprintf(outputfile, "%d\n%s\n",VARHDRSZ + size, result); // ファイルに書く
    fclose(outputfile);          // ファイルをクローズ(閉じる)

    text *destination = (text *) palloc(VARHDRSZ + size);
    SET_VARSIZE(destination, VARHDRSZ + size);
    memcpy(destination->vl_dat, result, size);
    // for  debug

    mecab_destroy(mecab);

    PG_RETURN_TEXT_P(destination);
}
