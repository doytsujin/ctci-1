# *Cracking the Coding Interview* Solutions

## Solutions

Here are my solutions to the *CTCI* problems.  You can find the solutions from the author herself [here](http://www.crackingthecodinginterview.com/solutions.html).

| \#   | Interview Questions |
| ---  | ---------------     |
| 4.   | ***Chapter 4 - Trees and Graphs*** |
| 4.1  | [Route Between Nodes](src/routeBetweenNodes.cpp) |

<!--
| *Lesson Template* | |
// 90-100% Green
// 80-89% - Blue
// 70-79% - Yellow
// 60-69% - Orange
// <60% - Red
[]().[cpp]() | ![](https://img.shields.io/badge/D-easy-green.svg)
[]().[cpp]() | ![](https://img.shields.io/badge/D-medium-yellow.svg)
[]().[cpp]() | ![](https://img.shields.io/badge/D-hard-red.svg)
-->

## Tests
Assuming you are using cmake, tests will be located in your `$BUILD_DIR}/bin` directory.  All tests are in the same `ctci ` binary.  Individual tests can be run per the [googletest framework documentation](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#running-test-programs-advanced-options).  Here is a quick reference:

```
/path/to/build/bin> ctci --help
/path/to/build/bin> ctci --gtest_list_tests
/path/to/build/bin> ctci --gtest_filter=TestName.Test
/path/to/build/bin> ctci --seed 12345
```

### Dependencies

Test are built using the following packages.  Use CMake and the dependencies will be downloaded and built for you.

* [gflags](https://gflags.github.io/gflags/) 
* [googletest](https://github.com/google/googletest) 


### Building
You can build the tests for your favorite development environment using `cmake`.  e.g.:

* For the command line:

```shell
mkdir test/build
cd test/build
cmake ..
make
```

* For XCode:

```shell
mkdir test/xcode
cd test/xcode
cmake -G Xcode ..
make
```


Tests will be created in the `bin` directory located wherever you ran cmake from (`test\build\bin` in the example above).

## Contributing
You are welcome to contribute provided you accept the [Contributor Covenant Code of Conduct](CONTRIBUTING.md).

## License
This repository is licensed under [The Unlicense](LICENSE.md).

## Acknowledgements
* Thank you to the [gflags](https://gflags.github.io/gflags/) command line parsing library.
* Thank you to the [googletest](https://github.com/google/googletest) C++ test framework.
* McDowell, Gayle Laakmann. [Cracking the Coding Interview](https://www.amazon.com/dp/0984782850/ref=cm_sw_em_r_mt_dp_U_F-JoCbXAJE3MH).  Career Cup LLC, 2016.  
