/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "urlencoder.h"

CWF_BEGIN_NAMESPACE

QString URLEncoder::decode(const QByteArray &url)
{
    QUrl copy(url);
    copy.setQuery(copy.query(QUrl::FullyDecoded), QUrl::DecodedMode);

    return copy.toString();
}

QString URLEncoder::encode(const QByteArray &url)
{
    QUrl copy(url);
    return copy.toEncoded();
}

QString URLEncoder::paramEncode(const QByteArray &param)
{
    QUrl url("?p=" + param);
    return url.toEncoded().remove(0, 3);
}

QString URLEncoder::paramDecode(const QByteArray &param)
{
    QUrl url("?p=" + param);
    url.setQuery(url.query(QUrl::FullyDecoded), QUrl::DecodedMode);

    return url.toString().remove(0, 3);
}

CWF_END_NAMESPACE
