/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "filemanager.h"

CWF_BEGIN_NAMESPACE

QString FileManager::extract(QString &name, char ch) const
{
    QString fName;
    for(int i = (name.size() - 1); i >= 0 ; --i)
    {
        if(name[i] == ch)
            break;
        fName.push_front(name[i]);
    }
    return fName;
}

QString FileManager::fileName(QString &name) const
{
    return extract(name, '/');
}

QString FileManager::fileExtention(QString &name) const
{
    return extract(name, '.');
}

void FileManager::removeLastBar(QString &path) const
{
    if(path.endsWith("/"))
        path.remove(path.length() - 1, 1);
}

void FileManager::removeFirstBar(QString &path) const
{
    if(path.startsWith("/"))
        path.remove(0, 1);
}

void FileManager::putFirstBar(QString &path)  const
{
    if(!path.startsWith("/"))
        path.push_front("/");
}

QByteArray FileManager::readAll(const QString &fileName, QFile::FileError &fileErro)  const
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileErro = file.error();
        return file.errorString().toLatin1();
    }
    return file.readAll();
}

CWF_END_NAMESPACE
