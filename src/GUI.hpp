#include <optional>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GUIState.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"


#pragma once


class GUI {
public:
    GUI();
    void start();
private:
    void handleCellClick(const CellClick& click);
    void playSound(const std::string& name);

    sf::RenderWindow window;
    GUIState state;
    Renderer renderer;
    std::optional<sf::Sound> sound;
};
