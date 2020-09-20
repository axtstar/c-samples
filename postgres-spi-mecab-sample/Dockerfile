FROM postgres:latest

RUN apt-get update

# for build
RUN apt-get install -y make clang llvm gcc git curl sudo

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

# neologd
RUN cd /tmp \
     && git clone --depth 1 https://github.com/neologd/mecab-ipadic-neologd.git \
     && cd mecab-ipadic-neologd \
     && yes yes | ./bin/install-mecab-ipadic-neologd -n

