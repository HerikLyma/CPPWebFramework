#include "variant.h"

CWF_BEGIN_NAMESPACE

Variant::Variant(int value) : variant(value)
{

}

Variant::Variant(double value) : variant(value)
{

}

Variant::Variant(qlonglong value) : variant(value)
{

}

Variant::Variant(const QString &value) : variant(value)
{

}

int Variant::toInt(bool *ok) const
{
    return variant.toInt(ok);
}

void Variant::setInt(int value)
{
    variant = value;
}

double Variant::toDouble(bool *ok) const
{
    return variant.toDouble(ok);
}

void Variant::setDouble(double value)
{
    variant = value;
}

qlonglong Variant::toLongLong(bool *ok) const
{
    return variant.toLongLong(ok);
}

void Variant::setLongLong(qlonglong value)
{
    variant = value;
}

QString Variant::toString() const
{
    return variant.toString();
}

void Variant::setString(const QString &value)
{
    variant = value;
}

CWF_END_NAMESPACE
