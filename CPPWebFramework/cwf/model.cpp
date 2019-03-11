#include "model.h"

CWF_BEGIN_NAMESPACE

void Model::updateDB()
{
    // ****************************************************************
    // Check the table corresponding to the model exists in the DB
    // ****************************************************************
    //
    // If it does not exist then we create it.

    verifyDbTableExist();

    // ****************************************************************
    // Check the table has the correct fields
    // ****************************************************************

    verifyDbFields();

    // ****************************************************************
}

void Model::build(const qint64 &id)
{
    QMap<QString, QVariant> cond;
    cond.insert("id", QVariant::fromValue(id) );

    build(cond);
}

void Model::build(const QMap<QString, QVariant> &selectCondition)
{
    // Get the data from the db and populate the model with them

    QStringList properties = listAllProperties();

    QMap<QString, QVariant> propValueMap = basicOperation.build(name, selectCondition, properties);

    // Loop on all the prop value to update the current object
    for(const auto& it : propValueMap.toStdMap() )
    {
        setProperty(it.first.toStdString().c_str(), it.second);
    }

    // Depending on the content of propValueMap, we set the built flag to true or false.
    // If the db query failed then the list is empty here.
    if(propValueMap.empty() )
        built = false;
    else
        built = true;
}

void Model::buildFromJson(const QJsonObject &json, bool withTableNamePrefix)
{
    QStringList props = listAllProperties();

    // Loop on all props
    for(const QString& prop : props)
    {
        QString propName;

        if(withTableNamePrefix)
            propName = getTableName() + "_" + prop;
        else
            propName = prop;

        const QJsonValue& jsonValue = json.value(propName);

        if(jsonValue.isUndefined() )
        {
            built = false;
            break;
        }

        QVariant value = jsonValue.toVariant();

        bool success = setProperty(prop.toStdString().c_str(), value);

        if(!success)
        {
            built = false;
            break;
        }
    }
}

bool Model::save()
{
    // Go through the pre-save check before saving
    bool proceed = preSaveCheck();

    // Quit the function if precheck failed
    if(!proceed)
    {
        return false;
    }

    // --------------------------------------------------
    // Set the createdDateTime and lastModifiedDateTime
    // --------------------------------------------------

    QDateTime currentDt = QDateTime::currentDateTime();

    // Creation of a new object
    if(id == -1)
    {
        this->setProperty("createdDateTime", currentDt.toString(dtFormat) );
        setCreatedDt(currentDt);
    }

    // Modification
    this->setProperty("lastModifiedDateTime", currentDt.toString(dtFormat) );
    setLastModifiedDt(currentDt);

    // --------------------------------------------------

    // Save the model in the db

    // Second, Get the values of all the properties and create a map
    // [propertyName] = QVariant
    // We will give this map to the sql helper that will save the model in the db

    QMap<QString, QVariant> propsMap = computePropsMap(*this);

    qint64 id = basicOperation.save(name, propsMap);

    setProperty("id", id);

    if(id == -1)
        return false;
    else
        return true;
}

bool Model::remove()
{
    const qint64& id = getId();

    return basicOperation.remove(getTableName(), id);
}

QString Model::getCreatedDtStr() const
{
    return createdDateTime;
}

QDateTime Model::getCreatedDt() const
{
    return QDateTime::fromString(createdDateTime, dtFormat);
}

QDateTime Model::getLastModifiedDt() const
{
    return QDateTime::fromString(lastModifiedDateTime, dtFormat);
}

QString Model::getLastModifiedDtStr() const
{
    return lastModifiedDateTime;
}

QStringList Model::listAllProperties() const
{
    QStringList properties;

    const QMetaObject* metaObject = this->metaObject();

    // Add the properties of the current object and of its QObject parents
    do {
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
        {
            QString propertyName = QString::fromLatin1(metaObject->property(i).name() );

            // We ignore 'objectName' since it is a qt-only flag
            if(propertyName != "objectName")
                properties.push_back(QString::fromLatin1(metaObject->property(i).name() ) );
        }

        // Return nullptr if there is no base class
        metaObject = metaObject->superClass();
    }
    while(metaObject != nullptr);

    return properties;
}

QJsonObject Model::toJson() const
{
    return QJsonObject::fromVariantMap(computePropsMap(*this) );
}

bool Model::preSaveCheck() const
{
    return true;
}

