/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

// clazy:excludeall=non-pod-global-static
#include <QString>
#include <QByteArray>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
//CONFIGURATION CONSTANTS
namespace CONFIGURATION
{
    const QByteArray CPP_CONFIG          = "/config/";
    const QByteArray CPP_WEB_INI         = "CPPWeb.ini";
    const QByteArray CPP_LOG_FILE        = "CPPWebServer.log";
    const QString    CPP_LOG_VAR         = "cwf_log_file";
    const QString    CPP_LOG_MAX_VAR     = "cwf_log_max";
}

//XML CONSTANTS
namespace XML
{
    const QByteArray HEADER = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n";
}

//GETTER AND SETTER CONSTANTS
namespace GET_SET
{
    const QString GET_LOWER = "get";
    const QString SET_LOWER = "set";
    const QString GET_UPPER = "GET";
    const QString SET_UPPER = "SET";
}

//STATUS CONSTANTS
namespace STATUS
{
    const QByteArray  STATUS_401  = "/config/cppwebserverpages/401.view";
    const QByteArray  STATUS_403  = "/config/cppwebserverpages/403.view";
    const QByteArray  STATUS_404  = "/config/cppwebserverpages/404.view";
    const QByteArray  NOT_FOUND   = "Not Found";
}

//CSTL CONSTANTS
namespace CSTL
{
    //CSTL TAGS CONSTANTS
    namespace TAG
    {
        const QString OUT    = "out";
        const QString FOR    = "for";
        const QString IF     = "if";
        const QString IMPORT = "import";
        const QByteArray BEGIN  = "<cstl>";
        const QByteArray END    = "</cstl>";

        //PROPERTIES CONSTANTS
        namespace PROPERTY
        {
            const QString VAR        = "var";
            const QString ERROR      = "error";
            const QString CONDITION  = "condition";

            namespace IMPORT
            {
                const QString URL    = "url";
            }

            namespace FOR
            {
                const QString ITEMS      = "items";
                const QString FROM       = "from";
                const QString TO         = "to";
                const QString INCREMENT  = "increment";
            }

            namespace IF
            {
                const QString EQUAL          = "equal";
                const QString DIFFERENT      = "different";
                const QString GREATER        = "greater";
                const QString GREATER_EQUAL  = "greater_equal";
                const QString LESS           = "less";
                const QString LESS_EQUAL     = "less_equal";
            }
        }
    }

    //SUPORTED TYPES CONSTANTS
    namespace SUPPORTED_TYPES
    {
        const QString QSTRING                = "QString";
        const QString STD_STRING             = "std::string";
        const QString BOOL                   = "bool";
        const QString CHAR                   = "char";
        const QString UNSIGNED_CHAR          = "uchar";
        const QString SHORT                  = "short";
        const QString UNSIGNED_SHORT         = "ushort";
        const QString INT                    = "int";
        const QString UNSIGNED_INT           = "uint";
        const QString LONG                   = "long";
        const QString UNSIGNED_LONG          = "ulong";
        const QString LONG_LONG              = "qlonglong";
        const QString UNSIGNED_LONG_LONG     = "qulonglong";
        const QString FLOAT                  = "float";
        const QString DOUBLE                 = "double";
        const QString CWF_QLISTOBJECT        = "CWF::QListObject";
    }
}

//CONTENT TYPE CONSTANTS
namespace HTTP
{
    const QByteArray SERVER                           = "Server";
    const QByteArray SERVER_VERSION                   = "C++-Web-Server/3.1";
    const QByteArray DATA                             = "Data";
    const QByteArray TRANSFER_ENCODING                = "Transfer-Encoding";
    const QByteArray CHUNKED                          = "chunked";
    const QByteArray END_LINE                         = "\r\n";
    const QByteArray SEPARATOR                        = ": ";
    const QByteArray HTTP_1_1                         = "HTTP/1.1 ";
    const QByteArray END_OF_MESSAGE                   = "\r\n\r\n";
    const QByteArray END_OF_MESSAGE_WITH_ZERO         = "0\r\n\r\n";
    const QByteArray CONTENT_TYPE                     = "Content-Type";
    const QByteArray CONTENT_LENGTH                   = "Content-Length";
    const QByteArray CONTENT_DISPOSITION              = "Content-Disposition";
    const QByteArray CONTENT_DISPOSITION_COLON        = "Content-Disposition:";
    const QByteArray CONTENT_DISPOSITION_COLON_SPACE  = "Content-Disposition: ";
    const QByteArray MULTIPART                        = "multipart";
    const QByteArray URLENCODED                       = "urlencoded";
    const QByteArray COOKIE                           = "Cookie";
    const QByteArray SET_COOKIE                       = "Set-Cookie: ";
    const QByteArray SESSION_ID                       = "sessionId";
    const QByteArray FILENAME                         = "filename";
    const QByteArray FORM_DATA_COLON_SPACE            = "form-data; ";
    const QByteArray WEBKIT                           = "WebKit";
    const QByteArray LOCATION                         = "Location";
    const QByteArray REDIRECT                         = "Redirect";
    const QByteArray SEE_OTHER                        = "See Other";
    const QByteArray ACCEPT_ENCODING                  = "Accept-Encoding";
    const QByteArray ACCEPT_LANGUAGE                  = "Accept-Language";
    const QByteArray HOST                             = "Host";
    const QByteArray USER_AGENT                       = "User-Agent";
    const QByteArray OK                               = "OK";
    /*
    const QByteArray            = "";
    const QByteArray            = "";
    */


