#ifndef RAY_H
#define RAY_H

// Ray Class

struct Ray {
	vec3 origin;
	vec3 dir;
};
		
Ray rayInit(in vec3 o, in vec3 d) {
	Ray ray;
	ray.origin = o;
	ray.dir = d;
	return ray;
}

vec3 at(Ray ray, float t) {
	return (ray.origin + t*ray.dir);
}


#endif