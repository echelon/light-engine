
----------

* Point
	* Points

* Path
	* Paths

* Geo
	- pathIterator() TODO
	- pointIterator() TODO

----------

- BlankPath (?)

<><> Geo
	<><> UnblankedGeo
	<><> BlankedGeo

	- If we scale a blanked geo, the blanking can change;
	- based on scan angle.

blanked = UnblankedGeo.getBlanked(scanAngle, misc, etc)
	 it = blanked.pointIterator()

for pt in it :
	yield pt

	- will need to blank to head again.

trackingPath = calculate\_tracking(geoA, geoB, scanAngle, misc, etc)

	- generate all of this on the fly?
	- remember the plan for "frames" of objects?

Frame = [[ lots of points ]]

	- frame-to-frame tracking can be determined if the first and last
	- objects change place. Or I can just provide a bool or something.

	foo(frameTrack=true)

