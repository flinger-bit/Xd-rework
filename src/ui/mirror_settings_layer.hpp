#pragma once

#include "../includes.hpp"

class MirrorSettingsLayer : public geode::Popup<> {

    bool setup() override {
        setTitle("Mirror Settings");

        float w = m_mainLayer->getContentSize().width;
        float h = m_mainLayer->getContentSize().height;

        auto menu = CCMenu::create();
        menu->setPosition(ccp(0, 0));

        auto lbl = CCLabelBMFont::create("Invert Mirror:", "bigFont.fnt");
        lbl->setAnchorPoint({0.f, 0.5f});
        lbl->setScale(0.35f);
        lbl->setOpacity(200);
        lbl->setPosition(w / 2 - 100, h / 2);
        m_mainLayer->addChild(lbl);

        auto on  = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        auto off = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto toggle = CCMenuItemToggler::create(off, on, this, menu_selector(MirrorSettingsLayer::onInvert));
        toggle->setPosition(w / 2 + 70, h / 2);
        toggle->setScale(0.55f);
        toggle->toggle(Mod::get()->getSavedValue<bool>("p2_input_mirror_inverted"));
        menu->addChild(toggle);

        m_mainLayer->addChild(menu);
        return true;
    }

    void onInvert(CCObject* obj) {
        auto toggle = static_cast<CCMenuItemToggler*>(obj);
        Mod::get()->setSavedValue("p2_input_mirror_inverted", !toggle->isToggled());
    }

public:

    STATIC_CREATE(MirrorSettingsLayer, 240, 100)

    void open(CCObject*) {
        MirrorSettingsLayer::create()->show();
    }
};
