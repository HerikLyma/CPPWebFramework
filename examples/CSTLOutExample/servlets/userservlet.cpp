/**
  @file userservlet.cpp
  @author Herik Lima
*/

#include "userservlet.h"

void UserServlet::doGet(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp)
{
    User user;
    user.setId(1);
    user.setGender('M');
    user.setName("Herik Lima");
    user.setAddress("350 5th Ave, New York, NY 10118, EUA");

    req.addAttribute("user", &user);
    req.getRequestDispatcher("/pages/user").forward(req, resp);
}
