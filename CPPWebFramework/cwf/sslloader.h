#ifndef SSLLOADER_H
#define SSLLOADER_H

#include "cppwebframework_global.h"
#include <QSslConfiguration>
#include "configuration.h"

CWF_BEGIN_NAMESPACE

/**
 * @brief The SslLoader class is responsible for loading the SSL settings.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT SslLoader
{
    Configuration configuration;
public:
    /**
     * @brief SslLoader constructor requires a Configuration object.
     */
    SslLoader(Configuration configuration);
    /**
     * @brief Returns a QSslConfiguration. It will returns nullptr if it fails.
     */
    QSslConfiguration *getSslConfiguration() const;
};

CWF_END_NAMESPACE

#endif // SSLLOADER_H
