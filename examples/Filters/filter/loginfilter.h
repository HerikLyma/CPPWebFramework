/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
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
