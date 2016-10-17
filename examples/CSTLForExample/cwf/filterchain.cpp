/**
  @file filterchain.cpp
  @author Herik Lima
*/

#include "filterchain.h"
#include "configuration.h"

namespace CWF
{
    extern Configuration configuration;

    FilterChain::FilterChain(HttpServlet *servlet) :  servlet(servlet)
    {
    }

    void FilterChain::doFilter(CWF::HttpServletRequest &request, CWF::HttpServletResponse &response)
    {
        if(servlet != nullptr)
        {
            const HttpParser &parser = request.getHttpParser();
            if(parser.getMethod() == HttpRequestMethod::getGet())
                servlet->doGet(request, response);
            else if(parser.getMethod() == HttpRequestMethod::getPost())
                servlet->doPost(request, response);
            else if(parser.getMethod() == HttpRequestMethod::getPut())
                servlet->doPut(request, response);
            else if(parser.getMethod() == HttpRequestMethod::getDelete())
                servlet->doDelete(request, response);
            else if(parser.getMethod() == HttpRequestMethod::getOptions())
                servlet->doOptions(request, response);
            else if(parser.getMethod() == HttpRequestMethod::getTrace())
                servlet->doTrace(request, response);
        }
        else
        {
            FileManager fileManager;
            QString url  = request.getRequestURL();
            QString path = request.getPath();
            const QString &extention = fileManager.fileExtention(url);

            if(url == "/")
            {
                QMutex mutex;
                QMutexLocker locker(&mutex);
                request.getRequestDispatcher(configuration.indexPage).forward(request, response);
            }
            else if(extention == "html" || extention == "htm")
            {
                write(response, path, url, "Content-Type", "text/html; charset=UTF-8");
            }
            else if(extention == "css" || extention == "txt" || extention == "php")
            {
                write(response, path, url, "Content-Type", ("text/" + extention.toLatin1() + "; charset=UTF-8") );
            }
            else if(extention == "ico")
            {
                write(response, path, url, "Content-Type", "image/vnd.microsoft.icon");
            }
            else if(extention == "png" || extention == "gif" || extention == "bmp")
            {
                write(response, path, url, "Content-Type", ("image/" + extention.toLatin1()));
            }
            else if(extention == "jpe" || extention == "jpg")
            {
                write(response, path, url, "Content-Type", "image/jpeg");
            }
            else if(extention == "tiff" || extention == "tif")
            {
                write(response, path, url, "Content-Type", "image/tiff");
            }
            else if(extention == "svg" || extention == "svgz")
            {
                write(response, path, url, "Content-Type", "image/svg+xml");
            }
            else if(extention == "pdf" || extention == "xml" || extention == "json" || extention == "zip")
            {
                write(response, path, url, "Content-Type", ("application/" + extention.toLatin1()) );
            }
            else if(extention == "mp3")
            {
                write(response, path, url, "Content-Type", "audio/mpeg");
            }
            else if(extention == "mp4")
            {
                write(response, path, url, "Content-Type", "video/mp4");
            }
            else if(extention == "flv")
            {
                write(response, path, url, "Content-Type", "video/x-flv");
            }
            else if(extention == "doc")
            {
                write(response, path, url, "Content-Type", "application/msword");
            }
            else if(extention == "rtf")
            {
                write(response, path, url, "Content-Type", "application/rtf");
            }
            else if(extention == "xls")
            {
                write(response, path, url, "Content-Type", "application/vnd.ms-excel");
            }
            else if(extention == "ppt")
            {
                write(response, path, url, "Content-Type", "application/vnd.ms-powerpoint");
            }
            else if(extention == "js")
            {
                write(response, path, url, "Content-Type", "application/javascript");
            }
            else if(extention == "odt")
            {
                write(response, path, url, "Content-Type", "application/vnd.oasis.opendocument.text");
            }
            else if(extention == "ods")
            {
                write(response, path, url, "Content-Type", "application/vnd.oasis.opendocument.spreadsheet");
            }
            else if(extention == "swf")
            {
                write(response, path, url, "Content-Type", "application/x-shockwave-flash");
            }
            else if(extention == "rar")
            {
                write(response, path, url, "Content-Type", "application/x-rar-compressed");
            }
            else if(extention == "exe" || extention == "msi")
            {
                write(response, path, url, "Content-Type", "application/x-msdownload");
            }
            else if(extention == "cab")
            {
                write(response, path, url, "Content-Type", "application/vnd.ms-cab-compressed");
            }
            else if(extention == "psd")
            {
                write(response, path, url, "Content-Type", "image/vnd.adobe.photoshop");
            }
            else if(extention == "ai" || extention == "eps" || extention == "ps")
            {
                write(response, path, url, "Content-Type", "application/postscript");
            }
            else if(extention == "ini")
            {
                QMutex mutex;
                QMutexLocker locker(&mutex);
                QString file(std::move(fileManager.fileName(url)));
                if(file != "CPPWeb.ini")
                    write(response, path, url, "Content-Type", ("text/" + extention.toLatin1() + "; charset=UTF-8") );
                else if(configuration.accessCPPWebIni)
                    write(response, path, url, "Content-Type", ("text/" + extention.toLatin1() + "; charset=UTF-8") );
                else
                    request.getRequestDispatcher("/config/cppwebserverpages/401").forward(request, response);
            }
            else
            {
                response.setStatus(HttpServletResponse::SC_NOT_FOUND, "Not Found");
                response.addHeader("Content-Type; charset=UTF-8", "text/html");                
                request.getRequestDispatcher("/config/cppwebserverpages/404").forward(request, response);
            }
        }
    }

    void FilterChain::write(HttpServletResponse &response, const QString &path, const QString &url, const QByteArray &name, const QByteArray &value) const
    {
        QFile file(path + url);
        if(file.open(QIODevice::ReadOnly))
        {
            response.addHeader(name, value);
            response.write(file.readAll());
        }
        else
        {
            response.sendError(0, file.errorString().toLatin1());
        }
    }
}
