
> sudo apt-get install postgresql
> sudo apt-get install postgresql-common
> sudo apt install postgresql-server-dev-all
> sudo apt install postgresql-server-dev-10
> sudo apt-get install libpq-dev
> sudo apt-get install libc6

> gcc -o server_version server_version.c -I/usr/include/postgresql -lpq -std=c99

> gcc -o aaa sample.c -I /usr/include/postgresql/10/server -I/usr/include/postgresql -lpq -std=c99