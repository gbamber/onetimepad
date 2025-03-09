<!-- 
  -- Documentation written and Copyright (c) 2025 gbamber
  -- Licensed under CC BY-NC-ND 4.0
  -- SPDX-License-Identifier: CC BY-NC-ND 4.0
  -- License URL: https://creativecommons.org/licenses/by-nc-nd/4.0/
  -->
# OneTimePad <!-- omit from toc -->

<b>OneTimePad</b> is a very basic implementation of a [one-time pad](https://en.wikipedia.org/wiki/One-time_pad "Wikipedia artice 'one-time pad'") in C++.

## Author and Copyright
OneTimePad is written and copyright (c) 2025 gbamber


## Table of Contents

- [Author and Copyright](#author-and-copyright)
- [Table of Contents](#table-of-contents)
- [Disclaimer](#disclaimer)
- [Overview](#overview)
  - [Usage](#usage)
  - [Description](#description)
- [Build](#build)
- [License](#license)
  - [Software](#software)
  - [Documentation](#documentation)
- [Contributing](#contributing)
  - [CLA](#cla)
  - [Report bugs](#report-bugs)
  - [Coding style](#coding-style)
- [Credits / Acknolegements](#credits--acknolegements)

## Disclaimer
This is work in progress, that I write in my free time for recreational purposes and that may contain defects or 'bugs'. See sections 7 and 8 of the license. 

In short: Use at your own risc.

## Overview

Symmetric one-time pad encryption/decryption.

### Usage

`onetimepad [-v] -i inFile -p padFile -o outFile`

* -v  
  verbose output
* -i *inFile*  
  the name of the file to be encrypted/decrypted
* -o *outFile*  
  the name of the file to which the result of the encryption/decryption shall be written
* -p *padFile*  
  the name of the one-time pad file used to do the encryption/decryption

### Description

A very simple symmetric one-time pad encryption/decryption software. While encypting/decrypting the pad is erased. This comes with some drawbacks:

* when out of sync, decryption will fail (i.e. yield gibberish)  
  TODO: add a headder to encrypted data
* decryption only can be done once, as the pad is void after using it. That - of course - is the purpose of a one-time pad. **But**: When decrypting a second time, the pads get out of sync.
* the recipient of encrypted data needs to know the original filename if they want to reproduce it.

Other implementations have mitigated theese drawbacks. 

## Build

I'm using CMake as a build system. The `CMakeLists.txt` is included in the git repository. To build the executable do:

    mkdir ./build
    cd ./build
    cmake ..
    make

The code commpiles with `gcc 12.2.0` and `clang 15.0.6`. 

## License

### Software

Except specific files which bear a different mention, OneTimePad is licensed under the EUPL-1.2

SPDX-License-Identifier: EUPL-1.2

See https://commission.europa.eu/content/european-union-public-licence_en for
further information.

### Documentation

The Documentation is licensed [CC BY-NC-ND 4.0](https://creativecommons.org/licenses/by-nc-nd/4.0/ "link to creativecommons.org"). 

SPDX-License-Identifier: CC-BY-NC-ND-4.0

To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-nd/4.0/

## Contributing
### CLA
By contributing you  &ndash; the contributor &ndash; agree to the follwoing 
terms and conditions:
- you agree to place your contribution under the EUPL license or any other 
  license as I &ndash; gbamber &ndash; see fit.
- you give me &ndash; gbamber &ndash; the unlimited, unrestricted and 
  irrevocable right to use, modify, sublicense, distribute your contribution. 

### Report bugs
If you want to contribute to the project, open an Issue or &ndash; better 
&ndash; send a Pull request. If you find think you have found a bug, please 
report it by opening a new issue. Please include as much detail as possible, 
and ideally some code to reproduce the problem.

### Coding style
As you might have noticed, I use a distinct coding style, derived from the 
[Code Conventions for the Java Programming Language](
https://www.oracle.com/java/technologies/javase/codeconventions-introduction.html
"https://www.oracle.com/java/technologies/javase/codeconventions-introduction.html") 
and/or the [Google Java Style Guide](
https://google.github.io/styleguide/javaguide.html 
"https://google.github.io/styleguide/javaguide.html"). 
Some rules I *try* hard to follow:
- Use [lowerCamelCase](https://en.wikipedia.org/wiki/Camel_case 
  "https://en.wikipedia.org/wiki/Camel_case") for *variables*, *member-functions* and *other functions*
  and  
  [UpperCamelCase](
  https://en.wikipedia.org/wiki/Naming_convention_(programming)#Examples_of_multiple-word_identifier_formats 
  "https://en.wikipedia.org/wiki/Naming_convention_(programming)#Examples_of_multiple-word_identifier_formats")
  for *class* names.  
  If you use more conventional C/C++ [snake_case](
  https://en.wikipedia.org/wiki/Snake_case 
  "https://en.wikipedia.org/wiki/Snake_case") I will most probabely be 
  forgiving &ndash; and immediately refactor it :-)
- 4 spaces indentation
- Opening braces should not be placed on a new line
- Nesting: If it is nested more than 4 layers deep, it should most probabely
  be refactored into seperate functions
- Functions with more than 100 lines should most probabely be refactored
  into sub-functions

BTW: I *know* that this is not the common coding style for C/C++, but it´s my 
code, ain´t it? Take it or leave it.

## Credits / Acknolegements

none :-)