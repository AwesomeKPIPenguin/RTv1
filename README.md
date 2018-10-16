# RTv1

Available for **MacOS** only

Discover the fundamental principles of Raytracing: the creation of computer-generated images.
This first project will make you realize simple scenes involving objects and simple lights.

## Instalation and Usage

Run make

```
make
```

Executable **RTv1** will appear. The usage is next:

```
./RTv1 scene_file
```

Here are some rules of creation the scene file:

```
cat scenes/INFO.txt

# Example of the scene file

scene {
    name: Example Scene;            # default: New Scene
    world_color: 0x0;               # default: 0x0 (black)
}

camera {
    origin: (-2000, 0, 0);          # default: (-1000, 0, 0)
    alpha: 0;                       # default: 0 (in degrees)
                                    #   angle of camera rotation (near OY)
    beta: 0;                        # default: 0 (in degrees)
                                    #   angle of camera rotation (near OX)
    gamma: 0;                       # default: 0 (in degrees)
                                    #   angle of camera rotation (near OZ)
    fov: 100;                       # default: 100 (in degrees) (60 - 120)
                                    #   Field Of View
}

light {
    bright: 0.25;                   # default: 0.15 (0.0 - 1.0, excluding 0)
    origin: (0, 10000, 0);          # default: (0, 10000, 0)
}

#
#   Line comment symbol - '#'
#

################################################################################
#                                                                              #
#   Next properties are valid for each object:                                 #
#                                                                              #
#    - color;                                                                  #
#       values: in hex form - 0xrrggbb OR 0XRRGGBB;                            #
#       default: 0xffff00;                                                     #
#                                                                              #
#    - ambnt (ambient);                                                        #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.1;                                                          #
#       koef of an artificial illumination of the objects (ambient light);     #
#                                                                              #
#    - diff (diffuse);                                                         #
#       values: 0.0 - 1.0;                                                     #
#       default: 1.0;                                                          #
#       brightness of the object's own color;                                  #
#                                                                              #
#    - spclr (specularity);                                                    #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.0;                                                          #
#       specularity koef of the object;                                        #
#                                                                              #
#    - s_blur (specular blur);                                                 #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.0;                                                          #
#       koef of the blur effect of reflection;                                 #
#                                                                              #
#    - trans (transparency);                                                   #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.0;                                                          #
#       transparency koef of the object;                                       #
#                                                                              #
#    - t_blur (transparent blur);                                              #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.0;                                                          #
#       koef of the blur effect of transparency;                               #
#                                                                              #
#    - phong (Phong shading);                                                  #
#       values: 0.0 - 1.0;                                                     #
#       default: 0.2;                                                          #
#       koef of the shining effect;                                            #
#                                                                              #
#   Also, there are 2 functions:                                               #
#                                                                              #
#    - translate;                                                              #
#       values: point, as a move vector;                                       #
#       default: (0.0, 0.0, 0.0);                                              #
#                                                                              #
#    - rotate;                                                                 #
#       values: point with alpha, beta and gamma angles as                     #
#           x, y and z respectively;                                           #
#       default: (0.0, 0.0, 0.0);                                              #
#                                                                              #
################################################################################

plane {
    origin: (0, -500, 0)            # default: (0, -1000, 0)
    norm: (0, 1, 0)                 # default: (0, 1, 0)
                                    #   normal vector of the plane
    color: 0x0000ff;
    phong: 0;
}

sphere {
    origin: (0, 0, 0);              # default: (0, 0, 0)
    radius: 300;                    # default: 100
    color: 0xff0000;
}

cone {
    base: (0, -500, 0);             # default: (0, 0, -200)
    base_rad: 300;                  # default: 100
    vert: (0, -150, 0);             # default: (0, 0, 200)
    vert_rad: 150;                  # default: 100
    color: 0x00ff00;
}

```

## Output

plane.scn:

<img width="1201" alt="screen shot 2018-09-26 at 2 52 39 pm" src="https://user-images.githubusercontent.com/22004388/46985603-f7edfe80-d0f3-11e8-9599-1916538266be.png">

sphere.scn:

<img width="1199" alt="screen shot 2018-09-26 at 2 53 04 pm" src="https://user-images.githubusercontent.com/22004388/46985604-f7edfe80-d0f3-11e8-87c3-25b054414c0e.png">

cone.scn:

<img width="1200" alt="screen shot 2018-09-26 at 2 53 21 pm" src="https://user-images.githubusercontent.com/22004388/46985607-f8869500-d0f3-11e8-9cb4-624a31d8b9b6.png">

all_together.scn:

<img width="1200" alt="screen shot 2018-09-26 at 2 54 02 pm" src="https://user-images.githubusercontent.com/22004388/46985602-f7edfe80-d0f3-11e8-9d25-db16466901c7.png">
