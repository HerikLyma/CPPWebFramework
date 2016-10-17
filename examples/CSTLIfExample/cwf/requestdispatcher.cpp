/**
  @file requestdispatcher.cpp
  @author Herik Lima
*/

#include "requestdispatcher.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "cstlcompiler.h"
#include <QByteArray>

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
        response.addHeader("Content-Type", "text/html; charset=UTF-8");
        QString page( std::move(QString::fromUtf8(cstl.output())) );
        response.write(page.toUtf8());
    }
}
