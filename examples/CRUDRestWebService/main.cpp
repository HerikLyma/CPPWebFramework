#include <cwf/cppwebapplication.h>
#include <cwf/sqlquery.h>

CWF::SqlDatabaseStorage storage("QPSQL", "HOST", "DB", "USER", "PASSWORD", 5432);

//Use a tool like Postman to test all methods
class QueryController : public CWF::Controller
{
public:    
    //Call with GET method
    //http://localhost:8080/service?table=tableName
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(storage);
        query.exec("select * from " + request.getParameter("table"));
        response.write(query.toJson());
    }
    //Call with POST method and insert a JSON into the body of the request
    //http://localhost:8080/service?table=tableName
    void doPost(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(storage);
        response.write(query.insertFromJson(request.bodyToJsonObject(), request.getParameter("table")));
    }
    //Call with PUT method and insert a JSON into the body of the request
    //http://localhost:8080/service?table=tableName&pk=pkName&value=id
    void doPut(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(storage);
        response.write(query.updateFromJson(request.bodyToJsonObject(), request.getParameter("table"),
                                        request.getParameter("pk") + "=" + request.getParameter("value")));
    }
    //Call with DELETE method
    //http://localhost:8080/service?table=tableName&pk=pkName&value=id
    void doDelete(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery query(storage);
        response.write(query.deleteRecord(request.getParameter("table"),
                                      request.getParameter("pk") + "=" + request.getParameter("value")));
    }
};

int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/CRUDRestWebService/server");
    server.addController<QueryController>("/service");
    return server.start();
}
