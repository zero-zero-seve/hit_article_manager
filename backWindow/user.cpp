#include "user.h"

user::user()
{
}

user::~user()
{
}

crow::response user::registeruser(MYSQL* mysql,string name,string password)
{
    int uid;

    //分配uid
    string command = "select max(uid) from user";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    uid = atoi(row[0]) + 1;
    mysql_free_result(res);

    //信息录入数据库
    command = "insert into user values ('" + to_string(uid) + "','" + name + "','" + password + "',NULL," + "NULL," + "NULL," + "NULL," + "NULL)";
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Register succeed , your uid is " << uid << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        crow::json::wvalue response;
        response["status"] = "success";
        response["result"] = uid;
        crow::response ress{response};
        return ress;
    }
    else
    {
        cout << "Register fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        crow::json::wvalue response;
        response["status"] = "failure";
        response["result"] = mysql_error(mysql);
        crow::response ress{response};
        return ress;
    }
}

crow::response loginuser(MYSQL* mysql,int uid,string password)
{
    //检查uid和密码是否正确
    string command = "select* from user where uid=" + to_string(uid) + " and password='" + password + "'";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    if(mysql_fetch_row(res)!=NULL)
    {
        cout << "Login succeed" << endl;
        mysql_free_result(res);
        crow::json::wvalue response;
        response["status"] = "success";
        response["result"] = "Login succeed";
        crow::response ress{response};
        return ress;
    }
    else
    {
        cout << "Login fail" << endl;
        mysql_free_result(res);
        crow::json::wvalue response;
        response["status"] = "failure";
        response["result"] = mysql_error(mysql);
        crow::response ress{response};
        return ress;
    }
}

crow::response user::createarticle(MYSQL* mysql,int uid)
{
    string title;
    string time;
    string keyword1;
    string keyword2;
    string keyword3;
    string keyword4;
    string keyword5;
    string keyword6;
    string content;
    string category1;
    string category2;
    string category3;
    string category4;
    int share;

    cin >> title;
    cin >> time;
    cin >> content;
    cin >> share;
    cin >> keyword1;
    cin >> keyword2;
    cin >> keyword3;
    cin >> keyword4;
    cin >> keyword5;
    cin >> keyword6;
    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //分配aid
    string command = "select max(aid) from article";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int aid = atoi(row[0]) + 1;
    mysql_free_result(res);

    //禁止同一用户在相同分类下创建相同标题的文章
    command = "select* from article where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and title='" + title + "'and uid =" + to_string(uid);
    ret = mysql_query(mysql,command.c_str());
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(res);
    if(row)
    {
        cout << "Create article fail : Same name article" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }

    //文章信息录入数据库
    command = "insert into article values ('" + to_string(aid) + "','" + to_string(uid) + "','" + title + "','" + time + "','" + keyword1 + "','" + keyword2 + "','" + keyword3 + "','" + keyword4 + "','" + keyword5 + "','" + keyword6 + "','" + content + "','" + category1 + "','" + category2 + "','" + category3 + "','" + category4 + "','" + to_string(share) + "')";
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Create article fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Create article succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return aid;
}

