# UntitledTankGame

This is currently just a sandbox to play around with some components that might be useful for
[BZFlag](https://www.bzflag.org).


## Building

This requires CMake and vcpkg. Create a VCPKG_ROOT environment variable pointing to the root of your vcpkg git clone or
manually define CMAKE_TOOLCHAIN_FILE pointing to the ```scripts/buildsystems/vcpkg.cmake``` file of your vcpkg.

```
mkdir build
cd build
cmake ..
make
```

## Component Ideas

* **Common** - Components used by the most/all applications (client, server, etc)
 * **Configuration** - TOML-backed configuration system with value constraints and update callbacks
 * **FSHelper** - Functions for obtaining filesystem locations that return platform-specific answers (such as the
   documents, configuration, or cache directories)
 * **NetUtils** - Tools for handling IP addresses, address range matches, DNS lookups, UPnP/NAT-PMP, and mDNS/DNS-SD
 * **ModelLoader** - Loads GLTF models and supports reading a custom extension that would contain BZFlag world information
* **Graphics** - Components used by the client and other graphical programs
  * **Window** - Targets SDL2 that take the desired window state (windowed/fullscreen, size/resolution, display index)
    and figures out how to get to that state
* **Simulation** - Components for calculating a deterministic simulation of the game based on input states

## License

This code is released under the LGPL 2.1. See License.md for the full license text.

```
Copyright (C) 2022  Scott Wichser

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
```

