[![GitHub issues](https://img.shields.io/github/issues/HerikLyma/CPPWebFramework.svg)](https://github.com/HerikLyma/CPPWebFramework/issues)
[![Travis-CI](https://travis-ci.org/HerikLyma/CPPWebFramework.svg?branch=master)](https://travis-ci.org/HerikLyma/CPPWebFramework)
[![Language (C++)](https://img.shields.io/badge/powered_by-C++-green.svg?style=flat-square)](https://img.shields.io/badge/powered_by-C++-green.svg?style=flat-square)

# C++ Web Framework

The C++ Web Framework (CWF) is a web framework, under <a href="https://github.com/HerikLyma/CPPWebFramework/blob/master/LICENSE.txt">MIT license</a>, created by Herik Lima and Marcelo Eler, 
using C++ with Qt to be used in the development of web applications, having been heavily inspired by Java Servlets,
JavaServer Pages Standard Tag Library (JSTL), designed to consume few computational resources such as 
memory and processing and, a low response time for requests while keeping the presentation and the 
business layer separated through the C++ Server Pages Standard Tag Library (CSTL). 
Because it is created in Qt, the C++ Web Framework can run on the same platforms supported by Qt:
<ul>
    <li><b>Desktop:</b> Linux, OS X, Windows</li>
    <li><b>Embedded and RTOS:</b> Linux, QNX, VxWorks, Windows</li>
    <li><b>Mobile:</b> Android, iOS, Windows</li>
</ul>
This web framework has a simplified set of classes and only one configuration file, called CPPWeb.ini,
to make web development as simple as possible, even for developers starting in the web development world.</br></br>
<b>Steps to test the C++ Web Framework's examples:</b>
<ol>
	<li>Download and install Qt Creator: https://www.qt.io/download-open-source/</li>
	<li>Install Qt Libraries: sudo apt-get install qt5-default</li>
	<li>Make a project clone: git clone https://github.com/HerikLyma/CPPWebFramework.git</li>
	<li>Open the CPPWebFramework.pro file using Qt Creator</li>
	<li>Change the path in the main.cpp file: CWF::CppWebApplication a(argc, argv, CWF::Configuration("/home/MYNAME/CPPWebFramework/CPPWebFramework/server/"));</li>
	<li>Change the path in the CPPWeb.ini file: path=/home/MYNAME/CPPWebFramework/CPPWebFramework/server/</li>
	<li>Run the project</li>
	<li>Open your browser and type: http://127.0.0.1:8080</li>
</ol>
<b>Documentation:</b> http://www.cppwebframework.com <br>
<b>Videos:</b> https://www.youtube.com/channel/UCf-Jt44A1k-PQ6z_mhN2GYQ

