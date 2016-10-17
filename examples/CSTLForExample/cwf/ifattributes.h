/**
  @file ifattributes.h
  @author Herik Lima
*/

#ifndef IFATTRIBUTES_H
#define IFATTRIBUTES_H

#include <QString>
#include <QXmlStreamAttributes>

namespace CWF
{
    class IfAttributes
    {
    public:
        QString var;
        QString equal;
        QString notEqual;
        QString greater;
        QString less;
        QString greaterEqual;
        QString lessEqual;
        QString error;
        bool condition = false;
        IfAttributes(const QXmlStreamAttributes &attributes);
    };
}

#endif // IFATTRIBUTES_H
