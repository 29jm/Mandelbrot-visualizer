#include <iostream>
#include <complex>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

static const int width = 800;
static const int height = 600;
static const int max_iterations = 100;
static const double displacement = 0.01;

double scale(double value, double imin, double imax, double omin, double omax);

int main() {
	sf::RenderWindow window(VideoMode(width, height), "Mandelbrot set");
	Image frame;
	frame.create(width, height);

	double zoom = 1;
	double xoffs = 0;
	double yoffs = 0;

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Subtract) {
					zoom += zoom/10;
				}
				else if (event.key.code == Keyboard::Add) {
					zoom -= zoom/10;
				}
				else if (event.key.code == Keyboard::Left) {
					xoffs -= displacement*zoom;
				}
				else if (event.key.code == Keyboard::Right) {
					xoffs += displacement*zoom;
				}
				else if (event.key.code == Keyboard::Up) {
					yoffs -= displacement*zoom;
				}
				else if (event.key.code == Keyboard::Down) {
					yoffs += displacement*zoom;
				}
			}
		}

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double xscaled = scale(x, 0, width, -1.5, 0.5);
				double yscaled = scale(y, 0, height, -1, 1);
				complex<double> c(zoom*xscaled + xoffs, zoom*yscaled + yoffs);
				complex<double> z = 0;
				int iteration = 0;

				while (iteration < max_iterations and abs(z) < 2) {
					z = z*z + c;
					iteration += 1;
				}

				Color color;
				color.r = scale(iteration, 0, max_iterations, 255, 0);

				frame.setPixel(x, y, color);
			}
		}

		Texture texture;
		texture.loadFromImage(frame);

		Sprite sprite;
		sprite.setTexture(texture);

		window.draw(sprite);
		window.display();

		sleep(milliseconds(3));
	}
}

double scale(double value, double imin, double imax, double omin, double omax) {
	return (((value - imin)*(omax - omin))/(imax - imin)) + omin;
}

