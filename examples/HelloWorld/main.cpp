/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>

class HelloWorldServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override
    {
        Q_UNUSED(request)
        response.write("<html><body>Hello World!</body></html>");
    }
};

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/HelloWorld/server");

    server.addUrlServlet("/hello", new HelloWorldServlet);

    return server.start();
}
