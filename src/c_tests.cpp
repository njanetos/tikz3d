#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "common.h"

#include "c_line.h"
#include "c_polygon.h"
#include "c_camera.h"
#include "c_scene_manager.h"
#include "c_node.h"

TEST_CASE("Polygon normals") {
    c_polygon polygon(0, 0, 0, 1, 0, 0, 0, 0, 1);
    c_point point = polygon.normal();

    //std::cout << point;
}

TEST_CASE("Splitting a line") {

    c_line line1(0, 0, 0, 1, 1, 1);

    c_polygon polygon(1, 0, 0, 0, 1, 0, 0, 0, 1);

    std::vector< std::vector<c_tikz_obj*> > splitted = line1.split(&polygon);

    REQUIRE( splitted.size() == 3 );
    REQUIRE( splitted[0].size() == 1 );
    REQUIRE( splitted[1].size() == 0 );
    REQUIRE( splitted[2].size() == 1 );

    REQUIRE( fabs(((c_line*) splitted[0][0])->sx - 0) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[0][0])->sy - 0) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[0][0])->sz - 0) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[0][0])->ex - 0.33333333) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[0][0])->ey - 0.33333333) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[0][0])->ez - 0.33333333) < PRECISION );

    REQUIRE( fabs(((c_line*) splitted[2][0])->sx - 0.33333333) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[2][0])->sy - 0.33333333) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[2][0])->sz - 0.33333333) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[2][0])->ex - 1) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[2][0])->ey - 1) < PRECISION );
    REQUIRE( fabs(((c_line*) splitted[2][0])->ez - 1) < PRECISION );

}

TEST_CASE("Splitting a polygon") {

    c_polygon polygon1(0, 0, 0, 1, 0, 0, 0, 1, 0);
    c_polygon polygon2(0, 0, -1, 1, 0, 1, 0, 0, 1);

    std::vector< std::vector<c_tikz_obj*> > splitted = polygon2.split(&polygon1);

    REQUIRE( splitted.size() == 3 );
    REQUIRE( splitted[0].size() == 2 );
    REQUIRE( splitted[1].size() == 0 );
    REQUIRE( splitted[2].size() == 1 );

}

TEST_CASE("Render to file") {

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

    polygon1.add_param("opacity=0.2");
    polygon2.add_param("opacity=0.2");

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

    // Render a 'cross-eyed' projection.
    scene_manager.render_cross_to_file("testCross.txt", &eye_1, &eye_2);

}

TEST_CASE("BSP creation") {
    c_polygon polygon1(0, 0, 0, 0, 1, 0, 1, 0, 0);
    c_polygon polygon2(0, 0, 1, 2, 2, 1, 2, 2, -1);

    c_scene_manager scene_manager;
    scene_manager.add_to_scene(&polygon1);
    scene_manager.add_to_scene(&polygon2);

    scene_manager.render_bsp();



}
