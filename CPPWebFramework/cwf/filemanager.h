/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>
#include "cppwebframework_global.h"

CWF_BEGIN_NAMESPACE
/**
 * @brief The FileManager class can manage file's name.
 */
class CPPWEBFRAMEWORKSHARED_EXPORT FileManager
{
public:
     QString extract(QString &name, char ch) const;
     QString fileName(QString &name) const;
     QString fileExtention(QString &name) const;
     void removeLastBar(QString &path) const;
     void removeFirstBar(QString &path) const;
     void putFirstBar(QString &path) const;
     QByteArray readAll(const QString &fileName, QFileDevice::FileError &fileErro) const;
};

CWF_END_NAMESPACE

#endif // FILEMANAGER_H
