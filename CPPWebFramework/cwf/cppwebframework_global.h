/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CPPWEBFRAMEWORK_GLOBAL_H
#define CPPWEBFRAMEWORK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CPPWEBFRAMEWORK_TEST)
#  define CPPWEBFRAMEWORKSHARED_EXPORT
#elif defined(CPPWEBFRAMEWORK_LIBRARY)
#  define CPPWEBFRAMEWORKSHARED_EXPORT Q_DECL_EXPORT
#else    
#  define CPPWEBFRAMEWORKSHARED_EXPORT Q_DECL_IMPORT
#endif

#define CWF_BEGIN_NAMESPACE namespace CWF {
#define CWF_END_NAMESPACE }

#endif // CPPWEBFRAMEWORK_GLOBAL_H
