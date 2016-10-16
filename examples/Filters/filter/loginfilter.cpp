/**
  @file loginfilter.cpp
  @author Herik Lima
*/

#include "loginfilter.h"

void LoginFilter::doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response, CWF::FilterChain &chain)
{
    QString url = request.getRequestURL();
    if(url.endsWith(".css") || url.endsWith(".png") || url.endsWith(".jpg"))
    {
        chain.doFilter(request, response);
    }
    else if(url != "/login")
    {
        if(request.getSession().getAttribute("user") == nullptr || request.getSession().isExpired())
        {
            request.getRequestDispatcher("/pages/login").forward(request, response);
        }
        else
        {
            chain.doFilter(request, response);
        }
    }
    else
    {
        chain.doFilter(request, response);
    }
}
