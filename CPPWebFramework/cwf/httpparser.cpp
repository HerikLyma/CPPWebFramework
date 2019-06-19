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

CWF_BEGIN_NAMESPACE

bool HttpParser::extractHeaderAndBody(QByteArray &httpMessage)
{
    int index = httpMessage.indexOf(HTTP::END_OF_MESSAGE);
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
    QByteArrayList lines(httpMessage.split('\n'));
    QByteArrayList firstHeaderLine;
    if(!lines.empty())
        firstHeaderLine = lines[0].split(' ');

    if(firstHeaderLine.size() < 3)
    {
        valid = false;
        return;
    }

    method      = firstHeaderLine[0].toUpper();
    url         = std::move(firstHeaderLine[1]);
    httpVersion = std::move(firstHeaderLine[2]);
    doParseUrl();

    int size = lines.size();
    for(int i = 1, column = 0; i < size; ++i)
    {
        QByteArray &line = lines[i];
        if(line.isEmpty())
            continue;
        column = line.indexOf(':');
        headerField.insert(line.left(column).trimmed(), line.mid(column + 1).trimmed());
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
        QByteArrayList realUrl(url.split('?'));
        url = std::move(realUrl[0]);

        QByteArrayList tempParam;
        if(realUrl.size() > 1)
            tempParam = realUrl[1].split('&');

        int size = tempParam.size();
        for(int i = 0; i < size; ++i)
        {
            QByteArrayList p(tempParam[i].split('='));
            if(p.size() == 2)
                parameters.insert(p[0], p[1]);
            else if(p.size() == 1)
                parameters.insert(p[0], "");
        }
    }
}

void HttpParser::doParseBody()
{
    if(body.contains("&"))
    {
        QByteArrayList tempBody(body.split('&'));
        int size = tempBody.size();
        for(int i = 0; i < size; ++i)
        {
            QByteArrayList p(tempBody[i].split('='));
            if(p.size() == 2)
                parameters.insert(p[0], p[1]);
            else if(p.size() == 1)
                parameters.insert(p[0], "");
        }
    }
    else
    {
        QByteArrayList p(body.split('='));
        if(p.size() == 2)
            parameters.insert(p[0], p[1]);
        else if(p.size() == 1)
            parameters.insert(p[0], "");
    }
}

void HttpParser::extractCookies()
{
    QByteArrayList temp(headerField.values(HTTP::COOKIE));
    int size = temp.size();
    for(int i = 0; i < size; ++i)
    {
        const QByteArray &txt = temp[i].replace(";", ";\n");;
        QList<QNetworkCookie> cookiesList = QNetworkCookie::parseCookies(txt);
        for(QNetworkCookie &cookie : cookiesList)
        {
            if(cookie.name() == HTTP::SESSION_ID)
                sessionId = cookie.value();
            cookies.push_back(std::move(cookie));
        }
    }
}

void HttpParser::doParseFiles()
{
    if(!body.startsWith(HTTP::CONTENT_DISPOSITION_COLON))
        body.remove(0, body.indexOf(HTTP::CONTENT_DISPOSITION_COLON));

    QByteArrayList cont(body.split('\n'));
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
                QByteArrayList tmp(temp.split('='));
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

CWF_END_NAMESPACE
