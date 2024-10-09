# Black Pill CMake Example Project

#### *No ST tool required. Glory to Opensource!* 

This repository is a guide to landing STM32 chip development. Let's get started stm32 project just like arduino.

## Target Board

Hands on black pill board : STM32F401 (<4$)

![Black Pill](https://stm32world.com/images/8/87/Black_pill_pinout.png)

You can use ST-Link v2 copy (<2$)
<img src="https://www.tinytronics.nl/image/cache/data/product-2686/STLINKV2_1-1000x1000.jpg" width="500" />

## Environment setup

Highly recommend to use package manager to set-up environment.

### Windows

With regard to windows, We'll use [```scoop```](https://scoop.sh/#/).

- Install scoop with the [instruction](https://scoop.sh/#/) 
- Add packages required

```sh
scoop bucket add extras
scoop install main/cmake main/openocd main/ninja extras/gcc-arm-none-eabi # if you have no git, install main/git as well
```

### Ubuntu

Unfortunately, ```gcc-arm-none-eabi(embedded)``` is not available in apt package manager from focal. So we use nix package manager as alternative. If you have any other package manager you prefer, do not hesitate to use it :)

- Install nix with the [instruction](https://nixos.org/download/#nix-install-linux)
- Add packages required
```sh
nix-env -iA nixpkgs.cmake nixpkgs.openocd nixpkgs.ninja nixpkgs.gcc-arm-embedded
```

### Mac OS

Mac have all with ```brew```. Cheers! :beers:

- Install brew with the [instruction](https://brew.sh/)

```sh
brew install cmake openocd ninja gcc-arm-embedded #if you have no git, add it
```

## Build & Debug

### VScode

You can use vscode with extensions (recommended!)
- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)

Just hit the ```F5``` for launch. and, that's it.

### Command line

If you hate vscode, just compile it as you always do with cmake.

```sh
git clone https://github.com/DongHoonPark/blackpill-stm32-cmake
cd blackpill-stm32-cmake
# If you use vscode & cmake plugin, the procedure below can be done in vscode
mkdir build 
cd build
cmake .. -G Ninja
cmake --build . --target stm32-blackpill
```

After then, you can use ```.elf``` file to utilize openocd debugger