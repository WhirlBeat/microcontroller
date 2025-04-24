#pragma once

#include <drivers.hpp>
#include "../../base/base.hpp"


namespace Engine {
    class ArrowsScenePart : public ScenePart {
    public:
        int row = 0;

        ArrowsScenePart();

        void init(int row);

        void begin() override;
        void tick() override;

        void render();

        void clear_without_arrows();
    };
}