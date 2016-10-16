/**
  @file main.cpp
  @author Herik Lima
*/

#include <QCoreApplication>
#include <cwf/cppwebapplication.h>

int main(int argc, char *argv[])
{
    CWF::CppWebApplication a(argc, argv, CWF::Configuration("/home/herik/CPPWebFramework/CPPWebFramework/server/"));

    return a.start();
}
