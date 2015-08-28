# tikz3D

Library for generating nice 3D pictures in tikz that are readable with 3D glasses.

Example:

```{c++}
#include "c_camera.h"
#include "c_line.h"
#include "c_scene_manager.h"

using namespace std;

int main() {

    c_camera camera(62, 56, 48, -3.14/4, 0, -3.14/4);

    c_scene_manager scene_manager;

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

    scene_manager.render_to_file("test.txt", &camera);

    c_camera eye_1(62, 56, 48, -3.14/4, 0, -3.14/4);
    c_camera eye_2(63, 55, 48, -3.14/4, 0, -3.14/4);

    scene_manager.render_3d_to_file("test3d.txt", &eye_1, &eye_2);

    return 0;
}
```

See `test.pdf` to see the output of this code.
