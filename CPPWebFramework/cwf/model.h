#ifndef MODEL_HH
#define MODEL_HH

#include "sqlquery.h"
#include "modelbasicoperation.h"

#include <memory>
#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>

CWF_BEGIN_NAMESPACE

/**
 * @brief The Model class implements basic ORM features and should be used as base class for every model (or entity).
 *
 * The class allows any derived model to be saved, retrieved or deleted from the database in very direct fashion
 * (see the example below). By default, the class contains three properties that should not be overriden:
 * - id : The id of the model. Its value is -1 when it the model is created or when the model could not be loaded from the database.
 * - createdDateTime : The date at which the model was first created.
 * - lastModifiedDateTime : The latest date at which the model was modified.
 * These properties will be added to every model.
 *
 * Each model is represented by a table in the database which is identical to the name of the model.
 *
 * A typical model is defined as:
 *
 * ```cpp
 * class UserModel : public Model
 * {
 *    Q_OBJECT
 *
 *    Q_PROPERTY(QString email MEMBER email NOTIFY emailChanged)
 *
 *    public:
 *      UserModel() : Model("user") // Name of the model and database table
 *      {

 *      }
 *      ~UserModel() override;
 *
 *    signals:
 *      void emailChanged();
 *
 *    private:
 *      QString email;
 * }
 * ```
 *
 * And can be used in a controller with:
 * ```cpp
 * // Create an empty instance of your model
 * MyModel myModel;
 *
 * // Set some values
 * myModel.setEmail(myEmail);
 *
 * // Save it in the database
 * myModel.save();
 *
 * // Get the database id of the model just persisted.
 * int myModelId = myModel.getId();
 *
 * // Create another instance
 * MyModel myModel2;
 *
 * // Load the first instance data from the database
 * myModel2.build(myModelId); // We use the id of the first instance
 *
 * // Check the object was loaded
 * if(!myModel2.getWasBuild() )
 * {
 *      // Error: it was not loaded for some reason...
 * }
 *
 * // Delete the object from the database
 * myModel2.remove();
 * ```
 */
class CPPWEBFRAMEWORKSHARED_EXPORT Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint64 id MEMBER id NOTIFY idChanged)
    Q_PROPERTY(QString createdDateTime MEMBER createdDateTime NOTIFY createdDateTimeChanged)
    Q_PROPERTY(QString lastModifiedDateTime MEMBER lastModifiedDateTime NOTIFY lastModifiedDateTimeChanged)

