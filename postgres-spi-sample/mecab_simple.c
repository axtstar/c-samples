#include <mecab.h>
#include <stdio.h>
#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "utils/geo_decls.h"

PG_MODULE_MAGIC;

/* 可変長の参照渡し */

PG_FUNCTION_INFO_V1(copytext);

Datum
copytext(PG_FUNCTION_ARGS)
{
    text     *t = PG_GETARG_TEXT_PP(0);

    /*

     * VARSIZEは、そのヘッダのVARHDRSZまたはVARHDRSZ_SHORTを引いた
     * 構造体の総長をバイト数で表したものです。
     * 完全な長さのヘッダと合わせたコピーを作成します。
     */
    text     *new_t = (text *) palloc(VARSIZE_ANY_EXHDR(t) + VARHDRSZ);
    SET_VARSIZE(new_t, VARSIZE_ANY_EXHDR(t) + VARHDRSZ);

    /*

     * VARDATAは新しい構造体のデータ領域へのポインタです。
     * コピー元はshortデータかもしれませんので、VARDATA_ANYでデータを取り出します。
     */

    memcpy((void *) VARDATA(new_t), /* コピー先 */
           (void *) VARDATA_ANY(t), /* コピー元 */
           VARSIZE_ANY_EXHDR(t));   /* バイト数 */
    PG_RETURN_TEXT_P(new_t);
}

#define CHECK(eval) if (! eval) { \
    fprintf (stderr, "Exception:%s\n", mecab_strerror (mecab)); \
    mecab_destroy(mecab); \
    return -1; }

int main (int argc, char *argv[])  {
  char *input = argv[1]; // "太郎は次郎が持っている本を花子に渡した。";
  mecab_t *mecab;
  const mecab_node_t *node;
  const char *result;
  int i;
  size_t len;

  // Create tagger object
  mecab = mecab_new(argc, argv);
  CHECK(mecab);

  // Gets tagged result in string.
  result = mecab_sparse_tostr(mecab, input);
  CHECK(result)
  printf ("input: %s\n", input);
  printf ("RESULT:\n%s", result);

  mecab_destroy(mecab);

  return 0;
}
