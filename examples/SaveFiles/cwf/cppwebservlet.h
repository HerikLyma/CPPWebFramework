/**
  @file cppwebservlet.h
  @author Herik Lima
*/

#ifndef CPPWEBSERVLET_H
#define CPPWEBSERVLET_H

#include "httpservlet.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"

namespace CWF
{
    class CppWebServlet : public HttpServlet
    {
    public:
        void doGet(HttpServletRequest &req, HttpServletResponse &resp);
    };
}

#endif // CPPWEBSERVLET_H
