#pragma once

#include "../includes.hpp"
#include "../macro.hpp"

class SaveMacroLayer : public geode::Popup<>, public TextInputDelegate {

    TextInput* authorInput = nullptr;
    TextInput* descInput = nullptr;
    TextInput* pathInput = nullptr;

    bool setup() override {
        setTitle("Save Macro");

        float w = m_mainLayer->getContentSize().width;
        float h = m_mainLayer->getContentSize().height;

        auto addLabel = [&](const char* text, float y) {
            auto lbl = CCLabelBMFont::create(text, "bigFont.fnt");
            lbl->setAnchorPoint({0.f, 0.5f});
            lbl->setScale(0.32f);
            lbl->setOpacity(200);
            lbl->setPosition(w / 2 - 130, y);
            m_mainLayer->addChild(lbl);
        };

        auto& g = Global::get();
        std::filesystem::path macrosFolder = g.mod->getSettingValue<std::filesystem::path>("macros_folder");
        std::string defaultPath = (macrosFolder / "macro").string();

        addLabel("Author:", h - 55);
        authorInput = TextInput::create(180, "Author");
        authorInput->setPosition(w / 2 + 30, h - 55);
        authorInput->setString(GJAccountManager::sharedState() ? GJAccountManager::sharedState()->m_username : "");
        authorInput->setDelegate(this);
        m_mainLayer->addChild(authorInput);

        addLabel("Description:", h - 85);
        descInput = TextInput::create(180, "Description");
        descInput->setPosition(w / 2 + 30, h - 85);
        descInput->setDelegate(this);
        m_mainLayer->addChild(descInput);

        addLabel("Path:", h - 115);
        pathInput = TextInput::create(180, "Path");
        pathInput->setPosition(w / 2 + 30, h - 115);
        pathInput->setString(defaultPath);
        pathInput->setDelegate(this);
        m_mainLayer->addChild(pathInput);

        auto menu = CCMenu::create();
        menu->setPosition(ccp(0, 0));

        auto saveLabel = CCLabelBMFont::create("Save", "goldFont.fnt");
        saveLabel->setScale(0.7f);
        auto saveBtn = CCMenuItemSpriteExtra::create(saveLabel, this, menu_selector(SaveMacroLayer::onSave));
        saveBtn->setPosition(w / 2, h - 148);
        menu->addChild(saveBtn);

        m_mainLayer->addChild(menu);
        return true;
    }

    void onSave(CCObject*) {
        std::string author = authorInput ? authorInput->getString() : "";
        std::string desc = descInput ? descInput->getString() : "";
        std::string path = pathInput ? pathInput->getString() : "";

        if (path.empty()) {
            FLAlertLayer::create("Error", "Please enter a file path.", "OK")->show();
            return;
        }

        int result = Macro::save(author, desc, path);
        if (result == 0) {
            FLAlertLayer::create("Saved", "Macro saved successfully!", "OK")->show();
            keyBackClicked();
        } else {
            FLAlertLayer::create("Error", ("Failed to save macro. Code: " + std::to_string(result)).c_str(), "OK")->show();
        }
    }

    void textChanged(CCTextInputNode*) override {}

public:

    STATIC_CREATE(SaveMacroLayer, 320, 190)

    static void open() {
        SaveMacroLayer::create()->show();
    }
};
