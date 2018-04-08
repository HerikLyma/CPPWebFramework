/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "userscontroller.h"

void UsersController::doGet(CWF::Request &request, CWF::Response &response) const
{
    User user;
    user.setId(1);
    user.setGender('M');
    user.setName("Herik Lima");
    user.setAddress("350 5th Ave, New York, NY 10118, EUA");

    request.addAttribute("user", &user);
    request.getRequestDispatcher("/pages/user.view").forward(request, response);
}
