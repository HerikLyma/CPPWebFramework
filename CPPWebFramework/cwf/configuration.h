/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSettings>
#include <QSslSocket>
#include <QHostAddress>
#include "filemanager.h"
#include "cppwebframework_global.h"
/**
 * @brief All classes of C++ Web Framework are contained within the namespace CWF.
 */
CWF_BEGIN_NAMESPACE
/**
 * @brief This class is responsable to read a ini file and extract its information.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Configuration
{    
    bool valid                = false;
    bool accessCPPWebIni      = false;
    bool accessServerPages    = false;
    quint16 port              = 8080;
    int timeOut               = 30000;
    int sessionExpirationTime = 1800000;
    int cleanupInterval       = 86400000;    
    int maxThread             = 100;
    QString sslKeyFile;
    QString sslCertFile;
    QString path;
    QString logFilePath;
    QString indexPage;
    QByteArray sslPassPhrase;
    QHostAddress host;
    qint64 maxUploadFile = 2097152;
    qint64 maxLogFile    = 20000000;
    QSsl::KeyAlgorithm sslKeyAlgorithm = QSsl::Rsa;
    QSsl::KeyType sslKeyType = QSsl::PrivateKey;
    QSsl::EncodingFormat sslEncodingFormat = QSsl::Pem;
    QSsl::SslProtocol sslProtocol = QSsl::TlsV1SslV3;
    QSslSocket::PeerVerifyMode sslPeerVerifyMode = QSslSocket::VerifyNone;
    void configure();
public:
    /**
     * @brief Will make reading the CPPWeb.ini file and extract all of its properties.
     * @param QString serverFilesPath : You should always points to the directory server.
     * @par Example
     * @code
     * #include <QCoreApplication>
     * #include <cwf/cppwebapplication.h>
     *
     * int main(int argc, char *argv[])
     * {     
     *     CWF::CppWebApplication a(argc, argv, "PATH_TO_SERVER_FOLDER");
     *     return a.start();
     * }
     * @endcode
     */
    explicit Configuration(const QString &serverFilesPath = "");   
    /**
     * @brief Returns the timeOut property that will be used by the server to expire threads that are not in use.
     * Such threads will be restarted as needed. The default timeOut is 30000 milliseconds (30 seconds).
     * If timeOut is negative, newly created threads will not expire, e.g., they will not exit until the thread pool is destroyed.
     * @param int : Time in milliseconds.
     */
    inline int getTimeOut() const noexcept { return timeOut; }
    /**
     * @brief Returns the Session Expiration Time.
     * @param int : Time in milliseconds.
     */
    inline int getSessionExpirationTime() const noexcept { return sessionExpirationTime; }
    /**
     * @brief Returns the clean up interval Time.
     * @param int : Time in milliseconds.
     */
    inline int getCleanupInterval() const noexcept { return cleanupInterval; }
    /**
     * @brief Returns the port number.
     * @param quint16 : port.
     */
    inline quint16 getPort() const noexcept { return port; }
    /**
     * @brief Returns the address.
     * @param QHostAddress : host.
     */
    inline QHostAddress getHost() const noexcept { return host; }
    /**
     * @brief Returns the max thread number.
     * @param int : max.
     */
    inline int getMaxThread() const noexcept { return maxThread; }
    /**
     * @brief Returns the ssl key file.
     * @param QString : sslKeyFile name.
     */
    inline QString getSslKeyFile() const noexcept { return sslKeyFile; }
    /**
     * @brief Returns the ssl cert file.
     * @param QString : sslCertFile name.
     */
    inline QString getSslCertFile() const noexcept { return sslCertFile; }
    /**
     * @brief Returns the path to the server's folder.
     * @param QString : path.
     */
    inline QString getPath() const noexcept { return path; }
    /**
     * @brief Returns the log file path.
     * @param QString : log file.
     */
    inline QString getLogFilePath() const noexcept { return logFilePath; }
    /**
     * @brief Returns max upload file size supported by the server.
     * @param qint64: max file size.
     */
    inline qint64 getMaxUploadFile() const noexcept { return maxUploadFile; }
    /**
     * @brief getMaxLogFile the max file log
     * @return qint64 : Max file log in bytes.
     */
    inline qint64 getMaxLogFile() const noexcept { return maxLogFile; }
    /**
     * @brief Returns the index page.
     * @return QString : index page name.
     */
    inline QString getIndexPage() const noexcept { return indexPage; }
    /**
     * @brief Returns the access server page.
     * @return bool : Access server pages.
     */
    inline bool getAccessServerPages() const noexcept { return accessServerPages; }
    /**
     * @brief Returns the ssl pass phrase
     * @return QByteArray : sslPassPhrase.
     */
    inline QByteArray getSslPassPhrase() const noexcept { return sslPassPhrase; }
    /**
     * @brief Returns true if the Configuration is ok. Otherwise returns false.
     * @param bool : is valid.
     */
    inline bool isValid() const noexcept { return valid; }
    /**
     * @brief Returns the SSL Key Algorithm. The RSA is defined by default.
     * @param QSsl::KeyAlgorithm : SSL key Algorithm.
     */
    inline QSsl::KeyAlgorithm getSslKeyAlgorithm() const noexcept { return sslKeyAlgorithm; }
    /**
     * @brief Returns the SSL Key Type. The private is defined by default.
     * @param QSsl::KeyType : SSL key Type.
     */
    inline QSsl::KeyType getSslKeyType() const noexcept { return sslKeyType; }
    /**
     * @brief Returns the SSL Encoding Format. The PEM is defined by default.
     * @param QSsl::EncodingFormat : SSL key Encoding Format.
     */
    inline QSsl::EncodingFormat getSslEncodingFormat() const noexcept { return sslEncodingFormat; }
    /**
     * @brief Returns the SSL Peer Veryfy Mode. The VerifyNone is defined by default.
     * @param QSslSocket::PeerVerifyMode : Peer Veryfy Mode;
     */
    inline QSslSocket::PeerVerifyMode getSslPeerVerifyMode() const noexcept { return sslPeerVerifyMode; }
    /**
     * @brief Returns the SSL Protocol. The TlsV1SslV3 is defined by default.
     * @param QSsl::SslProtocol : SSL Protocol;
     */
    inline QSsl::SslProtocol getSslProtocol() const noexcept { return sslProtocol; }    
    /**
     * @brief Returns the sslOptionDisableEmptyFragments. It is defined false by default.
     * @param bool : true if is enable otherwise returns false;
     */
};

CWF_END_NAMESPACE

#endif // CONFIGURATION_H
