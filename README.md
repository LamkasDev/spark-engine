# Spark Engine
[![Release](https://img.shields.io/github/v/release/LamkasDev/spark-engine)](https://github.com/LamkasDev/spark-engine/releases)
[![Contributors](https://img.shields.io/github/contributors/LamkasDev/spark-engine)](https://github.com/LamkasDev/spark-engine)
[![Issues](https://img.shields.io/bitbucket/issues-raw/LamkasDev/spark-engine)](https://github.com/LamkasDev/spark-engine/issues)

## Description
Spark Engine is a 2D/3D game engine written in C, using OpenGL as a rendering pipeline.

## Building
Building is done via Make with <code>make</code> or <code>make debug</code> (includes debugging symbols).

**Requirements:**  
<code>g++</code> 5.1 or later  
<code>make</code> 3.81 or later  
<code>CMake</code> 2.8 or later  

## Building needed libraries
Build <a href="https://github.com/glfw/glfw/releases/tag/3.3.4">GLFW 3.3.4</a> (create build folder, use CMake to build Makefile, make)  
Copy the built library named <code>build/src/libglfw3.a</code> into <code>spark-engine/libs/lib/libglfw3.a</code>  
Build <a href="https://github.com/recp/cglm/releases/tag/v0.8.3">CGML 0.8.3</a> (create build folder, use CMake to build Makefile, make)  
Copy the built library named <code>build/libcglm.dll.a</code> into <code>spark-engine/libs/lib/libcglm.a</code>  
Build <a href="https://download.savannah.gnu.org/releases/freetype/">Freetype 2.9</a> (create build folder, use CMake to build Makefile, make)  
Copy the built library named <code>build/libfreetype.a</code> into <code>spark-engine/libs/lib/libfreetype.a</code>  

## Platforms
<table>
    <tr>
        <th>Windows</th>
        <th>Linux</th>
        <th>macOS</th>
    </tr>
    <tr>
        <th>✅</th>
        <th>❓</th>
        <th>❌</th>
    </tr>
</table>

* Linux support is experimental and not tested. 
* macOS support is not planned, unless somebody adds support for it.

## Contributing
If you want a feature added or you found a bug, make a new <a href="https://github.com/LamkasDev/spark-engine/issues">Issue</a>.  
If you want to contribute, make a new <a href="https://github.com/LamkasDev/spark-engine/pulls">Pull Request</a>.  
There are no guidelines or any of the sort and contributing is highly encougaraged!

## License
Spark Engine is licensed under the [GNU General Public License v3.0](https://github.com/LamkasDev/spark-engine/blob/master/LICENSE).
