/**
 * @Author: Brandon Wolenetz
 * @Date:   15-Oct-2020
 * @Project: Elite Dangerous Telemetry System V1
 * @Filename: EDStatusReader.cpp
 * @Last modified by:   Brandon Wolenetz
 * @Last modified time: 15-Oct-2020
 */

#include "EDStatusReader.h"
#include <iostream>
#include <string>

#include <windows.h>

namespace EliteDangerousTelemetry {

    // filepath for the Status json file
    char* userpath = getenv("USERPROFILE");
    std::string status_path =
        userpath +
        std::string(
            "/Saved Games/Frontier Developments/Elite Dangerous/Status.json");

    // public methods
    EDStatusReader::EDStatusReader() {
        // initialize ifstream
        // std::cout << "creating ifstream: " << status_path << std::endl;
        m_ifs = new std::ifstream(status_path);

        if (!*m_ifs) {
            std::cerr << "faild to create ifstream!" << std::endl;
            throw std::runtime_error("faild to create ifstream!");
        }

        // create charReader
        // std::cout << "creating char reader" << std::endl;
        Json::CharReaderBuilder charReaderBuilder;
        m_charReader = charReaderBuilder.newCharReader();
    }
    EDStatusReader::~EDStatusReader() {
        m_ifs->close();
        delete m_ifs;
        delete m_charReader;
    }

    void EDStatusReader::UpdateInfo() {
        // seek to start of file
        m_ifs->clear();
        m_ifs->seekg(0);

        // read file
        std::string content;
        std::string buf;
        while (!m_ifs->eof()) {
            content = buf;
            std::getline(*m_ifs, buf);
        }

        if (content.size() == 0)
            return;

        // parse file
        std::string errors;
        try {
            if (m_charReader->parse(content.data(),
                                    content.data() + content.length(), &m_root,
                                    &errors)) {
                // save parsed information
                timestamp = m_root.get("timestamp", "null").asString();

                try {
                    updateFlags();
                } catch (const std::exception& exc) {
                    std::cerr << "Unknown Error Updating Flags: " << exc.what()
                              << std::endl;
                }
                try {
                    updatePips();
                } catch (const std::exception& exc) {
                    std::cerr << "Unknown Error Updating Pips: " << exc.what()
                              << std::endl;
                }
                try {
                    updateFiregroup();
                } catch (const std::exception& exc) {
                    std::cerr
                        << "Unknown Error Updating Firegroup: " << exc.what()
                        << std::endl;
                }
                try {
                    updateGUIFocus();
                } catch (const std::exception& exc) {
                    std::cerr
                        << "Unknown Error Updating GUI Focus: " << exc.what()
                        << std::endl;
                }
                try {
                    updateFuel();
                } catch (const std::exception& exc) {
                    std::cerr << "Unknown Error Updating Fuel: " << exc.what()
                              << std::endl;
                }
                try {
                    updateCargo();
                } catch (const std::exception& exc) {
                    std::cerr << "Unknown Error Updating Cargo: " << exc.what()
                              << std::endl;
                }
                try {
                    updateLegalState();
                } catch (const std::exception& exc) {
                    std::cerr
                        << "Unknown Error Updating Legal State: " << exc.what()
                        << std::endl;
                }
                try {
                    updatePlanetInfo();
                } catch (const std::exception& exc) {
                    std::cerr
                        << "Unknown Error Updating Planet Info: " << exc.what()
                        << std::endl;
                }

            } else {
                std::cerr << errors << std::endl;
                std::cout << content << std::endl;
                Sleep(1000000);
            }
        } catch (const std::exception& exc) {
            std::cerr << exc.what() << std::endl;
        }
    }

    bool getFlag(uint32_t f, int k) {
        return (f & (1 << k)) >> k;
    }

    // private methods
    void EDStatusReader::updateFlags() {
        if (m_root["Flags"].isNull())
            return;

        int flagsTemp = m_root.get("Flags", 0).asUInt64();

        flags = flagsTemp;

        docked                    = getFlag(flags, 0);
        landed                    = getFlag(flags, 1);
        landingGearDown           = getFlag(flags, 2);
        shieldsUp                 = getFlag(flags, 3);
        supercruise               = getFlag(flags, 4);
        flightAssistOff           = getFlag(flags, 5);
        hardpointsDeployed        = getFlag(flags, 6);
        inWing                    = getFlag(flags, 7);
        lightsOn                  = getFlag(flags, 8);
        cargoScoopDeployed        = getFlag(flags, 9);
        silentRunning             = getFlag(flags, 10);
        scoopingFuel              = getFlag(flags, 11);
        srvHandbreak              = getFlag(flags, 12);
        srvTurretView             = getFlag(flags, 13);
        srvTurretRetracted        = getFlag(flags, 14);
        srvDriveAssist            = getFlag(flags, 15);
        massLocked                = getFlag(flags, 16);
        fsdCharging               = getFlag(flags, 17);
        fsdCooldown               = getFlag(flags, 18);
        lowFuel                   = getFlag(flags, 19);
        overHeating               = getFlag(flags, 20);
        hasLatLong                = getFlag(flags, 21);
        isInDanger                = getFlag(flags, 22);
        beingInterdicted          = getFlag(flags, 23);
        inMainShip                = getFlag(flags, 24);
        inFighter                 = getFlag(flags, 25);
        inSRV                     = getFlag(flags, 26);
        analysisMode              = getFlag(flags, 27);
        nightVision               = getFlag(flags, 28);
        altitudeFromAverageRadius = getFlag(flags, 29);
        fsdJump                   = getFlag(flags, 30);
        srvHighBeam               = getFlag(flags, 31);
    }

