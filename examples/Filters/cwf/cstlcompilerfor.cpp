/**
  @file cstlcompilerfor.cpp
  @author Herik Lima
*/

#include "cstlcompilerfor.h"

namespace CWF
{
    CSTLCompilerFor::CSTLCompilerFor(const QXmlStreamAttributes &attr)
    {
        for(int i = 0; i < attr.size(); ++i)
        {
            QString name(attr[i].name().toString().toLower());
            QString value(attr[i].value().toString());
            if(name != "items" && name != "var" && name != "from" &&
               name != "to" && name != "increment")
            {
                attributes.insert("error", "***ERROR FOR TAG - FOR TAG DOESN'T PERMITS AN ATTRIBUTE CALLED " + name + "***");
                return;
            }
            attributes.insert(name, value);
        }
        if(!attributes.contains("items") || !attributes.contains("var"))
        {
            bool from, to, increment;
            attributes["from"].toInt(&from);
            attributes["to"].toInt(&to);
            attributes["increment"].toInt(&increment);

            if(!(from && to && increment) || !attributes.contains("var"))
            {
                attributes.insert("error", "***ERROR FOR TAG - USE THE CORRECT ATTRIBUTES (FROM, TO, INCREMENT, VAR OR ITEMS, VAR)***");
            }
        }
    }
}
