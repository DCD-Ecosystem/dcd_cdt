---
content_title: Binary Releases
---

DCD.CDT currently supports Mac OS X brew, Linux x86_64 Debian packages, and Linux x86_64 RPM packages.

**If you have previously installed DCD.CDT, run the `uninstall` script (it is in the directory where you cloned DCD.CDT) before downloading and using the binary releases.**

## Mac OS X Brew Install

```sh
brew tap dcd/dcd.cdt
brew install dcd.cdt
```

## Mac OS X Brew Uninstall

```sh
brew remove dcd.cdt
```

## Debian Package Install

```sh
wget https://github.com/DCD/dcd.cdt/releases/download/v1.8.1/dcd.cdt_1.8.1-ubuntu-18.04_amd64.deb
sudo apt install ./dcd.cdt_1.8.1-ubuntu-18.04_amd64.deb
```

## Debian Package Uninstall

```sh
sudo apt remove dcd.cdt
```

## RPM Package Install

```sh
wget https://github.com/DCD/dcd.cdt/releases/download/v1.8.1/dcd.cdt-1.8.1.el7.x86_64.rpm
sudo yum install ./dcd.cdt-1.8.1.el7.x86_64.rpm
```

## RPM Package Uninstall

```sh
sudo yum remove dcd.cdt
```

# Guided Installation or Building from Scratch

```sh
git clone --recursive https://github.com/dcd/dcd.cdt
cd dcd.cdt
mkdir build
cd build
cmake ..
make -j8
```

From here onward you can build your contracts code by simply exporting the `build` directory to your path, so you don't have to install globally (makes things cleaner).
Or you can install globally by running this command

```sh
sudo make install
```

## Uninstall after manual installation

```sh
sudo rm -fr /usr/local/dcd.cdt
sudo rm -fr /usr/local/lib/cmake/dcd.cdt
sudo rm /usr/local/bin/dcd-*
```

# Installed Tools

* dcd-cpp
* dcd-cc
* dcd-ld
* dcd-init
* dcd-abidiff
* dcd-wasm2wast
* dcd-wast2wasm
* dcd-ranlib
* dcd-ar
* dcd-objdump
* dcd-readelf

The following tools are not installed after brew install, you get them when you build the repository and install it from scratch, [see here](#guided-installation-or-building-from-scratch):

* dcd-abidiff
* dcd-ranlib
* dcd-ar
* dcd-objdump
* dcd-readelf

License
[MIT](../LICENSE)
