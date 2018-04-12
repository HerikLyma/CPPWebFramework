/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebcontroller.h"

CWF_BEGIN_NAMESPACE

void CppWebController::doGet(CWF::Request &request, CWF::Response &response) const
{
    QString url(request.getRequestURL());
    if(url.endsWith("/index"))
    {
        request.getRequestDispatcher("/config/cppwebserverpages/index.view").forward(request, response);
    }
    else if(url.endsWith("/examples"))
    {
        request.getRequestDispatcher("/config/cppwebserverpages/examples.view").forward(request, response);
    }
    else if(url.endsWith("/documentation"))
    {
        request.getRequestDispatcher("/config/cppwebserverpages/documentation.view").forward(request, response);
    }
    else if(url.endsWith("/ssl"))
    {
        request.getRequestDispatcher("/config/cppwebserverpages/ssl.view").forward(request, response);
    }
    else if(url.endsWith("/authors"))
    {
        request.getRequestDispatcher("/config/cppwebserverpages/authors.view").forward(request, response);
    }
}

CWF_END_NAMESPACE
