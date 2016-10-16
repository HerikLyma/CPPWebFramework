/**
  @file configurationservlet.cpp
  @author Herik Lima
*/

#include "configurationservlet.h"

void ConfigurationServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    request.getRequestDispatcher("/pages/configuration").forward(request, response);
}