public:
    /**
      * @brief Constructor
     */
    Model(const QString &name) : name(name) {}
    /**
      * @brief Destructor
      */
    virtual ~Model() = default;
    /**
     * @brief updateDB Will create or update the database schema to match the model class.     
     * This allows to create a working table from scratch or to update one. Note that a table update can add new
     * fields (Qt properties in the model code) but cannot remove any. Therefore, a developer should only add new
     * properties to a model and never remove one.
     */
    void updateDB();
    /**
     * @brief build Populate the model with data from the database.
     * @param id The id of the data to be used to populate the model.
     */
    void build(const qint64& id);
    /**
     * @brief build Populate the model with data from the database.
     * @param selectCondition A map ([propertyName] = propertyValue) of property values
     * used to choose which data to insert in the model.
     *
     * The first entry of database table that matchs all the property values will be used to populate the model.
     */
    void build(const QMap<QString, QVariant> &selectCondition);
    /**
     * @brief buildFromJson Populate a model from json data
     * @param json The data used to populate the model instance
     * @param withTableNamePrefix Are the date properties prefixed with the name of this model db table ? This is false by default.
     */
    void buildFromJson(const QJsonObject &json, bool withTableNamePrefix = false);
    /**
     * @brief save Persist the model in the database
     * @return Bool: Was the model correctly persisted ?
     */
    bool save();
    /**
     * @brief remove Delete the model from the database
     * @return Bool: Was the data removed without error ?
     */
    bool remove();
    /**
     * @brief setCreatedDt Manually set the creation date
     * @param dt Date of the model first save into the database.
     */
    void setCreatedDt(const QDateTime& dt);
    /**
     * @brief setLastModifiedDt Set the last date at which the model was persisted in the database.
     * @param dt The date to be used.
     */
    void setLastModifiedDt(const QDateTime& dt);
    /**
     * @brief setWasBuild Set the "was build" flag that indicate if a model instance was correctly populated (build) by data.
     * @param b The flag.
     */
    void setWasBuild(bool b) { built = b;}

    /**
     * @brief getWasBuild Get the value of the "was build" flag.
     * @return Bool: Was the model instance populated by data from the database ?
     */
    bool getWasBuild() const { return built; }

    /**
     * @brief getId Get the id of the model
     * @return qint64: The id of the model
     */
    const qint64& getId() const { return id; }

    /**
     * @brief getCreatedDt Get the creation date of the model
     * @return QDateTime: Creation date
     */
    QDateTime getCreatedDt() const;

    /**
     * @brief getCreatedDtStr Get the creation date as a string
     * @return QString: Creation date as a string
     */
    QString getCreatedDtStr() const;

    /**
     * @brief getLastModifiedDt Get the last date at which the model was modified and persisted in the database
     * @return QDateTime: Last modified and persisted date
     */
    QDateTime getLastModifiedDt() const;

    /**
     * @brief getLastModifiedDtStr Get the last date at which the model was modified and persisted in the database
     * @return QString: Last modified and persisted date as a string
     */
    QString getLastModifiedDtStr() const;

    /**
     * @brief getTableName The name of database table corresponding to the model
     * @return QString: Name of database table and of the model
     */
    const QString& getTableName() const { return name; }

    /**
     * @brief findProperty Find a property with its name
     * @param propertyName The name of the property
     * @return QMetaProperty: The property object
     */
    QMetaProperty findProperty(const QString& propertyName) const;

    /**
     * @brief propertyType Find the type of a property value from the property name
     * @param propertyName The name of the property
     * @return QVariant::Type: Type of the property
     */
    QVariant::Type propertyType(const QString& propertyName) const;

    /**
     * @brief computePropsMap Iterate on all the model properties to insert them in a map
     * @param m The model that should be used (it often is "*this")
     * @return QMap<QString, QVariant>: A map of all the model properties
     */
    QMap<QString, QVariant> computePropsMap(const Model& m) const;

    /**
     * @brief listAllProperties Iterate on all the model properties to insert their names in a list
     * @return QStringList: A list of all the model properties
     */
    QStringList listAllProperties() const;

    /**
     * @brief toJson Convert the model data (its property name and value pairs) in JSON format
     * @return QJsonObject: A JSON version of the model
     */
    QJsonObject toJson() const;

signals:
    void idChanged();
    void createdDateTimeChanged();
    void lastModifiedDateTimeChanged();

protected:
    ModelBasicOperation basicOperation;

    /**
     * @brief preSaveCheck Perform some checks before persisting (saving) the model instance.
     * The persisting is done only if the checks where successful.
     * @return Bool: Was the check successful ?
     */
    virtual bool preSaveCheck() const;
    /**
     * @brief customizeField Allow to give special instructions when a field is created in the database.
     */
    virtual void customizeField(const QString &fieldName,
                                const QVariant::Type &type,
                                const QString &tableName
                                ) const = 0;

private:
    QString name; ///< @brief name The name of the model
    /**
     * @brief id The database id of the model
     * The id is set to -1 by default. It may change if the model was populated with data from the database (the id will become the one
     * of the entity stored in the database) or if a user manually set the variable before.
     */
    qint64 id = -1;

    qint64 version; ///< @brief The version of the table (database side)
    bool built = false; ///< @brief Was the model instance populated with data ?

    QString dtFormat = "dd/MM/yyyy hh:mm:ss.zzz"; ///< @brief Format of the date used in this class
    QString createdDateTime; ///< @brief First save in the database date
    QString lastModifiedDateTime; ///< @brief Last modified and persisted date

    void verifyDbTableExist(); ///< @brief Check the database contains table corresponding to this model. Also create or update the table if needed.
    void verifyDbFields(); ///< @brief Check the database table contains all required fields (columns). If not, create them.
};

CWF_END_NAMESPACE

#endif // MODEL_HH
