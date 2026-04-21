#include <unordered_map>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#pragma once


class Storage {
public:
    static Storage& get() {
        static Storage inst;
        return inst;
    }
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;

    void setRoot(const std::string& newRoot);

    void addTexture(const std::string& name, const std::string& path);
    void addSoundBuffer(const std::string& name, const std::string& path);

    sf::Texture& getTexture(const std::string& name);
    sf::SoundBuffer& getSoundBuffer(const std::string& name);
private:
    Storage() = default;

    std::string root;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};
