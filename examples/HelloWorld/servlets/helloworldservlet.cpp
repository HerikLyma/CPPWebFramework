/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "helloworldservlet.h"

void HelloWorldServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(request)
    response.write("<html><body>Hello World!</body></html>");
}
