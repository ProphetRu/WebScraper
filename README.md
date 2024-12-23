# Web Scraper
WebScraper - a program that parses (scrapes) a website (`fust for fun`)

* Sends a request to a URL
* Receives an HTML page in response
* Parses the HTML page and finds the necessary data
* Generates and saves data in CSV format

## Dependencies
* [googletest](https://github.com/google/googletest)
* [cpr](https://github.com/libcpr/cpr)
* [libxml2](https://github.com/GNOME/libxml2)

## Build local Windows/Linux
```shell
vcpkg install gtest cpr libxml2
vcpkg integrate install

cd WebScraper
mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"

cmake --build . --config Release
```

## Testing
```shell
ctest
```
