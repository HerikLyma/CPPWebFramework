#ifndef LOGINSERVLET_H
#define LOGINSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"
#include "entities/user.h"

class LoginServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
    void doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

#endif // LOGINSERVLET_H
