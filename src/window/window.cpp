#include "window.h"

Window::Window() {}

Window::~Window() { ImGui::SFML::Shutdown(); }

void Window::Run() {
    window.create(sf::VideoMode(sf::Vector2u(1280, 720)), "Physics Simulation");
    ImGui::SFML::Init(window);

    if (!window.isOpen()) {
        std::cerr << "Error while trying to open the window!" << std::endl;
        exit(EXIT_FAILURE);
    }

    open = true;
    sf::Vector2i mousePosWindow;
    sf::Clock delayClock;
    bool canPress = true;
    const float delayTime = 0.2f;


    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;


    while (open) {
        sf::Event evnt;
        mousePosWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (window.pollEvent(evnt)) {
            ImGui::SFML::ProcessEvent(evnt);
            
            if (evnt.type == sf::Event::Closed) {
                window.close();
                open = false;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && canPress) {
                ball.push_back(Ball(mousePos.x, mousePos.y));
                canPress = false;
                delayClock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                ball.clear();
            }
            if (!canPress && delayClock.getElapsedTime().asSeconds() >= delayTime) {
                canPress = true;
            }
        }

        sf::Time deltaTime = deltaClock.restart();

        ImGui::SFML::Update(window, deltaTime);
        //ImGui::ShowDemoWindow();
        
        for (auto& c : ball) {
            if (c.isFalling()) c.fall(gravity);
            else c.bounce();
        }


        //Clear Window
        window.clear();

        //Draw Stuff
        ImGui::SFML::Render(window);
        for (auto& c : ball) c.Draw(window);
        window.display();
    }

    Window::~Window();
}