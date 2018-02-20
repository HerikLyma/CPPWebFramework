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
     static QString extract(QString &name, char ch);
     inline static QString fileName(QString &name) { return extract(name, '/'); }
     inline static QString fileExtention(QString &name) { return extract(name, '.'); }
     static void removeLastBar(QString &path);
     static void removeFirstBar(QString &path);
     static void putFirstBar(QString &path);
     static QByteArray readAll(const QString &fileName, QFileDevice::FileError &fileErro);
     static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

CWF_END_NAMESPACE

#endif // FILEMANAGER_H
