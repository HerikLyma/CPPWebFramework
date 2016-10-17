/**
  @file userservlet.cpp
  @author Herik Lima
*/

#include "usersservlet.h"

void UsersServlet::doGet(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp)
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

    CWF::QListObject users;
    users.add(&userOne);
    users.add(&userTwo);
    users.add(&userThree);
    users.add(&userFour);

    req.addAttribute("users", &users);
    req.getRequestDispatcher("/pages/users").forward(req, resp);
}
