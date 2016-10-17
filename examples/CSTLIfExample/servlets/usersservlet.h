/**
  @file usersservlet.h
  @author Herik Lima
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
