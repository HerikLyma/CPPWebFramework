/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>

class HelloWorldFilter : public CWF::Filter
{
    const QByteArray url{"/hello"};
public:
    void doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response, CWF::FilterChain &chain) override
    {
        if(request.getHttpParser().getUrl() == url)
            response.write("<html><body>Hello World!</body></html>");
        else
            chain.doFilter(request, response);
    }
};

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/HelloWorldFilter/server", new HelloWorldFilter);
    return server.start();
}
