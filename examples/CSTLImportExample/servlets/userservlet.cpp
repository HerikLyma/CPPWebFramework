/**
  @file userservlet.cpp
  @author Herik Lima
*/

#include "userservlet.h"

void UserServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    User user;
    user.setId(1);
    user.setGender('M');
    user.setName("Herik Lima");
    user.setAddress("350 5th Ave, New York, NY 10118, EUA");

    request.addAttribute("user", &user);
    request.getRequestDispatcher("/pages/user").forward(request, response);
}
