<div>
    <h1>Spark Engine</h1>
</div>
<div>
    <h3>2D/3D game engine in development</h3>
    <div>
        <img src="https://img.shields.io/github/v/release/LamkasDev/spark-engine" />
        <img src="https://img.shields.io/github/contributors/LamkasDev/spark-engine" />
        <img src="https://img.shields.io/bitbucket/issues-raw/LamkasDev/spark-engine" />
    </div>
    <br />
    <p>
    - Written in C<br />
    - Using OpenGL<br />
    - Similar concepts as in Unity<br />
    </p>
</div>
<hr />
<div>
    <h3>Building the game engine</h3>
    <p>
        <b>Requirements:</b><br />
        - <code>g++</code> 5.1 or later<br />
        - <code>make</code> 3.81 or later<br />
        - <code>CMake</code> 2.8 or later<br /><br />
        <b>Building needed libraries:</b><br />
        - Build <a href="https://github.com/glfw/glfw/releases/tag/3.3.4">GLFW 3.3.4</a> (create build folder, use CMake to build Makefile, make)<br />
        - Copy the built library named <code>build/src/libglfw3.a</code> into <code>spark-engine/libs/lib/libglfw3.a</code><br /><br />
        - Build <a href="https://github.com/recp/cglm/releases/tag/v0.8.3">CGML 0.8.3</a> (create build folder, use CMake to build Makefile, make)<br />
        - Copy the built library named <code>build/libcglm.dll.a</code> into <code>spark-engine/libs/lib/libcglm.a</code><br /><br />
        - Build <a href="https://download.savannah.gnu.org/releases/freetype/">Freetype 2.9</a> (create build folder, use CMake to build Makefile, make)<br />
        - Copy the built library named <code>build/libfreetype.a</code> into <code>spark-engine/libs/lib/libfreetype.a</code><br /><br />
        - Build <a href="https://github.com/yaml/libyaml">YAML 0.2.5</a> (create build folder, use CMake to build Makefile, make)<br />
        - Copy the built library named <code>build/libyaml.a</code> into <code>spark-engine/libs/lib/libyaml.a</code><br /><br />
        <b>Building the game engine:</b><br />
        - run <code>make</code> for production build<br />
        - run <code>make debug</code> for build with debugging symbols
    </p>
</div>
<hr />
<div>
    <h3>Platform support</h3>
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
    <p>
    - Linux support is experimental and not tested.<br />
    - macOS support is not planned, unless somebody adds support for it.
    </p>
</div>
<hr />
<div>
    <h3>Contributing</h3>
    <p>
    If you want a feature added or you found a bug, make a new <a href="https://github.com/LamkasDev/spark-engine/issues">Issue</a>.<br />
    If you want to contribute, make a new <a href="https://github.com/LamkasDev/spark-engine/pulls">Pull Request</a>.<br />
    There are no guidelines or any of the sort and contributing is highly encougaraged!
    </p>
</div>
