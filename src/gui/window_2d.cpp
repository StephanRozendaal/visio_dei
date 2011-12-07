/*
 * window_2d.cpp
 *
 *  Created on: Dec 7, 2011
 *      Author: stephan
 */
#include "gui.h"
using namespace sf;

window2D::window2D() {
	//TODO: videomode staat nu hard-coded, we hebben een slimmere manier nodig.
	window.Create(VideoMode(800, 600, 32), "GUI", Style::Default); // 4e parameter is weggelaten
}

window2D::~window2D() {
	window.Close();
}

void window2D::addToDraw(image_resource& input) {

	std::vector<unsigned char> data = input.to_sfml();
	image.LoadFromMemory(data.data(), data.size());

	texture.LoadFromImage(image);
	sprite = Sprite(texture);
}
void window2D::Display() {
	while (window.IsOpened())
	     {
	         // Process events
	         sf::Event event;
	         while (window.PollEvent(event))
	         {
	             // Close window : exit
	             if (event.Type == sf::Event::Closed)
	                 window.Close();
	         }

	         // Clear screen
	         window.Clear();

	         // Draw the sprite
	         window.Draw(sprite);

	         // Update the window
	         window.Display();
	     }
}
