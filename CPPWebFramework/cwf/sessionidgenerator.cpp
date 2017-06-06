/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "sessionidgenerator.h"
#include "constants.h"
#include <QCryptographicHash>
#include <QDateTime>

CWF_BEGIN_NAMESPACE

SessionIdGenerator::SessionIdGenerator(const HttpParser &httpParser) : httpParser(httpParser)
{
}

QByteArray SessionIdGenerator::getSessionID() const
{
    QByteArray session = httpParser.getUrl();

    session += httpParser.getHeaderField(HTTP::ACCEPT_ENCODING);
    session += httpParser.getHeaderField(HTTP::ACCEPT_LANGUAGE);
    session += httpParser.getHeaderField(HTTP::HOST);
    session += httpParser.getHttpVersion();
    session += httpParser.getMethod();
    session += httpParser.getHeaderField(HTTP::USER_AGENT);
    session += QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss:zzz");

    return QCryptographicHash::hash(session, QCryptographicHash::Sha1).toHex();
}

CWF_END_NAMESPACE
