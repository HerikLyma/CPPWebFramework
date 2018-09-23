FROM ubuntu:16.04

LABEL maintainer="imacellone <italomacellone@gmail.com>"

RUN apt update
RUN apt install build-essential -y
RUN apt install qt5-default -y

COPY ./CPPWebFramework /CPPWebFramework

WORKDIR /CPPWebFramework

RUN qmake CPPWebFramework.pro
RUN make -j8
RUN make install