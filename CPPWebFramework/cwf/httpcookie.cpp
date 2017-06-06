#include "httpcookie.h"
#include "constants.h"

CWF_BEGIN_NAMESPACE

HttpCookie::HttpCookie(const QByteArray &source)
{
   QList<QByteArray> list(std::move(splitCSV(source)));
   for(QByteArray &current : list)
   {
       QByteArray name;
       QByteArray value;
       int position = current.indexOf('=');
       if(position)
       {
           name  = current.left(position).trimmed();
           value = current.mid(position + 1).trimmed();
       }
       else
       {
           name = current.trimmed();
           value = "";
       }

       if(name == COOKIE::COMMENT)
       {
           comment = value;
       }
       else if(name == COOKIE::DOMAIN_COOKIE)
       {
           domain = value;
       }
       else if(name == COOKIE::MAX_AGE)
       {
           maxAge = value.toInt();
       }
       else if(name == COOKIE::PATH)
       {
           path = value;
       }
       else if(name == COOKIE::SECURE)
       {
           secure = true;
       }
       else if(name == COOKIE::VERSION)
       {
           version = value.toInt();
       }
       else
       {
           if (this->name.isEmpty())
           {
               this->name  = name;
               this->value = value;
           }
           else
           {
               qDebug() << "HttpCookie: Ignoring unknown " << name.data() << "=" << value.data();
           }
       }
   }
}

HttpCookie::HttpCookie(const QByteArray &name, const QByteArray &value) : name(name), value(value)
{
}

QByteArray HttpCookie::toByteArray() const
{
   QByteArray buffer(name);
   buffer.append('=');
   buffer.append(value);
   if(!comment.isEmpty())
   {
       buffer.append("; Comment=");
       buffer.append(comment);
   }
   if(!domain.isEmpty())
   {
       buffer.append("; Domain=");
       buffer.append(domain);
   }
   if(maxAge != 0)
   {
       buffer.append("; Max-Age=");
       buffer.append(QByteArray::number(maxAge));
   }
   if(!path.isEmpty())
   {
       buffer.append("; Path=");
       buffer.append(path);
   }
   if(secure)
   {
       buffer.append("; Secure");
   }
   buffer.append("; Version=");
   buffer.append(QByteArray::number(version));
   return buffer;
}

void HttpCookie::setName(const QByteArray &name)
{
   this->name = name;
}

void HttpCookie::setValue(const QByteArray &value)
{
   this->value = value;
}

void HttpCookie::setComment(const QByteArray &comment)
{
   this->comment = comment;
}

void HttpCookie::setDomain(const QByteArray &domain)
{
   this->domain = domain;
}

void HttpCookie::setMaxAge(int maxAge)
{
   this->maxAge = maxAge;
}

void HttpCookie::setPath(const QByteArray &path)
{
   this->path = path;
}

void HttpCookie::setSecure(bool secure)
{
   this->secure = secure;
}

QByteArray HttpCookie::getName() const
{
   return name;
}

QByteArray HttpCookie::getValue() const
{
   return value;
}

QByteArray HttpCookie::getComment() const
{
   return comment;
}

QByteArray HttpCookie::getDomain() const
{
   return domain;
}

int HttpCookie::getMaxAge() const
{
   return maxAge;
}

QByteArray HttpCookie::getPath() const
{
   return path;
}

bool HttpCookie::getSecure() const
{
   return secure;
}

int HttpCookie::getVersion() const
{
   return version;
}

QList<QByteArray> HttpCookie::splitCSV(const QByteArray &source)
{
   bool inString = false;
   QList<QByteArray> list;
   QByteArray buffer;
   int size = source.size();
   for(int i = 0; i < size; ++i)
   {
       char c = source.at(i);
       if(inString==false)
       {
           if(c == '\"')
           {
               inString=true;
           }
           else if(c == ';')
           {
               QByteArray trimmed(std::move(buffer.trimmed()));
               if (!trimmed.isEmpty())
               {
                   list.append(trimmed);
               }
               buffer.clear();
           }
           else
           {
               buffer.append(c);
           }
       }
       else if(c == '\"')
       {
           inString = false;
       }
       else
       {
           buffer.append(c);
       }
   }
   QByteArray trimmed(std::move(buffer.trimmed()));
   if(!trimmed.isEmpty())
   {
       list.append(trimmed);
   }
   return list;
}

CWF_END_NAMESPACE
