/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CSTLCOMPILEROBJECT_H
#define CSTLCOMPILEROBJECT_H

#include <QObject>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The Properties class is an auxiliar class to the CSTLCompiler.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompilerObject : public QObject
{
   Q_OBJECT
private:
    QString value;
    QString type;
public:
    /**
     * @brief This constructor can set the CSTLCompilerObject's parent.
     * @param QObject *parent : parent.
     */
    explicit CSTLCompilerObject(QObject *parent = 0);
public slots:
    /**
     * @brief Returns the value.
     * @return QString : Value.
     */
    QString getValue() const;
    /**
     * @brief Sets the value.
     * @param const QString &value : Value.
     */
    void setValue(const QString &value);
    /**
     * @brief Returns the type.
     * @return QString : Type.
     */
    QString getType() const;
    /**
     * @brief Sets the type.
     * @param const QString &value : Type.
     */
    void setType(const QString &value);
};

CWF_END_NAMESPACE

#endif // CSTLCOMPILEROBJECT_H
