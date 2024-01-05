#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/nes.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    nes* system = new nes(&window);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}