/**
  @file httpservlet.cpp
  @author Herik Lima
*/

#include "httpservlet.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include <QTcpSocket>

namespace CWF
{
    void HttpServlet::doMessage(HttpServletRequest &req, HttpServletResponse &resp, QString method)
    {
        QString msg = "http.method_" + method.toLower() + "_not_supported";
        if (req.getProtocol().endsWith("1.1"))
            resp.sendError(HttpServletResponse::SC_METHOD_NOT_ALLOWED, msg.toLatin1());
        else
            resp.sendError(HttpServletResponse::SC_BAD_REQUEST, msg.toLatin1());
    }

    HttpServlet::~HttpServlet() {}

    void HttpServlet::doDelete(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "delete");
    }

    void HttpServlet::doGet(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "get");
    }

    void HttpServlet::doOptions(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "options");
    }

    void HttpServlet::doPost(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "post");
    }

    void HttpServlet::doPut(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "put");
    }

    void HttpServlet::doTrace(HttpServletRequest &req, HttpServletResponse &resp)
    {
        doMessage(req, resp, "trace");
    }
}
