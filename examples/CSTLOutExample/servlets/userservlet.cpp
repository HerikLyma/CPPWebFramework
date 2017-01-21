/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
