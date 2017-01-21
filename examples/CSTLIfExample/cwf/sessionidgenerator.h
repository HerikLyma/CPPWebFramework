/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef SESSIONIDGENERATOR_H
#define SESSIONIDGENERATOR_H

#include "httpparser.h"

namespace CWF
{
    /**
     * @brief The SessionIdGenerator class is responsable to generate sessions id to the clients.
     */
    class SessionIdGenerator
    {
        const HttpParser &httpParser;
    public:
        /**
         * @brief This constructor receives a HttpParser
         * @param const HttpParser &httpParser : Used to generate Session ID.
         */
        explicit SessionIdGenerator(const HttpParser &httpParser);
        /**
         * @brief This method process some informations of httpParser and generates a session id.
         * @return QByteArray : Session ID.
         */
        QByteArray getSessionID() const;
    };
}

#endif // SESSIONIDGENERATOR_H
