
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include "solve.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "HArCKER BOYYYYYYY");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "fon.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Sprite sprite(texture);
    sprite.setScale((float)1600 / 1080, (float)900 / 608);
    
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "KeyGen.wav"))
        return EXIT_FAILURE;
    // Play the music
    music.play();
    

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("relax, everything is under control", font, 50);
    text.setFillColor(sf::Color::Green);
    text.setPosition(50, 50);
    
    sf::Text timeText("", font, 50);
    timeText.setPosition(50, 130);
    
    
    sf::Image heroimage;
    heroimage.loadFromFile(resourcePath() + "dino.jpeg");
    heroimage.createMaskFromColor(sf::Color(15, 128, 255));

    sf::Texture herotexture;
    herotexture.loadFromImage(heroimage);

    sf::Sprite herospite;
    herospite.setTexture(herotexture);
    herospite.setTextureRect(sf::IntRect(96, 128, 48, 64));
    herospite.setPosition(250, 240);
    herospite.setScale(5, 5);

    sf::Clock clock;
    float CurrentFrame = 0;
    float time = 0;
    float speed = 0.3;
    bool hacked = false;
    
    // Start the game loop
    while (window.isOpen())
    {
        time = clock.getElapsedTime().asMilliseconds();
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            CurrentFrame += 0.005;
            if (CurrentFrame > 3)
                CurrentFrame = 0;
            herospite.move(0, speed);
            herospite.setTextureRect(sf::IntRect(48 * (int)CurrentFrame, 0, 48, 64));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            CurrentFrame += 0.005;
            if (CurrentFrame > 3)
                CurrentFrame = 0;
            herospite.move(0, -speed);
            herospite.setTextureRect(sf::IntRect(48 * (int)CurrentFrame, 192, 48, 64));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            CurrentFrame += 0.005;
            if (CurrentFrame > 3)
                CurrentFrame = 0;
            herospite.move(speed, 0);
            herospite.setTextureRect(sf::IntRect(48 * (int)CurrentFrame, 128, 48, 64));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            CurrentFrame += 0.005;
            if (CurrentFrame > 3)
                CurrentFrame = 0;
            herospite.move(-speed, 0);
            herospite.setTextureRect(sf::IntRect(48 * (int)CurrentFrame, 64, 48, 64));
        }
        
        window.clear();
        window.draw(sprite);
        
        if (time < 10000) {
            
            std::ostringstream tmp;
            tmp << 100 - int(time / 100);
            timeText.setString("Remaining time: " + tmp.str());
            window.draw(timeText);
            
        } else {
            
            if (!hacked) {
                
                solve();
                
                hacked = true;
            }
            
            text.setCharacterSize(88);
            text.setString("eh, your program said \"quack-quack!\"");
            
        }
        
        window.draw(text);
        window.draw(herospite);
        window.display();
    }
    
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
        
    }

    return EXIT_SUCCESS;
}
