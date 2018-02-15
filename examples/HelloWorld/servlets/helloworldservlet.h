/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
