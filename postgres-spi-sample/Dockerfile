FROM postgres:latest

RUN apt-get update

# for build
RUN apt-get install -y bash git curl swig strace make clang llvm gcc

# mecab
RUN apt-get install -y mecab libmecab-dev mecab-ipadic-utf8

# postgresql dev
RUN apt-get -y install wget postgresql-server-dev-12

COPY . /tmp

RUN cd /tmp \
     && make \
     && make install
