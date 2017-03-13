/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
            request.getRequestDispatcher("/pages/login.xhtml").forward(request, response);
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