    void EDStatusReader::updatePips() {
        if (m_root["Pips"].isNull()) {
            return;
        }

        pips[0] = m_root["Pips"][0].asInt();
        pips[1] = m_root["Pips"][1].asInt();
        pips[2] = m_root["Pips"][2].asInt();

        systemsPips = pips[0];
        enginesPips = pips[1];
        weaponsPips = pips[2];
    }

    void EDStatusReader::updateFiregroup() {
        if (m_root["FireGroup"].isNull()) {
            return;
        }

        firegroup = m_root["FireGroup"].asInt();
    }

    void EDStatusReader::updateGUIFocus() {
        if (m_root["GuiFocus"].isNull()) {
            return;
        }

        switch (m_root["GuiFocus"].asInt()) {
        default:
        case 0:
            guiFocus = GUIFocus::NoFocus;
            break;
        case 1:
            guiFocus = GUIFocus::RightPanel;
            break;
        case 2:
            guiFocus = GUIFocus::LeftPanel;
            break;
        case 3:
            guiFocus = GUIFocus::CommsPanel;
            break;
        case 4:
            guiFocus = GUIFocus::RolePanel;
            break;
        case 5:
            guiFocus = GUIFocus::StationServices;
            break;
        case 6:
            guiFocus = GUIFocus::GalaxyMap;
            break;
        case 7:
            guiFocus = GUIFocus::SystemMap;
            break;
        case 8:
            guiFocus = GUIFocus::Orrery;
            break;
        case 9:
            guiFocus = GUIFocus::FSSmode;
            break;
        case 10:
            guiFocus = GUIFocus::SAAmode;
            break;
        case 11:
            guiFocus = GUIFocus::Codex;
        }
    }

    void EDStatusReader::updateFuel() {
        if (m_root["Fuel"].isNull()) {
            return;
        }

        if (!m_root["Fuel"]["FuelMain"].isNull()) {
            fuelMain = m_root["Fuel"]["FuelMain"].asFloat();
        }

        if (!m_root["Fuel"]["FuelReservoir"].isNull()) {
            fuelReservoir = m_root["Fuel"]["FuelReservoir"].asFloat();
        }

        fuelTotal = fuelMain + fuelReservoir;
    }

    void EDStatusReader::updateCargo() {
        if (m_root["Cargo"].isNull()) {
            return;
        }

        cargoMass = m_root["Cargo"].asInt();
    }

    void EDStatusReader::updateLegalState() {
        if (m_root["LegalState"].isNull()) {
            return;
        }

        // yay! an if-ladder!!!!

        std::string str = m_root["LegalState"].asString();

        if (str == "Clean")
            legalState = LegalState::Clean;
        else if (str == "IllegalCargo")
            legalState = LegalState::IllegalCargo;
        else if (str == "Speeding")
            legalState = LegalState::Speeding;
        else if (str == "Wanted")
            legalState = LegalState::Wanted;
        else if (str == "Hostile")
            legalState = LegalState::Hostile;
        else if (str == "PassengerWanted")
            legalState = LegalState::PassengerWanted;
        else if (str == "Warrant")
            legalState = LegalState::Warrant;
    }

    void EDStatusReader::updatePlanetInfo() {
        if (!hasLatLong) {
            latitude     = 0;
            longitude    = 0;
            altitude     = 0;
            planetRadius = 0;
            heading      = 0;
            bodyName     = "null";
            return;
        }

        if (!m_root["Latitude"].isNull()) {
            latitude = m_root["Latitude"].asFloat();
        }

        if (!m_root["Longitude"].isNull()) {
            longitude = m_root["Longitude"].asFloat();
        }

        if (!m_root["Altitude"].isNull()) {
            altitude = m_root["Altitude"].asFloat();
        }

        if (!m_root["Heading"].isNull()) {
            heading = m_root["Heading"].asFloat();
        }

        if (!m_root["PlanetRadius"].isNull()) {
            planetRadius = m_root["PlanetRadius"].asFloat();
        }

        if (!m_root["BodyName"].isNull()) {
            bodyName = m_root["BodyName"].asString();
        }
    }

} // namespace EliteDangerousTelemetry
