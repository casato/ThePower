//
// sueda
// November, 2014/ wood 16
//

#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class MatrixStack;
class Program;
class Texture;

class Particle
{
public:
	Particle();
	virtual ~Particle();
	void load();
	void rebirth(float t);
	void update(float t, float h, const glm::vec3 &g, const bool *keyToggles);
	const vec3 &getPosition() const { return x; };
	const vec3 &getVelocity() const { return v; };
	const vec4 &getColor() const { return color; };
	
private:
	float charge; // +1 or -1
	float m; // mass
	float d; // viscous damping
	vec3 x; // position
	vec3 v; // velocity
	float lifespan; // how long this particle lives
	float tEnd;     // time this particle dies
	float scale;
	vec4 color;
};

#endif
