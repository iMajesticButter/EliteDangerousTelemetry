/**
 * @Author: Brandon Wolenetz
 * @Date:   15-Oct-2020
 * @Project: Elite Dangerous Telemetry System V1
 * @Filename: main.cpp
 * @Last modified by:   Brandon Wolenetz
 * @Last modified time: 15-Oct-2020
 */

#include "EDStatusReader.h"
#include <iostream>

#include <TrmGraphics.h>

#include <windows.h>

/*char* userpath = getenv("USERPROFILE");

std::string folder_path =
    userpath +
    std::string("/Saved Games/Frontier Developments/Elite Dangerous/");*/

template <typename t>
void printValWithLabel(std::string label, t value,
                       TrmGraphics::ConsoleGraphics& console) {
    console << label;
    console << value;
    console << "\n";
}

int main() {
    // test program to repetedly print status

    EliteDangerousTelemetry::EDStatusReader status =
        EliteDangerousTelemetry::EDStatusReader();

    TrmGraphics::ConsoleGraphics console =
        TrmGraphics::ConsoleGraphics(100, 30, false, DEFAULT_FONT_SIZE, false);

    while (true) {

        status.UpdateInfo();

        console.draw(true);
        console.setCursorPos(0, 0);

        printValWithLabel("Timestamp: ", status.timestamp, console);

        console << "-------Pips-------\n";

        printValWithLabel("Systems Pips: ", status.systemsPips / 2.0f, console);
        printValWithLabel("Engines Pips: ", status.enginesPips / 2.0f, console);
        printValWithLabel("Weapons Pips: ", status.weaponsPips / 2.0f, console);

        console << "-------Misc-------\n";
        printValWithLabel("Firegroup: ", status.firegroup, console);
        printValWithLabel("GUI focus: ", status.guiFocus, console);
        printValWithLabel("main fuel: ", status.fuelMain, console);
        printValWithLabel("reservoir fuel: ", status.fuelReservoir, console);
        printValWithLabel("total fuel: ", status.fuelTotal, console);
        printValWithLabel("cargo mass: ", status.cargoMass, console);
        printValWithLabel("legal state: ", status.legalState, console);

        console << "-------Systems-------\n";
        printValWithLabel("lights: ", status.lightsOn, console);
        printValWithLabel("night vision: ", status.nightVision, console);
        printValWithLabel("fsd charging: ", status.fsdCharging, console);
        printValWithLabel("analysis mode: ", status.analysisMode, console);

        console << "-------Planet Info-------\n";
        printValWithLabel("latitude: ", status.latitude, console);
        printValWithLabel("longitude: ", status.longitude, console);
        printValWithLabel("altitude: ", status.altitude, console);
        printValWithLabel("heading: ", status.heading, console);
        printValWithLabel("body name: ", status.bodyName, console);
        printValWithLabel("planet radius: ", status.planetRadius, console);
    }

    return 0;
}
