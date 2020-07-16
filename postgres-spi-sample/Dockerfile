FROM postgres:11-alpine

RUN apk add --update bash git curl build-base swig gfortran linux-headers strace libc6-compat clang llvm postgresql-dev postgresql-libs


RUN cd /tmp \
    && git clone https://github.com/taku910/mecab.git \
    && cd mecab/mecab/ \
    && ./configure --enable-utf8-only --with-charset=utf8 \
    && make \
    && make install \
    && cd ../mecab-ipadic \
    && ./configure --with-charset=utf8 \
    && make \
    && make install

RUN apk add wget
COPY . /tmp/
RUN cd /tmp \
     && tar zxfv mecab-ipadic-2.7.0-20070801.tar.gz \
     && cd mecab-ipadic-2.7.0-20070801 \
     && ./configure --enable-utf8-only --with-charset=utf8 \
     && make \
     && make install

RUN cd /tmp \
     && make \
     && make install
