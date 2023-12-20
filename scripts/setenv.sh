#!/bin/bash

sudo echo -n "Setting up environment"; sleep 1; echo -n '.';
sleep 1; echo -n '.'; sleep 1; echo -n '.'; sleep 1; echo '';
sudo apt update && sudo apt upgrade

apt list --installed | grep -q libgtk-3-0
if [ $? -ne 0 ]; then
	sudo apt install libgtk-3-0 libgtk-3-dev
fi

apt list --installed | grep -q libgtk-3-dev
if [ $? -ne 0 ]; then
	sudo apt install libgtk-3-dev
fi

if [ ! $(which make) ]; then
	sudo apt install make
fi

if [ ! $(which gcc) ]; then
	sudo apt install gcc
fi

if [ ! $(which pkg-config) ]; then
	sudo apt install pkg-config
fi

if [ ! $(which mysql) ]; then
	sudo apt install mysql-server libmysqlclient-dev
fi

if [ $(echo $PWD | rev | cut -f1 -d/ | rev) = "scripts" ]; then
	cd ..
fi

if [ ! -f "./mysql/setDB.sql" -a -f "./mysql/DDL.sql" -a -f "./mysql/fillDB.sql" ]; then
	echo "Database configuration: SQL files in '../mysql/' were not found"
	exit 1
fi

sudo mysql <<< exit 2>/dev/null
if [ $? -ne 0 ]; then
	echo -n "Enter MySQL server password for root: "
	read password
	mysqladmin -uroot -p"$password" password '' 2>/dev/null
	if [ $? -ne 0 ];
	then
		echo "Database configuration: Wrong password"
		echo "Database configuration failed"
		exit 1
	fi
fi

sudo mysql <./mysql/setDB.sql
mysql -uroot -p1234 Foodle_DB <./mysql/DDL.sql 2>/dev/null
mysql -uroot -p1234 Foodle_DB <./mysql/fillDB.sql 2>/dev/null

echo "Environment is configured"

exit 0

