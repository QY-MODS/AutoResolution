#include "Settings.h"

namespace Settings {
    inline float ratio = 1.0f;
};

void GetINISettings() {
    // We have one section called [Settings] and just one key called "fRatio" with value 1.0

    // first make sure the INI file exists
    const bool iniExists = std::filesystem::exists(std::format("Data/SKSE/Plugins/{}.ini", Utilities::mod_name));
    if (!iniExists) {
        // make the INI file
        std::ofstream iniFile(std::format("Data/SKSE/Plugins/{}.ini", Utilities::mod_name));
        iniFile << "[Settings]\n";
        iniFile << "fRatio=1.0\n";
        iniFile.close();

        logger::info("INI file created.");

        return;
    } else {
        logger::info("INI file exists.");
    }

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(std::format("Data/SKSE/Plugins/{}.ini", Utilities::mod_name).c_str());

    const float new_ratio = ini.GetDoubleValue("Settings", "fRatio", Settings::ratio);
    Settings::ratio = std::min(std::max(new_ratio, 0.1f), 1.0f);
    logger::info("fRatio: {}", Settings::ratio);

    // write the value back to the INI file
    ini.SetValue("Settings", "fRatio", std::to_string(Settings::ratio).c_str());

    ini.SaveFile(std::format("Data/SKSE/Plugins/{}.ini", Utilities::mod_name).c_str());

    logger::info("INI file updated.");
};

void ReadWriteDisplayTweaksINI() {
    // first make sure the INI file exists
    const bool iniExists = std::filesystem::exists("Data/SKSE/Plugins/SSEDisplayTweaks.ini");
    if (!iniExists) {
		logger::error("SSEDisplayTweaks.ini does not exist.");
		return;
	}
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile("Data/SKSE/Plugins/SSEDisplayTweaks.ini");
    
    // get user's actual windows display resolution
    auto displayWidth = GetSystemMetrics(SM_CXSCREEN);
    auto displayHeight = GetSystemMetrics(SM_CYSCREEN);
    logger::info("Display resolution: {}x{}", displayWidth, displayHeight);
    logger::info("Ratio: {}", Settings::ratio);

    // apply the ratio to the display resolution
    displayWidth = displayWidth * Settings::ratio;
    displayHeight = displayHeight * Settings::ratio;

    const auto windows_resolution = fmt::format("{}x{}", displayWidth, displayHeight);
    
    auto resolutions = ini.GetValue("Render", "Resolution", windows_resolution.c_str());
    logger::info("Resolution: {}", resolutions);
    // set the Display Tweaks resolution to the user's display resolution
    ini.SetValue("Render", "Resolution", windows_resolution.c_str());
    ini.SaveFile("Data/SKSE/Plugins/SSEDisplayTweaks.ini");
};
