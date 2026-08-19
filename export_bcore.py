"""
Blender export script for BCore Engine map format.

Run this from Blender's scripting tab with the objects you want to
export selected in the viewport. It writes a plain-text map file
that BCore_MapManager.h can load directly.
"""

import bpy

# Path where the map file will be saved
output_path = "D:\\Projeto_BCore\\mapas\\fase1.txt"

with open(output_path, "w") as f:
    f.write("// Model | PX PY PZ | RX RY RZ | Scale\n")
    for obj in bpy.context.selected_objects:
        # Object name (e.g. 'column.obj') - matches the object's name in Blender
        name = obj.name.split('.')[0] + ".obj"
        p = obj.location
        r = obj.rotation_euler
        s = obj.scale.x  # BCore uses uniform scale

        # Convert radians to degrees for BCore
        rx, ry, rz = r.x * 57.2958, r.y * 57.2958, r.z * 57.2958

        line = f"{name} {p.x:.2f} {p.y:.2f} {p.z:.2f} {rx:.2f} {ry:.2f} {rz:.2f} {s:.2f}\n"
        f.write(line)

print("Map exported for BCore!")
