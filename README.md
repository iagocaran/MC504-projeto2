# MC504-overcooked

A simulation of a kitchen in the style of the game Overcooked! using threads, semaphores and SDL done in C for the MC504 subject at University of Campinas (UNICAMP)

## Introduction

Although very simple, this implementation aims to simulate limited resources being accessed by different threads and synchronized through semaphores.
The C implementation uses the pthread and SDL libraries.

## Getting started

### Installation

This project uses SDL and pthread that should be installed before compiling, if you are using windows, pthread is already bundled in the project.
After installing everything you should:

1. Clone the repo:
```sh
git clone https://github.com/iagocaran/MC504-projeto2.git
```
2. Build with cmake
```sh
cmake .
make
```

**Disclaimer:** This project wasn't tested under linux and mac environments, so it may not compile. (Sorry 😅)

## Usage

After running, you should see a window with the kitchen and two chefs that will get some orders, collec the ingredients, cook them and deliver the dish at the end.

## Credits

* I used some sprites from https://opengameart.org/, but I didn't listed them all here, will probably do it later (Sorry again 😕)
* Also used https://sanderfrenken.github.io/Universal-LPC-Spritesheet-Character-Generator/ for the chefs

