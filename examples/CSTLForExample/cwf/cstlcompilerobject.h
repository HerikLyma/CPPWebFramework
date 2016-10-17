/**
  @file cstlcompilerobject.h
  @author Herik Lima
*/

#ifndef CSTLCOMPILEROBJECT_H
#define CSTLCOMPILEROBJECT_H

#include <QObject>

namespace CWF
{
    class CSTLCompilerObject : public QObject
    {
    Q_OBJECT
        QString value;
        QString type;
    public:
        CSTLCompilerObject(QObject *parent = 0);
    public slots:
        QString getValue() const;
        void setValue(const QString &value);
        QString getType() const;
        void setType(const QString &value);
    };
}

#endif // CSTLCOMPILEROBJECT_H
