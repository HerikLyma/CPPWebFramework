/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <usermodel.h>
#include <cwf/cppwebapplication.h>
#include <cwf/sqldatabasestorage.h>

/*
 * ORM (Experimental) - Tested only on PostgreSQL
 */

CWF::SqlDatabaseStorage conexao("QPSQL", "localhost", "postgres", "postgres", "1234", 5432);

class ORMController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        UserModel user{conexao};
        user.setName("Herik Lima");
        user.setPhone("+55 11 9 99999-0000");
        user.setCountry("Brazil");
        user.setState("São Paulo");
        response.write(QByteArray("<html><body>") + (user.save() ? "Saved" : "Error") + "</body></html>");
    }
};


int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/ORM/server");
    UserModel{conexao}.updateDB();//Create or update the table in database
    server.addController<ORMController>("/orm");
    return server.start();
}
