/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "bmicontroller.h"

void BmiController::doGet(CWF::Request &request, CWF::Response &response) const
{
    QJsonObject json;
    User user;

    request.fillQObject(&user);

    json["bmi"]      =  user.getBmi();
    json["name"]     =  user.getName();
    json["category"] =  user.getCategory();
    json["mass"]     =  user.getMass();
    json["height"]   =  user.getHeight();

    response.write(json);
    //Call
    //http://localhost:8080/bmi?name=Herik&mass=75&height=1.75
}
