/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

#include "filemanager.h"
#include "request.h"
#include "response.h"
#include "controller.h"
#include "filterchain.h"
#include "httpparser.h"
#include "constants.h"
#include "requestdispatcher.h"
#include "cppwebframework_global.h"
#include <QFile>

CWF_BEGIN_NAMESPACE
/**
 * @brief The FilterChain class is responsable to dispatch a requisition.
 * This class was built to work with Filter. Always when a Filter makes all the
 * necessary validations, it can dispatches the requisition to the FilterChain.
 * NOTE: It is a final class, you can't derive from it.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT FilterChain final
{
    Controller *controller = nullptr;
    const Configuration &configuration;
    /**
     * @brief This method writes a response into the Response.
     * @param response : This is a reference to the Response.
     * @param path     : This is a reference to the QString.
     * @param url      : This is a reference to the QString.
     * @param name     : This is a reference to the QByteArray.
     * @param value    : This is a reference to the QByteArray.
     */
    void write(Response &response, const QString &path, const QString &url, const QByteArray &name, const QByteArray &value) const;
public:
    /**
     * @brief FilterChain
     * @param controller
     */
    FilterChain(Controller *controller, const Configuration &configuration);
    /**
     * @brief This method dispaches a requisition to a Request or, if the requesition
     * is for a file, it can reads and send the file through the Response.
     * @param request  : This is a reference to the Request.
     * @param response : This is a reference to the Response.
     */
    void doFilter(CWF::Request &request, CWF::Response &response);
};

CWF_END_NAMESPACE

#endif
