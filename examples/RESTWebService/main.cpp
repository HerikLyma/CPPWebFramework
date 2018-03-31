/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/sqlquery.h>
#include <cwf/cppwebapplication.h>
#include <cwf/sqldatabasestorage.h>

/*
 * SQL Script
 * create table countries (co_id serial primary key, co_name varchar unique);
 * insert into countries (co_name) values ('BRAZIL'), ('UNITED STATES OF AMERICA'), ('CANADA');
 */

CWF::SqlDatabaseStorage storage("QPSQL", "localhost", "postgres", "postgres", "1234", 5432);

class CountriesServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override
    {
        CWF::SqlQuery qry(storage);
        qry.exec("select * from countries");
        response.write(qry.toJson());
    }
};

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/RESTWebService/server");
    server.addUrlServlet("/countries", new CountriesServlet);
    return server.start();
}
