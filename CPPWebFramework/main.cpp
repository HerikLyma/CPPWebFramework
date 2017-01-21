/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include <cwf/cppwebapplication.h>

int main(int argc, char *argv[])
{
    CWF::CppWebApplication a(argc, argv, CWF::Configuration("/home/herik/CPPWebFramework/CPPWebFramework/server/"));

    return a.start();
}
