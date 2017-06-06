/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPSERVLET_H
#define HTTPSERVLET_H

#include <QString>
#include "httpservletrequest.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
class HttpServletRequest;
class HttpServletResponse;

/**
 * @brief The HttpServlet class is responsable to attend a request from a specific url.
 * You will need to create a derived class from HttpServlet and then, reconstruct the
 * desired method to response a request, after this, you will need mapping the url to the
 * new servlet that you created, you need to do it into the ConfigureCppWebServer using
 * the method addUrlServlet.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT HttpServlet
{
    /**
     * @brief This method is used to make a default response.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     * @param method : This parameter holds the method name.
     */
    void doMessage(HttpServletRequest &req, HttpServletResponse &resp, QString method);
public:
    /**
     * @brief Destructor.
     */
    virtual ~HttpServlet();

    /**
     * @brief This is an virtual method that can be overloaded to attend the delete request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doDelete(HttpServletRequest &req, HttpServletResponse &resp);

    /**
     * @brief This is an virtual method that can be overloaded to attend the get request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doGet(HttpServletRequest &req, HttpServletResponse &resp);

    /**
     * @brief This is an virtual method that can be overloaded to attend the options request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doOptions(HttpServletRequest &req, HttpServletResponse &resp);

    /**
     * @brief This is an virtual method that can be overloaded to attend the post request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doPost(HttpServletRequest &req, HttpServletResponse &resp);

    /**
     * @brief This is an virtual method that can be overloaded to attend the put request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doPut(HttpServletRequest &req, HttpServletResponse &resp);

    /**
     * @brief This is an virtual method that can be overloaded to attend the trace request method.
     * @param req    : This is a reference to the HttpServletRequest.
     * @param resp   : This is a reference to the HttpServletResponse.
     */
    virtual void doTrace(HttpServletRequest &req, HttpServletResponse &resp);
};

CWF_END_NAMESPACE

#endif // HTTPSERVLET_H
