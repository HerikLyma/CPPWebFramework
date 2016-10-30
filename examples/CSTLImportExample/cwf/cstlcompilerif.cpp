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
        {
            relationalOperator = RelationalOperator::ERROR;
            attributes.insert("error", "***ERROR IF TAG - IF TAG NEEDS TWO ATTRIBUTES ***");
        }
        else if(size == 2)
        {
            for(int i = 0; i < size; ++i)
            {
                QString name(std::move(attr[i].name().toString().toLower()));
                QString value(std::move(attr[i].value().toString()));
                if(name == "var")
                {
                    attributes.insert("var", value);
                }
                else
                {
                    if(name == "equal")
                    {
                        relationalOperator = RelationalOperator::EQUAL;
                    }
                    else if(name == "different")
                    {
                        relationalOperator = RelationalOperator::DIFFERENT;
                    }
                    else if(name == "greater")
                    {
                        relationalOperator = RelationalOperator::GREATER;
                    }
                    else if(name == "greater_equal")
                    {
                        relationalOperator = RelationalOperator::GREATER_EQUAL;
                    }
                    else if(name == "less")
                    {
                        relationalOperator = RelationalOperator::LESS;
                    }
                    else if(name == "less_equal")
                    {
                        relationalOperator = RelationalOperator::LESS_EQUAL;
                    }
                    else
                    {
                        relationalOperator = RelationalOperator::ERROR;
                        attributes.insert("error", "***ERROR IF TAG - IF TAG DOESN'T PERMITS AN ATTRIBUTE CALLED \"" + name + "\"***");
                        break;
                    }

                    value.toDouble(&isNumber);
                    attributes.insert("condition", value);
                }
            }
        }
        else if(size > 2)
        {
            relationalOperator = RelationalOperator::ERROR;
            attributes.insert("error", "***ERROR IF TAG - IF TAG DOESN'T PERMITS MORE THAN ONE ATTRIBUTE ***");
        }
    }
}
