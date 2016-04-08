// a contrived vertex shader, that colors each vertex in a triangle
// according to its position

// we are going to be getting an attribute from the main program, named
// "vPosition", one for each vertex.
//
// on mac you may have to say: "attribute vec4 vPosition;" instead of this:
//in vec4 vPosition;
attribute vec4 vPosition;

// we are going to be outputting a single 4-vector, called color, which
// may be different for each vertex.
// the fragment shader will be expecting these values, and interpolate
// them according to the distance of the fragment from the vertices
//
// on mac you may have to say: "varying vec4 color;" instead of this:

varying vec4 color;


void main()
{

  // pass through the position unchanged ("gl_position" is already defined for us)
  gl_Position = vPosition;

  // you'd probably never want to write a shade this way, but it illustrates
  // the concept.
  // in this shader, we are going to identify which triangle vertex the shader
  // is considering, and apply a specific color.
  //
  if (vPosition.x == -.25) {
    color = vec4(1.,0.,0.,1.);
  }
  else if (vPosition.x == .25) {
    color = vec4(0.,1.,0.,1.);
  }
  else { //if (vPosition.y == .5)
    color = vec4(0.,0.,1.,1.);
  }
} 
