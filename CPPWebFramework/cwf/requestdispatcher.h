/**
  @file requestdispatcher.h
  @author Herik Lima
*/

#ifndef REQUESTDISPATCHER_H
#define REQUESTDISPATCHER_H

#include <QString>

namespace CWF
{
    class HttpServletRequest;

    class HttpServletResponse;

    /**
     * @brief The RequestDispatcher class can be used to dispatch a requisition to a xhtml page.
     */

    class RequestDispatcher
    {
        QString path;
    public:
        /**
         * @brief This constructor receives a path to a xhtml file.
         * @param path : This is the path to the xhtml file
         */
        RequestDispatcher(const QString &path);

        /**
         * @brief Destructor
         */
        virtual ~RequestDispatcher();

        /**
         * @brief This method will dispatch the xhtml file specificated in path to the CSTLCompiler,
         * the CSTLCompiler will compile the xhtml file and returns the result.
         * After this, the RequestDispatcher will take the return and write it on the response.
         * @param request  : This is a reference to the HttpServletRequest.
         * @param response : This is a reference to the HttpServletResponse.
         */
        void forward(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response);
    };
}

#endif // REQUESTDISPATCHER_H
