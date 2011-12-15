/*
 * window_3d.h
 *
 *  Created on: Dec 7, 2011
 *      Author: stephan
 */

#ifndef WINDOW_3D_H_
#define WINDOW_3D_H_

class window3D {
public:
	window3D();
	~Window3D();
	void addToDraw();

protected:

private:
	sf::Window window; // speciaal voor 3D beelden
};


#endif /* WINDOW_3D_H_ */
