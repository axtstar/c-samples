FROM postgres:12

RUN apt-get update

# for build
RUN apt-get install -y make clang llvm llvm-dev libclang-dev gcc git curl sudo

# mecab
RUN apt-get install -y mecab libmecab-dev mecab-ipadic-utf8

# postgresql dev
RUN apt-get -y install postgresql-server-dev-12

# for python
RUN apt-get install -y postgresql-plpython3-12

COPY . /work

RUN cd /work \
     && make \
     && make install

# neologd
RUN cd /work \
     && git clone --depth 1 https://github.com/neologd/mecab-ipadic-neologd.git \
     && cd mecab-ipadic-neologd \
     && yes yes | ./bin/install-mecab-ipadic-neologd -n

# rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | bash -s -- -y
RUN echo 'source $HOME/.cargo/env' >> $HOME/.bashrc

RUN cargo install bindgen

# for argo-pgx
RUN cargo install rustfmt

RUN apt-get install pkg-config libreadline-dev zlib1g-dev
RUN apt-get install libssl-dev
RUN cargo install cargo-pgx

WORKDIR /work