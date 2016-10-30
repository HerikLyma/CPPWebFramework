/**
  @file homeservlet.h
  @author Herik Lima
*/

#ifndef HOMESERVLET_H
#define HOMESERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"

class HomeServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

#endif // HOMESERVLET_H
