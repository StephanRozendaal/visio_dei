/*
 * window_2d.h
 *
 *  Created on: Dec 6, 2011
 *      Author: stephan
 */

#ifndef WINDOW_2D_H_
#define WINDOW_2D_H_
#include "library.h"
class window2D {
public:
	window2D();
	~window2D();
	void addToDraw(image_resource&);
	void Display();
private:
	sf::RenderWindow window; // speciaal voor 2D beelden
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
protected:

};

#endif /* WINDOW_2D_H_ */
