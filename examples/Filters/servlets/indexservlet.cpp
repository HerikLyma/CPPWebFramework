/**
  @file indexservlet.cpp
  @author Herik Lima
*/

#include "indexservlet.h"
#include "loginservlet.h"

void IndexServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    request.getRequestDispatcher("/pages/index").forward(request, response);
}
