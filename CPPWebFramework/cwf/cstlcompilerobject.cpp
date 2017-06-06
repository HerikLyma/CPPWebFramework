/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cstlcompilerobject.h"

CWF_BEGIN_NAMESPACE

CSTLCompilerObject::CSTLCompilerObject(QObject *parent) : QObject(parent)
{
}

QString CSTLCompilerObject::getValue() const
{
    return value;
}

void CSTLCompilerObject::setValue(const QString &value)
{
    this->value = value;
}

QString CSTLCompilerObject::getType() const
{
    return type;
}

void CSTLCompilerObject::setType(const QString &value)
{
    this->type = value;
}

CWF_END_NAMESPACE
