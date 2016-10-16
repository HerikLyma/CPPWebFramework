/**
  @file httpparser.h
  @author Herik Lima
*/

#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QMap>
#include <QVector>
#include <QByteArray>
#include "httpcookie.h"

namespace CWF
{
    class HttpParser
    {
        friend class HttpReadRequest;                
        qint64     contentLenght = 0;
        QByteArray contentType;
        QByteArray httpVersion;
        QByteArray method;            
        QByteArray body;
        QByteArray sessionId;
        QByteArray url;
        QMultiMap<QByteArray, QByteArray> parameters;
        QMultiMap<QByteArray, QByteArray> headerField;
        QMultiMap<QByteArray, QByteArray> files;
        QVector<HttpCookie> cookies;
        bool    valid     = false;
        bool    multiPart = false;
        bool    readFile  = false;
        bool    extractHeaderAndBody(QByteArray &httpMessage);
        void    doParse(QByteArray &httpMessage);
        void    doParseHttpHeader(QByteArray &httpMessage);
        void    doParseUrl();
        void    doParseBody();
        void    doParseFiles();
        void    extractCookies();
        void    adjustParameters();
    public:
        HttpParser(QByteArray &httpMessage);
        qint64 getContentLenght() const;
        QByteArray getContentType() const;
        QByteArray getHttpVersion() const;
        QByteArray getMethod() const;
        QByteArray getBody() const;
        QByteArray getSessionId() const;
        QByteArray getUrl() const;                         
        QByteArray getParameter(const QByteArray &name) const;
        QByteArrayList getParameters(const QByteArray &name) const;
        QMap<QByteArray, QByteArray> getParameters() const;
        QVector<HttpCookie> getCookies() const;
        QByteArrayList getHeaderFields(const QByteArray &headerField) const;
        QByteArray getHeaderField(const QByteArray &headerField) const;
        bool isValid() const;        
        bool isMultiPart() const;        
        bool getReadFile() const;               
        QMultiMap<QByteArray, QByteArray> getUploadedFiles() const;
    };
}

#endif // HTTPPARSER_H
