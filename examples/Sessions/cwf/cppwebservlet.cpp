/**
  @file cppwebservlet.cpp
  @author Herik Lima
*/

#include "cppwebservlet.h"

namespace CWF
{
    void CppWebServlet::doGet(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp)
    {
        Q_UNUSED(resp)
        QString url(req.getRequestURL());
        if(url.endsWith("/index"))
            req.getRequestDispatcher("/config/cppwebserverpages/index").forward(req, resp);
        else if(url.endsWith("/examples"))
            req.getRequestDispatcher("/config/cppwebserverpages/examples").forward(req, resp);
        else if(url.endsWith("/documentation"))
            req.getRequestDispatcher("/config/cppwebserverpages/documentation").forward(req, resp);
        else if(url.endsWith("/ssl"))
            req.getRequestDispatcher("/config/cppwebserverpages/ssl").forward(req, resp);
        else if(url.endsWith("/authors"))
            req.getRequestDispatcher("/config/cppwebserverpages/authors").forward(req, resp);
    }
}
