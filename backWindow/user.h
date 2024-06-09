#include "include\mysql.h"
#include <iostream>
#include <string>
#include <crow.h>
using namespace std;
class user
{
    public:
    int uid;
    user();
    ~user();
    crow::response registeruser(MYSQL* mysql,string name,string password);
    crow::response loginuser(MYSQL* mysql,int uid,string password);
    crow::response createarticle(MYSQL* mysql,int uid,string title.string time,string keyword1,string keyword2,string keyword3,string keyword4,string keyword5,string keyword6,string content,string category1,string category2,string category3,string category4,int share);
    crow::response deletearticle(MYSQL* mysql,int uid);
    crow::response updatearticle(MYSQL* mysql,int uid);
    crow::response querytime(MYSQL* mysql,int uid);
    crow::response querykeyword(MYSQL* mysql,int uid);
    crow::response querytitle(MYSQL* mysql,int uid);
    crow::response querycategory(MYSQL* mysql,int uid);
    crow::response querycontent(MYSQL* mysql,int uid);
    crow::response updateinformation(MYSQL* mysql,int uid);
    crow::response comment(MYSQL* mysql,int uid);
    crow::response createcategory(MYSQL* mysql,int uid);
    crow::response updatecategory(MYSQL* mysql,int uid);
    crow::response deletecategory(MYSQL* mysql,int uid);
};