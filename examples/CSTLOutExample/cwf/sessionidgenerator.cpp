/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "sessionidgenerator.h"
#include <QCryptographicHash>
#include <QDateTime>

namespace CWF
{
    SessionIdGenerator::SessionIdGenerator(const HttpParser &httpParser) : httpParser(httpParser)
    {
    }

    QByteArray SessionIdGenerator::getSessionID() const
    {
        QByteArray session = httpParser.getUrl();

        session += httpParser.getHeaderField("Accept-Encoding");
        session += httpParser.getHeaderField("Accept-Language");
        session += httpParser.getHeaderField("Host");
        session += httpParser.getHttpVersion();
        session += httpParser.getMethod();
        session += httpParser.getHeaderField("User-Agent");
        session += QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss:zzz");

        return QCryptographicHash::hash(session, QCryptographicHash::Sha1).toHex();
    }
}
