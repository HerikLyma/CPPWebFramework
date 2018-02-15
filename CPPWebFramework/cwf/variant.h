#ifndef VARIANT_H
#define VARIANT_H

#include <QObject>
#include <QVariant>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
* @brief This class is designed to facilitate the passing of simple type parameters such as
* qlonglong, double, int, and QString to the CSTL (C++ Server Pages Standard Tags Library).
*/
class CPPWEBFRAMEWORKSHARED_EXPORT Variant : public QObject
{
    Q_OBJECT
    QVariant variant;
public:
    /**
     * @brief Constructs an invalid variant.
     */
    Variant() = default;
    /**
     * @brief Constructs a new variant with an integer value.
     */
    explicit Variant(int value);
    /**
     * @brief Constructs a new variant with an double value.
     */
    explicit Variant(double value);
    /**
     * @brief Constructs a new variant with an qlonglong value.
     */
    explicit Variant(qlonglong value);
    /**
     * @brief Constructs a new variant with an QString value.
     */
    explicit Variant(const QString &value);
public slots:
    /**
     * @brief Returns the variant as an int if the variant has userType() QMetaType::Int, QMetaType::Bool, QMetaType::QByteArray, QMetaType::QChar, QMetaType::Double, QMetaType::LongLong, QMetaType::QString, QMetaType::UInt, or QMetaType::ULongLong; otherwise returns 0.
     * @warning: If the value is convertible to a QMetaType::LongLong but is too large to be represented in an int, the resulting arithmetic overflow will not be reflected in ok. A simple workaround is to use QString::toInt()
     * @param If ok is non-null: *ok is set to true if the value could be converted to an int; otherwise *ok is set to false.
     */
    int toInt(bool *ok = nullptr) const;
    /**
     * @brief Constructs a new variant with an int value.
     */
    void setInt(int value);
    /**
     * @brief Returns the variant as a double if the variant has userType() QMetaType::Double, QMetaType::Float, QMetaType::Bool, QMetaType::QByteArray, QMetaType::Int, QMetaType::LongLong, QMetaType::QString, QMetaType::UInt, or QMetaType::ULongLong; otherwise returns 0.0.
     * @param If ok is non-null: *ok is set to true if the value could be converted to a double; otherwise *ok is set to false.
     */
    double toDouble(bool *ok = nullptr) const;
    /**
     * @brief Constructs a new variant with an double value.
     */
    void setDouble(double value);
    /**
     * @brief Returns the variant as a long long int if the variant has userType() QMetaType::LongLong, QMetaType::Bool, QMetaType::QByteArray, QMetaType::QChar, QMetaType::Double, QMetaType::Int, QMetaType::QString, QMetaType::UInt, or QMetaType::ULongLong; otherwise returns 0.
     * @param If ok is non-null: *ok is set to true if the value could be converted to an int; otherwise *ok is set to false.
     */
    qlonglong toLongLong(bool *ok = nullptr) const;
    /**
     * @brief Constructs a new variant with an qlonglong value.
     */
    void setLongLong(qlonglong value);
    /**
     * @brief Returns the variant as a QString if the variant has userType() QMetaType::QString, QMetaType::Bool, QMetaType::QByteArray, QMetaType::QChar, QMetaType::QDate, QMetaType::QDateTime, QMetaType::Double, QMetaType::Int, QMetaType::LongLong, QMetaType::QStringList, QMetaType::QTime, QMetaType::UInt, or QMetaType::ULongLong; otherwise returns an empty string.
     */
    QString toString() const;
    /**
     * @brief Constructs a new variant with an QString value.
     */
    void setString(const QString &value);
};

CWF_END_NAMESPACE

#endif // VARIANT_H
