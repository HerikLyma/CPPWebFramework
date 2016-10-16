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
         * @param httpParser : This is a reference to a HttpParser
         */
        SessionIdGenerator(const HttpParser &httpParser);
        /**
         * @brief This method process some informations of httpParser and generates a session id.
         * @return QString.
         */
        QByteArray getSessionID() const;
    };
}

#endif // SESSIONIDGENERATOR_H
