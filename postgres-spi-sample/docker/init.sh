#!/bin/sh
echo '************************init start***************************'
echo $dynamic_library_path 
# http://pgsql-jp.github.io/current/html/runtime-config-client.html#GUC-DYNAMIC-LIBRARY-PATH
export dynamic_library_path=/usr/local/lib/postgresql:/usr/local/lib/
echo $dynamic_library_path
echo '************************init   end***************************'
