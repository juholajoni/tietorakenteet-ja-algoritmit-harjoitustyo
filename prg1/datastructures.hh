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

    // Estimate of performance: Vakio
    // Short rationale for estimate: size() tehokkuus on vakio
    unsigned int town_count();

    // Estimate of performance: N
    // Short rationale for estimate: clear() tehokkuus on lineaarinen
    void clear_all();

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() ja insert molemmat keskiarvoltaan vakioita
    // ja huonoimmaissa tapauksessa lineaarisia, jolloin add_town on lineaarinen
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() keskimäärin vakio ja huonoimmassa
    // tapauksessa lineaarinen
    Name get_town_name(TownID id);

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() keskimäärin vakio ja huonoimmassa
    // tapauksessa lineaarinen
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() keskimäärin vakio ja huonoimmassa
    // tapauksessa lineaarinen
    int get_town_tax(TownID id);

    // Estimate of performance: N
    // Short rationale for estimate: Käydään towns_ map läpi ja jokainen kaupunki
    // lisätään vektoriin push_back metodilla joka on vakio eli funktio on
    // lineaarinen
    std::vector<TownID> all_towns();

    // Estimate of performance: N
    // Short rationale for estimate: Käydään towns_ map läpi ja kaupunki saatetaan
    // lisätä vektoriin push_back metodilla joka on vakio eli funktio on
    // lineaarinen
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() ja at() metodit keskiarvoltaan vakioita
    // ja huonoimmassa tapauksissa lineaarisia.
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: N
    // Short rationale for estimate: for loopit lineaarisia ja sort keskimäärin
    // lineaarinen. Mitkään näistä ei ole päällekkäin, joten funktion tehokkuus
    // on lineaarinen
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: N
    // Short rationale for estimate: for loopit lineaarisia ja sort keskimäärin
    // lineaarinen. Mitkään näistä ei ole päällekkäin, joten funktion tehokkuus
    // on lineaarinen
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: N
    // Short rationale for estimate: kutsutaan towns_distance_increasing() funktiota
    // jonka tehokkuus on lineaarinen. Size() ja vektorin at() ovat vakioita
    TownID min_distance();

    // Estimate of performance: N
    // Short rationale for estimate: kutsutaan towns_distance_increasing() funktiota
    // jonka tehokkuus on lineaarinen. Size() ja vektorin at() ovat vakioita
    TownID max_distance();

    // Estimate of performance: Vakio
    // Short rationale for estimate: find() ja at() metodit keskiarvoltaan vakioita
    // ja huonoimmassa tapauksissa lineaarisia.
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: N
    // Short rationale for estimate: Jos käydään id vassalit läpi for loopista niin
    // niitä voi olla huonoimmassa tapauksessa n-1 kpl eli tehokkuus on lineaarinen.
    // Muulloin tehokkuus on vakio, koska find() on keskiarvoltaan vakio ja push_back()
    // on myös vakio
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: N
    // Short rationale for estimate: Jos käydään id masterit läpi while loopissa niin
    // huonoimmassa tapauksessa se on lineaarinen operaatio eli tehokkuus on lineaarinen.
    // Muut operaatiot ovat vakioita.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: N
    // Short rationale for estimate: For loopit ovat pahimmassa tapauksessa lineaarisia
    // ja vectorin find operaatio on myös lineaarinen. Erase operaatiot vakioita, koska
    // poistetaan vain yksi alkio
    bool remove_town(TownID id);

    // Estimate of performance: N
    // Short rationale for estimate: for loopit lineaarisia ja sort keskimäärin
    // lineaarinen. Mitkään näistä ei ole päällekkäin, joten funktion tehokkuus
    // on lineaarinen
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance: N
    // Short rationale for estimate: Deepest_vassal apufunktio ja
    // while looppi ovat pahimillaan lineaarisia. Ja lisäksi reverse algoritmi on n
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: N
    // Short rationale for estimate: Vassals_tax apufunktio on lineaarinen. Muut
    // operaatiot ovat vakioaikaisia
    int total_net_tax(TownID id);

private:
    // Add stuff needed for your class implementation here

    struct Node {
        std::string name_;
        TownID id_;
        Coord coord_;
        int tax_;
        std::vector<TownID> vassals_;
        Node* master_;
    };

    std::unordered_map<TownID, Node> towns_;

    std::pair<TownID,int> deepest_vassal(TownID id,int current_level,
                                         int deepest_level, TownID last);

    int vassals_tax(TownID id,bool first_id);

};

#endif // DATASTRUCTURES_HH
