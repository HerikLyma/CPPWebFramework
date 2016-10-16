/**
  @file showfileservlet.h
  @author Herik Lima
*/

#ifndef SHOWFILESERVLET_H
#define SHOWFILESERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"

class ShowFileServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override;
    void doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override;
};

#endif // SHOWFILESERVLET_H
