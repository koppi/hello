Hello, world!

![GitHub last commit](https://img.shields.io/github/last-commit/koppi/hello)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/koppi/hello)
[![OS](https://github.com/koppi/hello/actions/workflows/os.yml/badge.svg)](https://github.com/koppi/hello/actions/workflows/os.yml)
[![Web](https://github.com/koppi/hello/actions/workflows/web.yml/badge.svg)](https://github.com/koppi/hello/actions/workflows/web.yml)
[![GitHub issues](https://img.shields.io/github/issues/koppi/hello)](https://github.com/koppi/hello/issues)

```shell
$ cmake --list-presets
Available configure presets:

  "debug"         - Debug
  "release"       - Release
$ cmake --preset debug
$ cmake --build --list-presets
Available build presets:

  "app-debug"   - Build Debug
  "app-release" - Build Release
$ cmake --build --preset app-debug
...
```