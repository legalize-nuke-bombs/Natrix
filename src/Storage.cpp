#include "Storage.hpp"


void Storage::setRoot(const std::string& newRoot) {
    root = newRoot;
}
void Storage::addTexture(const std::string& name, const std::string& path) {
    std::string fullPath = root + "/" + path;
    if (!textures[name].loadFromFile(fullPath)) {
        throw std::runtime_error("Failed to load texture: " + fullPath);
    }
}
void Storage::addSoundBuffer(const std::string& name, const std::string& path) {
    std::string fullPath = root + "/" + path;
    if (!soundBuffers[name].loadFromFile(fullPath)) {
        throw std::runtime_error("Failed to load sound buffer: " + fullPath);
    }
}
sf::Texture& Storage::getTexture(const std::string& name) {
    return textures.at(name);
}
sf::SoundBuffer& Storage::getSoundBuffer(const std::string& name) {
    return soundBuffers.at(name);
}
