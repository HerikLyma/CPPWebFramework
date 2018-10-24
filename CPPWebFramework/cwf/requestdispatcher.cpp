/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "requestdispatcher.h"
#include "request.h"
#include "response.h"
#include "cstlcompiler.h"

CWF_BEGIN_NAMESPACE

void RequestDispatcher::forward(CWF::Request &request, CWF::Response &response)
{    
    response.write(CSTLCompiler(file.toLatin1(), request.getPath(), request.attributes).output());
}

CWF_END_NAMESPACE
