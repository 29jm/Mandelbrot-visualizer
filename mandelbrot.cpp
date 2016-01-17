#include <iostream>
#include <complex>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

static const int width = 1024;
static const int height = 768;
static const double displacement = 0.01;
static const double zoom_factor = 1.0/10.0;

static int max_iterations = 50;

double scale(double value, double imin, double imax, double omin, double omax);
void setPixel(Uint8* pixels, int x, int y, Color color, int width, int height);

int main() {
	Uint8* pixels = new Uint8[width*height*4]();
	Image frame;
	Texture texture;
	Sprite sprite;

	sf::RenderWindow window(VideoMode(width, height), "Mandelbrot set");

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
				switch (event.key.code) {
				case Keyboard::Subtract:
					zoom += zoom*zoom_factor;
					break;
				case Keyboard::Add:
					zoom -= zoom*zoom_factor;
					break;
				case Keyboard::Multiply:
					max_iterations += 50;
					break;
				case Keyboard::Divide:
					max_iterations -= 50;
					break;
				case Keyboard::Left:
					xoffs -= displacement*zoom;
					break;
				case Keyboard::Right:
					xoffs += displacement*zoom;
					break;
				case Keyboard::Up:
					yoffs -= displacement*zoom;
					break;
				case Keyboard::Down:
					yoffs += displacement*zoom;
					break;
				default:
					break;
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

				Color color(Color::Black);
				if (iteration < max_iterations) {
					color.b = scale(iteration, 0, max_iterations, 0, 255);
				}

				setPixel(pixels, x, y, color, width, height);
			}
		}

		frame.create(width, height, pixels);

		texture.loadFromImage(frame);
		sprite.setTexture(texture);

		window.draw(sprite);
		window.display();

		sleep(milliseconds(3));
	}
}

inline
double scale(double value, double imin, double imax, double omin, double omax) {
	return (((value - imin)*(omax - omin))/(imax - imin)) + omin;
}

inline
void setPixel(Uint8* pixels, int x, int y, Color color, int width, int height) {
	pixels[(y*width + x)*4] = color.r;
	pixels[(y*width + x)*4+1] = color.g;
	pixels[(y*width + x)*4+2] = color.b;
	pixels[(y*width + x)*4+3] = color.a;
}

