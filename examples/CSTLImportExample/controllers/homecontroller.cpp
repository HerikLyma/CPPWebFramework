/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "homecontroller.h"

void HomeController::doGet(CWF::Request &request, CWF::Response &response) const
{
    Q_UNUSED(response)
    request.getRequestDispatcher("/pages/home.view").forward(request, response);
}
