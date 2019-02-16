/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef URLENCODER_H
#define URLENCODER_H

#include <QUrl>
#include <QByteArray>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The URLEncoder class
 */
class CPPWEBFRAMEWORKSHARED_EXPORT URLEncoder
{
public:
    /**
     * @brief decode
     * @param url
     * @return
     */
    static QString decode(QByteArray url, bool replacePlusForSpace = true);
    /**
     * @brief encode
     * @param url
     * @return
     */
    static QString encode(const QByteArray &url);
    /**
     * @brief paramEncode
     * @param param
     * @return
     */
    static QString paramEncode(const QByteArray &param);
    /**
     * @brief paramDecode
     * @param param
     * @return
     */
    static QString paramDecode(QByteArray param, bool replacePlusForSpace = true);
};

CWF_END_NAMESPACE

#endif // URLENCODER_H
