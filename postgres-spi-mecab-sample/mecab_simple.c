#include <mecab.h>
#include <stdio.h>
#include "postgres.h"
#include <string.h>
#include "fmgr.h"
#include "utils/geo_decls.h"

// デバッグ用のプロトタイプ宣言
int fileWrite(const char *path, const char *content );

// これはmecab用
#define CHECK(eval) if (! eval) { \
    fprintf (stderr, "Exception:%s\n", mecab_strerror (mecab)); \
    mecab_destroy(mecab); \
    return -1; }

// 非互換性のチェック
PG_MODULE_MAGIC;

/* 可変長の参照渡し */
PG_FUNCTION_INFO_V1(mecab);
PG_FUNCTION_INFO_V1(mecab_args);
PG_FUNCTION_INFO_V1(mecab_nbest);
PG_FUNCTION_INFO_V1(mecab_dic_info);
PG_FUNCTION_INFO_V1(mecab_version_info);


//37.10.3 Version 1 呼び出し規約を利用
Datum mecab(PG_FUNCTION_ARGS)
{
  // それぞれの実引数は、引数のデータ型に合ったPG_GETARG_xxx()マクロを使用して取り出す。
  // 厳格でない関数では、PG_ARGNULL_xxx()を使って引数がNULLかどうか事前に確認することが必要
    text     *t = PG_GETARG_TEXT_PP(0); // input value
    text     *destination; // for return value

    char *input=t->vl_dat;
    int size; // return value size

    // mecab
    mecab_t *mecab;
    const char *result;

    // Create tagger object
    // available command line argument?
    // https://taku910.github.io/mecab/format.html
    // http://www.mwsoft.jp/programming/munou/mecab_command.html#output-format-type

    // mecab_new2
    // const char* mecab_args = "-Oyomi";
    // mecab = mecab_new2(mecab_args);

    // mecab_new
    mecab = mecab_new(1, &input);
    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_sparse_tostr(mecab, input);
    CHECK(result)

    //fileWrite("/tmp/mecab_simple.txt", result); //for debug

    size = strlen(result);

    // メモリアロケーションはpalloc/palloc0を利用すること
    destination = (text *) palloc0(VARHDRSZ + size);
    // 長さ確保マクロ
    SET_VARSIZE(destination, VARHDRSZ + size);
    // https://www.postgresql.jp/document/12/html/xfunc-c.html
    // `char data[FLEXIBLE_ARRAY_MEMBER]`
    // ↑とあるが、vl_datの誤り？
    // see https://github.com/postgres/postgres/blob/de8feb1f3a23465b5737e8a8c160e8ca62f61339/src/include/c.h#L565
    memcpy(destination->vl_dat, result, size);

    // mecabの終了処理
    mecab_destroy(mecab);

    // 返却値用マクロ
    PG_RETURN_TEXT_P(destination);
}

//37.10.3 Version 1 呼び出し規約を利用
Datum mecab_args(PG_FUNCTION_ARGS)
{
  // それぞれの実引数は、引数のデータ型に合ったPG_GETARG_xxx()マクロを使用して取り出す。
  // 厳格でない関数では、PG_ARGNULL_xxx()を使って引数がNULLかどうか事前に確認することが必要
    text     *t = PG_GETARG_TEXT_PP(0); // input value
    text     *a = PG_GETARG_TEXT_PP(1); // args value
    text     *destination; // for return value

    char *input=t->vl_dat;
    char *args=a->vl_dat;
    int size; // return value size

    // mecab
    mecab_t *mecab;
    const char *result;

    // Create tagger object
    // available command line argument?
    // https://taku910.github.io/mecab/format.html
    // http://www.mwsoft.jp/programming/munou/mecab_command.html#output-format-type

    // mecab_new2
    // const char* mecab_args = "-Oyomi";
    mecab = mecab_new2(args);

    // mecab_new
    //mecab = mecab_new(1, &input);
    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_sparse_tostr(mecab, input);
    CHECK(result)

    //fileWrite("/tmp/mecab_simple.txt", result); //for debug

    size = strlen(result);

    // メモリアロケーションはpalloc/palloc0を利用すること
    destination = (text *) palloc0(VARHDRSZ + size);
    // 長さ確保マクロ
    SET_VARSIZE(destination, VARHDRSZ + size);
    // https://www.postgresql.jp/document/12/html/xfunc-c.html
    // `char data[FLEXIBLE_ARRAY_MEMBER]`
    // ↑とあるが、vl_datの誤り？
    // see https://github.com/postgres/postgres/blob/de8feb1f3a23465b5737e8a8c160e8ca62f61339/src/include/c.h#L565
    memcpy(destination->vl_dat, result, size);

    // mecabの終了処理
    mecab_destroy(mecab);

    // 返却値用マクロ
    PG_RETURN_TEXT_P(destination);
}


