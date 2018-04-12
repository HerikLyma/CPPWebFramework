/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CPPWEBCONTROLLER_H
#define CPPWEBCONTROLLER_H

#include "controller.h"
#include "request.h"
#include "response.h"
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
* @brief This class is responsible for displaying the standard pages of C++ Web Framework: index, examples, documentation, ssl and authors.
*/
class CPPWEBFRAMEWORKSHARED_EXPORT CppWebController : public Controller
{
public:
    /**
     * @brief Method overload to answer the requests the system default pages.
     * @param Request  &request  : Parameter generated by HttpReadRequest.
     * @param Response &response : Parameter generated by HttpReadRequest.
     */
    void doGet(Request &request, Response &response) const override;
};

CWF_END_NAMESPACE

#endif // CPPWEBCONTROLLER_H