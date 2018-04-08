/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "indexcontroller.h"
#include "logincontroller.h"

void IndexController::doGet(CWF::Request &request, CWF::Response &response) const
{
    if(request.getSession().getAttribute("user") == nullptr || request.getSession().isExpired())
    {
        LoginController().doGet(request, response);
    }
    else
    {
        request.getRequestDispatcher("/pages/index.view").forward(request, response);
    }
}
