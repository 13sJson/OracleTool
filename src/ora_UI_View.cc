
/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           ファイル名： ora_UI_View.pc             ( Oracle Select UIView )            *
*                                                                                      *
*           説明：チェック済みのクエリをPL/SQLにて実行し、                                 *
*                返りを一つのレコードずつ表示する形式でUI画面に表示                        *
*                                                                                      *                                               *
*                                                                                      *
* *********************************************************************************** */

/* ヘッダファイル */
#include <iostreame>
#include <string>

#inclede "ora_Viewtool.hpp"

EXEC SQL INCLUDE sqlca;
EXEC SQL INCLUDE sqlda;

/* static */

EXEC BEGIN DECLARE SECTION;
    static std::string user;
    static std::string pass;
EXEC SQL END DECLARE SECTION;
static SQLDA *select_dp = (SQLDA *)0;

/* 関数宣言 */
ora_UI_View_select();



/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           関数名： ora_UI_View                  ( Oracle UIViewメイン )               *
*                                                                                      *
*                                                                                      *
*           引数： ora_UI_View (s1)                                                     *
*                i1...クエリ文                                                          *
*                                                                                      *
*           戻り値： 0...正常                                                           *
*                  -1...パラメータエラー                                                *
*                  -2...ファイル読み込みエラー                                           *
*                                                                                      *
*           使用方法：引数にて実行可能                                                   *
*                    実行モードにより記憶機能をON/OFF可（拡張予定）                        *
*                    自フォルダ内のSQLファイルを読み込みクエリを取得する                   *
*                                                                                      *
*                                                                                      *
* ************************************************************************************ */
int    ora_UI_View(std::string sql_s)
{
    std::string func = "ora_UI_View";
    int sts;

    /* Oracleログイン */
    SqlU sqlu;
    user = sqlu.getuser();
    pass = sqlu.getpass();

    EXEC SQL CONNECT :user IDENTIFIED BY :pass;
    if (sqlca.sqlcode != 0){
        std::cout << "DB接続エラー" << std::endl;
        sts = DB_LOGIN_ERR;
        return sts;
    }


    /* SQL実行 */
    EXEC SQL PREPARA S FROM :sql_s; 
    EXEC SQL DECLARE C CURSOR FOR S;

    EXEC SQL OPEN C;

    /* 最大項目数の設定 */
    select_dp->N = MAX_ITEM;
    
    /* 動的SQLのための設定を発行 */
    EXEC SQL DESCRIBE SELECT LIST FOR S INTO select_dp;

    if (select_dp->F < 0){
        std::cout << "項目数取得エラー[select_dp: " << select_dp->N << "]" << std::endl;
        sts = DB_ERR
        EXEC SQL ROLLBACK WORK RELEASE;
        return sts;
    }

    /* 最大項目数に実際項目数を設定 */
    select_dp->N = select_dp->F;

    for (i = 0; i < select_dp->F; i++){
        /* NULL/NOTNULL ビットのクリア */
        SQLColumnNullCheck(dvoid *context, unsigned short *value_type, 
                           unsigned short *type_code, int *null_status);
    
    
    }

}