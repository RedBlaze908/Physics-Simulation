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

    //CHANGE IT PLEASE
    sf::Font font;
    font.loadFromFile("../../../font/OpenSans-Bold.ttf");
    sf::Text t1, t2;
    t2.setFont(font);
    t2.setString("ALPHA VERSION 1.0.0");
    t2.setCharacterSize(20);
    t2.setFillColor(sf::Color::Red);
    t2.setPosition(sf::Vector2f(window.getSize().x / 2, 10));
    
    t1.setFont(font);
    t1.setString("R -> Remove All The Balls");
    t1.setCharacterSize(20);
    t1.setFillColor(sf::Color::White);
    t1.setPosition(sf::Vector2f(window.getSize().x / 2, 40));

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

        //CHANGE IT PLEASE
        ImGui::SFML::Update(window, deltaTime);
        ImGui::SetNextWindowSize(ImVec2(180, 100));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        if (ImGui::Begin("NULL", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar)) {

            ImGui::SliderFloat("Gravity", &gravity, 1, 30);
        }
        ImGui::End();
        


        for (auto& c : ball) {
            if (c.isFalling()) c.fall(gravity);
            else c.bounce();
        }


        //Clear Window
        window.clear();

        //Draw Stuff
        ImGui::SFML::Render(window);
        for (auto& c : ball) c.Draw(window);
        window.draw(t1);
        window.draw(t2);
        window.display();
    }

    Window::~Window();
}