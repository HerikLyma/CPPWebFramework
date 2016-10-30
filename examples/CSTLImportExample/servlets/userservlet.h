/**
  @file userservlet.h
  @author Herik Lima
*/

#ifndef USERSERVLET_H
#define USERSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"
#include "entities/user.h"

class UserServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

#endif // USERSERVLET_H
