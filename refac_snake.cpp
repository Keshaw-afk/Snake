#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>

const int width = 800;
const int height = 800;
const sf::Color screen_color_red = sf::Color::Red;
const int initial_snake_length = 5;
const sf::Color snake_outline_black = sf::Color::Black;
const sf::Color snake_body_color_white = sf::Color::White;
const sf::Color snake_head_color_green = sf::Color::Green;
const float snake_unit_side = 30;
const float snake_velocity = 30;
enum {UP, DOWN, LEFT, RIGHT};

class Snake
{
    public:
    Snake();
    std::vector<sf::RectangleShape> snake_body;
    int snake_length;
    void render_snake(sf::RenderWindow& window);
    void move(sf::Event event);

};

Snake::Snake():snake_length(initial_snake_length)
{
    for (int i = 0; i<snake_length; i++)
    {
        sf::RectangleShape square;
        if (i == 0)
        {
            square.setFillColor(snake_head_color_green);
        }
        else
        {
            square.setFillColor(snake_body_color_white);
        }
        square.setOutlineColor(snake_outline_black);
        square.setOutlineThickness(4.0);
        square.setPosition({(float)(width/2.0 + snake_unit_side*i), height/2.0});
        square.setSize({snake_unit_side, snake_unit_side});
        snake_body.push_back(square);

    }
    snake_body[0].setFillColor(sf::Color::Green); //head

}

void Snake::render_snake(sf::RenderWindow& window)
{
   for (auto& square : snake_body)
    {
        window.draw(square);
    }
}

void Snake::move(sf::Event event)
{
    sf::Vector2f movement({0.0f, 0.0f});
    
    sf::Keyboard::Key key = event.key.code;

    if (key == sf::Keyboard::W)
    {
        movement = {0.0f, -snake_velocity};
    }
    if (key == sf::Keyboard::A)
    {
        movement = {-snake_velocity, 0.0f};
    }
    if (key == sf::Keyboard::S)
    {
        movement = {0.0f, snake_velocity};
    }
    if (key == sf::Keyboard::D)
    {
        movement = {snake_velocity, 0.0f};
    }

    for (int i = snake_length-1; i>0; i--)
    {
        snake_body[i].setPosition(snake_body[i-1].getPosition());
    }
    snake_body[0].move(movement);

}

class Game
{
    public:
    Game();
    void run();

    private:
    Snake snake;
    sf::RenderWindow window;
    void process_events();
    void update();
    void render();

};

Game::Game():window(sf::VideoMode({width, height}), "Snake" )
{
    
}

void Game::run()
{
    while(window.isOpen())
    {
       render();
       process_events();
       update();
    }
}

void Game::render()
{
    window.clear(screen_color_red);
    snake.render_snake(window);
    window.display();
}

void Game::process_events()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                snake.move(event);
                break;
        }
    }
}

void Game::update()
{

}

int main()
{
    Game game;
    game.run();
}
