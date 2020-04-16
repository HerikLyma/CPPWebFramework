[![GitHub issues](https://img.shields.io/github/issues/HerikLyma/CPPWebFramework.svg)](https://github.com/HerikLyma/CPPWebFramework/issues)
[![Travis-CI](https://travis-ci.org/HerikLyma/CPPWebFramework.svg?branch=master)](https://travis-ci.org/HerikLyma/CPPWebFramework)
[![Build status](https://ci.appveyor.com/api/projects/status/d8u7th2wl1qro6m2?svg=true)](https://ci.appveyor.com/project/HerikLyma/cppwebframework)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/8b818182369744f0af42a52785f7b5fe)](https://www.codacy.com/app/HerikLyma/CPPWebFramework?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=HerikLyma/CPPWebFramework&amp;utm_campaign=Badge_Grade)
[![Language (C++)](https://img.shields.io/badge/powered_by-C++-green.svg?style=flat-square)](https://isocpp.org/)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/HerikLyma/CPPWebFramework/blob/master/LICENSE.txt)


# C++ Web Framework (CWF)



​The C++ Web Framework (CWF) is a MVC web framework, Open Source, under <a href="https://github.com/HerikLyma/CPPWebFramework/blob/master/LICENSE.txt">MIT License</a>, using C++ with Qt to be used in the development of web applications. The CWF was designed to consume few computational resources, such as memory and processing, and have a low response time for requests. 
With MVC (Model-View-Controller) architecture, where you can create classes to take care of the business layer (Model), use CSTL (C++ Server Pages Standard Tag Library) within the Web Pages 
to take care of data presentation (View) and use the controllers as a between the two layers (Controller). The CWF had inspirations in Java Servlets, JSTL and Spring Framework.

​
Because it is created in Qt, the C++ Web Framework can run on the same platforms supported by Qt:

<ul>
    <li><b>Desktop:</b> Linux, OS X, Windows</li>
    <li><b>Embedded and RTOS:</b> Linux, QNX, VxWorks, Windows</li>
    <li><b>Mobile:</b> Android, iOS, Windows</li>
</ul>


The CWF has only one configuration file, called CPPWeb.ini and a policy of using only C++ and Qt in the development of its components in order to avoid the installation of numerous libraries and conflicts, maintain multiplatform characteristics, facilitate installation and keep the learning curve low in order to make web development as simple as possible, even for beginners.



<hr/><b>Hello World - Example</b></br></br>

```cpp
#include "cppwebapplication.h"

class HelloWorldController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        response.write("<html><body>Hello World!</body></html>");
    }
};

//Call
//http://localhost:8080/hello
int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/PATH_TO_EXAMPLE/server/");
    server.addController<HelloWorldController>("/hello");
    return server.start();
}
```

<hr/><b>MVC (Model-View-Controller) - Example</b></br></br>

```cpp
//hellomodel.h (Model)
#include <QObject>

class HelloModel : public QObject
{
    Q_OBJECT
public slots:
    QString greeting() const
    {
        return "Hello User!";
    }
};

//helloview.view (View)
<html>
    <head>
        <title>Hello</title>
    </head>
    <body>
        <out value="#{model.greeting}"/>
    </body>
</html>

//hellocontroller.h (Controller)
#include <cwf/controller.h>
#include <model/hellomodel.h>

class HelloController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        HelloModel model;
        request.addAttribute("model", &model);
        request.getRequestDispatcher("/pages/helloview.view").forward(request, response);
    }
};

//main.cpp
#include <cwf/cppwebapplication.h>
#include <controller/hellocontroller.h>

//Call
//http://localhost:8080/hello
int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/PATH_TO_EXAMPLE/server/");
    server.addController<HelloController>("/hello");
    return server.start();
}
```

<hr/><b>REST Web Service - Example</b></br></br>

```cpp
#include <cwf/sqlquery.h>
#include <cwf/cppwebapplication.h>
#include <cwf/sqldatabasestorage.h>

/* 
 * SQL Script
 * create table countries (co_id serial primary key, co_name varchar unique);
 * insert into countries (co_name) values ('BRAZIL'), ('UNITED STATES OF AMERICA'), ('CANADA');
 */

CWF::SqlDatabaseStorage storage("QPSQL", "localhost", "postgres", "postgres", "1234", 5432);

class CountriesController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        CWF::SqlQuery qry(storage);
        qry.exec("select * from countries");
        response.write(qry.toJson());
    }
};

//Call
//http://localhost:8080/countries
int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "/PATH_TO_EXAMPLE/server/");
    server.addController<CountriesController>("/countries");
    return server.start();
}
```

<hr/><b>ORM (Object Relational Mapper) - Experimental - Example</b></br></br>

```cpp
#include <usermodel.h>
#include <cwf/cppwebapplication.h>
#include <cwf/sqldatabasestorage.h>
/*
* ORM (Experimental) - Tested only on PostgreSQL
*/
CWF::SqlDatabaseStorage conexao("QPSQL", "localhost", "postgres", "postgres", "1234", 5432);

class ORMController : public CWF::Controller
{
public:
    void doGet(CWF::Request &request, CWF::Response &response) const override
    {
        UserModel user{conexao};
        user.setName("Herik Lima");
        user.setPhone("+55 11 9 99999-0000");
        user.setCountry("Brazil");
        user.setState("São Paulo");
        response.write(QByteArray("<html><body>") + (user.save() ? "Saved" : "Error") + "</body></html>");
    }
};
//Call
//http://localhost:8080/orm
int main(int argc, char *argv[])
{        
    CWF::CppWebApplication server(argc, argv, "/home/herik/CPPWebFramework/examples/ORM/server");
    UserModel{conexao}.updateDB();//Create or update the table in database
    server.addController<ORMController>("/orm");
    return server.start();
}

//usermodel.h
#ifndef USERMODEL_H
#define USERMODEL_H

#include <cwf/model.h>

class UserModel : public CWF::Model
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString phone READ getPhone WRITE setPhone)
    Q_PROPERTY(QString country READ getCountry WRITE setCountry)
    Q_PROPERTY(QString state READ getState WRITE setState)
    QString name;
    QString phone;
    QString country;
    QString state;
public:
    explicit UserModel(CWF::SqlDatabaseStorage &connection) : CWF::Model(connection, "usuario") {}
public slots:
    QString getName() const { return name; }
    void setName(const QString &value) { name = value; }
    QString getPhone() const { return phone; }
    void setPhone(const QString &value) { phone = value; }
    QString getCountry() const { return country; }
    void setCountry(const QString &value) { country = value; }
    QString getState() const { return state; }
    void setState(const QString &value) { state = value; }
};

#endif // USERMODEL_H

```


</br><hr/><b>Installation</b></br>
<ol>
    <li>Download and install Qt 5.9 or higher: https://www.qt.io/download-open-source/</li>
    <li>Open the terminal</li>
    <li>Install Qt Libraries: sudo apt-get install qt5-default (Linux)</li>
    <li>Make a project clone: git clone https://github.com/HerikLyma/CPPWebFramework.git</li>
    <li>cd CPPWebFramework/CPPWebFramework</li>
    <li>qmake CPPWebFramework.pro</li>
    <li>make</li>
    <li>make install (use sudo on Linux)</li>
</ol><hr/>

<b>jemalloc optional installation (recommended)</b></br>
<ol>
    <li>Install jemalloc: sudo apt-get install libjemalloc-dev (linux)</li>
    <li>Enable jemalloc in the .pro file: LIBS += -ljemalloc</li>
</ol><hr/>

<b>Steps to test the C++ Web Framework's examples</b></br>
<ol>
    <li>Open a .pro file from an example using Qt Creator</li>
    <li>Change the path in the main.cpp file: CWF::CppWebApplication a(argc, argv, "/PATH_TO_EXAMPLE/server/");</li>
    <li>Run the project</li>
    <li>Open your browser and type: http://localhost:8080 to check if the server is online</li>
</ol><hr/>

<b>Steps to test the C++ Web Framework's HelloWorldDocker example with Docker containers</b></br>
<ol>
    <li>Install Docker</li>
    <li>sudo docker run -d -p 80:80 imacellone/cwf-helloworld:1.0</li>
    <li>Open your browser and type: http://localhost to check if the server is online</li>
    <li>If you want to test your own examples, please follow the steps demonstrated on the CPPWebFramework/examples/helloworld.Dockerfile file, build and run the image.</li>
</ol>
<hr/>
<b>cppwebframework mailing list:</b> https://groups.google.com/forum/#!forum/cppwebframework <br>
<b>Videos:</b> https://www.youtube.com/channel/UCf-Jt44A1k-PQ6z_mhN2GYQ
