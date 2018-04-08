/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "logincontroller.h"
#include "indexcontroller.h"

void LoginController::doGet(CWF::Request &request, CWF::Response &response) const
{
    request.getRequestDispatcher("/pages/login.view").forward(request, response);
}

void LoginController::doPost(CWF::Request &request, CWF::Response &response) const
{
    User *user = new User;
    user->setName(request.getParameter("name"));
    user->setPassword(request.getParameter("password"));
    if(user->getName() == "herik" && user->getPassword() == "1234")
    {
        request.getSession().addAttribute("user", user);
        request.getSession().validate();
        IndexController().doGet(request, response);
    }
    else
    {
        doGet(request, response);
    }
}
