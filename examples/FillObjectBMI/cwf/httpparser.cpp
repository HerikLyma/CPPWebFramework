/**
  @file httpparser.cpp
  @author Herik Lima
*/

#include "httpparser.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QMultiMap>

namespace CWF
{
    bool HttpParser::extractHeaderAndBody(QByteArray &httpMessage)
    {
        int index = httpMessage.indexOf("\r\n\r\n");
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

        if(method == "GET")
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

        contentLenght = headerField.value("Content-Length").toLongLong();
        contentType   = headerField.value("Content-Type");
        multiPart     = contentType.contains("multipart");
        if(contentType.contains("urlencoded"))
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
        adjustParameters();
    }

    void HttpParser::extractCookies()
    {
        QByteArrayList temp(headerField.values("Cookie"));
        int size = temp.size();
        for(int i = 0; i < size; ++i)
        {
            HttpCookie cookie(temp[i]);
            if(cookie.getName() == "sessionId")
                sessionId = cookie.getValue();
            cookies.push_back(std::move(cookie));
        }
    }

    void HttpParser::adjustParameters()
    {
        for(QMultiMap<QByteArray, QByteArray>::iterator it = parameters.begin();
            it != parameters.end();
            ++it)
        {
            QByteArray &tmp = it.value();
            tmp.replace("+", " ");

            tmp.replace("%2B", "+");
            tmp.replace("%C3%B5", "%");

            tmp.replace("%C3%A3", "ã");
            tmp.replace("%C3%A1", "á");
            tmp.replace("%C3%A0", "à");
            tmp.replace("%C3%83", "Ã");
            tmp.replace("%C3%81", "Á");
            tmp.replace("%C3%80", "À");
            tmp.replace("%C3%B5", "õ");

            tmp.replace("%C3%A9", "é");
            tmp.replace("%C3%AA", "ê");
            tmp.replace("%E1%BA%BD", "ẽ");
            tmp.replace("%C3%89", "É");
            tmp.replace("%C3%8A", "Ê");
            tmp.replace("%E1%BA%BC", "Ẽ");

            tmp.replace("%C3%AD", "í");
            tmp.replace("%C3%AC", "ì");
            tmp.replace("%C3%8D", "Í");
            tmp.replace("%C3%8C", "Ì");

            tmp.replace("%C3%B3", "ó");
            tmp.replace("%C3%B2", "ò");
            tmp.replace("%C3%B5", "õ");
            tmp.replace("%C3%93", "Ó");
            tmp.replace("%C3%92", "Ò");
            tmp.replace("%C3%95", "Õ");

            tmp.replace("%C3%BA", "ú");
            tmp.replace("%C3%B9", "ù");
            tmp.replace("%C5%A9", "ũ");
            tmp.replace("%C3%9A", "Ú");
            tmp.replace("%C3%99", "Ù");
            tmp.replace("%C5%A8", "Ũ");

            tmp.replace("%C3%A7", "ç");
            tmp.replace("%C3%87", "Ç");

            tmp.replace("%C3%B1", "ñ");
            tmp.replace("%C3%91", "Ñ");
        }
    }

    void HttpParser::doParseFiles()
    {
        if(!body.startsWith("Content-Disposition:"))
            body.remove(0, body.indexOf("Content-Disposition:"));

        QByteArrayList cont(std::move(body.split('\n')));
        body.clear();
        int total = cont.size();
        QByteArray fileName;
        for(int i = 0; i < total; ++i)
        {
            QByteArray &temp = cont[i];
            if(temp.contains("Content-Disposition: "))
            {
                temp.replace("Content-Disposition: ", "").replace("form-data; ","").replace("\r", "").replace("\"", "");
                if(temp.contains("filename"))
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
                        if(name.contains("filename"))
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
            if(!temp.contains("WebKit") && !temp.contains("--------"))
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
