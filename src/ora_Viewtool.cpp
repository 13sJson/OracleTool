
/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           ファイル名：  ora_Viewtool.cpp            ( oraTool Viewツール )             *
*                                                                                      *
*                                                                                      *
*           引数： ora_Viewtool.cpp (void)                                              *
*                                                                                      *
*           使用方法：bashから起動され、引数によって遷移する                               *
*                    本ファイル内にて.sqlファイルからクエリを取得し                        *
*                    ora_UI_View.pcへクエリを送り実行する                                *
*                                                                                      *
*           注意：本プロセスはselect文のみ使用可とし、それ以外の入力は拒否する               *
*                                                                                      *
* ************************************************************************************ */


/*** ヘッダファイル ***/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "ora_ViewTool.hpp"

/*** static ***/
static std::string filename;                  /* SQLファイル名        */
static std::string sql_s                      /* クエリ              */
static int exeflg;                            /* 実行フラグ（拡張予定）*/

/*** 関数宣言 ***/
int arg_check(int, char**);
int sql_check(std::string);




/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           関数名： main                  ( oraTool ユーザーインターフェース )           *
*                                                                                      *
*                                                                                      *
*           引数： main (i1, s2)                                                        *
*                i1...args    引数個数                                                  *
*                s2...argv[]  1.実行モード（0.nomal, 1.save）＃(拡張予定)                *
*                             2.sqlファイル名                                           *
*           戻り値： 0...正常                                                           *
*                  -1...パラメータエラー                                                *
*                  -2...ファイル読み込みエラー                                           *
*                                                                                      *
*           使用方法：引数にて実行可能                                                   *
*                    実行モードにより記憶機能をON/OFF可（拡張予定）                        *
*                    自フォルダ内のSQLファイルを読み込みクエリを取得し実行する              *
*                                                                                      *
*                                                                                      *
* ************************************************************************************ */

int        main(int args, char** argv)
{
    int sts;
    int flg;
    const char *c_filename;
    std::string buf;
    std::ifstream ifs;

    /* 引数チェック */
    sts = arg_check(args, argv);
    if (sts != 0){
        goto L_end;
    }

    c_filename = filename.c_str();

    /* ファイルの読み込み */
    ifs.open(c_filename);
    if (!ifs){
        std::cerr << "ファイルが見つかりません：" << filename << std::endl;
        sts = NOTFOUNDFILE;
        goto L_end;
    }

    flg = 0;

    while (std::getline(ifs, buf)){
        /* 段落がある場合 */
        if (flg > 0){
            sql_s = sql_s + " ";
        }

        sql_s = sql_s + buf;

        flg++;
    }
    
    /* クエリチェック */
    sts = query_check(sql_s);
    if (sts != 0){
        goto L_end;
    }

    /* SQL*Plus実行 */
    sts = ora_UI_View(sql_s);

    /* 実行モード遷移（拡張予定） */
    

L_end:
    return sts;

}

/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           関数名： arg_check             ( 引数チェック )                              *
*                                                                                      *
*                                                                                      *
*           引数： main (i1, s2)                                                        *
*                i1...args    引数個数                                                  *
*                s2...argv[]  1.実行モード（0.nomal, 1.save）＃(拡張予定)                *
*                             2.sqlファイル名                                           *
*           戻り値： 0...正常                                                           *
*                  -1...パラメータエラー                                                *
*                                                                                      *
* *********************************************************************************** */
int arg_check(int args, char** argv)
{

    std::string funk = "arg_check"
    int sts;

    if (args < 3 or args > 3){
        sts = PARAERR;
        goto L_end;
    }

    /* 実行モード */
    exeflg = atoi(argv[1]);

    /* ファイル名取得 */
    filename = argv[2];

L_end:
    if(sts != 0){    
        std::cout << "err>" << funk << "= (args=" << args << 
            "(argv[1]=" << argv[1] << ",argv[2]=" << argv[2] << ")" << std::endl;
    }
    return sts;
}

/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           関数名： query_check             ( クエリチェック )                          *
*                                                                                      *
*                                                                                      *
*           引数： main (s1)                                                            *
*                i1...sql_s    sqlクエリ                                                *
*                                                                                      *
*           戻り値： 0...正常                                                           *
*                  -1...パラメータエラー                                                *
*                                                                                      *
* *********************************************************************************** */
int    query_check(std::string sql_s){
    
    std::string funk = "query_check";
    int sts;
    std::string sql_so;

    /* クエリを大文字に変換 */
    std::transform(sql_s.begin(), sql_s.end(), sql_so.begin(), toupper);

    /* SELECTチェック*/
    if (sql_so.find("SELECT") == std::string::npos){
        std::cerr << "err>" << funk <<"=NotFound SELECT" << std::endl
        sts = PARAERR;
        return sts;
    }

    /* FROMチェック */
    if (sql_so.find("FROM") == std::string::npos){
        std::cerr << "err>" << funk <<"=NotFound FROM" << std::endl
        sts = PARAERR;
        return sts;
    }

    return sts;
}