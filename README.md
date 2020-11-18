# 🎮 VIOLENCE Engine

#### Re-usable game engine made in ECS with SFML


![VE demo](http://kolibis.fr/projects/assets/violence_engine-demo.gif 'VE demo')

### 💾 Install conan

`sudo pip install conan`

*cf : https://docs.conan.io/en/latest/installation.html*
*cf : https://leinnan.github.io/blog/conan-adventuressfml-and-entt-in-c.html*

##### 📡 Add remotes
Basic repo : `conan remote add conan-center https://conan.bintray.com`

Bincrafters repo : `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`

*Use `conan search <NAME> --remote=<REMOTE>` for search package recipes*

### 🛠 Build

#### For Linux 🐧 / macOS 🍎

> use `./install` or `./install -h` in root project for auto install

`mkdir build && cd build`

`conan install ..` or *`conan install .. --build missing` if error*

`cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release`

`cmake --build .`

#### For Windows 🪟

`cmake .. -G "Visual Studio 15 Win64"`

`cmake --build . --config Release`

#### Utils
<details>
      <summary><i>Conan libX dependencies for <b>Fedora</b></i></summary>

      Use `sudo dnf install libXaw-devel libXcomposite-devel libXdmcp-devel libXft-devel libXtst-devel xorg-x11-xkb-utils-devel libXres-devel libXScrnSaver-devel libXvMC-devel xorg-x11-xtrans-devel xcb-util-wm-devel xcb-util-image-devel xcb-util-keysyms-devel xcb-util-renderutil-devel libXv-devel xkeyboard-config-devel`
</details>
<details>
      <summary><i>Conan libX dependencies for <b>Ubuntu</b></i></summary>

      Use `sudo apt-get install libgl1-mesa-dev xorg-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-xinerama0-dev libudev-dev`
</details>


*Use `conan info .. --graph=file.html` for create a graph*

---

#### Project realised by:
- **[@Frederic S.](https://github.com/red-gecko27)** 🦎
- **[@Louis C.](https://github.com/Kdaudau)** 🦦
- **[@Théo C.](https://github.com/GreenDjango)** 🐙
- **[@Yann M.](https://github.com/Paquity)** 🐤