// Datastructures.hh
//
// Student name: Joni Juhola
// Student email: joni.juhola@tuni.fi
// Student number: K440164

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <memory>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

enum Colour {WHITE, GRAY, BLACK};

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int town_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_town_name(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_town_coordinates(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int get_town_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> all_towns();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID min_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID max_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);


    // Phase 2 operations

    // Estimate of performance: N*R
    // Short rationale for estimate: Teiden mukaan lineaarinen. Käydään N kaupunkia läpi
    // ja clear komennolla tyhjennetään kaupungin tie vektori. Pahimmissa tapauksessa
    // jokaisella kaupungilla on R kpl teitä eli teiden max määrä eli clear tehokkuus on myös R.
    void clear_roads();

    // Estimate of performance: N*R*log(R)
    // Short rationale for estimate: Teiden mukaan lineaarinen. Käydään N kaupunkia läpi
    // ja käydään vielä kaupungit tiet läpi ja pahimmassa tapauksessa jokaisella kaupungilla
    // on R kpl teitä eli tehokkuus on N*R. Lisäksi tiet lisätään settiin joka on log(R)
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: R
    // Short rationale for estimate: Kaupungin teiden mukaan lineaarinen. Find komento
    // on keskimäärin vakioaikainen. Toisen kaupungin tiet käydään läpi eli pahimmassa
    // tapauksessa niitä teitä on R kpl. Muut funktion komennot keskimäärin vakioaikaisia
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: R
    // Short rationale for estimate: Kaupungin teiden mukaan lineaarinen. Find komento
    // on keskimäärin vakioaikainen. Toisen kaupungin tiet käydään läpi eli pahimmassa
    // tapauksessa niitä teitä on R kpl.
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: N+R
    // Short rationale for estimate: Syvyys-ensin-haku tehokkuus pahimmillaan on
    // n kaupunkien määrä + R kaarien=teiden määrä
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance: R
    // Short rationale for estimate: Teiden mukaan lineaarinen. Käydään kaupunkien
    // tiet läpi ja poistetaan tie, jos se löytyy. Teitä voi olla R kpl. Find, at ja
    // erase komennot on keskimäärin vakioaikaisia.
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: N+R
    // Short rationale for estimate: Leveys-ensin-haku tehokkuus pahimmillaan on
    // n kaupunkien määrä + R kaarien=teiden määrä
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance: N+R
    // Short rationale for estimate: Syvyys-ensin-haku tehokkuus pahimmillaan on
    // n kaupunkien määrä + R kaarien=teiden määrä
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance: (N+R)*log(N+R)
    // Short rationale for estimate: A* algoritmin tehokkuus on (N+R)*log(N+R), jossa
    // N on kaupunkien määrä ja R kaarien=teiden määrä.
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:
    // Add stuff needed for your class implementation here
    
    struct Node {
        std::string name_;
        TownID id_;
        Coord coord_;
        int tax_;
        std::vector<TownID> vassals_;
        Node* master_;
        std::vector<std::pair<Node*,Distance>> town_roads_;
        Colour colour_;
        float d_;
        Node* path_back_;
    };

    std::unordered_map<TownID, Node> towns_;

    std::pair<TownID,int> deepest_vassal(TownID id,int current_level,
                                         int deepest_level, TownID last);

    int vassals_tax(TownID id,bool first_id);

};

#endif // DATASTRUCTURES_HH
