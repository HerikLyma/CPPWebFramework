/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef HTTPREQUESTMETHOD_H
#define HTTPREQUESTMETHOD_H

#include <QString>

namespace CWF
{
    /**
     * @brief The HttpRequestMethod class holds fixed strings that represents request methods.
     */
    class HttpRequestMethod
    {
    public:
        /**
         * @brief This is a static method and returns a string to the delete request method.
         * @return QString : Returns "DELETE"
         */
        inline static const QString getDelete() { return "DELETE";  }
        /**
         * @brief This is a static method and returns a string to the get request method.
         * @return QString : Returns "GET"
         */
        inline static const QString getGet()    { return "GET";     }
        /**
         * @brief This is a static method and returns a string to the head request method.
         * @return QString : Returns "HEAD"
         */
        inline static const QString getHead()   { return "HEAD";    }
        /**
         * @brief This is a static method and returns a string to the options request method.
         * @return QString : Returns "OPTIONS"
         */
        inline static const QString getOptions(){ return "OPTIONS"; }
        /**
         * @brief This is a static method and returns a string to the post request method.
         * @return QString : Returns "POST"
         */
        inline static const QString getPost()   { return "POST";    }
        /**
         * @brief This is a static method and returns a string to the put request method.
         * @return QString : Returns "PUT"
         */
        inline static const QString getPut()    { return "PUT";     }
        /**
         * @brief This is a static method and returns a string to the trace request method.
         * @return QString : Returns "TRACE"
         */
        inline static const QString getTrace()  { return "TRACE";   }
    };
}

#endif // HTTPREQUESTMETHOD_H
