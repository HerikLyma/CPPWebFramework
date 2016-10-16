/**
  @file forattributes.h
  @author Herik Lima
*/

#include "forattributes.h"

namespace CWF
{
    ForAttributes::ForAttributes(const QXmlStreamAttributes &attributes)
    {
        for(int i = 0; i < attributes.size(); ++i)
        {
            QString name(attributes[i].name().toString().toLower());
            QString value(attributes[i].value().toString().replace("#{", "").replace("}", ""));
            if(name == "items")
            {
                items = value;
            }
            else if(name == "var")
            {
                var = value;
            }
            else if(name == "from")
            {
                from = value;
            }
            else if(name == "to")
            {
                to = value;
            }
            else if(name == "increment")
            {
                increment = value;
            }
            else
            {
                error = "***ERROR FOR TAG - FOR TAG DOESN'T PERMITS AN ATTRIBUTE CALLED " + attributes[i].name().toString() + "***";
                return;
            }
        }
        if(items.isEmpty() || var.isEmpty())
        {
            bool from, to, increment;
            this->from.toInt(&from);
            this->to.toInt(&to);
            this->increment.toInt(&increment);

            if(!(from && to && increment) || var.isEmpty())
            {
                error = "***ERROR FOR TAG - USE THE CORRECT ATTRIBUTES (FROM, TO, INCREMENT, VAR OR ITEMS, VAR)***";
            }
        }
    }
}
