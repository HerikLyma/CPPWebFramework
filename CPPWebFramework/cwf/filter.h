/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef FILTER_H
#define FILTER_H

#include "request.h"
#include "response.h"
#include "filterchain.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The Filter class works like a filter. You can use this class to validate sessions or
 * measuring runtime of a specific method, for example.
 * To use this class, you will need to create a derived class and reconstruct the doFilter method,
 * after this, you will need to configure it into the ConfigureCppWebServer, using the setFilter method.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Filter
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Filter() = default;
    /**
     * @brief This method will be called always that the CppWebServer receives a requisition.
     * @param request  : This is a reference to the Request.
     * @param response : This is a reference to the Response.
     * @param chain    : This is a reference to the FilterChain.
     * @par Example
     * @code
     * //----loginfilter.h-----
     *
     * #ifndef LOGINFILTER_H
     * #define LOGINFILTER_H
     *
     * #include "cwf/filter.h"
     *
     * class LoginFilter : public CWF::Filter
     * {
     * public:
     *     void doFilter(CWF::Request &request, CWF::Response &response, CWF::FilterChain &chain)
     *     {
     *         QString url = request.getRequestURL();
     *         if(url.endsWith(".css") || url.endsWith(".png") || url.endsWith(".jpg"))
     *         {
     *             chain.doFilter(request, response);
     *         }
     *         else if(url != "/login")
     *         {
     *             if(request.getSession().getAttribute("user") == nullptr || request.getSession().isExpired())
     *             {
     *                 request.getRequestDispatcher("/pages/login").forward(request, response);
     *             }
     *             else
     *             {
     *                 chain.doFilter(request, response);
     *             }
     *          }
     *          else
     *          {
     *              chain.doFilter(request, response);
     *          }
     *     }
     * };
     *
     * #endif // LOGINFILTER_H
     *
     * //----main.h-----
     *
     * #include <filter/loginfilter.h>
     * #include "cwf/cppwebapplication.h"
     *
     * int main(int argc, char *argv[])
     * {
     *     CWF::CppWebApplication server(argc,
     *                                   argv,
     *                                   "PATH_TO_SERVER_FOLDER",
     *                                   new LoginFilter);
     *
     *     return server.start();
     * }
     *
     * @endcode
     */
    virtual void doFilter(CWF::Request &request, CWF::Response &response, FilterChain &chain);
};

CWF_END_NAMESPACE

#endif // FILTER_H
