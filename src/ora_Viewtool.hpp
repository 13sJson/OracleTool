
/* *********************************************************************************** *
*                                                                                      *
*                                                                                      *
*           ファイル名：  ora_Viewtool.hpp     ( oraTool Viewツール 共通ヘッダファイル)   *
*                                                                                      *
*                                                                                      *
*           引数： ora_Viewtool.hpp                                                     *
*                                                                                      *
*           内容： 各DB専用クラスへの引数構造体の宣言の専用ヘッダ                           *
*                 共通マクロ・構造体の宣                                                 *
*                                                                                      *
* ************************************************************************************ */

/*** 共通include定義 ***/


/*** マクロ定義 ***/
#define MAX_ITEM          1024        /* 選択リスト項目の最大数 */

/* Pro*C SQLDA*/
#define TYPE_VARCHAR2     1           /* VARCHAR2             */
#define TYPE_NUMBER       2           /* NUMBER               */
#define TYPE_INTEGER      3           /* INTEGER              */
#define TYPE_FLOAT        4           /* FLOAT                */
#define TYPE_STRING       5           /* STRING               */
#define TYPE_LONG         8           /* LONG                 */
#define TYPE_ROWID       11           /* ROWID                */
#define TYPE_DATE        12           /* DATE                 */
#define TYPE_ROW         23           /* ROW                  */
#define TYPE_LONGROW     24           /* LONGROW              */
#define TYPE_CHAR        96           /* CHAR                 */
#define TYPE_CLOB       112           /* CLOB                 */



#define PARAERR          -1           /* パラメータエラー*/
#define NOTFOUNDFILE     -2           /* ファイル不正 */
#define DB_LOGIN_ERR     -3           /* DBログインエラー */


#define USER             "system"
#define PASS             "jiji"

/*** 関数定義 ***/
int ora_UI_View(std::string);

/*** クラス定義 ***/
class SqlU
{
private:
    const std::string user = USER;
    const std::string pass = PASS;

public:
    std::string getuser(){
        return user;
    }

    std::string getpass(){
        return pass;
    }
};