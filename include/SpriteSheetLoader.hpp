#pragma once

#include "BasicShape.hpp"

namespace cf
{
    class SpriteSheetLoader
    {
        public:
           SpriteSheetLoader(const std::string &path) noexcept;
           std::vector<sf::IntRect> getFrames() const noexcept {return _frames;};
           std::string getSpritePath() const noexcept {return _spritePath;};
        protected:
            std::vector<sf::IntRect> _frames;
            std::string _spritePath;
    };
}