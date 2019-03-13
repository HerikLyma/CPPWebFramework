#include "filter.h"

CWF_BEGIN_NAMESPACE

void Filter::doFilter(Request &request, Response &response, FilterChain &chain)
{
    chain.doFilter(request, response);
}

CWF_END_NAMESPACE
