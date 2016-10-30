/**
  @file helloworldservlet.cpp
  @author Herik Lima
*/

#include "helloworldservlet.h"

void HelloWorldServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(request)
    response.write("<html><body>Hello World!</body></html>");
}
