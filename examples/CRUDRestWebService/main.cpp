#include <cwf/cppwebapplication.h>
#include <cwf/sqlquery.h>

CWF::SqlDatabaseStorage storage("QPSQL", "HOST", "DB", "USER", "PASSWORD", 5432);

//Use a tool like Postman to test all methods
class QueryServlet : public CWF::HttpServlet
{
public:    
    //Call with GET method
    //http://localhost:8080/service?table=tableName
    void doGet(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp) override
    {
        CWF::SqlQuery query(storage);
        query.exec("select * from " + req.getParameter("table"));
        resp.write(query.toJson());
    }
    //Call with POST method and insert a JSON into the body of the request
    //http://localhost:8080/service?table=tableName
    void doPost(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp) override
    {
        CWF::SqlQuery query(storage);
        resp.write(query.insertFromJson(req.bodyToJsonObject(), req.getParameter("table")));
    }
    //Call with PUT method and insert a JSON into the body of the request
    //http://localhost:8080/service?table=tableName&pk=pkName&value=id
    void doPut(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp) override
    {
        CWF::SqlQuery query(storage);
        resp.write(query.updateFromJson(req.bodyToJsonObject(), req.getParameter("table"),
                                        req.getParameter("pk") + "=" + req.getParameter("value")));
    }
    //Call with DELETE method
    //http://localhost:8080/service?table=tableName&pk=pkName&value=id
    void doDelete(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp) override
    {
        CWF::SqlQuery query(storage);
        resp.write(query.deleteRecord(req.getParameter("table"),
                                      req.getParameter("pk") + "=" + req.getParameter("value")));
    }
};

int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/CRUDRestWebService/server");
    server.addUrlServlet("/service", new QueryServlet);
    return server.start();
}