    //TEXT
    const QByteArray TEXT_HTML_UTF8       = "text/html; charset=UTF-8";

    //IMAGE
    const QByteArray IMAGE_MICROSOFT_ICO    = "image/vnd.microsoft.icon";
    const QByteArray IMAGE_JPEG             = "image/jpeg";
    const QByteArray IMAGE_TIFF             = "image/tiff";
    const QByteArray IMAGE_SVG_XML          = "image/svg+xml";

    //AUDIO
    const QByteArray AUDIO_MP3              = "image/mpeg";
    const QByteArray AUDIO_MP4              = "image/mp4";
    const QByteArray APPLICATION_PHOTOSHOP  = "image/vnd.adobe.photoshop";

    //VIDEO
    const QByteArray VIDEO_FLV              = "video/x-flv";

    //APPLICATION
    const QByteArray APPLICATION_MSWORD                      = "application/msword";
    const QByteArray APPLICATION_RTF                         = "application/rtf";
    const QByteArray APPLICATION_EXCEL                       = "application/vnd.ms-excel";
    const QByteArray APPLICATION_JSON                        = "application/json";
    const QByteArray APPLICATION_POWER_POINT                 = "application/vnd.ms-powerpoint";
    const QByteArray APPLICATION_JAVASCRIPT                  = "application/javascript";
    const QByteArray APPLICATION_OPEN_DOCUMENT_TEXT          = "application/vnd.oasis.opendocument.text";
    const QByteArray APPLICATION_OPEN_DOCUMENT_SPREADSHEET   = "application/vnd.oasis.opendocument.spreadsheet";
    const QByteArray APPLICATION_SHOCKWAVE_FLASH             = "application/x-shockwave-flash";
    const QByteArray APPLICATION_RAR_COMPRESSED              = "application/x-rar-compressed";
    const QByteArray APPLICATION_MS_DOWNLOAD                 = "application/x-msdownload";
    const QByteArray APPLICATION_CAB_COMPRESSED              = "application/vnd.ms-cab-compressed";
    const QByteArray APPLICATION_POSTSCRIPT                  = "application/postscript";
    const QByteArray APPLICATION_WWW_FORM_URLENCODED         = "application/x-www-form-urlencoded";
    const QByteArray APPLICATION_FONT_WOFF                   = "application/x-font-woff";
    const QByteArray APPLICATION_FONT_TTF                    = "application/octet-stream";

    //HTTP METHODS CONSTANTS
    namespace METHOD
    {
        const QByteArray GET     = "GET";
        const QByteArray PUT     = "PUT";
        const QByteArray POST    = "POST";
        const QByteArray DELETE  = "DELETE";
        const QByteArray OPTIONS = "OPTIONS";
        const QByteArray HEAD    = "HEAD";
        const QByteArray TRACE   = "TRACE";
    }
}

namespace COOKIE
{
    const QByteArray COMMENT        = "Comment";
    const QByteArray DOMAIN_COOKIE  = "Domain";
    const QByteArray MAX_AGE        = "Max-Age";
    const QByteArray PATH           = "Path";
    const QByteArray SECURE         = "Secure";
    const QByteArray VERSION        = "Version";
}

//FILE EXTENTIONS CONSTANTS
namespace FILE_EXTENTION
{
    const QByteArray BAR  = "/";
    const QByteArray HTML = "html";
    const QByteArray HTM  = "htm";
    const QByteArray CSS  = "css";
    const QByteArray TXT  = "txt";
    const QByteArray PHP  = "php";
    const QByteArray ICO  = "ico";
    const QByteArray PNG  = "png";
    const QByteArray GIF  = "gif";
    const QByteArray BMP  = "bmp";
    const QByteArray JPE  = "jpe";
    const QByteArray JPG  = "jpg";
    const QByteArray TIF  = "TIF";
    const QByteArray TIFF = "TIFF";
    const QByteArray SVG  = "svg";
    const QByteArray SVGZ = "svgz";
    const QByteArray PDF  = "pdf";
    const QByteArray XML  = "xml";
    const QByteArray JSON = "json";
    const QByteArray ZIP  = "zip";
    const QByteArray MP3  = "mp3";
    const QByteArray MP4  = "mp4";
    const QByteArray FLV  = "flv";
    const QByteArray DOC  = "doc";
    const QByteArray RTF  = "rtf";
    const QByteArray XLS  = "xls";
    const QByteArray PPT  = "ppt";
    const QByteArray JS   = "js";
    const QByteArray ODT  = "odt";
    const QByteArray ODS  = "ods";
    const QByteArray SWF  = "swf";
    const QByteArray RAR  = "rar";
    const QByteArray EXE  = "exe";
    const QByteArray MSI  = "msi";
    const QByteArray CAB  = "cab";
    const QByteArray PSD  = "psd";
    const QByteArray AI   = "ai";
    const QByteArray EPS  = "eps";
    const QByteArray PS   = "ps";
    const QByteArray INI  = "ini";
    const QByteArray EOT  = "eot";
    const QByteArray TTF  = "ttf";
    const QByteArray WOFF = "woff";
    const QByteArray WOFF2= "woff2";
}

CWF_END_NAMESPACE

#endif // CONSTANTS_H
