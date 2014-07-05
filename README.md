Light Engine: Real Time Laser Graphics
======================================
**A graphics engine for laser projectors.** 
(unfinished / work in progress)

This project aims to support runtime interactive laser projection.

_I'm interested in finding collaborators for this project. Find my email and contact me!_

**Keywords:** laser projector, projection, lasers, scanning, DAC, EtherDream, Ether Dream.

Scope of Work and Current Status
--------------------------------

1. DAC Support
	1. Ether Dream -- working (incomplete, inefficient)
	2. ...
2. Point Streaming
	1. Frame Streams (frames contain point paths and can be replayed until a new frame is ready) 
		-- working (incomplete, inefficient, buggy)
	2. Raw Point Streams 
		-- no need currently; going to defer this for later
3. 2D Graphics Engine / Pipeline
	1. Matrix Stack and Transforms -- mostly implemented, but awful code
	2. Clipping -- not yet started
	3. ...
4. 3D Graphics Engine / Pipeline -- not yet started
	1. Vetorization
	2. Backface culling
	3. Clipping
	4. View frustum
	5. ...
5. Projection Features -- Not yet started
	1. Multi-Dac projection
	2. Projection Control
		1. Projection Boundaries
		2. Projection Resizing
		3. Matrix Projection Mapping
		4. Spherical and/or Polygon Projection Mapping
6. Algorithmically Optimized Realtime Streaming -- not yet started
	1. Dynamic Tracking (object to object)
	2. Topological Path Optimization (TSP, etc.)
	3. Dynamic Blanking
7. Bindings / Scripting -- not yet started, may elect not to do
	1. Python bindings
	2. Lua scripting

My other laser projects 
-----------------------
*See [lasers.io](http://lasers.io) for videos of my laser projection work.*

* [Laser Asteroids](https://github.com/echelon/laser-asteroids), 
  my first Python laser projector game
* [Laser Testbed](https://github.com/echelon/laser-testbed), 
  my earliest laser experiments in Python including interactive 
  animations, OpenCV, Graffiti Markup Language, and more.
* [Laser Client](https://github.com/echelon/laser-client), 
  simple laser shows that cycle. I actually wrote this to run 
  "advertisements" or text displays. Some parts of the code are 
  based on "Laser Testbed", and much remains to be backported.


