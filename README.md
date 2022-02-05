# tuxapp
Tuxedo to Enduro/X migration demo application


This is sample project which demonstrates Oarcle Tuxedo to Enduro/X migration process

* Tuxedo install path: /opt/tuxedo12.2.2.0.0 (see tux.env)
* Oracle DB setting (common.env)
* Prapre DB users according to src/tlogsv/README

To build Tuxedo version:

* Install Tuxedo accordingly
* Then:

    $ . tux.env
    $ cd src
    $ make

To build Enduro/X version:
* Install Enduro/X accordingly
* Then:
    $ . ex.env
    $ cd src
    $ make

![Application diagram](doc/program.drawio.png?raw=true "Application diagram")
