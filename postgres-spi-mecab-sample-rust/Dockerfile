FROM postgres:12

RUN apt-get update

# for build
RUN apt-get install -y make clang llvm gcc

# mecab
RUN apt-get install -y mecab libmecab-dev mecab-ipadic-utf8

# postgresql dev
RUN apt-get -y install postgresql-server-dev-12

# for python
RUN apt-get install -y postgresql-plpython3-12

COPY . /tmp

RUN cd /tmp \
     && make \
     && make install
