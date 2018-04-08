/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef BMICONTROLLER_H
#define BMICONTROLLER_H

#include "cwf/controller.h"
#include "cwf/request.h"
#include "cwf/response.h"
#include "model/user.h"

class BmiController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override;
};

#endif // BMICONTROLLER_H
