// the simplest fragment shader: get the color (from the vertex shader - 
// probably interpolated from values specified in the vertex shader - and
// just pass them through to the render:
// 

// on Mac, you may have to say this: 
// "varying vec4 color;" instead of this:
//in vec4 color;
varying vec4 color;

void main() 
{ 
  // "gl_FragColor" is already defined for us - it's the one thing you have
  // to set in the fragment shader:
  gl_FragColor = color;
} 

