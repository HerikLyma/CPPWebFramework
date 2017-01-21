/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
