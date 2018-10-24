/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "filemanager.h"
#include <QDir>

CWF_BEGIN_NAMESPACE

QString FileManager::extract(QString &name, char ch)
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

void FileManager::removeLastBar(QString &path)
{
    if(path.endsWith("/"))
        path.remove(path.length() - 1, 1);
}

void FileManager::removeFirstBar(QString &path)
{
    if(path.startsWith("/"))
        path.remove(0, 1);
}

void FileManager::putFirstBar(QString &path)
{
    if(!path.startsWith("/"))
        path.push_front("/");
}

QByteArray FileManager::readAll(const QString &fileName, QFile::FileError &fileErro)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileErro = file.error();
        return file.errorString().toLatin1();
    }
    return file.readAll();
}

bool FileManager::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists())
    {
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList(sourceDir.entryInfoList());
    for(const QFileInfo &fileInfo : fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
        {
            continue;
        }
        if(fileInfo.isDir())
        {
            if(!copyDirectoryFiles(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()), coverFileIfExist))
            {
                return false;
            }
        }
        else
        {
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName()))
            {
                targetDir.remove(fileInfo.fileName());
            }
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}

CWF_END_NAMESPACE
