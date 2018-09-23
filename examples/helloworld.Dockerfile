FROM imacellone/cwf

LABEL maintainer="imacellone <italomacellone@gmail.com>"

COPY HelloWorldDocker /HelloWorldDocker

WORKDIR /HelloWorldDocker

RUN qmake HelloWorldDocker.pro
RUN make

ENTRYPOINT [ "/HelloWorldDocker/HelloWorldDocker" ]

EXPOSE 80