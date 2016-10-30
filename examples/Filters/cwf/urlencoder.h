#ifndef URLENCODER_H
#define URLENCODER_H

#include <QUrl>
#include <QByteArray>

namespace CWF
{
    /**
     * @brief The URLEncoder class
     */
    class URLEncoder
    {
    public:
        /**
         * @brief decode
         * @param url
         * @return
         */
        static QString decode(const QByteArray &url);
        /**
         * @brief encode
         * @param url
         * @return
         */
        static QString encode(const QByteArray &url);
        /**
         * @brief paramEncode
         * @param param
         * @return
         */
        static QString paramEncode(const QByteArray &param);
        /**
         * @brief paramDecode
         * @param param
         * @return
         */
        static QString paramDecode(const QByteArray &param);
    };
}

#endif // URLENCODER_H
