# NOTE
This has been replaced by [`pb-rs`](https://github.com/ceilingfans/pb-rs)

<details>
    <summary>Table of Contents</summary>
    <ol>
        <li>
            <a href="#about-the-project">About the Project</a>
            <ul>
                <li><a href="#built-with">Built With</a></li>
            </ul>
        </li>
        <li>
            <a href="#getting-started">Getting Started</a>
            <ul>
                <li><a href="prerequisites">Prerequisites</a></li>
            </ul>
        </li>
        <li>
            <a href="#building">Building</a>
            <ul>
                <li><a href="#build-script">Build Script</a></li>
                <li><a href=#"manual-build">Manual Build</a></li>
            </ul>
        </li>
        <li><a href="#running-the-game">Running the Game</a></li>
    </ol>
</details>

## About the Project
![Game](https://github.com/ceilingfans/pnut-butta/blob/main/img/game.png?raw=true)
Pnut-Butta is a game revolved around matching substrings

### Built With 
* [flag.h](https://github.com/tsoding/flag.h)

## Getting Started
This is an example of how to set up the project locally

### Prerequisites
* a c++ compiler
* cmake
* make

## Building 
* Clone the repository
```shell
git clone https://github.com/ceilingfans/pnut-butta.git
cd pnut-butta
```

### Build Script
* Build
```shell
sh ./build.sh
```

### Manual Build
* Create CMake files
```shell
cmake .
```
You may need to specify the generator for cmake with the `-G` flag, see [this](https://stackoverflow.com/a/35935066/15283724) for more information

* Make
```shell
make
```

## Running the game
Once you have built the project, you will see a new `bin` folder, in the `bin` folder there will be the executable file.
