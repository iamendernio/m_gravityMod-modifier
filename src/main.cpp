// clang-format off
#include <Geode/Bindings.hpp>
#include <Geode/loader/SettingV3.hpp>
#include "../build/bindings/bindings/Geode/modify/PlayerObject.hpp"

// clang-format on

using namespace geode::prelude;

bool m_isEnabled = false;
bool m_showDebugInformation = false;
float m_gravityMod2 = 1.0f;

$on_mod(Loaded) {
    m_isEnabled = Mod::get()->getSettingValue<bool>("Is-Mod-Enabled?");
    listenForSettingChanges<bool>("Is-Mod-Enabled?", [](bool value) {
        m_isEnabled = value;
    });

    m_showDebugInformation = Mod::get()->getSettingValue<bool>("debug");
    listenForSettingChanges<bool>("debug", [](bool value) {
        m_showDebugInformation = value;
    });

    m_gravityMod2 = Mod::get()->getSettingValue<float>("m_gravityMod");
    listenForSettingChanges<float>("m_gravityMod", [](float value) {
        m_gravityMod2 = value;
    });
};

class $modify(ShipFix, PlayerObject) {
    std::string m_gameMode() {
        std::string m_gameMode;
        if (this->m_isShip) m_gameMode = "Ship";
        if (this->m_isBall) m_gameMode = "Ball";
        if (this->m_isBird) m_gameMode = "Ufo";
        if (this->m_isDart) m_gameMode = "Wave";
        if (this->m_isRobot) m_gameMode = "Robot";
        if (this->m_isSpider) m_gameMode = "Spider";
        if (this->m_isSwing) m_gameMode = "Swing";
        if (!this->m_isSpider && !this->m_isSwing && !this->m_isRobot && !this->m_isBall &&
            !this->m_isDart && !this->m_isShip)
            m_gameMode = "Cube";
        return m_gameMode;
    }

    virtual void update(float dt) {
        PlayerObject::update(dt);
        PlayLayer* playLayer = PlayLayer::get();

        if (!this || !playLayer) return;

        if (m_isEnabled) {
            if (this->m_isShip && this->m_isUpsideDown) {
                this->m_gravityMod = m_gravityMod2;
            }

            if (playLayer->m_gameState.m_isDualMode) {
                this->m_gravityMod = 1.0f;
            }
            // if (playLayer->m_player2) {
            //     this->m_gravityMod = 1.0f;
            // }

            //     if (this && this->m_isShip && playLayer && playLayer->m_gameState.m_isDualMode) {
            //         this->m_gravityMod = 0.800f;
            //     }
            //     else {
            //         this->m_gravityMod = 1.0f;
            //     }
            // }
            // else {
            //     this->m_gravityMod = 1.0f;
            // }
        }

        if (m_showDebugInformation) {
            log::info(

                "{}, gravityMod {:2f}, gravity {:2f}, yVelocity {:2f}",
                m_gameMode(),
                m_gravityMod,
                m_gravity,
                m_yVelocity

            );
        }
    }
};
