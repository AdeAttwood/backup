# Project Title

One Paragraph of project description goes here

### Prerequisities

The programme is made with QT C++ famework.

For development install QT
https://www.qt.io/download/

For instalation the depencys need for debian are: 

libqt5core5a
libc6
libstdc++6
libc6
libgcc1
libc6
zlib1g
libicu52
libicu52
libc6
libglib2.0-0
libc6
libc6
libicu52
libpcre3

To install with apt
```
sudo apt-get install qt5-qmake libqt5core5a libc6 libstdc++6 libc6 libgcc1 libc6 zlib1g libicu52 libicu52 libc6 libglib2.0-0 libc6 libc6 libicu52 libpcre3
```

### Installing


When all of the dependencys have been installed there is a make script in the bin folder that makes the main app and all the tests.
When run they can all be found in the bin folder.

```
./bin/make-all
```

For cleaning there is a clean script in the bin folder that removes all of the working files.
This will remove the executables created by the make script.

```
./bin/clean-all
```

## Running the tests

After install tests are in the bin folder with test at the end of the executable name.


## Authors

* **Ade Attwood** - *Initial work* - [AdeAttwood](https://github.com/AdeAttwood)

