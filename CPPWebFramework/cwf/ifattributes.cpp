/**
  @file ifattributes.cpp
  @author Herik Lima
*/

#include "ifattributes.h"

namespace CWF
{
    IfAttributes::IfAttributes(const QXmlStreamAttributes &attributes)
    {
        int total = 0;
        for(int i = 0; i < attributes.size(); ++i)
        {
            QString name(attributes[i].name().toString().toLower());
            QString value(attributes[i].value().toString().replace("#{", "").replace("}", ""));
            if(name == "var")
            {
                ++total;
                var = value;
            }
            else if(name == "equal")
            {
                ++total;
                equal = value;
            }
            else if(name == "notequal")
            {
                ++total;
                notEqual = value;
            }
            else if(name == "greater")
            {
                ++total;
                greater = value;
            }
            else if(name == "greaterequal")
            {
                ++total;
                greaterEqual = value;
            }
            else if(name == "less")
            {
                ++total;
                less = value;
            }
            else if(name == "lessequal")
            {
                ++total;
                lessEqual = value;
            }
            else
            {
                error = "***ERROR FOR TAG - FOR TAG DOESN'T PERMITS AN ATTRIBUTE CALLED " + attributes[i].name().toString() + "***";
                return;
            }
            if(total > 2)
            {
                error = "***ERROR FOR TAG - MORE THAN ONE CONDITION SPECIFIED ***";
                return;
            }
        }

        if(total < 2)
        {
            error = "***ERROR FOR TAG - VAR AND OPERATOR IS NEEDED ***";
            return;
        }

        if(!equal.isEmpty())
        {
            condition = var == equal;
        }
        else if(!notEqual.isEmpty())
        {
            condition = var != notEqual;
        }
        else if(!greater.isEmpty())
        {
            condition = var > greater;
        }
        else if(!greaterEqual.isEmpty())
        {
            condition = var >= greaterEqual;
        }
        else if(!less.isEmpty())
        {
            condition = var < less;
        }
        else if(!lessEqual.isEmpty())
        {
            condition = var <= lessEqual;
        }
    }
}
