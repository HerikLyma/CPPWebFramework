/**
  @file cstlcompiler.cpp
  @author Herik Lima
*/

#include "cstlcompiler.h"
#include "cstlcompilerattributes.h"
#include "cstlcompilerfor.h"
#include "cstlcompilerobject.h"
#include "cstlcompilerif.h"
#include "cstlcompilerimport.h"

namespace CWF
{
    CSTLCompiler::CSTLCompiler(const QByteArray &str,
                               QMap<QString, QObject *> &objects,
                               bool isStrFileName) : str(str),
                                                     objects(objects),
                                                     isStrFileName(isStrFileName)
    {
    }

    QByteArray CSTLCompiler::openFile(QXmlStreamReader &xml)
    {
        if(isStrFileName)
        {
            QFile file(str);
            if(!file.open(QIODevice::ReadOnly))
                return "<html><body>" + file.errorString().toLatin1() + "</body></html>";
            QByteArray content(std::move(file.readAll()));
            file.close();
            xml.addData(content);
        }
        else
        {
            xml.addData(str);
        }

        if (xml.hasError())
            return "<html><body>XML ERROR: " + xml.errorString().toLatin1() + "</body></html>";
        return "";
    }

    QByteArray CSTLCompiler::processOutTag(QMap<QString, QString> &attr)
    {
        int size = attr.size();
        if(size < 1)
            return "";
        else if(size > 1)
            return "***ERROR - OUT TAG DOES NOT HAS MORE THAN PROPERTY***";

        return CSTLCompilerAttributes(objects).buildAttributes(attr, false).toLatin1();
    }

    QByteArray CSTLCompiler::getBody(QXmlStreamReader &xml, const QString &tagName)
    {
        QByteArray name, text, content("<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n");
        QString att;
        CSTLCompilerAttributes compilerAttributes(objects);
        QMap<QString, QString> attributes;
        QMap<QString, QString>::iterator it;

        xml.readNext();
        while(!xml.atEnd())
        {
            name = xml.name().toLatin1().toLower();
            text = xml.text().toLatin1();

            if(xml.isStartElement())
            {
                attributes = std::move(compilerAttributes.getAttributes(xml.attributes()));
                for(it = attributes.begin(); it != attributes.end(); ++it)
                    att += " " + it.key() + "=\"" + it.value() + "\"";
                content += "<" + name + att + ">" + text;
                attributes.clear();
                att.clear();
            }
            else if(xml.isEndElement() && name == tagName)
                break;
            else if(xml.isEndElement())
                content += text + "</" + name + ">";
            else
                content += text;
            xml.readNext();
        }
        return content;
    }

    QByteArray CSTLCompiler::processForTag(QXmlStreamReader &xml)
    {
        const QString tagName("for");
        QByteArray htmlOut;
        CSTLCompilerFor forAttributes(xml.attributes());
        CSTLCompilerAttributes compilerAttributes(objects);


        if(forAttributes.attributes.contains("error"))
        {
            getBody(xml, tagName);
            htmlOut = forAttributes.attributes["error"].toLatin1();
        }
        else
        {            
            QString items(forAttributes.attributes["items"]);
            items.replace("#{", "").replace("}", "");
            if(objects.contains(items))
            {                
                QObject *object = (QObject*)objects[items];
                QString type(object->metaObject()->className());

                if(!items.isEmpty())
                {
                    if(type != "CWF::QListObject")
                    {
                        htmlOut = "***ERROR - " + type.toLatin1() + " ISN'T A CWF::QListObject***";
                        getBody(xml, tagName);
                    }
                    else
                    {
                        QListObject *qListObject = (QListObject*)object;
                        QString ret(std::move(getBody(xml, tagName)));
                        QString var(forAttributes.attributes["var"]);
                        var.replace("#{", "").replace("}", "");
                        for(int iL = 0; iL < qListObject->size(); ++iL)
                        {                            
                            objects.insert(var, qListObject->operator [](iL) );
                            QXmlStreamReader forBody(ret);
                            htmlOut += processXml(forBody);
                            objects.remove(var);
                        }
                    }
                }
            }
            else
            {
                int from      = forAttributes.attributes["from"].toInt();
                int to        = forAttributes.attributes["to"].toInt();
                int increment = forAttributes.attributes["increment"].toInt();
                QString tagBody(std::move(getBody(xml, tagName)));
                QString &var = forAttributes.attributes["var"];
                for(int i = from; i <= to; i += increment)
                {                    
                    QString copy(tagBody);
                    CSTLCompilerObject obj;
                    obj.setValue(QString::number(i));
                    objects.insert(var, &obj);

                    copy.replace("<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>", "");
                    QString outPutText;
                    compilerAttributes.compile(copy, outPutText);
                    copy = "<out>" + outPutText + "</out>";
                    copy = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>" + copy;

                    QXmlStreamReader forBody(copy);
                    htmlOut += processXml(forBody);
                    objects.remove(var);
                }
            }                
        }
        return htmlOut;
    }

