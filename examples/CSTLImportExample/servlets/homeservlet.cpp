#include "homeservlet.h"

void HomeServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/home").forward(request, response);
}
