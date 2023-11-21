#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    //memory allocation

    //allocate mem for frame count
    unsigned int loopCount{0};

    //alocate memory for a window called 'window1'
    sf::RenderWindow window1(sf::VideoMode(800, 800), "SFML works 2!");

    //allocate mem for shape called 'polygon';
    sf::ConvexShape polygon;

    //set params for 'polygon'
    polygon.setPointCount(3);
    polygon.setPoint(0, sf::Vector2f(0, 0));
    polygon.setPoint(1, sf::Vector2f(0, 20));
    polygon.setPoint(2, sf::Vector2f(50, 10));
    polygon.setOutlineColor(sf::Color::Red);
    polygon.setOutlineThickness(5);
    polygon.setPosition(10, 20);


    // Create a font
    sf::Font font;
    if (!font.loadFromFile("tahoma.ttf")) {
        // Handle error: unable to load font
        return EXIT_FAILURE;
    }
    //Time stuff
    auto t1 = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(t1);
    
   
    // Create a text object
    sf::Text text;
    text.setFont(font); // Set the font
    //text.setString(std::ctime(&current_time_t)); // Set the text
    text.setCharacterSize(24); // Set the character size
    text.setFillColor(sf::Color::White); // Set the fill color

    //Create a second text object for display frame count
    sf::Text text2;
    text2.setFont(font); // Set the font
    //text2.setString("TESTING"); // Set the text
    text2.setCharacterSize(24); // Set the character size
    text2.setFillColor(sf::Color::White); // Set the fill color
    text2.setPosition(0, 100);

    //shape.setFillColor(sf::Color::Red);
    //polygon.setFillColor(sf::Color::Red);

/*
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
*/

auto start_time = std::chrono::high_resolution_clock::now();

float movement{0.0f};

int desiredFPS = 120;

//update(render) and display frame loop 
    while (window1.isOpen())
    {
        //Time stuff
        //std::time_t start_t = std::chrono::high_resolution_clock::to_time_t(start_time);
        auto end_time = std::chrono::high_resolution_clock::now();
        //std::time_t end_t = std::chrono::high_resolution_clock::to_time_t(end_time);

        // Calculate the duration between iterations
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);        

        auto deltaTime = duration.count();
        auto actualFPS = 1000000.0f/deltaTime;

        // Convert the time point to a time_t object
        //std::time_t duration_t = std::chrono::high_resolution_clock::to_time_t(d);
        text.setString(std::to_string(actualFPS)); // Set the text, either 'deltaTime' or 'movement' or 'fps'

        //Set frame count text
        loopCount++;
        //convert loopCount to string and put it into text2
        text2.setString(std::to_string(loopCount));

        //handle input events
        sf::Event event2;
        while (window1.pollEvent(event2))
        {
            if (event2.type == sf::Event::Closed)
                window1.close();
        }
        
        movement += 5.0f * (deltaTime/1000000.0f);
        //update
        text2.setPosition(0, 100);
        polygon.setPosition(10, 20 + movement);

        //render(display)
        window1.clear();
        window1.draw(polygon);
        window1.draw(text);
        window1.draw(text2);
        window1.display();

       
        //Grab time at this point for calculation of minTime
        auto beforeSleep_time = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - beforeSleep_time);
        auto minTime = duration2.count();

        start_time = end_time;
        
        std::this_thread::sleep_for(std::chrono::milliseconds((1000/desiredFPS) - (1000/minTime)));
    }

    return 0;
}