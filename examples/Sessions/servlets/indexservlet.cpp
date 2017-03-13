/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "indexservlet.h"
#include "loginservlet.h"

void IndexServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    if(request.getSession().getAttribute("user") == nullptr || request.getSession().isExpired())
    {
        LoginServlet().doGet(request, response);
    }
    else
    {
        request.getRequestDispatcher("/pages/index.xhtml").forward(request, response);
    }
}
