/**
  @file filter.h
  @author Herik Lima
*/

#ifndef FILTER_H
#define FILTER_H

#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "filterchain.h"


namespace CWF
{
    /**
     * @brief The Filter class works like a filter. You can use this class to validate sessions or
     * measuring runtime of a specific method, for example.
     * To use this class, you will need to create a derived class and reconstruct the doFilter method,
     * after this, you will need to configure it into the ConfigureCppWebServer, using the setFilter method.
     */
    class Filter
    {
    public:
        /**
         * @brief Destructor
         */
        virtual ~Filter();
        /**
         * @brief This method will be called always that the CppWebServer receives a requisition.
         * @param request  : This is a reference to the HttpServletRequest.
         * @param response : This is a reference to the HttpServletResponse.
         * @param chain    : This is a reference to the FilterChain.
         */
        virtual void doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response, FilterChain &chain);
    };
}

#endif // FILTER_H
