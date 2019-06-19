/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include "variant.h"
#include "constants.h"
#include "request.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
class Request;
class Response;

/**
 * @brief The Controller class is responsable to attend a request from a specific url.
 * You will need to create a derived class from Controller and then, reconstruct the
 * desired method to response a request, after this, you will need mapping the url to the
 * new controller that you created, you need to do it into the ConfigureCppWebServer using
 * the method addUrlController.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Controller
{
    /**
     * @brief This method is used to make a default response.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     * @param method : This parameter holds the method name.
     */
    void doMessage(Request &req, Response &resp, const QString &method) const;
public:
    /**
     * @brief Destructor.
     */
    virtual ~Controller() = default;
    /**
     * @brief This is an virtual method that can be overloaded to attend the delete request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doDelete(Request &req, Response &resp) const;
    /**
     * @brief This is an virtual method that can be overloaded to attend the get request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doGet(Request &req, Response &resp) const;
    /**
     * @brief This is an virtual method that can be overloaded to attend the options request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doOptions(Request &req, Response &resp) const;
    /**
     * @brief This is an virtual method that can be overloaded to attend the post request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doPost(Request &req, Response &resp) const;
    /**
     * @brief This is an virtual method that can be overloaded to attend the put request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doPut(Request &req, Response &resp) const;
    /**
     * @brief This is an virtual method that can be overloaded to attend the trace request method.
     * @param req    : This is a reference to the Request.
     * @param resp   : This is a reference to the Response.
     */
    virtual void doTrace(Request &req, Response &resp) const;
};

CWF_END_NAMESPACE

#endif // CONTROLLER_H
