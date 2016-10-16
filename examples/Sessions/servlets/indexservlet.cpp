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
        request.getRequestDispatcher("/pages/index").forward(request, response);
    }
}
