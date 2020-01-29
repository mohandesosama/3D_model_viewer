# Simple 3D OpenGL Model Viewer
 
 ## Requirements
           
The viewer should be able to load the following 5 models:
 
* Cube
* Teapot
* Jack (see text Figure 5.61)
* A mesh from "WINEGLASS.3VN" file (see text Figure 6.15, 6.17, 6.69 - Mesh.h)
* Any arbitrary model of your own (the more complex, the better)
 
These models should be loaded by pressing the corresponding keys 1, 2, 3, 4, 5. (At any time, only a single object is displayed and manipulated).
 
The user should be able to change the material color of the current model by pressing key "m". At least 5 different colors should be provided (and toggled each time the key is pressed).
 
The viewer displays 3 axes as 3D objects (red for x-axis, green for y-axis, blue for z-axis).
 
The object is initially centered at the global origin O (when loaded).
 
Transformations on the object should be enabled as follows:
 
### Rotation: 
The user first presses "r" to set the transformation mode to rotation. Then uses "x" for x-roll with positive angle, and "X" for x-roll with negative angle. If the user keeps the key pressed down, rotation should be done continuously (use double buffer for smooth animation). Similarly, "y" and "Y" are used for y-roll, and "z" and "Z" for z-roll.
 
### Translation: 
The user first presses "t" to set the transformation mode to translation. Then "x" for positive x-translation, and "X" for negative x-translation. Similarly, "y", "Y", "z", "Z" are used for y- or z-translation.
 
### Scaling: 
Only uniform scaling is allowed (Sx = Sy = Sz). The user first presses "s" to set the transformation mode to scaling. Then "x" for expanding (Sx > 1), and "X" for shrinking (0 < Sx < 1). No negative scaling factor is allowed.
 
Note that the user may perform a series of transformations in a row (for example, first scale by factor 3.5, then translate by (3.0, 2.5, -1.9), then rotate by ..., then translate by ... ), in which case their accumulated effect must show on the transformed object.
 
The user should be able to restore the initial configuration (object centered at O with no transformation) at anytime with pressing key "d".
 
The camera can be moved (rotated) around the origin to see the object from different viewpoint. Left-arrow and right-arrow keys control horizontal rotation angle (theta), and up-arrow and down-arrow keys control vertical rotation angle (phi).
 
The object can be displayed as wireframe, flat-shaded, or smooth-shaded. These 3 modes should be toggled by key "w".
 
 ## Sample code
           
SimpleViewer.cpp (You can build on this program)
 
## Sample Mesh files (*.3VN)
           
BUCK.3VN
BUCKY.3VN
CUBES3.3VN
DIAMOND.3VN
GLASS.3VN
ICOSA.3VN
PAWN.3VN
SIMPBARN2.3VN
WINEGLASS.3VN
