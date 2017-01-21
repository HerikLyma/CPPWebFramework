/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "bmiservlet.h"

void BmiServlet::doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    request.getRequestDispatcher("/pages/bmi.html").forward(request, response);
}

void BmiServlet::doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{
    User user;
    request.fillQObject(&user);    
    request.addAttribute("user", &user);
    request.getRequestDispatcher("/pages/bmiresults.xhtml").forward(request, response);
}

