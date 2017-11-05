#include "hlt/hlt.hpp"
#include "hlt/navigation.hpp"
#include "Vector2.h"

std::vector<hlt::Move> moves;

bool DockPlanet(const hlt::Map& a_map, const hlt::Ship& a_ship, hlt::Planet& a_planet) {

	if (a_ship.can_dock(a_planet)) {
		a_planet.unitsGettingSentTo++;
		moves.push_back(hlt::Move::dock(a_ship.entity_id, a_planet.entity_id));
		return true;
	}

	const hlt::possibly<hlt::Move> move = hlt::navigation::navigate_ship_to_dock(a_map, a_ship, a_planet, hlt::constants::MAX_SPEED);

	if (move.second) {
		moves.push_back(move.first);
		a_planet.unitsGettingSentTo++;
		return true;
	}
	
	return false;
}

bool AttackShip(const hlt::Map& a_Map, const hlt::Ship& a_Ship, const hlt::Ship& a_Target) {
}

bool AttackClosestShip(const hlt::Map& a_Map, const hlt::Ship& a_Ship, std::vector<const hlt::Ship*>& a_EnemyShipsByDistance) {
}

int main() {
    const hlt::Metadata metadata = hlt::initialize("IvanTheTerrible");
    const hlt::PlayerId player_id = metadata.player_id;

    const hlt::Map& initial_map = metadata.initial_map;

    // We now have 1 full minute to analyse the initial map.
    std::ostringstream initial_map_intelligence;
    initial_map_intelligence
            << "width: " << initial_map.map_width
            << "; height: " << initial_map.map_height
            << "; players: " << initial_map.ship_map.size()
            << "; my ships: " << initial_map.ship_map.at(player_id).size()
            << "; planets: " << initial_map.planets.size();
    hlt::Log::log(initial_map_intelligence.str());

    std::vector<hlt::Move> moves;
    for (;;) {
        moves.clear();
        const hlt::Map map = hlt::in::get_map();

        for (const hlt::Ship& ship : map.ships.at(player_id)) {
            if (ship.docking_status != hlt::ShipDockingStatus::Undocked) {
                continue;
            }

            for (const hlt::Planet& planet : map.planets) {
                if (planet.owned) {
                    continue;
                }

                if (ship.can_dock(planet)) {
                    moves.push_back(hlt::Move::dock(ship.entity_id, planet.entity_id));
                    break;
                }

                const hlt::possibly<hlt::Move> move =
                        hlt::navigation::navigate_ship_to_dock(map, ship, planet, hlt::constants::MAX_SPEED);
                if (move.second) {
                    moves.push_back(move.first);
                }

                break;
            }
        }

        if (!hlt::out::send_moves(moves)) {
            hlt::Log::log("send_moves failed; exiting");
            break;
        }
    }
}