crow::response user::deletearticle(MYSQL* mysql,int uid)
{
    string title;
    string category1;
    string category2;
    string category3;
    string category4;

    cin >> title;
    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //通过uid，分类和标题唯一的确定一篇文章
    string command = "delete from article where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and title='" + title + "' and uid =" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    if(ret)
    {
        cout << "Delete article fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Delete article succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return 1;
}

crow::response user::updatearticle(MYSQL* mysql,int uid)
{
    string title;
    string time;
    string keyword1;
    string keyword2;
    string keyword3;
    string keyword4;
    string keyword5;
    string keyword6;
    string content;
    string category1;
    string category2;
    string category3;
    string category4;
    int share;

    cin >> title;
    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //获得正在修改的文章的aid
    string command = "select aid from article where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and title='" + title + "'and uid =" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int aid = atoi(row[0]);
    mysql_free_result(res);

    cin >> title;
    cin >> time;
    cin >> content;
    cin >> share;
    cin >> keyword1;
    cin >> keyword2;
    cin >> keyword3;
    cin >> keyword4;
    cin >> keyword5;
    cin >> keyword6;
    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    ////禁止同一用户在相同分类下由于修改而产生相同标题的文章
    command = "select* from article where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and title='" + title + "' and uid=" + to_string(uid) + " and aid!=" + to_string(aid);
    ret = mysql_query(mysql,command.c_str());
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(res);
    if(row)
    {
        cout << "Update article fail : Same name article" << endl;
        res=mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }

    //更新文章信息到数据库
    command = "update article set title='" + title + "',time='" + time + "',keyword1='" + keyword1 + "',keyword2='" + keyword2 + "',keyword3='" + keyword3 + "',keyword4='" + keyword4 + "',keyword5='" + keyword5 + "',keyword6='" + keyword6 + "',content='" + content + "',category1='" + category1 + "',category2='" + category2 + "',category3='" + category3 + "',category4='" + category4 + "',share=" + to_string(share) + " where aid=" + to_string(aid);
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Update article fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Update article succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return aid;
}

crow::response user::querytime(MYSQL* mysql,int uid)
{
    //按时间查询
    string time;
    cin >> time;
    string command = "select* from article where time='" + time + "' and (uid=" + to_string(uid) + " or share!=" + to_string(0) + ")";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL)
    {
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            if(row[i])
            {
                cout << row[i] << "\t";
            }
        }
        cout << endl;
    }
    mysql_free_result(res);
    return 1;
}

crow::response user::querycategory(MYSQL* mysql,int uid)
{
    //按类别查询
    string category;
    cin >> category;
    string command = "select* from article where (category1='" + category + "' or category2='" + category + "' or category3='" + category + "' or category4='" + category + "')" + " and (uid=" + to_string(uid) + " or share!=" + to_string(0) + ")";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL)
    {
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            if(row[i])
            {
                cout << row[i] << "\t";
            }
        }
        cout << endl;
    }
    mysql_free_result(res);
    return 1;
}

crow::response user::querycontent(MYSQL* mysql,int uid)
{
    //全文检索
    string content;
    cin >> content;
    string command = "select* from article where content='" + content + "' and (uid=" + to_string(uid) + " or share!=" + to_string(0) + ")";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL)
    {
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            if(row[i])
            {
                cout << row[i] << "\t";
            }
        }
        cout << endl;
    }
    mysql_free_result(res);
    return 1;
}

crow::response user::querykeyword(MYSQL* mysql,int uid)
{
    //按关键字查询
    string keyword;
    cin >> keyword;
    string command = "select* from article where (keyword1='" + keyword + "' or keyword2='" + keyword + "' or keyword3='" + keyword + "' or keyword4='" + keyword + "' or keyword5='" + keyword +  + "' or keyword6='" + keyword + "')" + " and (uid=" + to_string(uid) + " or share!=" + to_string(0) + ")";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL)
    {
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            if(row[i])
            {
                cout << row[i] << "\t";
            }
        }
        cout << endl;
    }
    mysql_free_result(res);
    return 1;
}

crow::response user::querytitle(MYSQL* mysql,int uid)
{   
    //按标题查询
    string title;
    cin >> title;
    string command = "select* from article where title='" + title + "' and (uid=" + to_string(uid) + " or share!=" + to_string(0) + ")";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL)
    {
        for(int i = 0; i < mysql_num_fields(res); i++)
        {
            if(row[i])
            {
                cout << row[i] << "\t";
            }
        }
        cout << endl;
    }
    mysql_free_result(res);
    return 1;
}

