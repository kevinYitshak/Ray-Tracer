cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES)

file(COPY
    models/PlantJar.mtl
    models/PlantJar.obj
    models/Plant.mtl
    models/Plant.obj
    models/plank.png
    models/green_table.png
    models/candle2.png
    models/leaf.png
    models/flame.png
    models/s.png
    models/base.png
    models/emission.png
    models/ant.png
    models/mushroom.png
    models/dark_forest.png
    models/leaf1.png
    models/s1.png
    models/bghost.png
    DESTINATION ${CMAKE_BINARY_DIR}/models
)

file(COPY
    models/outer_cube.obj
    models/outer_cube.mtl
    models/pumpkin.obj
    models/pumpkin.mtl
    models/candle2.obj
    models/candle2.mtl
    models/ghost.obj
    models/ghost.mtl
    models/bg.obj
    models/bg.mtl
    models/glass1.obj
    models/glass1.mtl
    models/glass2.obj
    models/glass2.mtl
    models/glass3.obj
    models/glass3.mtl
    models/candle_flame2.obj
    models/candle_flame2.mtl
    models/candle_glass2.obj
    models/candle_glass2.mtl
    models/spider_web.obj
    models/spider_web.mtl
    models/spider.obj
    models/spider.mtl
    models/ant.obj
    models/ant.mtl
    models/tree_obj.obj
    models/tree_obj.mtl
    models/leaf1.obj
    models/leaf1.mtl
    models/mirrorframe.obj
    models/mirrorframe.mtl
    models/mirror.obj
    models/mirror.mtl
    models/mirror_plane.obj
    models/mirror_plane.mtl
    models/mushroom.obj
    models/mushroom.mtl
    models/plank.obj
    models/plank.mtl
    DESTINATION ${CMAKE_BINARY_DIR}/models
)