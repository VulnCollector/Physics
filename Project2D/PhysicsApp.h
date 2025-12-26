#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class Sphere;
class Plane;
class Stick;
class Pocket;

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	PhysicsScene* m_physicsScene;
	Stick* stick;
	Sphere* cueBall;

	std::vector<Pocket> pockets;

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	float m_timer;
};