void Model::verifyDbTableExist()
{
    bool tableExistInDb = basicOperation.isTableInDb(name);

    if(!tableExistInDb)
    {
       bool success = basicOperation.createTable(name);

       if(success)
       {
           qInfo() << "Model::verifyDbTableExist:" << "Table " << name << " was successfuly created";
       }
    }
}

void Model::verifyDbFields()
{
    // Flag used to detect if we performed a change in the database
    bool dbChangedPerformed = false;

    // Get all the fields of the object in the code
    QStringList fieldsFromObject = listAllProperties();

    // Then get all the fields of the object that are stored in the db
    QStringList fieldsFromDb = basicOperation.fields(name);

    // Loop on all the fields of the object and check if they are in the database
    for(const QString& fieldName : fieldsFromObject)
    {
        bool existInDb = fieldsFromDb.contains(fieldName);

        if(!existInDb)
        {
            // The field is not present in the db and we need to add it

            qInfo() << "Model::verifyDbFields:"<< "In" << name
                     << "the field" << fieldName << "is present in the object but was not found in database."
                     << "We update the database."
                        ;

            // We will change the db
            dbChangedPerformed = true;

            QVariant::Type propertyType = this->propertyType(fieldName);

            basicOperation.addFieldToTable(fieldName, propertyType, name);

            customizeField(fieldName, propertyType, name);
        }
    }

    // Security loop to check no field is missing
    for(const QString& fieldName : fieldsFromDb)
    {
        if(!fieldsFromObject.contains(fieldName) )
        {
            qDebug() << "Model::verifyDbFields: The field "<<fieldName << "was present in the DB and not in the object."
                     << "It was probably deleted from the object property recently. "
                        "This is forbidden: a property should never be deleted because of db consistency"
                        ;
            qFatal("A property saved in the database was deleted");
        }
    }

    // If we performed a change in the db
    if(dbChangedPerformed)
    {
        qInfo() << "The database was modified to update the table" << name << "."
                << "We will update the version for this table."
                ;

        qint32 tableVersion = basicOperation.tableVersion(name);
        tableVersion += 1;
        basicOperation.changeTableVersion(name, tableVersion);
    }
}

QMetaProperty Model::findProperty(const QString &propertyName) const
{
    const QMetaObject* metaObject = this->metaObject();

    QMetaProperty property;
    bool found = false;

    // Add the properties of the current object and of its QObject parents
    do {
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
        {
            QString propName = QString::fromLatin1(metaObject->property(i).name() );

            if(propName == propertyName)
            {
                found = true;
                property = metaObject->property(i);
            }
        }

        if(!found)
            // Return nullptr if there is no base class
            metaObject = metaObject->superClass();
    }
    while(!found && metaObject != nullptr);

    if(!found)
    {
        QString msg = QString("") + "Model::findProperty:" + " The property " + propertyName + " was not found in " + name;
        qDebug() << msg;
        qFatal("Property should always be found here");
    }

    return property;
}

QVariant::Type Model::propertyType(const QString &propertyName) const
{
    QMetaProperty property = findProperty(propertyName);

    QVariant::Type type = property.type();

    return type;
}

QMap<QString, QVariant> Model::computePropsMap(const Model& m) const
{
    // First, list all the properties of the model
    QStringList properties = m.listAllProperties();

    // Second, Get the values of all the properties and create a map
    // [propertyName] = QVariant
    // We will give this map to the sql helper that will save the model in the db

    QMap<QString, QVariant> propsMap;

    // Loop on all the properties to save their value in a map
    // [propName] = value
    for(const QString& propName : properties)
    {
        QMetaProperty prop = m.findProperty(propName);
        QVariant value = prop.read(&m);

        if(!value.isValid())
        {
            qDebug() << "**** Error *****";
            qDebug() << "Model::computePropsMap: propName invalid: "<<propName;
            qDebug() << "***************";
        }

        propsMap[propName] = value;
    }

    return propsMap;
}

void Model::setCreatedDt(const QDateTime &dt)
{
    if(dt != getCreatedDt() )
    {
        createdDateTime = dt.toString(dtFormat);

        createdDateTimeChanged();
    }
}

void Model::setLastModifiedDt(const QDateTime &dt)
{
    if(dt != getLastModifiedDt() )
    {
        lastModifiedDateTime = dt.toString(dtFormat);

        lastModifiedDateTimeChanged();
    }
}

CWF_END_NAMESPACE
