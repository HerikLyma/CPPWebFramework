/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef INDEXCONTROLLER_H
#define INDEXCONTROLLER_H

#include "cwf/controller.h"
#include "cwf/request.h"
#include "cwf/response.h"

class IndexController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override;
};

#endif // INDEXCONTROLLER_H