crow::response user::updateinformation(MYSQL* mysql,int uid)
{
    string name;
    string password;
    string sex;
    string introduction;
    string birthday;
    string region;
    int age;

    cin >> name;
    cin >> password;
    cin >> sex;
    cin >> introduction;
    cin >> birthday;
    cin >> region;
    cin >> age;

    //更新用户信息到数据库
    string command = "update user set name='" + name + "',password='" + password + "',sex='" + sex + "',introduction='" + introduction + "',birthday='" + birthday + "',region='" + region + "',age=" + to_string(age) + " where uid=" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES* res;
    if(ret)
    {
        cout << "Update information fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Update information succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return uid;
}

crow::response user::comment(MYSQL* mysql,int cuid)
{
    int uid;
    string title;
    string category1;
    string category2;
    string category3;
    string category4;
    string comment;

    cin >> uid;
    cin >> title;
    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;
    cin >> comment;

    ////获得正在评论的文章的aid
    string command = "select aid from article where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and title='" + title + "'and uid =" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int aid = atoi(row[0]);
    mysql_free_result(res);

    //为评论分配cid
    command = "select max(cid) from comment";
    ret = mysql_query(mysql,command.c_str());
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(res);
    int cid = atoi(row[0]) + 1;
    mysql_free_result(res);

    //更新评论信息到数据库
    command = "insert into comment values ('" + to_string(cid) + "','" + to_string(cuid) + "','" + to_string(aid) + "','" + comment + "')";
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Comment fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Comment succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return cid;
}

crow::response user::createcategory(MYSQL* mysql,int uid)
{
    string category1;
    string category2;
    string category3;
    string category4;
    int depth;

    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;
    cin >> depth;

    //为分类分配cid
    string command = "select max(cid) from category";
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int cid = atoi(row[0]) + 1;
    mysql_free_result(res);

    //禁止同一用户在相同分类下有相同的分类
    command = "select* from category where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and uid=" + to_string(uid);
    ret = mysql_query(mysql,command.c_str());
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(res);
    if(row)
    {
        cout << "Create category fail : Same name category" << endl;
        res=mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }

    //更新分类信息到数据库
    command = "insert into category values ('" + to_string(cid) + "','" + to_string(uid) + "','" + category1 + "','" + category2 + "','" + category3 + "','" + category4 + "','" + to_string(depth) + "')";
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Create category fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Create category succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return cid;
}

crow::response user::updatecategory(MYSQL* mysql,int uid)
{
    string category1;
    string category2;
    string category3;
    string category4;

    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //根据uid和分类唯一的确定当前正在修改的分类，获得其cid
    string command = "select cid from category where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "'and uid =" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int cid = atoi(row[0]);
    mysql_free_result(res);

    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //避免因修改分类而在同一用户的同一分类下产生相同的分类
    command = "select* from category where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and uid=" + to_string(uid) + " and cid!=" + to_string(cid);
    ret = mysql_query(mysql,command.c_str());
    res = mysql_use_result(mysql);
    row = mysql_fetch_row(res);
    if(row)
    {
        cout << "Update category fail : Same name category" << endl;
        res=mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }

    //更新分类信息到数据库
    command = "update category set category1='" + category1 + "',category2='" + category2 + "',category3='" + category3 + "',category4='" + category4 + "' where cid=" + to_string(cid);
    ret = mysql_query(mysql,command.c_str());
    if(ret)
    {
        cout << "Update category fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Update category succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return cid;
}

crow::response user::deletecategory(MYSQL* mysql,int uid)
{
    string category1;
    string category2;
    string category3;
    string category4;

    cin >> category1;
    cin >> category2;
    cin >> category3;
    cin >> category4;

    //根据用户和分类唯一的确定要删除的分类
    string command = "delete from category where category1='" + category1 + "' and category2='" + category2 + "' and category3='" + category3 + "' and category4='" + category4 + "' and uid =" + to_string(uid);
    int ret = mysql_query(mysql,command.c_str());
    MYSQL_RES *res = mysql_use_result(mysql);
    if(ret)
    {
        cout << "Delete category fail" << mysql_error(mysql) << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
        return 0;
    }
    else
    {
        cout << "Delete category succeed" << endl;
        res = mysql_use_result(mysql);
        mysql_free_result(res);
    }
    return 1;
}
