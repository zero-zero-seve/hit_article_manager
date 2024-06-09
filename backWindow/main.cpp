#include "user.h"
crow::SimpleApp app;
MYSQL mysql;
user userr;
int main(int argc, char const *argv[])
{
    mysql_init(&mysql);
    const char host[]="localhost";
    const char user[]="root";
    const char psw[]="sunyangbin0412";
    const char database[]="software";
    unsigned int port=3306;
    if(!mysql_real_connect(&mysql,host,user,psw,database,port,NULL,0))
    {
        cout << "Error connecting to database:"<< mysql_error(&mysql) << endl;
        return 0;
    }
    mysql_set_character_set(&mysql,"gbk");

    CROW_ROUTE(app, "/receive_message").methods("POST"_method)([](const crow::request& req) 
    {
        auto message = crow::json::load(req.body);
        if (!message)
        {
            crow::response res;
            res.code = 400;
            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");
            return res;
        }
        string operation = message["operation"].s();
        cout << "Received operation: " << operation << endl;
        crow::response res;
        if(!operation.compare("registeruser"))
        {
            string name = message["name"].s();
            string password = message["password"].s();
            res=userr.registeruser(&mysql,name,password);
        }
        else if(!operation.compare("loginuser"))
        {
            int uid = message["uid"].i();
            userr.uid=uid;
            string password = message["password"].s();
            res=userr.loginuser(&mysql,uid,password);
        }
        else if(operation.compare("createarticle"))
        {
            string title = message["title"].s();
            string time = message["time"].s();
            string keyword1 = message["keyword1"].s();
            string keyword2 = message["keyword2"].s();
            string keyword3 = message["keyword3"].s();
            string keyword4 = message["keyword4"].s();
            string keyword5 = message["keyword5"].s();
            string keyword6 = message["keyword6"].s();
            string content = message["content"].s();
            string category1 = message["category1"].s();
            string category2 = message["category2"].s();
            string category3 = message["category3"].s();
            string category4 = message["category4"].s();
            int share = message["share"].i();
            userr.createarticle(&mysql,userr.uid,title,time,keyword1,keyword2,keyword3,keyword4,keyword5,keyword6,content,category1,category2,category3,category4,share);
        }
        /*else if(operation.compare("deletearticle"))
        {
            userr.deletearticle(mysql,userr.uid);
        }
        else if(operation.compare("updatearticle"))
        {
            userr.updatearticle(mysql,userr.uid);
        }
        else if(operation.compare("querytime"))
        {
            userr.querytime(mysql,userr.uid);
        }
        else if(operation.compare("querykeyword"))
        {
            userr.querykeyword(mysql,userr.uid);
        }
        else if(operation.compare("querytitle"))
        {
            userr.querytitle(mysql,userr.uid);
        }
        else if(operation.compare("querycategory"))
        {
            userr.querycategory(mysql,userr.uid);
        }
        else if(operation.compare("querycontent"))
        {
            userr.querycontent(mysql,userr.uid);
        }
        else if(operation.compare("updateinformation"))
        {
            userr.updateinformation(mysql,userr.uid);
        }
        else if(operation.compare("comment"))
        {
            userr.comment(mysql,userr.uid);
        }
        else if(operation.compare("createcategory"))
        {
            userr.createcategory(mysql,userr.uid);
        }
        else if(operation.compare("updatecategory"))
        {
            userr.updatecategory(mysql,userr.uid);
        }
        else if(operation.compare("deletecategory"))
        {
            userr.deletecategory(mysql,userr.uid);
        }*/

        /*crow::json::wvalue response;
        response["status"] = "success";
        response["received_message"] = "满怀希望就会所向披靡。";
        crow::response res{response};*/
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    CROW_ROUTE(app, "/send_message")([]() {
        crow::json::wvalue response;
        response["message"] = "Hello from Crow!";
        crow::response res{response};
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        cout << "run";
        return res;
    });

    app.port(18080).multithreaded().run();
    cout << "$%^";
    return 0;
}