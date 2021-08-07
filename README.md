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
    - Similar concepts as in Unity
    </p>
</div>
<hr />

<div>
    <h3>Building stuffs (>w<)</h3>
    <p>
        <b>Requirements:</b><br />
        - <code>g++</code> 5.1 or later<br />
        - <code>make</code> 3.81 or later<br />
        - <code>CMake</code> 2.8 or later<br /><br />  
        <b>Building needed libraries:</b><br />
        - Build <a href="https://github.com/glfw/glfw/releases/tag/3.3.4">GLFW 3.3.4</a> (create build folder, use CMake to build Makefile, make)<br /> 
        - Copy the <code>include/GLFW</code> folder into <code>spark-engine/libs/include/GLFW</code><br /> 
        - Copy the built library named <code>build/src/libglfw.a</code> into <code>spark-engine/libs/lib/libglfw.a</code><br /><br /> 
        - Build <a href="https://github.com/recp/cglm/releases/tag/v0.8.3">CGML 0.8.3</a> (create build folder, use CMake to build Makefile, make)<br /> 
        - Copy the <code>include/cglm</code> folder into <code>spark-engine/libs/include/cglm</code><br /> 
        - Copy the built library named <code>build/libcglm.dll.a</code> into <code>spark-engine/libs/lib/libcglm.a</code><br /><br /> 
        <b>Building the game engine:</b><br />
        - run <code>make</code> or <code>make debug</code><br />
    </p>
</div>
