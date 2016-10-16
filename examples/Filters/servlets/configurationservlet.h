/**
  @file configurationservlet.h
  @author Herik Lima
*/

#ifndef CONFIGURATIONSERVLET_H
#define CONFIGURATIONSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"

class ConfigurationServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

#endif // CONFIGURATIONSERVLET_H
