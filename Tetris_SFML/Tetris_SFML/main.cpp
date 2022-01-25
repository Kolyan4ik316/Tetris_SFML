#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

static const float SCALE = 30.f;

void CreateGround(b2World& World, float X, float Y);

void CreateBox(b2World& World, int MouseX, int MouseY);

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Window");
    window->setFramerateLimit(60u);
    sf::RectangleShape rect(sf::Vector2f(32.0f, 32.0f));
    rect.setFillColor(sf::Color::Cyan);

    sf::RectangleShape ground(sf::Vector2f(800.0f, 16.0f));
    ground.setFillColor(sf::Color::Magenta);

    b2Vec2 Gravity(0.f, 9.8f);
    b2World World(Gravity);
    CreateGround(World, 400.f, 500.f);
    while (window->isOpen())
    {
        sf::Event m_event;

        while (window->pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                int MouseX = sf::Mouse::getPosition(*window).x;
                int MouseY = sf::Mouse::getPosition(*window).y;
                CreateBox(World, MouseX, MouseY);
            }
            
        }
        World.Step(1 / 60.f, 8, 3);
        int BodyCount = 0;
        window->clear();
        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                rect.setOrigin(16.f, 16.f);
                rect.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                rect.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
                window->draw(rect);
                ++BodyCount;
            }
            else
            {
                ground.setOrigin(400.f, 8.f);
                ground.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
                ground.setRotation(180 / b2_pi * BodyIterator->GetAngle());
                window->draw(ground);
            }
        }
        window->display();
    }
    delete window;
    window = NULL;
}
void CreateBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

void CreateGround(b2World& World, float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}