/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QString>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
class HttpServletRequest;
class HttpServletResponse;
/**
 * @brief The RequestDispatcher class can be used to dispatch a requisition to a xhtml page.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT RequestDispatcher
{
    QString file;
public:
    /**
     * @brief This constructor receives a file name.
     */
    explicit RequestDispatcher(const QString &file) : file(file) {}
    /**
     * @brief Virtual destructor.
     */
    virtual ~RequestDispatcher() {}
    /**
     * @brief This method will dispatch the xhtml file specificated in path to the CSTLCompiler,
     * the CSTLCompiler will compile the xhtml file and returns the result.
     * After this, the RequestDispatcher will take the return and write it on the response.
     * @param CWF::HttpServletRequest &request   : Used to process the response.
     * @param CWF::HttpServletResponse &response : Used to response.
     */
    void forward(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
};

CWF_END_NAMESPACE

#endif // REQUESTDISPATCHER_H
