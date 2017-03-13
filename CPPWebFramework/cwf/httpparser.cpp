/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "httpparser.h"
#include "constants.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QMultiMap>

namespace CWF
{
    bool HttpParser::extractHeaderAndBody(QByteArray &httpMessage)
    {
        int index = httpMessage.indexOf(HTTP::END_OF_MENSAGE);
        if(index != -1)
        {
            index += 4;
            int size = httpMessage.size();
            for(int it = index; it < size; ++it)
            {
                body.push_back(httpMessage[it]);
            }
            httpMessage.remove(index, httpMessage.size());
            valid = true;
        }
        else
        {
            valid = false;
        }
        return valid;
    }

    void HttpParser::doParseHttpHeader(QByteArray &httpMessage)
    {
        httpMessage.replace("\r", "");
        QByteArrayList lines(std::move(httpMessage.split('\n')));
        QByteArrayList firstHeaderLine;
        if(lines.size() > 0)
            firstHeaderLine = std::move(lines[0].split(' '));

        if(firstHeaderLine.size() < 3)
        {
            valid = false;
            return;
        }

        method      = std::move(firstHeaderLine[0].toUpper());
        url         = std::move(firstHeaderLine[1]);
        httpVersion = std::move(firstHeaderLine[2]);

        if(method == GET_SET::GET_UPPER)
            doParseUrl();

        int size = lines.size();
        for(int i = 1, column = 0; i < size; ++i)
        {
            QByteArray &line = lines[i];
            if(line.isEmpty())
                continue;
            column = line.indexOf(':');
            headerField.insert(std::move(line.left(column).trimmed()), std::move(line.mid(column + 1).trimmed()));
        }

        contentLenght = headerField.value(HTTP::CONTENT_LENGTH).toLongLong();
        contentType   = headerField.value(HTTP::CONTENT_TYPE);
        multiPart     = contentType.contains(HTTP::MULTIPART);
        if(contentType.contains(HTTP::URLENCODED))
            doParseBody();

        extractCookies();
        if(multiPart)
        {
            qint64 bodySize = body.size();
            readFile = bodySize == contentLenght;
            if(readFile)
                doParseFiles();
        }

        valid = true;
    }

    void HttpParser::doParseUrl()
    {
        if(url.contains("?") && url.contains("="))
        {
            QByteArrayList realUrl(std::move(url.split('?')));
            url = std::move(realUrl[0]);

            QByteArrayList tempParam;
            if(realUrl.size() > 1)
                tempParam = std::move(realUrl[1].split('&'));

            int size = tempParam.size();
            for(int i = 0; i < size; ++i)
            {
                QByteArrayList p(std::move(tempParam[i].split('=')));
                if(p.size() == 2)
                    parameters.insert(std::move(p[0]), std::move(p[1]));
                else if(p.size() == 1)
                    parameters.insert(std::move(p[0]), std::move(""));
            }
        }
    }

    void HttpParser::doParseBody()
    {
        if(body.contains("&"))
        {
            QByteArrayList tempBody(std::move(body.split('&')));
            int size = tempBody.size();
            for(int i = 0; i < size; ++i)
            {
                QByteArrayList p(std::move(tempBody[i].split('=')));
                if(p.size() == 2)
                    parameters.insert(std::move(p[0]), std::move(p[1]));
                else if(p.size() == 1)
                    parameters.insert(std::move(p[0]), std::move(""));
            }
        }
        else
        {
            QByteArrayList p(std::move(body.split('=')));
            if(p.size() == 2)
                parameters.insert(std::move(p[0]), std::move(p[1]));
            else if(p.size() == 1)
                parameters.insert(std::move(p[0]), std::move(""));
        }
    }

    void HttpParser::extractCookies()
    {
        QByteArrayList temp(headerField.values(HTTP::COOKIE));
        int size = temp.size();
        for(int i = 0; i < size; ++i)
        {
            HttpCookie cookie(temp[i]);
            if(cookie.getName() == HTTP::SESSION_ID)
                sessionId = cookie.getValue();
            cookies.push_back(std::move(cookie));
        }
    }

