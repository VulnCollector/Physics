#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "PhysicsScene.h"
#include <glm\ext.hpp>
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Stick.h"
#include "Pocket.h"
#include "Ball.h"
#include <iostream>
#include <stdio.h> 
using namespace glm;

PhysicsApp::PhysicsApp() {

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() {

	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimeStep(0.01f);

	// balls setup
	glm::vec2 rackOrigin = { 17.0f, 0.0f };

	float ballRadius = 1.5f;
	float ballDiameter = ballRadius * 2.0f;
	float rowSpacing = ballDiameter;						// Horizontal distance between balls in a row
	float colSpacing = ballDiameter * sqrt(3) / 2.0f;	// Vertical offset (60° triangle)

	int ballIndex = 0;
	for (int row = 0; row < 5; ++row)
	{
		for (int i = 0; i <= row; ++i)
		{
			
			Ball* ball = new Ball({ 0,0 }, { 0,0 }, 4, ballRadius, { 1,0,0,1 }, 1);
			float x = rackOrigin.x + row * rowSpacing;
			float y = rackOrigin.y - row * colSpacing / 2.0f + i * colSpacing;

			ball->setPosition({ x,y });

			ball->setLinearDrag(0.3f);
			ball->setAngularDrag(0.3f);

			

			m_physicsScene->addActor(ball);
		}
	}
	int tableWidth = 40;
	int tableHeight = 20;
	// table setup
	Box* topBoundary = new Box(glm::vec2(0, 20), glm::vec2(0, 1), 4.0f, glm::vec2(tableWidth, 2), glm::vec4(0.139f, .1f, .05f, 1), 0, 0.8f);
	Box* leftBoundary = new Box(glm::vec2(-40, 0), glm::vec2(0, 1), 4.0f, glm::vec2(2, tableHeight + 2), glm::vec4(0.139f, .1f, .05f, 1), 0, 0.8f);
	Box* bottomBoundary = new Box(glm::vec2(0, -20), glm::vec2(0, 1), 4.0f, glm::vec2(tableWidth, 2), glm::vec4(0.139f, .1f, .05f, 1), 0, 0.8f);
	Box* rightBoundary = new Box(glm::vec2(39, 0), glm::vec2(0, 1), 4.0f, glm::vec2(2, tableHeight + 2), glm::vec4(0.139f, .1f, .05f, 1), 0, 0.8f);

	topBoundary->setKinematic(true);
	rightBoundary->setKinematic(true);
	bottomBoundary->setKinematic(true);
	leftBoundary->setKinematic(true);

	m_physicsScene->addActor(topBoundary);
	m_physicsScene->addActor(rightBoundary);
	m_physicsScene->addActor(bottomBoundary);
	m_physicsScene->addActor(leftBoundary);

	// table pockets
	pockets.push_back({ {tableWidth - 3, tableHeight - 2}, 3.0f });
	pockets.push_back({ {-tableWidth + 3, tableHeight - 2}, 3.0f });
	pockets.push_back({ {tableWidth - 3, -tableHeight + 2}, 3.0f });
	pockets.push_back({ {-tableWidth + 3, -tableHeight + 2}, 3.0f });
	pockets.push_back({ {0, -tableHeight + 2}, 3.0f });
	pockets.push_back({ {0, tableHeight - 2}, 3.0f });

	// setup cue ball

	cueBall = new Sphere({ -25,0 }, { 0,0 }, 4, ballRadius, { 1,1,1,1 }, 1);

	cueBall->setLinearDrag(0.3f);
	cueBall->setAngularDrag(0.3f);

	m_physicsScene->addActor(cueBall);

	// stick
	stick = new Stick(cueBall->getPosition());

	return true;
	return true;
}

void PhysicsApp::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
	//delete m_physicsScene;
}

void PhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->draw();
	stick->Update(deltaTime);

	// when a ball is pocketed
	std::vector<PhysicsObject*> toRemove;
	auto& actors = m_physicsScene->getActors();

	for (auto& actor : actors)
	{
		Ball* ball = dynamic_cast<Ball*>(actor);
		if (!ball || ball->IsPocketed())
		{
			Sphere* sphere = dynamic_cast<Sphere*>(actor);

			// check if cue ball because it is a sphere and white
			// could improve with a cue ball class
			if (sphere && sphere->getColour() == glm::vec4(1.0f))
			{
				if (sphere->getVelocity() == glm::vec2(0.0f))
				{
					stick->SetPosition(sphere->getPosition());
				}
			}
			continue;
		}

		for (auto& pocket : pockets)
		{
			if (ball->IsInPocket(pocket)) {
				ball->setVelocity({ 0, 0 });
				ball->setKinematic(true);
				ball->SetPocketed(true);

				toRemove.push_back(ball);
				std::cout << "Ball pocketed!" << std::endl;
				break;

			}
		}
	}

	// now remove the pocketed balls
	for (auto& actor : toRemove)
	{
		m_physicsScene->removeActor(actor);
	}



	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		cueBall->setVelocity(stick->GetDirection() * stick->GetPower());
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		stick->setAngle(stick->getAngle() + 0.01f);
		if (stick->getAngle() * 360.0f / (2 * 3.14) > 360)
			stick->setAngle(0);
		
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		if (stick->getAngle() * 360.0f / (2 * 3.14) < 0)
			stick->setAngle(360 / (360.0f / (2 * 3.14)));
		stick->setAngle(stick->getAngle() - 0.01f);
		

	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		stick->setPower(stick->GetPower() + 1.0f);
		if (stick->GetPower() > 250.0f)
			stick->setPower(250.0f);


	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		stick->setPower(stick->GetPower() - 1.0f);
		if (stick->GetPower() < 0.0f)
			stick->setPower(0.0f);


	}
		
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	setBackgroundColour(0, .3, 0, 1);

	// begin drawing sprites
	m_2dRenderer->begin();

	for (auto& pocket : pockets) {
		pocket.Draw();
	}

	stick->Draw();
	

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	char angle[20];
	sprintf(angle, "%.0f", stick->getAngle() * 360.0f / (2 * 3.14));
	char power[20];
	sprintf(power, "%.2f", stick->GetPower());
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	m_2dRenderer->drawText(m_font, "Cue Angle: ", 0, getWindowHeight() - 30);
	m_2dRenderer->drawText(m_font, angle , 200, getWindowHeight() - 30);
	m_2dRenderer->drawText(m_font, "Cue Power: ", 0, getWindowHeight() - 60);
	m_2dRenderer->drawText(m_font, power, 200, getWindowHeight() - 60);
	m_2dRenderer->drawText(m_font, "Controls", getWindowWidth() / 2, getWindowHeight() - 30);
	m_2dRenderer->drawText(m_font, "Up or Down Arrow - Move cue around ball.", getWindowWidth() / 3, getWindowHeight() - 60);
	m_2dRenderer->drawText(m_font, "Left Arrow - Increase shot power.", getWindowWidth() / 3, getWindowHeight() - 90);
	m_2dRenderer->drawText(m_font, "Right Arrow - Decrease shot power.", getWindowWidth() / 3, getWindowHeight() - 120);
	m_2dRenderer->drawText(m_font, "Space - Shoot ball.", getWindowWidth() / 3, getWindowHeight() - 150);

	
	// done drawing sprites
	m_2dRenderer->end();
}