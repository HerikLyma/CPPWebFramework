#ifndef SAVEFILESSERVLET_H
#define SAVEFILESSERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"

class SaveFilesServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
    void doPost(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

#endif // SAVEFILESSERVLET_H
