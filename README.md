# tikz3D

Library for generating nice 3D pictures in tikz that are readable with 3D glasses.

Example:

```{c++}
#include <iostream>

#include <vector>

#include "c_camera.h"
#include "c_point.h"
#include "c_line.h"
#include "c_polygon.h"
#include "c_node.h"
#include "c_scene_manager.h"
#include "utils.h"

using namespace std;


int main() {

    // Create a camera at coordinates (62, 56, 48), and set it to rotate
    // 45 degrees around the x axis, then 45 degrees around the z axis
    // so it points at (0, 0, 0).
    c_camera camera(62, 56, 48, -3.14/4, 0, -3.14/4);

    // Initialize a scene manager to allocate memory for scene objects.
    c_scene_manager scene_manager;

    // Create lines to define a 6x6x6 cube.
    c_line line1(0, 0, 0, 6, 0, 0);
    c_line line2(6, 0, 0, 6, 6, 0);
    c_line line3(6, 6, 0, 0, 6, 0);
    c_line line4(0, 6, 0, 0, 0, 0);
    c_line line5(0, 0, 6, 6, 0, 6);
    c_line line6(6, 0, 6, 6, 6, 6);
    c_line line7(6, 6, 6, 0, 6, 6);
    c_line line8(0, 6, 6, 0, 0, 6);
    c_line line9(0, 0, 0, 0, 0, 6);
    c_line line10(0, 6, 0, 0, 6, 6);
    c_line line11(6, 0, 0, 6, 0, 6);
    c_line line12(6, 6, 0, 6, 6, 6);

    // Shade in the bottom of the cube
    c_polygon polygon1(0, 0, 0, 0, 6, 0, 6, 6, 0);
    c_polygon polygon2(0, 0, 0, 6, 0, 0, 6, 6, 0);

    // Add some text in the middle of the cube
    c_node node(3, 3, 3, "socks");

    // Make it so the lines are drawn extra thick
    line1.add_param("ultra thick");
    line2.add_param("ultra thick");
    line3.add_param("ultra thick");
    line4.add_param("ultra thick");
    line5.add_param("ultra thick");
    line6.add_param("ultra thick");
    line7.add_param("ultra thick");
    line8.add_param("ultra thick");
    line9.add_param("ultra thick");
    line10.add_param("ultra thick");
    line11.add_param("ultra thick");
    line12.add_param("ultra thick");

    // Add all the lines to the scene.
    scene_manager.add_to_scene(&line1);
    scene_manager.add_to_scene(&line2);
    scene_manager.add_to_scene(&line3);
    scene_manager.add_to_scene(&line4);
    scene_manager.add_to_scene(&line5);
    scene_manager.add_to_scene(&line6);
    scene_manager.add_to_scene(&line7);
    scene_manager.add_to_scene(&line8);
    scene_manager.add_to_scene(&line9);
    scene_manager.add_to_scene(&line10);
    scene_manager.add_to_scene(&line11);
    scene_manager.add_to_scene(&line12);
    scene_manager.add_to_scene(&polygon1);
    scene_manager.add_to_scene(&polygon2);
    scene_manager.add_to_scene(&node);

    // Render the scene to file as a regular (no 3d glasses) projection.
    scene_manager.render_to_file("test.txt", &camera);

    c_camera eye_1(62, 56, 48, -3.14/4, 0, -3.14/4);
    c_camera eye_2(63, 55, 48, -3.14/4, 0, -3.14/4);

    // Render it to file as a 3D glasses projection.
    scene_manager.render_3d_to_file("test3d.txt", &eye_1, &eye_2);

    return 0;
}
```

See `test.pdf` to see the output of this code.
