#include "Engine.h"
#include <iostream>
using namespace std;
Engine::Engine() 
{
    m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Default);
}
void Engine::run() 
{
    Clock clock;
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;

    while (m_Window.isOpen()) 
    {
        float dtAsSeconds = clock.restart().asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}
void Engine::input() 
{
    Event event;
    while (m_Window.pollEvent(event)) 
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }
        else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
        {
            for (int i = 0; i < 5; ++i) 
            {
                int numPoints = rand() % 26 + 25;
                Particle newParticle(m_Window, numPoints, sf::Mouse::getPosition(m_Window));
                m_particles.push_back(newParticle);
            }
        }
    }
}
void Engine::update(float dtAsSeconds) 
{
    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        if (it->getTTL() > 0.0f) 
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else 
        {
            it = m_particles.erase(it);
        }
    }
}
void Engine::draw() 
{
    m_Window.clear();
    for (const auto& particle : m_particles) 
    {
        m_Window.draw(particle);
    }
    m_Window.display();
}