    QByteArray CSTLCompiler::processIfTag(QXmlStreamReader &xml)
    {
        const QString tagName("if");
        QByteArray htmlOut;
        CSTLCompilerIf ifAttributes(xml.attributes());

        if(ifAttributes.relationalOperator == RelationalOperator::ERROR)
        {
            getBody(xml, tagName);
            htmlOut = ifAttributes.attributes["error"].toLatin1();
        }
        else
        {
            QString var(ifAttributes.attributes["var"]), condition(ifAttributes.attributes["condition"]);
            CSTLCompilerObject conditionObj, varObj;
            bool removeVar = false, removeCondition = false;
            if(!objects.contains(var))
            {
                removeVar = true;
                varObj.setValue(var);
                objects.insert(var, &varObj);
            }
            if(!objects.contains(condition))
            {
                removeCondition = true;
                conditionObj.setValue(condition);
                objects.insert(condition, &conditionObj);
            }

            CSTLCompilerAttributes compilerAttributes(objects);
            QString tagBody(std::move(getBody(xml, tagName)));
            compilerAttributes.compileAttributes(ifAttributes.attributes);

            bool isTrue = false;

            if(ifAttributes.relationalOperator == RelationalOperator::EQUAL)
            {
                isTrue = ifAttributes.attributes["var"] == ifAttributes.attributes["condition"];
            }
            else if(ifAttributes.relationalOperator == RelationalOperator::DIFFERENT)
            {
                isTrue = ifAttributes.attributes["var"] != ifAttributes.attributes["condition"];
            }
            else if(ifAttributes.relationalOperator == RelationalOperator::GREATER)
            {
                if(ifAttributes.isNumber)
                {
                    isTrue = ifAttributes.attributes["var"].toDouble() > ifAttributes.attributes["condition"].toDouble();
                }
                else
                {
                    isTrue = ifAttributes.attributes["var"] > ifAttributes.attributes["condition"];
                }
            }
            else if(ifAttributes.relationalOperator == RelationalOperator::GREATER_EQUAL)
            {
                if(ifAttributes.isNumber)
                {
                    isTrue = ifAttributes.attributes["var"].toDouble() >= ifAttributes.attributes["condition"].toDouble();
                }
                else
                {
                    isTrue = ifAttributes.attributes["var"] >= ifAttributes.attributes["condition"];
                }
            }
            else if(ifAttributes.relationalOperator == RelationalOperator::LESS)
            {
                if(ifAttributes.isNumber)
                {
                    isTrue = ifAttributes.attributes["var"].toDouble() < ifAttributes.attributes["condition"].toDouble();
                }
                else
                {
                    isTrue = ifAttributes.attributes["var"] < ifAttributes.attributes["condition"];
                }
            }
            else if(ifAttributes.relationalOperator == RelationalOperator::LESS_EQUAL)
            {
                if(ifAttributes.isNumber)
                {
                    isTrue = ifAttributes.attributes["var"].toDouble() <= ifAttributes.attributes["condition"].toDouble();
                }
                else
                {
                    isTrue = ifAttributes.attributes["var"] <= ifAttributes.attributes["condition"];
                }
            }

            if(isTrue)
            {
                if(!tagBody.contains("<") || !tagBody.contains("</"))
                {
                    tagBody.replace("<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>", "");
                    QString outPutText;
                    compilerAttributes.compile(tagBody, outPutText);
                    tagBody = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?><out>" + outPutText + "</out>";
                }
                QXmlStreamReader forBody(tagBody);
                htmlOut += processXml(forBody);
            }

            if(removeVar)
                objects.remove(var);
            if(removeCondition)
                objects.remove(condition);
        }
        return htmlOut;
    }

    QByteArray CSTLCompiler::processXml(QXmlStreamReader &xml)
    {
        QByteArray htmlOut;
        while(!xml.atEnd())
        {
            CSTLCompilerAttributes compilerAttributes(objects);
            QString name(std::move(xml.name().toString().toLower()));
            QString text(std::move(xml.text().toString()));
            QString tagAttributes;
            QMap<QString, QString> attr;

            if(name == "out" && xml.isStartElement())
            {
                attr = std::move(compilerAttributes.getAttributes(xml.attributes()));
                htmlOut += processOutTag(attr);
                name.clear();
            }
            else if(name == "for" && xml.isStartElement())
            {
                htmlOut += processForTag(xml);
                name.clear();
            }
            else if(name == "if" && xml.isStartElement())
            {
                htmlOut += processIfTag(xml);
                name.clear();
            }
            else if(name == "import" && xml.isStartElement())
            {
                CSTLCompilerImport importUrl(xml.attributes());
                if(!importUrl.attributes.contains("error"))
                    htmlOut += importUrl.attributes["url"].toLatin1();
                else
                    htmlOut += importUrl.attributes["error"].toLatin1();
                name.clear();

            }
            else
            {
                if(name != "out" && name != "if" && name != "for")
                {
                    attr = std::move(compilerAttributes.getAttributes(xml.attributes()));
                    tagAttributes = compilerAttributes.buildAttributes(attr);
                    if(xml.isStartElement())
                        name = "<" + name + tagAttributes + ">";
                    else if(xml.isEndElement())
                        name = "</" + name + ">";
                }
                else
                {
                    name.clear();
                }
            }

            //process(text, number);
            htmlOut += name + text;
            xml.readNext();
            if(xml.hasError())
            {
                return "<html><body>XML ERROR: " + xml.errorString().toLatin1() + "</body></html>";
            }
        }
        return htmlOut;
    }

    QByteArray CSTLCompiler::output()
    {
        QXmlStreamReader xml;
        QByteArray htmlOutput(std::move(openFile(xml)));
        if(htmlOutput.isEmpty())
            return processXml(xml);
        return htmlOutput;
    }
}
