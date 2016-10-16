/**
  @file filter.cpp
  @author Herik Lima
*/

#include "filter.h"

namespace CWF
{
    Filter::~Filter()
    {

    }

    void Filter::doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response, FilterChain &chain)
    {
        chain.doFilter(request, response);
    }
}
