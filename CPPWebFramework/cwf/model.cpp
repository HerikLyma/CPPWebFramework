#include "model.h"

CWF_BEGIN_NAMESPACE

void Model::updateDB()
{
    verifyDbTableExist();
    verifyDbFields();
}

void Model::build(const QMap<QString, QVariant> &selectCondition)
{
    // Get the data from the db and populate the model with them

    const auto &properties = MetaClassParser(this, true).getAllPropertiesNames();
    const auto &propValueMap = basicOperation.build(name, selectCondition, properties);

    // Loop on all the prop value to update the current object
    for(const auto& it : propValueMap.toStdMap())
    {
        setProperty(it.first.toStdString().c_str(), it.second);
    }

    // Depending on the content of propValueMap, we set the built flag to true or false.
    // If the db query failed then the list is empty here.
    built = !propValueMap.empty();
}

void Model::buildFromJson(const QJsonObject &json, bool withTableNamePrefix)
{
    const auto &props = MetaClassParser(this, true).getAllPropertiesNames();
    // Loop on all props
    for(const auto &prop : props)
    {
        QString propName;

        if(withTableNamePrefix)
            propName = getTableName() + "_" + prop;
        else
            propName = prop;

        const auto &jsonValue = json.value(propName);

        if(jsonValue.isUndefined())
        {
            built = false;
            break;
        }

        if(!setProperty(prop.toStdString().c_str(), jsonValue.toVariant()))
        {
            built = false;
            break;
        }
    }
}

bool Model::save()
{
    if(!preSaveCheck())
    {
        return false;
    }

    const auto &currentDt = QDateTime::currentDateTime();
    if(id == -1)
    {
        this->setProperty("createdDateTime", currentDt.toString(dtFormat));
        setCreatedDt(currentDt);
    }

    this->setProperty("lastModifiedDateTime", currentDt.toString(dtFormat));
    setLastModifiedDt(currentDt);
    setProperty("id", id = basicOperation.save(name, computePropsMap(*this)));

    return id != -1;
}

void Model::customizeField(const QString &fieldName, const QVariant::Type &type, const QString &tableName) const
{
    Q_UNUSED(fieldName)
    Q_UNUSED(type)
    Q_UNUSED(tableName)
}

void Model::verifyDbTableExist()
{
    if(!basicOperation.isTableInDb("table_version"))
    {
        if(!basicOperation.createVersionTable())
        {
            return;
        }
    }
    if(!basicOperation.isTableInDb(name))
    {
        if(basicOperation.createTable(name))
        {
            qInfo() << "Model::verifyDbTableExist:" << "Table " << name << " was successfuly created";
        }
    }
}

void Model::verifyDbFields()
{
    MetaClassParser parser(this, true);
    auto dbChangedPerformed = false;
    const auto &fieldsFromDb = basicOperation.fields(name);
    const auto &fieldsFromObject = parser.getAllPropertiesNames();
    auto fieldsFromObjectTmp(fieldsFromObject);
    for(auto &f : fieldsFromObjectTmp)
        f = f.toLower();

    for(auto it = parser.props.begin(); it != parser.props.end(); ++it)
    {
        const auto &fieldName = it.key().second;
        auto existInDb = fieldsFromDb.contains(fieldName.toLower());

        if(!existInDb)
        {
            qInfo() << "Model::verifyDbFields:"<< "In" << name
                    << "the field" << fieldName << "is present in the object but was not found in database."
                    << "We update the database.";

            dbChangedPerformed = true;

            const auto &propertyType = this->propertyType(fieldName);

            basicOperation.addFieldToTable(fieldName, propertyType, name);

            customizeField(fieldName, propertyType, name);
        }
    }



    // Security loop to check no field is missing
    for(const auto &fieldName : fieldsFromDb)
    {
        if(!fieldsFromObjectTmp.contains(fieldName) )
        {
            qDebug() << "Model::verifyDbFields: The field "<<fieldName << "was present in the DB and not in the object."
                     << "It was probably deleted from the object property recently. "
                     << "This is forbidden: a property should never be deleted because of db consistency";
            qFatal("A property saved in the database was deleted");
        }
    }

    // If we performed a change in the db
    if(dbChangedPerformed)
    {
        qInfo() << "The database was modified to update the table" << name << "."
                << "We will update the version for this table.";

        auto tableVersion = basicOperation.tableVersion(name);
        tableVersion += 1;
        basicOperation.changeTableVersion(name, tableVersion);
    }
}

QMetaProperty Model::findProperty(const QString &propertyName)
{
    QMetaProperty emptyProperty;
    auto found = MetaClassParser(this, true).findProperty(propertyName);

    if(QString(found.name()) == QString(emptyProperty.name()))
    {
        QString msg(QString("Model::findProperty: The property ") + propertyName + " was not found in " + name);
        qDebug() << msg;
        qFatal("Property should always be found here");
    }

    return found;
}

QMap<QString, QVariant> Model::computePropsMap(Model &model)
{
    QMap<QString, QVariant> propsMap;
    const auto &properties = MetaClassParser(this, true).getAllPropertiesNames();

    for(const auto &propName : properties)
    {
        const auto &prop = model.findProperty(propName);
        const auto &value = prop.read(&model);

        if(!value.isValid())
        {
            qDebug() << "**** Error *****";
            qDebug() << "Model::computePropsMap: propName invalid: " << propName;
            qDebug() << "***************";
        }

        propsMap[propName] = value;
    }

    return propsMap;
}

void Model::setCreatedDt(const QDateTime &dt)
{
    if(dt != getCreatedDt())
    {
        createdDateTime = dt.toString(dtFormat);

        createdDateTimeChanged();
    }
}

void Model::setLastModifiedDt(const QDateTime &dt)
{
    if(dt != getLastModifiedDt())
    {
        lastModifiedDateTime = dt.toString(dtFormat);

        lastModifiedDateTimeChanged();
    }
}

CWF_END_NAMESPACE
