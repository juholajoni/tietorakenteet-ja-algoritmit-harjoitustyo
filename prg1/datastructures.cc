// Datastructures.cc
//
// Student name: Joni Juhola
// Student email: joni.juhola@tuni.fi
// Student number: K440164

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::town_count()
{
    // Replace the line below with your implementation
    return towns_.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    towns_.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    if (got!=towns_.end()){
        return false;
    }else{
        Node new_town;
        new_town.name_=name;
        new_town.coord_=coord;
        new_town.tax_=tax;
        towns_.insert({id,new_town});
        return true;
    }
}

Name Datastructures::get_town_name(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    if (got!=towns_.end()){
        return got->second.name_;
    }else{
        return NO_NAME;
    }
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    if (got!=towns_.end()){
        return got->second.coord_;
    }else{
        return NO_COORD;
    }
}

int Datastructures::get_town_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    if (got!=towns_.end()){
        return got->second.tax_;
    }else{
        return NO_VALUE;
    }
}

std::vector<TownID> Datastructures::all_towns()
{
    // Replace the line below with your implementation
    std::vector<TownID> allTowns;
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        allTowns.push_back(it->first);
    }
    return allTowns;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::vector<TownID> same_name_towns;
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        if (it->second.name_==name){
            same_name_towns.push_back(it->first);
        }
    }
    return same_name_towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    std::unordered_map<TownID,Node>::const_iterator got=towns_.find(id);
    if (got!=towns_.end()){
        towns_.at(id).name_=newname;
        return true;
    }else{
        return false;
    }
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_alphabetically()");
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_distance_increasing()");
}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("min_distance()");
}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("max_distance()");
}

bool Datastructures::add_vassalship(TownID /*vassalid*/, TownID /*masterid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_vassalship()");
}

std::vector<TownID> Datastructures::get_town_vassals(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_town_vassals()");
}

std::vector<TownID> Datastructures::taxer_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("taxer_path()");
}

bool Datastructures::remove_town(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_town()");
}

std::vector<TownID> Datastructures::towns_nearest(Coord /*coord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("towns_nearest()");
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
