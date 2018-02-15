/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "homeservlet.h"

void HomeServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/home.xhtml").forward(request, response);
}
