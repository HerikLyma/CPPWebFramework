#include "cstlcompilerimport.h"
#include "configuration.h"
#include "filemanager.h"

namespace CWF
{
    extern Configuration configuration;

    CSTLCompilerImport::CSTLCompilerImport(const QXmlStreamAttributes &attr)
    {
        int size = attr.size();
        if(size == 0)
        {
            attributes.insert("error", "***ERROR IMPORT TAG - IMPORT TAG NEEDS THE URL ATTRIBUTE***");
        }
        else if(size == 1)
        {
             QString name(std::move(attr[0].name().toString().toLower()));
             QString value(std::move(attr[0].value().toString()));

             if(name != "url")
             {
                 attributes.insert("error", "***ERROR IMPORT TAG - IMPORT TAG NEEDS THE URL ATTRIBUTE***");
             }
             else
             {
                 QString fileName(std::move(configuration.getPath()));
                 FileManager fileManager;
                 fileManager.removeLastBar(fileName);

                 fileName += value;

                 QFile::FileError fileError;
                 attributes.insert("url", fileManager.readAll(fileName, fileError));
             }
        }
        else
        {
            attributes.insert("error", "***ERROR IMPORT TAG - IMPORT TAG ONLY NEEDS THE URL ATTRIBUTE***");
        }
    }
}
