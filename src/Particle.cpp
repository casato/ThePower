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

static vec3 orig;
static bool gravity = true;
static bool collision = true;

bool releaseClick = false;
std::vector < std::shared_ptr<Particle>> particles;

float randFloat(float l, float h)
{
	float r = rand() / (float) RAND_MAX;
	return (1.0f - r) * l + r * h;
}

void Particle::load()
{
	// Random initialization
	rebirth(0.0f, 0, 0);
}

// all particles born at the origin
void Particle::rebirth(float t, float xOrig, float yOrig)
{
	charge = randFloat(0.0f, 1.0f) < 0.5f ? -1.0f : 1.0f;
	m = 1.0f;
	d = randFloat(0.0f, 0.02f);
	x.x = 0;
	x.y = 0;
	x.z = -2.0f;
	v.x = randFloat(-0.7f, 0.8f);
	v.y = randFloat(1.0f, 2.5f);
	v.z = 0;
	lifespan = randFloat(100, 200);
	tEnd = t + lifespan;

	scale = randFloat(0.2f, 1.0f);
	color = vec4(1.0, 1.0, 1.0, 1.0);
	color.a = 1.0f;
}

void Particle::update(float t, float h, const vec3 &g, const bool *keyToggles)
{


	// very simple update
	//gravity
	if (gravity)
	{	
		if (releaseClick)
		{
			v.x = randFloat(-2.0f, 2.0f);
			v.y = randFloat(1.0f, 2.5f);
			v.z = 0;
		}
		v.y += -0.03f;
		releaseClick = false;
	}
	else
	{
		v += (0.08f/distance(x, orig)) * (orig - x);
	}
	x += h * v;
	//color.a = (tEnd - t) / lifespan;
	if (collision)
	{
		for (std::shared_ptr<Particle> p : particles)
		{
			if (distance(p->x, x) < 0.05 && t > 1)
			{
				vec3 normal = normalize(p->x - x);
				vec3 relVel = p->v - v;
				float normVel = dot(relVel, normal);
				if (normVel <= 0)
				{
					v += normal * normVel / 1.7f;
					p->v -= normal * normVel / 1.7f;
				}
			}

		}
	}
	
	if (x.x < -1)
		v.x = 0.1;
	if (x.x > 1)
		v.x = -0.1;
	if (x.y < -0.95)
	{
		vec3 normal = vec3(0.0, 1.0, 0.0);
		vec3 relVel = v;
		float normVel = dot(relVel, normal);
		if (v.y < 0)
		{
			v.y = 0.4f * abs(normVel);
		}
		x.y = -0.949;

	}
	if (x.y > 1)
		v.y = -0.1;

}

void Particle::updateOrigin(float x, float y)
{
	orig.x = x;
	orig.y = y;
	orig.z = -2;
}

void Particle::setGravity(bool grav)
{
	gravity = grav;
	releaseClick = grav;
}

void Particle::updatePositions(std::vector<std::shared_ptr<Particle>> particlesPt)
{
	particles = particlesPt;
}
void Particle::setCollision(bool col)
{
	collision = col;
}


