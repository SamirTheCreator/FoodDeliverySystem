# FoodDeliverySystem
Linux Desktop Application. OS Project

## Configuration
Set up environment for build running `./scripts/setenv.sh`

## Build
Build project with `make all` or `make` command

## Run
Run server application `./build/server [PORT] [IPv4]`
- `[PORT]` - optional host port number by default 8080
- `[IPv4]` - optional host IP address by default 127.0.0.1

Run client application `./build/client [PORT] [IPv4]`
- `[PORT]` - optional server port number by default 8080
- `[IPv4]` - optional server IP address by default 127.0.0.1

#### Example
Run server and client with no arguments on single machine:
`./build/server`
`./build/client`

To reveal host IPv4 use command:
`hostname -I`

Run server and client on different machines:
`./build/server 8080 $(hostname -I)`
`./build/client 8080 <SERVER_IPv4>`
- `<SERVER_IPv4>` is printed as server runs

##### Test
Test phone and password: +998999686868 password
