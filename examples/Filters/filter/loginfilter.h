/**
  @file loginfilter.h
  @author Herik Lima
*/

#ifndef LOGINFILTER_H
#define LOGINFILTER_H

#include "cwf/filter.h"

class LoginFilter : public CWF::Filter
{
public:
    void doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response, CWF::FilterChain &chain);
};

#endif // LOGINFILTER_H
