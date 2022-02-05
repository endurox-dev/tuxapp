# tuxapp
Tuxedo to Enduro/X migration demo application


This is sample project which demonstrates Oarcle Tuxedo to Enduro/X migration process

* Tuxedo install path: /opt/tuxedo12.2.2.0.0 (see tux.env)
* Oracle DB setting (common.env)
* Prapre DB users according to src/tlogsv/README
* Demo is prepared on Centos 8 Linux, Oracle XE 18 database used

# Building

## Tuxeod version

To build Tuxedo version:

* Install Tuxedo accordingly
* Then:

```
    $ . tux.env
    $ cd src
    $ make clean
    $ make
```

## Enduro/X version

To build Enduro/X version:
* Install Enduro/X accordingly:
*   Download RPM from https://www.mavimax.com/downloads 
*   Install RPM e.g. $ sudo rpm -i endurox-8.0.4-1.oracleserver8_0_GNU_epoll.x86_64.rpm
*   Configure system limits according to https://www.endurox.org/dokuwiki/doku.php?id=endurox:v8.0.x:guides:ex_adminman chapter "2.2. Linux setup"
* Then:

```
    $ . ex.env
    $ cd src
    $ make clean
    $ make
```

# Running 

## Tuxedo version

```
    $ . tux.env
    $ cd conf
    -- See "README" for details to create TLOG device & QSPACE for first time
    $ tmloadcf -b 30000 ubbconfig -y
    $ tmboot -y
    $ txgencl
    -- Check databases:
    $ sqlplus1
    SQL> select count(*) from tlog;
    $ sqlplus2
    SQL> select count(*) from tlog;
```

## Enduro/X version

This includes migration step - ubbex for converting Tuxedo configuration to Enduro/X format:

```
    $ . ex.env
    $ cd conf
    -- Convert Tuxedo config to Enduro/X, first time:
    $ ubb2ex ubbconfig
    $ . setmach1
    $ xadmin start -y
    $ txgencl
    -- Check databases:
    $ sqlplus1
    SQL> select count(*) from tlog;
    $ sqlplus2
    SQL> select count(*) from tlog;
```

![Application diagram](doc/program.drawio.png?raw=true "Application diagram")
