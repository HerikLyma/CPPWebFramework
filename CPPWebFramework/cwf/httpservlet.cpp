/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpservlet.h"
#include "constants.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include <QTcpSocket>

CWF_BEGIN_NAMESPACE

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
    doMessage(req, resp, HTTP::METHOD::DELETE);
}

void HttpServlet::doGet(HttpServletRequest &req, HttpServletResponse &resp)
{
    doMessage(req, resp, HTTP::METHOD::GET);
}

void HttpServlet::doOptions(HttpServletRequest &req, HttpServletResponse &resp)
{
    doMessage(req, resp, HTTP::METHOD::OPTIONS);
}

void HttpServlet::doPost(HttpServletRequest &req, HttpServletResponse &resp)
{
    doMessage(req, resp, HTTP::METHOD::POST);
}

void HttpServlet::doPut(HttpServletRequest &req, HttpServletResponse &resp)
{
    doMessage(req, resp, HTTP::METHOD::PUT);
}

void HttpServlet::doTrace(HttpServletRequest &req, HttpServletResponse &resp)
{
    doMessage(req, resp, HTTP::METHOD::TRACE);
}

CWF_END_NAMESPACE
