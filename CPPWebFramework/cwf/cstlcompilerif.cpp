/*
 Copyright 2017 Herik Lima de Castro and Marcelo Medeiros Eler
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

#include "cstlcompilerif.h"
#include "constants.h"

CWF_BEGIN_NAMESPACE

CSTLCompilerIf::CSTLCompilerIf(const QXmlStreamAttributes &attr)
{
    int size = attr.size();
    if(size == 0 || size == 1)
    {
        relationalOperator = RelationalOperator::ERROR;
        attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IF TAG - IF TAG NEEDS TWO ATTRIBUTES ***");
    }
    else if(size == 2)
    {
        for(int i = 0; i < size; ++i)
        {
            QString name(std::move(attr[i].name().toString().toLower()));
            QString value(std::move(attr[i].value().toString()));
            if(name == CSTL::TAG::PROPERTY::VAR)
            {
                attributes.insert(CSTL::TAG::PROPERTY::VAR, value);
            }
            else
            {
                if(name == CSTL::TAG::PROPERTY::IF::EQUAL)
                {
                    relationalOperator = RelationalOperator::EQUAL;
                }
                else if(name == CSTL::TAG::PROPERTY::IF::DIFFERENT)
                {
                    relationalOperator = RelationalOperator::DIFFERENT;
                }
                else if(name == CSTL::TAG::PROPERTY::IF::GREATER)
                {
                    relationalOperator = RelationalOperator::GREATER;
                }
                else if(name == CSTL::TAG::PROPERTY::IF::GREATER_EQUAL)
                {
                    relationalOperator = RelationalOperator::GREATER_EQUAL;
                }
                else if(name == CSTL::TAG::PROPERTY::IF::LESS)
                {
                    relationalOperator = RelationalOperator::LESS;
                }
                else if(name == CSTL::TAG::PROPERTY::IF::LESS_EQUAL)
                {
                    relationalOperator = RelationalOperator::LESS_EQUAL;
                }
                else
                {
                    relationalOperator = RelationalOperator::ERROR;
                    attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IF TAG - IF TAG DOESN'T PERMITS AN ATTRIBUTE CALLED \"" + name + "\"***");
                    break;
                }

                value.toDouble(&isNumber);
                attributes.insert(CSTL::TAG::PROPERTY::CONDITION, value);
            }
        }
    }
    else if(size > 2)
    {
        relationalOperator = RelationalOperator::ERROR;
        attributes.insert(CSTL::TAG::PROPERTY::ERROR, "***ERROR IF TAG - IF TAG DOESN'T PERMITS MORE THAN ONE ATTRIBUTE ***");
    }
}

CWF_END_NAMESPACE
