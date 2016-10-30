/**
  @file sessionidgenerator.h
  @author Herik Lima
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
        SessionIdGenerator(const HttpParser &httpParser);
        /**
         * @brief This method process some informations of httpParser and generates a session id.
         * @return QByteArray : Session ID.
         */
        QByteArray getSessionID() const;
    };
}

#endif // SESSIONIDGENERATOR_H
