varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;

void main()
{
	// Exercise 3.3.2
    gl_FragColor = clamp(dot(normalize(normal), normalize(vertex_to_light_vector)) * color, 0.0, 1.0);
	
	// need this line so OpenGL doesn't optimize out the variables -- remove in your solution
    // {
	normal; color;
    // }
}