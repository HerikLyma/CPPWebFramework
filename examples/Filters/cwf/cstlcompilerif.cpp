/**
  @file cstlcompilerif.cpp
  @author Herik Lima
*/

#include "cstlcompilerif.h"

namespace CWF
{
    CSTLCompilerIf::CSTLCompilerIf(const QXmlStreamAttributes &attr)
    {
        int size = attr.size();
        if(size == 0 || size == 1)
            attributes.insert("error", "***ERROR IF TAG - IF TAG NEEDS TWO ATTRIBUTES ***");
        else if(size == 2)
        {
            for(int i = 0; i < size; ++i)
            {
                QString name(attr[i].name().toString().toLower());
                QString value(attr[i].value().toString());
                if(name == "var")
                    attributes.insert(name, value);
                else if(name == "equal")
                    attributes.insert(name, value);
                else
                    attributes.insert("error", "***ERROR IF TAG - IF TAG DOESN'T PERMITS AN ATTRIBUTE CALLED \"" + name + "\"***");
            }
        }
        else if(size > 2)
            attributes.insert("error", "***ERROR IF TAG - IF TAG DOESN'T PERMITS MORE THAN ONE ATTRIBUTE ***");
    }
}