//37.10.3 Version 1 呼び出し規約を利用
Datum mecab_nbest(PG_FUNCTION_ARGS)
{
  // それぞれの実引数は、引数のデータ型に合ったPG_GETARG_xxx()マクロを使用して取り出す。
  // 厳格でない関数では、PG_ARGNULL_xxx()を使って引数がNULLかどうか事前に確認することが必要
    text     *t = PG_GETARG_TEXT_PP(0); // input value
    int32    nbest = PG_GETARG_INT32(1);

    text     *destination; // for return value

    char *input=t->vl_dat;
    int size; // return value size

    // mecab
    mecab_t *mecab;
    const char *result;

    // Create tagger object
    // available command line argument?
    // https://taku910.github.io/mecab/format.html
    // http://www.mwsoft.jp/programming/munou/mecab_command.html#output-format-type

    // mecab_new2
    // const char* mecab_args = "-Oyomi";
    // mecab = mecab_new2(mecab_args);

    // mecab_new
    mecab = mecab_new(1, &input);
    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_nbest_sparse_tostr(mecab, nbest, input);
    CHECK(result)

    //fileWrite("/tmp/mecab_simple.txt", result); //for debug

    size = strlen(result);

    // メモリアロケーションはpalloc/palloc0を利用すること
    destination = (text *) palloc0(VARHDRSZ + size);
    // 長さ確保マクロ
    SET_VARSIZE(destination, VARHDRSZ + size);
    // https://www.postgresql.jp/document/12/html/xfunc-c.html
    // `char data[FLEXIBLE_ARRAY_MEMBER]`
    // ↑とあるが、vl_datの誤り？
    // see https://github.com/postgres/postgres/blob/de8feb1f3a23465b5737e8a8c160e8ca62f61339/src/include/c.h#L565
    memcpy(destination->vl_dat, result, size);

    // mecabの終了処理
    mecab_destroy(mecab);

    // 返却値用マクロ
    PG_RETURN_TEXT_P(destination);
}

//37.10.3 Version 1 呼び出し規約を利用
Datum mecab_dic_info(PG_FUNCTION_ARGS)
{
  // それぞれの実引数は、引数のデータ型に合ったPG_GETARG_xxx()マクロを使用して取り出す。
  // 厳格でない関数では、PG_ARGNULL_xxx()を使って引数がNULLかどうか事前に確認することが必要
    text     *destination; // for return value

    int size; // return value size

    // mecab
    mecab_t *mecab;
    const mecab_dictionary_info_t *result;

    // Create tagger object
    const char* mecab_args = "-Oyomi";
    mecab = mecab_new2(mecab_args);
    //mecab_new2

    CHECK(mecab);

    // Gets tagged result in string.
    result = mecab_dictionary_info(mecab);
    CHECK(result)

    size = strlen(result->filename);

    // メモリアロケーションはpalloc/palloc0を利用すること
    destination = (text *) palloc0(VARHDRSZ + size);
    // 長さ確保マクロ
    SET_VARSIZE(destination, VARHDRSZ + size);
    // https://www.postgresql.jp/document/12/html/xfunc-c.html
    // `char data[FLEXIBLE_ARRAY_MEMBER]`
    // ↑とあるが、vl_datの誤り？
    // see https://github.com/postgres/postgres/blob/de8feb1f3a23465b5737e8a8c160e8ca62f61339/src/include/c.h#L565
    memcpy(destination->vl_dat, result->filename, size);

    // mecabの終了処理
    mecab_destroy(mecab);

    // 返却値用マクロ
    PG_RETURN_TEXT_P(destination);
}

//37.10.3 Version 1 呼び出し規約を利用
Datum mecab_version_info(PG_FUNCTION_ARGS)
{
  // それぞれの実引数は、引数のデータ型に合ったPG_GETARG_xxx()マクロを使用して取り出す。
  // 厳格でない関数では、PG_ARGNULL_xxx()を使って引数がNULLかどうか事前に確認することが必要
    text     *destination; // for return value

    int size; // return value size

    const char *result;

    // Gets tagged result in string.
    result = mecab_version();

    size = strlen(result);

    // メモリアロケーションはpalloc/palloc0を利用すること
    destination = (text *) palloc0(VARHDRSZ + size);
    // 長さ確保マクロ
    SET_VARSIZE(destination, VARHDRSZ + size);
    // https://www.postgresql.jp/document/12/html/xfunc-c.html
    // `char data[FLEXIBLE_ARRAY_MEMBER]`
    // ↑とあるが、vl_datの誤り？
    // see https://github.com/postgres/postgres/blob/de8feb1f3a23465b5737e8a8c160e8ca62f61339/src/include/c.h#L565
    memcpy(destination->vl_dat, result, size);

    // 返却値用マクロ
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
