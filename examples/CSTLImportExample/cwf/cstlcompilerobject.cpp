#include "cstlcompilerobject.h"

namespace CWF
{
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
}
