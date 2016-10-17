/**
  @file filemanager.h
  @author Herik Lima
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>

namespace CWF
{
    /**
     * @brief The FileManager class can manage file's name.
     */
    class FileManager
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
}
#endif // FILEMANAGER_H
