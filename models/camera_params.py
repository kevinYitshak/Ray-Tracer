import bpy
from mathutils import Vector
from math import degrees

# get the active camera
cam = bpy.context.scene.camera

import bpy
from mathutils import Vector

cam = bpy.data.objects['Camera']
up = cam.matrix_world.to_quaternion() @ Vector((0.0, 1.0, 0.0))
cam_direction = cam.matrix_world.to_quaternion() @ Vector((0.0, 0.0, 1.0))
origin = cam.matrix_world @ Vector((0.0, 0.0, 0.0, 1.0))
fov = cam.data.angle

print('fov: ', fov)
print('origin: %f', origin)
print('up: %f', up)
print('dir: %f', cam_direction)

forward=at-pos

import bpy
from mathutils import Vector
from math import degrees

# get the active camera
cam = bpy.context.scene.camera

# Camera transform matrix
m = cam.matrix_world

# Compute at, look, up, fov
pos = m.to_translation()
at = m @ Vector((0,0,-1,1))   # Point one unit in front of the camera
up = m @ Vector((0,1,0,0))    # Vector in the y direction
fov = degrees(cam.data.angle) # Y field of view angle

# Rotate values into y-up system
print( "Pos = (%f, %f, %f)" % (pos.x, pos.z, -pos.y))
print( "At  = (%f, %f, %f)" % (at.x, at.z, -at.y))
print( "Up  = (%f, %f, %f)" % (up.x, up.z, -up.y))
print( "fov = %f" % (fov))
