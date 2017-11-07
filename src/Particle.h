//
// sueda
// November, 2014/ wood 16
//

#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <vector>

#include <glad/glad.h>

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

// Sort particles by their z values in camera space
class ParticleSorter
{

public:

	bool operator() (const std::shared_ptr<Particle> p0, const std::shared_ptr<Particle> p1) const
	{
		// Particle positions in world space
		const vec3 &x0 = p0->getPosition();
		const vec3 &x1 = p1->getPosition();

		// Particle positions in camera space
		vec4 x0w = C * glm::vec4(x0.x, x0.y, x0.z, 1.0f);
		vec4 x1w = C * glm::vec4(x1.x, x1.y, x1.z, 1.0f);
		return x0w.z < x1w.z;
	}

	mat4 C; // current camera matrix

};

#endif
