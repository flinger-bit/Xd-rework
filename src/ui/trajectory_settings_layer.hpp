#pragma once

#include "../includes.hpp"
#include "../hacks/show_trajectory.hpp"

class TrajectorySettingsLayer : public geode::Popup<>, public TextInputDelegate {

    TextInput* lengthInput = nullptr;

    bool setup() override {
        setTitle("Trajectory Settings");

        auto& g = Global::get();
        float w = m_mainLayer->getContentSize().width;
        float h = m_mainLayer->getContentSize().height;

        auto menu = CCMenu::create();
        menu->setPosition(ccp(0, 0));

        auto addLabel = [&](const char* text, float x, float y, float scale = 0.32f) {
            auto lbl = CCLabelBMFont::create(text, "bigFont.fnt");
            lbl->setAnchorPoint({0.f, 0.5f});
            lbl->setScale(scale);
            lbl->setOpacity(200);
            lbl->setPosition(x, y);
            m_mainLayer->addChild(lbl);
        };

        addLabel("Length (frames):", w / 2 - 110, h - 50);

        lengthInput = TextInput::create(70, "240");
        lengthInput->setPosition(w / 2 + 50, h - 50);
        lengthInput->setFilter("0123456789");
        auto lenVal = geode::utils::numFromString<int>(g.mod->getSavedValue<std::string>("trajectory_length"));
        lengthInput->setString(g.mod->getSavedValue<std::string>("trajectory_length"));
        lengthInput->setDelegate(this);
        lengthInput->setID("trajectory_length");
        m_mainLayer->addChild(lengthInput);

        addLabel("Both sides:", w / 2 - 110, h - 75);
        auto on  = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        auto off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto toggle = CCMenuItemToggler::create(off, on, this, menu_selector(TrajectorySettingsLayer::onBothSides));
        toggle->setPosition(w / 2 + 50, h - 75);
        toggle->setScale(0.55f);
        toggle->toggle(g.trajectoryBothSides);
        menu->addChild(toggle);

        m_mainLayer->addChild(menu);
        return true;
    }

    void onBothSides(CCObject* obj) {
        auto toggle = static_cast<CCMenuItemToggler*>(obj);
        bool val = !toggle->isToggled();
        Mod::get()->setSavedValue("macro_trajectory_both_sides", val);
        Global::get().trajectoryBothSides = val;
    }

    void textChanged(CCTextInputNode* input) override {
        std::string val = input->getString();
        Mod::get()->setSavedValue("trajectory_length", val);
        auto result = geode::utils::numFromString<int>(val);
        if (result) ShowTrajectory::get().length = result.unwrap();
    }

public:

    STATIC_CREATE(TrajectorySettingsLayer, 280, 140)

    void open(CCObject*) {
        TrajectorySettingsLayer::create()->show();
    }
};
