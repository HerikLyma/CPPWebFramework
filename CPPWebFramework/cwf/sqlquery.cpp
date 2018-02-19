/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "sqlquery.h"
#include <QSqlDriver>

CWF_BEGIN_NAMESPACE

SqlQuery::SqlQuery(CWF::SqlDatabaseStorage &dbStorage) : QSqlQuery(dbStorage.getDatabase())
{
}

void SqlQuery::makeBinds(const QVector<QVariant> &col, const QString &sql)
{
    prepare(sql);
    int total = col.size();
    for(int i = 0; i < total; ++i)
    {
        bindValue(i, col[i]);
    }
}

QJsonObject SqlQuery::validate(const QJsonObject &json, const QString &table)
{
    if(json.isEmpty())
    {
        return QJsonObject{{"success", false}, {"message", "JSON is empty"}};
    }
    else if(table.isEmpty())
    {
        return QJsonObject{{"success", false}, {"message", "Table name is empty"}};
    }
    return QJsonObject{{"success", true}};
}

void SqlQuery::loadColumns()
{
    int total = record().count();
    columns.resize(total);
    for(int i = 0; i < total; ++i)
    {
        columns[i] = std::move(record().fieldName(i));
    }
}

QJsonObject SqlQuery::exec()
{
    if(QSqlQuery::exec())
    {
        return QJsonObject{{"success", true}, {"message", "Success"}};
    }
    return QJsonObject{{"success", false}, {"message", lastError().text()}};
}

QJsonObject SqlQuery::exec(const QString &query)
{
    prepare(query);
    return exec();
}

QJsonArray SqlQuery::toJson()
{
    QJsonArray array;
    QString error(std::move(lastError().text()));
    if(!error.trimmed().isEmpty())
    {
        array.push_back(QJsonObject{{"success", false}, {"message", error}});
    }
    else if(isSelect())
    {
        loadColumns();
        first();
        int total = columns.size();
        while(isValid())
        {
            QJsonObject json;
            for(int i = 0; i < total; ++i)
            {
                QVariant var(record().value(i));
                if(var.type() == QVariant::Double)
                    json[columns[i]] = var.toDouble();
                else if(var.type() == QVariant::Int)
                    json[columns[i]] = var.toInt();
                else if(var.type() == QVariant::Bool)
                    json[columns[i]] = var.toBool();
                else
                    json[columns[i]] = var.toString();
            }
            array.push_back(json);
            next();
        }
        first();
    }
    return array;
}

QJsonObject SqlQuery::deleteRecord(const QString &table, const QString &condition)
{
    return exec("delete from " + table + " where " + condition);
}

QJsonObject SqlQuery::insertFromJson(const QJsonObject &json, const QString &table)
{
    QJsonObject status(validate(json, table));
    if(status["success"].toBool())
    {
        QString firstSql, secondSql;
        const QString comma(","), questionMark("?");
        QVector<QVariant> values;
        values.reserve(json.count());
        for(auto it = json.begin(); it != json.end(); ++it)
        {
            const QString &key = it.key();
            firstSql   += key + comma;
            secondSql  += questionMark + comma;
            values.push_back(it.value().toVariant());
        }
        firstSql.remove(firstSql.size() - 1, 1);
        secondSql.remove(secondSql.size() - 1, 1);
        makeBinds(values, "insert into " + table + "(" + firstSql + ") values(" + secondSql + ");");
        return exec();
    }
    return status;
}

QJsonObject SqlQuery::updateFromJson(const QJsonObject &json, const QString &table, const QString &condition)
{
    QJsonObject status(validate(json, table));
    if(status["success"].toBool())
    {
        QString sets;
        const QString comma(","), questionMark("?"), equal("=");
        QVector<QVariant> values;
        values.reserve(json.count());
        for(auto it = json.begin(); it != json.end(); ++it)
        {
            const QString &key = it.key();
            sets += key + equal + questionMark + comma;
            values.push_back(it.value().toVariant());
        }
        sets.remove(sets.size() - 1, 1);
        makeBinds(values, "update " + table + " set " + sets + " where " + condition);
        return exec();
    }
    return status;
}

CWF_END_NAMESPACE
