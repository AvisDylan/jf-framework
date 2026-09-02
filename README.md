# JF Framework
### License

JF Framework is licensed under [GPLv3](./License.txt)
### Description
JF Framework is a web framework coded in C as a school project.

### Progress
A roadmap can be found in the [TODO](./TODO.md).

### Contributing
Please read the [CONTRIBUTING](./CONTRIBUTING.md) before making pull requests.

### Documentation
Full documentation is found in the Doxygen generated site [Docs](https://avisdylan.github.io/jf-framework/html/).

### How to build
#### To build on amd64 you must run:
1. `cmake --preset build-x86 -S .`
2. `cmake --build --preset build-x86`

#### To build on arm64 you must run:
1. `cmake --preset build-arm -S .`
2. `cmake --build --preset build-arm`
