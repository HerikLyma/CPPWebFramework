/**
  @file httprequestmethod.h
  @author Herik Lima
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
         * @return QString
         */
        inline static const QString getDelete() { return "DELETE";  }
        /**
         * @brief This is a static method and returns a string to the get request method.
         * @return QString
         */
        inline static const QString getGet()    { return "GET";     }
        /**
         * @brief This is a static method and returns a string to the head request method.
         * @return QString
         */
        inline static const QString getHead()   { return "HEAD";    }
        /**
         * @brief This is a static method and returns a string to the options request method.
         * @return QString
         */
        inline static const QString getOptions(){ return "OPTIONS"; }
        /**
         * @brief This is a static method and returns a string to the post request method.
         * @return QString
         */
        inline static const QString getPost()   { return "POST";    }
        /**
         * @brief This is a static method and returns a string to the put request method.
         * @return QString
         */
        inline static const QString getPut()    { return "PUT";     }
        /**
         * @brief This is a static method and returns a string to the trace request method.
         * @return QString
         */
        inline static const QString getTrace()  { return "TRACE";   }
    };
}

#endif // HTTPREQUESTMETHOD_H
