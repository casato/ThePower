//
// sueda - geometry edits Z. Wood
// 3/16
//

#include <iostream>
#include "Particle.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Texture.h"


float randFloat(float l, float h)
{
	float r = rand() / (float) RAND_MAX;
	return (1.0f - r) * l + r * h;
}

void Particle::load()
{
	// Random initialization
	rebirth(0.0f);
}

// all particles born at the origin
void Particle::rebirth(float t)
{
	charge = randFloat(0.0f, 1.0f) < 0.5f ? -1.0f : 1.0f;
	m = 1.0f;
	d = randFloat(0.0f, 0.02f);
	x.x = 0;
	x.y = 0;
	x.z = randFloat(-3.f, -2.f);
	v.x = randFloat(-0.1f, 0.1f);
	v.y = randFloat(-0.1f, 0.1f);
	v.z = randFloat(-0.1f, 0.1f);
	lifespan = randFloat(100.f, 200.f);
	tEnd = t + lifespan;

	scale = randFloat(0.2f, 1.0f);
	color.r = randFloat(0.0f, 0.1f);
	color.g = randFloat(0.0f, 0.1f);
	color.b = randFloat(0.25f, 0.5f);
	color.a = 1.0f;
}

void Particle::update(float t, float h, const vec3 &g, const bool *keyToggles)
{
	if (t > tEnd)
	{
		rebirth(t);
	}

	// very simple update
	x += h * v;
	color.a = (tEnd - t) / lifespan;
}
