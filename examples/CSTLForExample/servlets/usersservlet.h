/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef USERSSERVLET_H
#define USERSSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"
#include "cwf/qlistobject.h"
#include "entities/user.h"

class UsersServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &req, CWF::HttpServletResponse &resp);
};

#endif // USERSSERVLET_H
