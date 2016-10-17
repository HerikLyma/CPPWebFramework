[!Language (C++)](https://img.shields.io/badge/powered_by-C++-red.svg?style=flat-square)
[![Github Issues](https://img.shields.io/github/issues/nlohmann/json.svg)](https://github.com/HerikLyma/CPPWebFramework/issues)
[![Travis-CI](https://travis-ci.org/HerikLyma/CPPWebFramework.svg?branch=master)](https://travis-ci.org/HerikLyma/CPPWebFramework)

# C++ Web Framework

The C++ Web Framework is a framework created in C++ with Qt for use in developing applications for the Web.

Steps:

1º: Download and install Qt Creator: https://www.qt.io/download-open-source/

2º: Install Qt Libraries: sudo apt-get install qt5-default

3º: Make a project clone: git clone https://github.com/HerikLyma/CPPWebFramework.git

4º: Open the CPPWebFramework.pro file using Qt Creator

5º: Change the path in the main.cpp file: CWF::CppWebApplication a(argc, argv, CWF::Configuration("/home/MYNAME/CPPWebFramework/CPPWebFramework/server/"));

6º: Change the path in the CPPWeb.ini file: path=/home/MYNAME/CPPWebFramework/CPPWebFramework/server/

7º: Run the project

8º: Open your browser and type: http://127.0.0.1:8080
