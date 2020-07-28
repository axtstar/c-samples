FROM postgres:latest

RUN apt-get update

# for build
RUN apt-get install -y make clang llvm gcc

# postgresql dev
RUN apt-get -y install postgresql-server-dev-12

COPY . /tmp

RUN cd /tmp \
     && make \
     && make install
