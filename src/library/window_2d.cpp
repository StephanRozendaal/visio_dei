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

/**
 * In deze methode is nog wat geknoeid, ik heb nu Sprite, Texture en Image als klasse parameters
 * toegevoegd, ze stonden eerst alleen in de scope van de functie addToDraw, maar doordat ze werden
 * verwijderd buiten de scope, werd de data van de Sprite die uiteindelijk op het scherm komt
 * ook verwijderd. Dit resulteerde in een wit vlak op het scherm.
 * TODO: uitzoeken welke objecten bewaard kunnen blijven.
 */
void window2D::addToDraw(image_resource& input) {
  std::vector<unsigned char> data = input.to_sfml();
  image.LoadFromMemory(data.data(), data.size());

  texture.LoadFromImage(image);
  sprite = Sprite(texture);
}

/**
 * Inhoud hiervan is tijdelijk, de main loop van een window moet ergens anders komen.
 */
void window2D::Display() {
  //while (window.IsOpened())
  //   {
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
  //  }
}
