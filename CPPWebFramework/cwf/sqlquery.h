/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QVector>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include "sqldatabasestorage.h"

CWF_BEGIN_NAMESPACE

/**
 * @brief The SqlQuery class was created to facilitate integration with SqlDataBaseStorage and manipulation to the database through JSON.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT SqlQuery : public QSqlQuery
{
    QVector<QString> columns;

    void loadColumns();

    void makeBinds(const QVector<QVariant> &col, const QString &sql);

    QJsonObject validate(const QJsonObject &json, const QString &table);
public:
    using QSqlQuery::QSqlQuery;
    /**
     * @brief Constructs a QSqlQuery object using the database dbStorage.
     * @param dbStorage
     */
    explicit SqlQuery(SqlDatabaseStorage &dbStorage);
    /**
     * @brief Executes and returns a JSON indicating success, or failure through the key success.
     * @return QJsonObject
     */
    QJsonObject exec();
    /**
     * @brief Executes a query and returns a JSON indicating success, or failure through the key "success" and "message".
     * @return QJsonObject
     */
    QJsonObject exec(const QString &query);
    /**
     * @brief Returns the result of a select converted to a QJsonArray.
     * If there is a failure, a JSON object with two fields will be returned: "success" and "message".
     * If there are no results, QJsonArray will return a empty object.
     * @return QJsonArray
     */
    QJsonArray toJson();
    /**
     * @brief Delete a record given a table and a condition.
     * Returns a JSON indicating success, or failure through the key "success" and "message".
     * @param table
     * @param condition
     * @return QJsonObject
     */
    QJsonObject deleteRecord(const QString &table, const QString &condition);
    /**
     * @brief Insert a record given a json and a table.
     * Returns a JSON indicating success, or failure through the key "success" and "message".
     * @param json
     * @param table
     * @return QJsonObject
     */
    QJsonObject insertFromJson(const QJsonObject &json, const QString &table);
    /**
     * @brief Update a record given a json, a table and a condition.
     * Returns a JSON indicating success, or failure through the key "success" and "message".
     * @param json
     * @param table
     * @return QJsonObject
     */    
    QJsonObject updateFromJson(const QJsonObject &json, const QString &table, const QString &condition);
};

CWF_END_NAMESPACE

#endif // SQLQUERY_H
