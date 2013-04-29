Light Engine
============
**A graphics system for laser projectors using the Ether Dream DAC** 
(new project/work in progress)

Current Status
--------------

1. Networking and Buffering -- incomplete
2. (TODO)

Goals
-----
I want to built a laser projector daemon that handles multiple 
objects, logical "frame buffers", and simple low-level scanning 
operations such as tracking and blanking the laser. 

As the library grows more advanced, I'd like to implement things
such as 2D and 3D geometry corrections as well as simply cropping 
the projection field.

A long-term goal would be to allow multiple laser projectors driven
by multiple Ether Dream units to use a single colinear surface and
distribute drawing between the beams.

API Design
----------
I'm not sure how much low-level control to usurp from client code. 
I may want to allow both high- and low-level API calls. I want to 
create Python bindings ASAP, as well.

License
-------
MIT licensed. (Though there's not much here, yet.)

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

