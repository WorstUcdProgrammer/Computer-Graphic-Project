Implemented:
	read in custom datas [DONE] (also tried the teapot, successful but it's too slow to read in...)
	3 Viewport of orthogonal projection on xy, xz, yz planes[DONE]
	Using fragment shader to draw the geos[DONE]
	using shader to calculate 3D transforms (translate, scale, rotate) [DONE]
	save files [DONE]

Interaction:
	At the top of the user menu,
	It's the id of geo to modify and display,
	then it's the translation of x, y and z,
	then it's the scaling factor of x, y and z,
	the next 6 values are the coordinates of two points then formed a line to rotate,
	p1 is less than p2,
	then it's the rotation angle, from -360 to +360,
	after that, the button will save the current coordinates to the original file.

Input format:
	It would be the same as the once provided in the prompt,
	At the top will be the number of geos,
	following by geo points,
	for each geo,
	number of points then each row is the points' x, y and z values.
	Following by  the number of edges,
	then each row is the two vertices that are connected

