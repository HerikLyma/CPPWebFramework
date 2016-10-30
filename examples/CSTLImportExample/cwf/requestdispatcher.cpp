/**
  @file requestdispatcher.cpp
  @author Herik Lima
*/

#include "requestdispatcher.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "cstlcompiler.h"

namespace CWF
{
    RequestDispatcher::RequestDispatcher(const QString &path) : path(path)
    {
    }

    RequestDispatcher::~RequestDispatcher()
    {
    }

    void RequestDispatcher::forward(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
    {
        CSTLCompiler cstl(path.toStdString().data(), request.attributes);                                 
        QString pageStr(cstl.output());

        response.write(pageStr.toLatin1());
    }
}
