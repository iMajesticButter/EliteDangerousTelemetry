/**
 * @Author: Brandon Wolenetz
 * @Date:   15-Oct-2020
 * @Project: Elite Dangerous Telemetry System V1
 * @Filename: EDStatusReader.h
 * @Last modified by:   Brandon Wolenetz
 * @Last modified time: 15-Oct-2020
 */

#ifndef ELITE_DANGEROUS_TELEMETRY_V1_EDSTATUSREADER_HEADER
#define ELITE_DANGEROUS_TELEMETRY_V1_EDSTATUSREADER_HEADER

#include "json/json.h"
#include <fstream>
#include <stdint.h>

namespace EliteDangerousTelemetry {

    enum GUIFocus {
        NoFocus,
        RightPanel,
        LeftPanel,
        CommsPanel,
        RolePanel,
        StationServices,
        GalaxyMap,
        SystemMap,
        Orrery,
        FSSmode,
        SAAmode,
        Codex
    };

    enum LegalState {
        Clean,
        IllegalCargo,
        Speeding,
        Wanted,
        Hostile,
        PassengerWanted,
        Warrant
    };

    class EDStatusReader {
      public:
        // public methods
        EDStatusReader();
        ~EDStatusReader();

        void UpdateInfo();

        // parsed data
        // more info at:
        // https://elite-journal.readthedocs.io/en/latest/Status%20File/
        std::string timestamp;

        std::vector<int> pips = std::vector<int>(3, 4);
        int systemsPips       = 4;
        int enginesPips       = 4;
        int weaponsPips       = 4;

        int firegroup = 0;
        GUIFocus guiFocus;
        float fuelMain      = 0.0f;
        float fuelReservoir = 0.0f;
        float fuelTotal     = 0.0f;
        int cargoMass       = 0;
        LegalState legalState;

        // planet information
        float latitude  = 0.0f;
        float longitude = 0.0f;
        float altitude  = 0.0f;
        float heading   = 0.0f;
        std::string bodyName;
        float planetRadius = 0.0f;

        // flags
        uint32_t flags                 = 0;
        bool docked                    = false;
        bool landed                    = false;
        bool landingGearDown           = false;
        bool shieldsUp                 = false;
        bool supercruise               = false;
        bool flightAssistOff           = false;
        bool hardpointsDeployed        = false;
        bool inWing                    = false;
        bool lightsOn                  = false;
        bool cargoScoopDeployed        = false;
        bool silentRunning             = false;
        bool scoopingFuel              = false;
        bool srvHandbreak              = false;
        bool srvTurretView             = false;
        bool srvTurretRetracted        = false;
        bool srvDriveAssist            = false;
        bool massLocked                = false;
        bool fsdCharging               = false;
        bool fsdCooldown               = false;
        bool lowFuel                   = false;
        bool overHeating               = false;
        bool hasLatLong                = false;
        bool isInDanger                = false;
        bool beingInterdicted          = false;
        bool inMainShip                = false;
        bool inFighter                 = false;
        bool inSRV                     = false;
        bool analysisMode              = false;
        bool nightVision               = false;
        bool altitudeFromAverageRadius = false;
        bool fsdJump                   = false;
        bool srvHighBeam               = false;

      private:
        // private methods
        void updateFlags();
        void updatePips();
        void updateFiregroup();
        void updateGUIFocus();
        void updateFuel();
        void updateCargo();
        void updateLegalState();
        void updatePlanetInfo();

        // private variables
        Json::CharReader* m_charReader;
        Json::Value m_root;

        std::ifstream* m_ifs;
    };

} // namespace EliteDangerousTelemetry

#endif
