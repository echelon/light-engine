Light Engine
============
**A graphics system for laser projectors using the Ether Dream DAC.** 
(a new project/work in progress)

This project aims to support research projects and laser projector hacking. As such, the code is primarily designed for programmers developing advanced interactive laser shows that might utilize OpenCV, Kinect, DSP, gesture input, game controller input, etc.

_I'm very interested in finding collaborators for this project._

Goals
-----
I want to built a laser projector daemon that handles multiple 
objects, logical "frame buffers", and simple low-level scanning 
operations such as tracking and blanking the laser. This system should make it easy to develop new programs or experiments quickly. 

**Logical and Physical Surfaces**

Currently, all drawing is done on a [-32767, 32767] x,y coordinate system with IRGB values in [0, 65535]. An internal, entirely logical representation of coordinates would be superior. I'm currently planning on all coordinates lying within the range [-1, 1] and colors within [0, 1]. Higher-level code (ie, the user) may use its own local coordinate systems.

**Processing Pipeline**

(DOC AND GRAPHICS TODO)

**Transformation of the Final Physical Surface**

This final step of the pipeline applies optional 2D (rotation, translation, scaling) and 3D (deformation map) geometry corrections as well as allows for cropping of the physical projection field. This should enable the laser show to be scaled down and projected from angles easily without modifying any other code. 

Research will have to be done as to how this impacts any computational shortcuts made when calculating the order of point drawing. 

**Objects, Automatic Tracking/Blanking, and Draw Order Optimization**

Objects would be the geometry/shapes that are drawn by the projector. Multiple objects might be visible at once, so I want to design a system to automatically track and blank between objects as they are all drawn. Additionally, the system should optimize for the order that these objects are drawn so the projector can draw as quickly as possible. There are several problems to solve here.

As this object system matures, I want to impart several features of 3D graphics engines such as clipping and backface culling on these objects. When an object passes in front or occludes another object, the posterior object should be temporarily clipped. 

**Frame Buffering**

(DOC TODO) 

**Long term: Simultaneous Multi-projector Epipolar Rectification**

I don't have the necessary equipment to explore this yet, but I want to try dispacthing the drawing of objects between two or more projectors to effectively incresease the draw speed. A central control program would manage what drawing tasks each of the projectors is given in order to optimize for speed. This is a complex project, and I don't expect to make headway on this anytime soon. If anyone researching in this area would like to team up and tackle this together, I'm interested. 

Current Status
--------------

1. Networking and Buffering -- work in progress; incomplete
2. Ether Dream Protocol -- work in progress; incomplete
3. Low-level primitives -- not yet started
4. Processing Pipeline -- not yet started
5. Matrix Libraries
6. Graphics Engine-like features (clipping, backface culling, etc.)
7. Path optimization (TSP, etc.)
8. Python bindings

**Overall:** Just started work on this. There's a lot to do here.

License
-------
This codebase is MIT licensed. In order to advance the state of laser projection, we should publish more of our code. 

My other laser projects 
-----------------------
* [Laser Asteroids](https://github.com/echelon/laser-asteroids), 
  a Python laser projector game
* [Laser Testbed](https://github.com/echelon/laser-testbed), 
  misc experiments including OpenCV, Graffiti Markup Language, 
  and more.
* [Laser Client](https://github.com/echelon/laser-client), 
  simple object shows that can cycle. Some parts are shared with 
  Laser Testbed, and much needs to be backported.

