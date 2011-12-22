///*
// * gui.cpp PANNENKOEK
// *
// *  Created on: 28 nov. 2011
// *      Author: sjors
// *
// *  Benodigdheden in de include van het project:
// *  - GL
// *  - GLU
// *  - SFML/graphics
// *  - SFML/audio
// *  - SFML/window
// *  - SFML/system
// */
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <string>
//using namespace std;
//
//sf::RenderWindow App;
//sf::Image RealityImage;
//sf::Image OverlayImage;
//sf::Sprite RealitySprite;
//sf::Sprite OverlaySprite;
//
//bool OverlayDrawn;
//
//
//bool setReality(string ImageLocation) {
//
//	if (!RealityImage.LoadFromFile(ImageLocation)) {
//		return false;
//	}
//	else {
//		RealitySprite.SetImage(RealityImage);
//		RealitySprite.SetCenter(0,0);
//		RealitySprite.SetPosition(0.f,0.f);
//		return true;
//	}
//
//}
//
//bool setOverlay(string ImageLocation, int x, int y, int angle, int scale) {
//
//	if (!OverlayImage.LoadFromFile(ImageLocation)) {
//		return false;
//	}
//	else {
//		OverlaySprite.SetImage(OverlayImage);
//		OverlaySprite.SetCenter(0,0);
//		OverlaySprite.SetPosition(x,y);
//		OverlaySprite.SetRotation(angle);
//		OverlaySprite.SetScaleX(0.55f);
//		OverlaySprite.SetScaleY(0.55f);
//		OverlaySprite.SetColor(sf::Color(255,255,255,128));
//		return true;
//	}
//
//}
//
//int main()
//{
//
//	App.Create(sf::VideoMode(850, 465, 32), "GUI");
//
//	if (setReality("img/whitepaper.JPG") == false) return EXIT_FAILURE;
//	if (setOverlay("img/google.jpg",117,70,-9,0.7f) == false) return EXIT_FAILURE;
//
//	sf::String Text("Eigenschappen", sf::Font::GetDefaultFont(), 20.f);
//	Text.SetColor(sf::Color(200, 128, 0));
//	Text.SetPosition(650.f, 5.f);
//
//	App.Clear();
//	App.Draw(RealitySprite);
//	App.Draw(Text);
//	App.Display();
//
//	OverlayDrawn = false;
//
//	//Event Handling
//	while (App.IsOpened()) {
//
//		sf::Event Event;
//		while (App.GetEvent(Event)) {
//
//			if (Event.Type == sf::Event::Closed) App.Close();
//			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) App.Close();
//			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Add) && OverlayDrawn == false) {
//				App.Draw(OverlaySprite);
//				App.Display();
//				OverlayDrawn = true;
//			}
//			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Subtract)) {
//				App.Clear();
//				App.Draw(RealitySprite);
//				App.Draw(Text);
//				App.Display();
//				OverlayDrawn = false;
//			}
//
//		}
//
//	}
//
//	return EXIT_SUCCESS;
//}
//
//
//
