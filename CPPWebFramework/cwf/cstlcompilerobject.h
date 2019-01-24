/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef CSTLCOMPILEROBJECT_H
#define CSTLCOMPILEROBJECT_H
//  clazy:excludeall=const-signal-or-slot
#include <QObject>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The Properties class is an auxiliar class to the CSTLCompiler.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT CSTLCompilerObject : public QObject
{
    Q_OBJECT
    QString value;
    QString type;
public:
    /**
     * @brief This constructor can set the CSTLCompilerObject's parent.
     * @param QObject *parent : parent.
     */
    explicit CSTLCompilerObject(QObject *parent = nullptr) : QObject(parent) {}
public slots:
    /**
     * @brief Returns the value.
     * @return QString : Value.
     */
    inline QString getValue() const noexcept { return value; }
    /**
     * @brief Sets the value.
     * @param const QString &value : Value.
     */
    inline void setValue(const QString &value) noexcept { this->value = value; }
    /**
     * @brief Returns the type.
     * @return QString : Type.
     */
    inline QString getType() const noexcept { return type; }
    /**
     * @brief Sets the type.
     * @param const QString &value : Type.
     */
    inline void setType(const QString &value) noexcept { type = value; }
};

CWF_END_NAMESPACE

#endif // CSTLCOMPILEROBJECT_H