    void HttpParser::doParseFiles()
    {
        if(!body.startsWith(HTTP::CONTENT_DISPOSITION_COLON))
            body.remove(0, body.indexOf(HTTP::CONTENT_DISPOSITION_COLON));

        QByteArrayList cont(std::move(body.split('\n')));
        body.clear();
        int total = cont.size();
        QByteArray fileName;
        for(int i = 0; i < total; ++i)
        {
            QByteArray &temp = cont[i];
            if(temp.contains(HTTP::CONTENT_DISPOSITION_COLON_SPACE))
            {
                temp.replace(HTTP::CONTENT_DISPOSITION_COLON, "").replace(HTTP::FORM_DATA_COLON_SPACE,"").replace("\r", "").replace("\"", "");
                if(temp.contains(HTTP::FILENAME))
                {
                    if(!fileName.isEmpty())
                    {
                        files.insert(fileName, body);
                        body.clear();
                    }
                    QByteArrayList tmp(std::move(temp.split('=')));
                    for(int j = 0; j < tmp.size(); ++j)
                    {
                        QByteArray &name = tmp[j];
                        if(name.contains(HTTP::FILENAME))
                        {
                            ++j;
                            if(j < tmp.size())
                            {
                                if(tmp[j] != "\r")
                                {
                                    fileName = std::move(tmp[j]);
                                    break;
                                }
                            }
                        }
                    }
                    i += 2;
                    continue;
                }
                else
                {
                    if(!fileName.isEmpty())
                    {
                        files.insert(fileName, body);
                        body.clear();
                    }
                    break;
                }
            }
            if(!temp.contains(HTTP::WEBKIT) && !temp.contains("--------"))
                body += temp + "\n";
        }
        if(files.isEmpty() && !fileName.isEmpty())
            files.insert(fileName, body);
    }

    void HttpParser::doParse(QByteArray &httpMessage)
    {
        //qDebug() << httpMessage;
        if(extractHeaderAndBody(httpMessage))
        {
            doParseHttpHeader(httpMessage);
        }
    }


    HttpParser::HttpParser(QByteArray &httpMessage)
    {
        doParse(httpMessage);
    }

    QByteArray HttpParser::getMethod() const
    {
        return method;
    }

    QByteArray HttpParser::getUrl() const
    {
        return url;
    }

    QByteArray HttpParser::getHttpVersion() const
    {
        return httpVersion;
    }

    QByteArray HttpParser::getSessionId() const
    {
        return sessionId;
    }

    bool HttpParser::isValid() const
    {
        return valid;
    }

    QMultiMap<QByteArray, QByteArray> HttpParser::getParameters() const
    {
        return parameters;
    }

    QVector<HttpCookie> HttpParser::getCookies() const
    {
        return cookies;
    }

    QByteArrayList HttpParser::getHeaderFields(const QByteArray &name) const
    {
        return headerField.values(name);
    }

    QByteArray HttpParser::getHeaderField(const QByteArray &name) const
    {
        return headerField.value(name);
    }

    QByteArrayList HttpParser::getParameters(const QByteArray &name) const
    {
        return parameters.values(name);
    }

    QByteArray HttpParser::getParameter(const QByteArray &name) const
    {
        return parameters.value(name);
    }

    qint64 HttpParser::getContentLenght() const
    {
        return contentLenght;
    }

    QByteArray HttpParser::getContentType() const
    {
        return contentType;
    }

    bool HttpParser::isMultiPart() const
    {
        return multiPart;
    }

    QByteArray HttpParser::getBody() const
    {
        return body;
    }

    bool HttpParser::getReadFile() const
    {
        return readFile;
    }

    QMultiMap<QByteArray, QByteArray> HttpParser::getUploadedFiles() const
    {
        return files;
    }
}
