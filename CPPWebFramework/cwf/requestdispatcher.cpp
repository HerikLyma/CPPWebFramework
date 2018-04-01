/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "requestdispatcher.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "cstlcompiler.h"

CWF_BEGIN_NAMESPACE

void RequestDispatcher::forward(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
{    
    response.write(std::move(CSTLCompiler(file.toLatin1(), request.getPath(), request.attributes).output()));
}

CWF_END_NAMESPACE
