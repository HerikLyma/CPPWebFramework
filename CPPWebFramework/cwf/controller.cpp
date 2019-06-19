/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "controller.h"
#include "request.h"
#include "response.h"

CWF_BEGIN_NAMESPACE

void Controller::doMessage(Request &req, Response &resp, const QString &method) const
{
    QString msg("http.method_" + method.toLower() + "_not_supported");
    if (req.getProtocol().endsWith("1.1"))
        resp.sendError(Response::SC_METHOD_NOT_ALLOWED, msg.toLatin1());
    else
        resp.sendError(Response::SC_BAD_REQUEST, msg.toLatin1());
}

void Controller::doDelete(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::DELETE);
}

void Controller::doGet(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::GET);
}

void Controller::doOptions(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::OPTIONS);
}

void Controller::doPost(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::POST);
}

void Controller::doPut(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::PUT);
}

void Controller::doTrace(Request &req, Response &resp) const
{
    doMessage(req, resp, HTTP::METHOD::TRACE);
}

CWF_END_NAMESPACE
