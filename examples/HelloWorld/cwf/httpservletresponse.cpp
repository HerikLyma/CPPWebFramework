#include "httpservletresponse.h"
#include "configuration.h"


namespace CWF
{
    extern Configuration configuration;
    HttpServletResponse::HttpServletResponse(QTcpSocket &socket) : socket(&socket)
    {
        statusCode       = HttpServletResponse::SC_OK;
        statusText       = "OK";        
    }

    HttpServletResponse::~HttpServletResponse()
    {
    }

    void HttpServletResponse::flushBuffer()
    {
        const int max = 32768;
        if(!content.isEmpty())
        {
            bool biggerThanLimit = content.size() > max;
            if(!biggerThanLimit)
            {
                writeHeaders();
                writeToSocket(content);
                writeToSocket("\r\n\r\n");
            }
            else
            {
                headers.insert("Transfer-Encoding","chunked");
                headers.insert("Content-Length", QByteArray::number(content.size()));
                writeHeaders();
                int total = (content.size() / max) + 1, last = 0;

                QVector<QByteArray> vetor;
                for(int i = 0; i < total; ++i)
                {
                    vetor.push_back(std::move(content.mid(last, max)));
                    last += max;
                }

                for(int i = 0; i < vetor.size(); ++i)
                {
                    QByteArray data(std::move(vetor[i]));
                    if(!data.isEmpty())
                    {
                        QByteArray buffer(std::move(QByteArray::number(data.size(), 16)));
                        buffer.append("\r\n");
                        writeToSocket(buffer);
                        writeToSocket(data);
                        writeToSocket("\r\n");
                    }
                }
                writeToSocket("0\r\n\r\n");
            }
            socket->disconnectFromHost();
            content.clear();
        }
    }

    int HttpServletResponse::getBufferSize() const
    {
        return content.size();
    }

    void HttpServletResponse::sendError(int sc, const QByteArray &msg)
    {
        writeHeaders();
        writeToSocket("<html><body><h1>" + QByteArray::number(sc) + " " + msg + "</h1></body></html>");
    }

    void HttpServletResponse::write(const QByteArray &data, bool flush)
    {
        content += data;
        if(flush)
            flushBuffer();
    }

    void HttpServletResponse::addHeader(const QByteArray &name, const QByteArray &value)
    {
        headers.insert(name,value);
    }

    void HttpServletResponse::addCookie(const HttpCookie &cookie)
    {
        cookies.push_back(cookie);
    }

    void HttpServletResponse::setStatus(const int &statusCode, const QByteArray &description)
    {
        this->statusCode = statusCode;
        statusText       = description;
    }

    void HttpServletResponse::writeToSocket(const QByteArray &data)
    {
        socket->moveToThread(QThread::currentThread());
        if(socket->ConnectingState && data.size() > 0)
        {
            socket->write(data, data.size());
            socket->flush();
            if(socket->ConnectingState)
            {
                QMutex mutex;
                mutex.lock();
                socket->waitForBytesWritten(configuration.timeOut);
                mutex.unlock();
            }
        }
    }

    void HttpServletResponse::writeHeaders()
    {
        QByteArray buffer;

        buffer.append("HTTP/1.1 ");
        buffer.append(QByteArray::number(statusCode));
        buffer.append(' ');
        buffer.append(statusText);
        buffer.append("\r\n");
        foreach(QByteArray name, headers.keys())
        {
            buffer.append(name);
            buffer.append(": ");
            buffer.append(headers.value(name));
            buffer.append("\r\n");
        }
        foreach(HttpCookie cookie, cookies)
        {
            buffer.append("Set-Cookie: ");
            buffer.append(cookie.toByteArray());
            buffer.append("\r\n");
        }
        buffer.append("\r\n");
        writeToSocket(buffer);
    }

    QTcpSocket &HttpServletResponse::getSocket() const
    {
        return *socket;
    }

    void HttpServletResponse::sendRedirect(const QByteArray &url)
    {
        setStatus(HttpServletResponse::SC_SEE_OTHER, "See Other");
        addHeader("Location", url);
        write("Redirect", true);
    }

    const int HttpServletResponse::SC_CONTINUE = 100;

    const int HttpServletResponse::SC_SWITCHING_PROTOCOLS = 101;

    const int HttpServletResponse::SC_OK = 200;

    const int HttpServletResponse::SC_CREATED = 201;

    const int HttpServletResponse::SC_ACCEPTED = 202;

    const int HttpServletResponse::SC_NON_AUTHORITATIVE_INFORMATION = 203;

    const int HttpServletResponse::SC_NO_CONTENT = 204;

    const int HttpServletResponse::SC_RESET_CONTENT = 205;

    const int HttpServletResponse::SC_PARTIAL_CONTENT = 206;

    const int HttpServletResponse::SC_MULTIPLE_CHOICES = 300;

    const int HttpServletResponse::SC_MOVED_PERMANENTLY = 301;

    const int HttpServletResponse::SC_MOVED_TEMPORARILY = 302;

    const int HttpServletResponse::SC_FOUND = 302;

    const int HttpServletResponse::SC_SEE_OTHER = 303;

    const int HttpServletResponse::SC_NOT_MODIFIED = 304;

    const int HttpServletResponse::SC_USE_PROXY = 305;

    const int HttpServletResponse::SC_TEMPORARY_REDIRECT = 307;

    const int HttpServletResponse::SC_BAD_REQUEST = 400;

    const int HttpServletResponse::SC_UNAUTHORIZED = 401;

    const int HttpServletResponse::SC_PAYMENT_REQUIRED = 402;

    const int HttpServletResponse::SC_FORBIDDEN = 403;

    const int HttpServletResponse::SC_NOT_FOUND = 404;

    const int HttpServletResponse::SC_METHOD_NOT_ALLOWED = 405;

    const int HttpServletResponse::SC_NOT_ACCEPTABLE = 406;

    const int HttpServletResponse::SC_PROXY_AUTHENTICATION_REQUIRED = 407;

    const int HttpServletResponse::SC_REQUEST_TIMEOUT = 408;

    const int HttpServletResponse::SC_CONFLICT = 409;

    const int HttpServletResponse::SC_GONE = 410;

    const int HttpServletResponse::SC_LENGTH_REQUIRED = 411;

    const int HttpServletResponse::SC_PRECONDITION_FAILED = 412;

    const int HttpServletResponse::SC_REQUEST_ENTITY_TOO_LARGE = 413;

    const int HttpServletResponse::SC_REQUEST_URI_TOO_LONG = 414;

    const int HttpServletResponse::SC_UNSUPPORTED_MEDIA_TYPE = 415;

    const int HttpServletResponse::SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416;

    const int HttpServletResponse::SC_EXPECTATION_FAILED = 417;

    const int HttpServletResponse::SC_INTERNAL_SERVER_ERROR = 500;

    const int HttpServletResponse::SC_NOT_IMPLEMENTED = 501;

    const int HttpServletResponse::SC_BAD_GATEWAY = 502;

    const int HttpServletResponse::SC_SERVICE_UNAVAILABLE = 503;

    const int HttpServletResponse::SC_GATEWAY_TIMEOUT = 504;

    const int HttpServletResponse::SC_HTTP_VERSION_NOT_SUPPORTED = 505;



    /** \example /home/herik/CWF/prototipos/HelloWorld/servlets/helloworldservlet.cpp
     * This is an example of how to use the HttpServletResponse class.
     * More details about this example.
     */
}
