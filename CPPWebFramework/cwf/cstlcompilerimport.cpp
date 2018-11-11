/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cstlcompilerimport.h"
#include "configuration.h"
#include "filemanager.h"
#include "constants.h"

CWF_BEGIN_NAMESPACE

CSTLCompilerImport::CSTLCompilerImport(const QXmlStreamAttributes &attr, QString path)
{
    int size = attr.size();
    if(size == 0)
    {
        attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IMPORT TAG - IMPORT TAG NEEDS THE URL ATTRIBUTE***");
    }
    else if(size == 1)
    {
         QString name(attr[0].name().toString().toLower());
         QString value(attr[0].value().toString());

         if(name != CSTL::TAG::PROPERTY::IMPORT::URL)
         {
             attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IMPORT TAG - IMPORT TAG NEEDS THE URL ATTRIBUTE***");
         }
         else
         {
             CWF::FileManager::removeLastBar(path);

             path += value;

             QFile::FileError fileError;
             attributes.insert(CSTL::TAG::PROPERTY::IMPORT::URL, CWF::FileManager::readAll(path, fileError));
         }
    }
    else
    {
        attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IMPORT TAG - IMPORT TAG ONLY NEEDS THE URL ATTRIBUTE***");
    }
}

CWF_END_NAMESPACE
