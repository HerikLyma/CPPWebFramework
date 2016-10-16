/**
  @file loginservlet.cpp
  @author Herik Lima
*/

#include "loginservlet.h"
#include "indexservlet.h"

void LoginServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    request.getRequestDispatcher("/pages/login").forward(request, response);
}

void LoginServlet::doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    User *user = new User;
    user->setName(request.getParameter("name"));
    user->setPassword(request.getParameter("password"));
    if(user->getName() == "herik" && user->getPassword() == "1234")
    {
        request.getSession().addAttribute("user", user);
        IndexServlet().doGet(request, response);
    }
    else
    {
        doGet(request, response);
    }
}
