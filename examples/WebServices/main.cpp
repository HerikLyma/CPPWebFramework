/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <cwf/cppwebapplication.h>
#include <servlets/bmiservlet.h>

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv,
                                  CWF::Configuration("/home/herik/CPPWebFramework/examples/WebServices/server/"));

    server.addUrlServlet("/bmi", new BmiServlet);

    return server.start();
}
