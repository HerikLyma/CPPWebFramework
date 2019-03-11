#include "model.h"

CWF_BEGIN_NAMESPACE

Model::Model(const QString &name) : QObject(nullptr)
{
    m_name = name;
}

Model::~Model()
{

}

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

    QMap<QString, QVariant> propValueMap = m_basicOperation.build(m_name, selectCondition, properties);

    // Loop on all the prop value to update the current object
    for(const auto& it : propValueMap.toStdMap() )
    {
        setProperty(it.first.toStdString().c_str(), it.second);
    }

    // Depending on the content of propValueMap, we set the built flag to true or false.
    // If the db query failed then the list is empty here.
    if(propValueMap.empty() )
        m_built = false;
    else
        m_built = true;
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
            m_built = false;
            break;
        }

        QVariant value = jsonValue.toVariant();

        bool success = setProperty(prop.toStdString().c_str(), value);

        if(!success)
        {
            m_built = false;
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
    if(m_id == -1)
    {
        this->setProperty("createdDateTime", currentDt.toString(m_dtFormat) );
        setCreatedDt(currentDt);
    }

    // Modification
    this->setProperty("lastModifiedDateTime", currentDt.toString(m_dtFormat) );
    setLastModifiedDt(currentDt);

    // --------------------------------------------------

    // Save the model in the db

    // Second, Get the values of all the properties and create a map
    // [propertyName] = QVariant
    // We will give this map to the sql helper that will save the model in the db

    QMap<QString, QVariant> propsMap = computePropsMap(*this);

    qint64 id = m_basicOperation.save(m_name, propsMap);

    setProperty("id", id);

    if(id == -1)
        return false;
    else
        return true;
}

bool Model::remove()
{
    const qint64& id = getId();

    return m_basicOperation.remove(getTableName(), id);
}

QString Model::getCreatedDtStr() const
{
    return m_createdDateTime;
}

QDateTime Model::getCreatedDt() const
{
    return QDateTime::fromString(m_createdDateTime, m_dtFormat);
}

QDateTime Model::getLastModifiedDt() const
{
    return QDateTime::fromString(m_lastModifiedDateTime, m_dtFormat);
}

QString Model::getLastModifiedDtStr() const
{
    return m_lastModifiedDateTime;
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
    bool tableExistInDb = m_basicOperation.isTableInDb(m_name);

    if(!tableExistInDb)
    {
       bool success = m_basicOperation.createTable(m_name);

       if(success)
       {
           qInfo() << "Model::verifyDbTableExist:" << "Table " << m_name << " was successfuly created";
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
    QStringList fieldsFromDb = m_basicOperation.fields(m_name);

    // Loop on all the fields of the object and check if they are in the database
    for(const QString& fieldName : fieldsFromObject)
    {
        bool existInDb = fieldsFromDb.contains(fieldName);

        if(!existInDb)
        {
            // The field is not present in the db and we need to add it

            qInfo() << "Model::verifyDbFields:"<< "In" << m_name
                     << "the field" << fieldName << "is present in the object but was not found in database."
                     << "We update the database."
                        ;

            // We will change the db
            dbChangedPerformed = true;

            QVariant::Type propertyType = this->propertyType(fieldName);

            m_basicOperation.addFieldToTable(fieldName, propertyType, m_name);

            customizeField(fieldName, propertyType, m_name);
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
        qInfo() << "The database was modified to update the table" << m_name << "."
                << "We will update the version for this table."
                ;

        qint32 tableVersion = m_basicOperation.tableVersion(m_name);
        tableVersion += 1;
        m_basicOperation.changeTableVersion(m_name, tableVersion);
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
        QString msg = QString("") + "Model::findProperty:" + " The property " + propertyName + " was not found in " + m_name;
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
        m_createdDateTime = dt.toString(m_dtFormat);

        createdDateTimeChanged();
    }
}

void Model::setLastModifiedDt(const QDateTime &dt)
{
    if(dt != getLastModifiedDt() )
    {
        m_lastModifiedDateTime = dt.toString(m_dtFormat);

        lastModifiedDateTimeChanged();
    }
}

CWF_END_NAMESPACE
