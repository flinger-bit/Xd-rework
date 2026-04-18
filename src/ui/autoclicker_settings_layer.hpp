#pragma once

#include "../includes.hpp"

class AutoclickerLayer : public geode::Popup<>, public TextInputDelegate {

    TextInput* holdInput  = nullptr;
    TextInput* releaseInput = nullptr;
    TextInput* holdInput2 = nullptr;
    TextInput* releaseInput2 = nullptr;

    bool setup() override {
        setTitle("Autoclicker Settings");

        auto menu = CCMenu::create();
        menu->setPosition(ccp(0, 0));

        float w = m_mainLayer->getContentSize().width;
        float h = m_mainLayer->getContentSize().height;

        auto addLabel = [&](const char* text, float x, float y, float scale = 0.32f) {
            auto lbl = CCLabelBMFont::create(text, "bigFont.fnt");
            lbl->setAnchorPoint({0.5f, 0.5f});
            lbl->setScale(scale);
            lbl->setOpacity(200);
            lbl->setPosition(x, y);
            m_mainLayer->addChild(lbl);
        };

        auto addToggle = [&](const char* label, const char* key, float x, float y) {
            addLabel(label, x - 30, y, 0.3f);
            auto on  = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
            auto off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
            auto toggle = CCMenuItemToggler::create(off, on, this, menu_selector(AutoclickerLayer::onToggle));
            toggle->setPosition(x + 40, y);
            toggle->setScale(0.5f);
            toggle->toggle(Mod::get()->getSavedValue<bool>(key));
            toggle->setID(key);
            menu->addChild(toggle);
        };

        addLabel("P1", w / 2 - 55, h - 38, 0.35f);
        addLabel("P2", w / 2 + 55, h - 38, 0.35f);
        addLabel("Hold (frames):",  w * 0.25f, h - 60, 0.3f);
        addLabel("Release (frames):", w * 0.25f, h - 82, 0.3f);

        holdInput = TextInput::create(60, "5");
        holdInput->setPosition(w / 2 - 55, h - 60);
        holdInput->setFilter("0123456789");
        holdInput->setString(std::to_string(Mod::get()->getSavedValue<int64_t>("autoclicker_hold_for")));
        holdInput->setDelegate(this);
        holdInput->setID("autoclicker_hold_for");
        m_mainLayer->addChild(holdInput);

        releaseInput = TextInput::create(60, "5");
        releaseInput->setPosition(w / 2 - 55, h - 82);
        releaseInput->setFilter("0123456789");
        releaseInput->setString(std::to_string(Mod::get()->getSavedValue<int64_t>("autoclicker_release_for")));
        releaseInput->setDelegate(this);
        releaseInput->setID("autoclicker_release_for");
        m_mainLayer->addChild(releaseInput);

        holdInput2 = TextInput::create(60, "5");
        holdInput2->setPosition(w / 2 + 55, h - 60);
        holdInput2->setFilter("0123456789");
        holdInput2->setString(std::to_string(Mod::get()->getSavedValue<int64_t>("autoclicker_hold_for2")));
        holdInput2->setDelegate(this);
        holdInput2->setID("autoclicker_hold_for2");
        m_mainLayer->addChild(holdInput2);

        releaseInput2 = TextInput::create(60, "5");
        releaseInput2->setPosition(w / 2 + 55, h - 82);
        releaseInput2->setFilter("0123456789");
        releaseInput2->setString(std::to_string(Mod::get()->getSavedValue<int64_t>("autoclicker_release_for2")));
        releaseInput2->setDelegate(this);
        releaseInput2->setID("autoclicker_release_for2");
        m_mainLayer->addChild(releaseInput2);

        addToggle("P1", "autoclicker_p1", w / 2 - 55, h - 104);
        addToggle("P2", "autoclicker_p2", w / 2 + 55, h - 104);

        m_mainLayer->addChild(menu);
        return true;
    }

    void onToggle(CCObject* obj) {
        auto toggle = static_cast<CCMenuItemToggler*>(obj);
        Mod::get()->setSavedValue<bool>(toggle->getID(), !toggle->isToggled());
        auto& g = Global::get();
        g.autoclickerP1 = Mod::get()->getSavedValue<bool>("autoclicker_p1");
        g.autoclickerP2 = Mod::get()->getSavedValue<bool>("autoclicker_p2");
    }

    void textChanged(CCTextInputNode* input) override {
        std::string id = input->getID();
        std::string val = input->getString();
        if (val.empty()) return;

        auto result = geode::utils::numFromString<int>(val);
        if (!result) return;
        int v = result.unwrap();

        Mod::get()->setSavedValue<int64_t>(id, v);
        auto& g = Global::get();
        if (id == "autoclicker_hold_for")      g.holdFor    = v;
        if (id == "autoclicker_release_for")   g.releaseFor = v;
        if (id == "autoclicker_hold_for2")     g.holdFor2   = v;
        if (id == "autoclicker_release_for2")  g.releaseFor2 = v;
    }

public:

    STATIC_CREATE(AutoclickerLayer, 260, 160)

    void open(CCObject*) {
        AutoclickerLayer::create()->show();
    }
};
