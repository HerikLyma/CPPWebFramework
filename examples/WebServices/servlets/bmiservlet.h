#ifndef BMISERVLET_H
#define BMISERVLET_H

#include "cwf/httpservlet.h"
#include "cwf/httpservletrequest.h"
#include "cwf/httpservletresponse.h"
#include "entities/user.h"
#include <QJsonDocument>
#include <QJsonObject>

class BmiServlet : public CWF::HttpServlet
{
public:
    void doGet(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response) override;
};

#endif // BMISERVLET_H
