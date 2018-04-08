#ifndef HELLOMODEL_H
#define HELLOMODEL_H

#include <QObject>

class HelloModel : public QObject
{
    Q_OBJECT
public slots:
    QString greeting() const
    {
        return "Hello User!";
    }
};

#endif // HELLOMODEL_H
