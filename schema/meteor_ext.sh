#!/bin/bash

DB_NAME=$1
echo $DB_NAME 
DB_USER=${2:-postgres}
echo $DB_USER

cd ./librandgeneration &&
    ./build-aux/autogen.sh &&
    ./configure --libdir=`pg_config --pkglibdir` &&
    make &&
    sudo make install &&

cd ../

echo -n enter $DB_USER Database password:
read -s dbpassword
echo $dbpassword
psql -f ./meteor_rand_ext.sql -U $DB_USER -W $dbpassword --dbname=$DB_NAME
