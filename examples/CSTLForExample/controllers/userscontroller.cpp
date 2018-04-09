/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "userscontroller.h"

void UsersController::doGet(CWF::Request &request, CWF::Response &response) const
{
    User userOne, userTwo, userThree, userFour;

    userOne.setId(1);
    userOne.setGender('M');
    userOne.setName("Herik Lima");
    userOne.setAddress("350 5th Ave, New York, NY 10118, EUA");

    userTwo.setId(2);
    userTwo.setGender('M');
    userTwo.setName("Marcelo Eler");
    userTwo.setAddress("350 5th Ave, New York, NY 101, EUA");

    userThree.setId(3);
    userThree.setGender('F');
    userThree.setName("Camila Calazans");
    userThree.setAddress("350 5th Ave, New York, NY 18, EUA");

    userFour.setId(4);
    userFour.setGender('F');
    userFour.setName("Ana Paula");
    userFour.setAddress("350 5th Ave, New York, NY 118, EUA");

    CWF::QListObject users({&userOne, &userTwo, &userThree, &userFour});

    request.addAttribute("users", &users);
    request.getRequestDispatcher("/pages/users.view").forward(request, response);
}
