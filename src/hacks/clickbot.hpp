#pragma once
#include "../includes.hpp"

const std::vector<std::string> buttonNames = {
    "hold_click", "release_click",
    "hold_left",  "release_left",
    "hold_right", "release_right"
};

const std::unordered_map<int, std::string> buttonInts = {
    {1, "click"}, {2, "left"}, {3, "right"}
};

enum class SoundPack {
    Default    = 0,
    Gaming     = 1,
    Office     = 2,
    Mechanical = 3,
    Laptop     = 4,
    Wood       = 5,
    Custom     = 99
};

static const std::vector<std::pair<int, std::string>> soundPackList = {
    { (int)SoundPack::Default,    "Default" },
    { (int)SoundPack::Gaming,     "Gaming Mouse" },
    { (int)SoundPack::Office,     "Office Mouse" },
    { (int)SoundPack::Mechanical, "Mechanical Keyboard" },
    { (int)SoundPack::Laptop,     "Laptop Trackpad" },
    { (int)SoundPack::Wood,       "Tabla de Picar" },
    { (int)SoundPack::Custom,     "Custom" }
};

static const std::unordered_map<int, std::string> soundPackDirNames = {
    { (int)SoundPack::Default,    "default" },
    { (int)SoundPack::Gaming,     "gaming" },
    { (int)SoundPack::Office,     "office" },
    { (int)SoundPack::Mechanical, "mechanical" },
    { (int)SoundPack::Laptop,     "laptop" },
    { (int)SoundPack::Wood,       "wood" },
    { (int)SoundPack::Custom,     "custom" }
};

struct ClickSetting {
    bool disabled = false;
    std::filesystem::path path;
    int volume = 75;
    float pitch = 1.f;
};

template<>
struct matjson::Serialize<ClickSetting> {
    static ClickSetting from_json(matjson::Value const& value) {
        ClickSetting setts;
        setts.disabled = value["disabled"].asBool().unwrapOr(false);
        setts.path     = std::filesystem::path(value["path"].asString().unwrapOrDefault());
        setts.volume   = value["volume"].asInt().unwrapOr(75);
        setts.pitch    = static_cast<float>(value["pitch"].asDouble().unwrapOr(1.0));
        return setts;
    }

    static matjson::Value to_json(ClickSetting const& sett) {
        matjson::Value obj;
        obj["disabled"] = sett.disabled;
        obj["path"]     = sett.path.string();
        obj["volume"]   = sett.volume;
        obj["pitch"]    = sett.pitch;
        return obj;
    }
};

class Clickbot {
public:
    FMOD::System*       system     = nullptr;
    FMOD::ChannelGroup* clickGroup = nullptr;

    static constexpr int SOUND_COUNT = 6;

    FMOD::Sound*   sounds[SOUND_COUNT]   = {};
    FMOD::Channel* channels[SOUND_COUNT] = {};

    static auto& get() {
        static Clickbot instance;
        return instance;
    }

    static int  nameToIndex(const std::string& id);
    static void initSystem();
    static void loadSoundsForPack(SoundPack pack);
    static void playSound(const std::string& id, bool player2 = false, bool isDual = false);
    static void updateSounds();
    static std::filesystem::path getPackDir(SoundPack pack);
    static SoundPack getCurrentPack();
};
