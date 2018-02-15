/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>
#include <servlets/bmiservlet.h>

int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/FillObjectBMI/server/");

    server.addUrlServlet("/bmi", new BmiServlet);

    return server.start();
}
