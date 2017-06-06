/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cppwebservlet.h"

CWF_BEGIN_NAMESPACE

void CppWebServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(response)
    QString url(request.getRequestURL());
    if(url.endsWith("/index"))
        request.getRequestDispatcher("/config/cppwebserverpages/index.xhtml").forward(request, response);
    else if(url.endsWith("/examples"))
        request.getRequestDispatcher("/config/cppwebserverpages/examples.xhtml").forward(request, response);
    else if(url.endsWith("/documentation"))
        request.getRequestDispatcher("/config/cppwebserverpages/documentation.xhtml").forward(request, response);
    else if(url.endsWith("/ssl"))
        request.getRequestDispatcher("/config/cppwebserverpages/ssl.xhtml").forward(request, response);
    else if(url.endsWith("/authors"))
        request.getRequestDispatcher("/config/cppwebserverpages/authors.xhtml").forward(request, response);
}

CWF_END_NAMESPACE
