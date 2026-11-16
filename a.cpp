#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class MaritimeVessel {
protected:
    string vesselRegistration;
    bool isAtSea;

public:
    static int activeFleetVessels;

    MaritimeVessel(string registration) : vesselRegistration(registration), isAtSea(true) {
        activeFleetVessels++;
    }

    virtual ~MaritimeVessel() {
        activeFleetVessels--;
    }

    virtual void transmitVoyageReport() = 0;
};

int MaritimeVessel::activeFleetVessels = 0;

class RadarNavigationModule : virtual public MaritimeVessel {
protected:
    double radarRangeNauticalMiles;

public:
    RadarNavigationModule(string registration, double range)
        : MaritimeVessel(registration), radarRangeNauticalMiles(range) {}

    void checkRadar() {
        cout << "Radar system [" << vesselRegistration << "] scanning range: " << radarRangeNauticalMiles << " NM." << endl;
    }
};

class PropulsionEngineModule : virtual public MaritimeVessel {
protected:
    double engineThrustMegawatts;

public:
    PropulsionEngineModule(string registration, double thrust)
        : MaritimeVessel(registration), engineThrustMegawatts(thrust) {}

    void checkPropulsion() {
        cout << "Propulsion engine [" << vesselRegistration << "] output: " << engineThrustMegawatts << " MW." << endl;
    }
};

class AutonomousCargoShip : public RadarNavigationModule, public PropulsionEngineModule {
private:
    int containersLoaded;

public:
    AutonomousCargoShip(string registration, double range, double thrust, int containers)
        : MaritimeVessel(registration),
          RadarNavigationModule(registration, range),
          PropulsionEngineModule(registration, thrust),
          containersLoaded(containers) {}

    ~AutonomousCargoShip() {
        cout << "Cargo ship " << vesselRegistration << " berthed and engines shut down." << endl;
    }

    void transmitVoyageReport() override {
        cout << "\n--- Autonomous Cargo Vessel Report: " << vesselRegistration << " ---" << endl;
        checkRadar();
        checkPropulsion();
        cout << "Containers Onboard: " << containersLoaded << " TEU" << endl;
        cout << "Voyage Status: On Schedule" << endl;
    }
};

int main() {
    MaritimeVessel* ship = new AutonomousCargoShip("IMO-984210", 48.5, 64.0, 14500);

    ship->transmitVoyageReport();

    cout << "\nActive Maritime Vessels: " << MaritimeVessel::activeFleetVessels << endl;

    delete ship;

    cout << "Active Vessels After Docking: " << MaritimeVessel::activeFleetVessels << endl;

    return 0;
}
