/**
  @file helloworldservlet.h
  @author Herik Lima
*/

#ifndef HELLOWORLDSERVLET_H
#define HELLOWORLDSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"

class HelloWorldServlet : public CWF::HttpServlet
{
public:    
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override;
};

#endif // HELLOWORLDSERVLET_H
