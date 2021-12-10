// Datastructures.cc
//
// Student name: Joni Juhola
// Student email: joni.juhola@tuni.fi
// Student number: K440164

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <stack>
#include <list>

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
    return towns_.size();
}

void Datastructures::clear_all()
{
    towns_.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);

    if (got!=towns_.end()){
        return false;
    }else{
        // Lisätään tarvittavat tiedot
        Node new_town;
        new_town.name_=name;
        new_town.id_=id;
        new_town.coord_=coord;
        new_town.tax_=tax;
        new_town.master_=nullptr;
        new_town.colour_=WHITE;
        new_town.d_=INFINITY;
        new_town.path_back_=nullptr;
        towns_.insert({id,new_town});
        return true;
    }
}

Name Datastructures::get_town_name(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);

    if (got!=towns_.end()){
        return got->second.name_;
    }else{
        return NO_NAME;
    }
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);

    if (got!=towns_.end()){
        return got->second.coord_;
    }else{
        return NO_COORD;
    }
}

int Datastructures::get_town_tax(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);

    if (got!=towns_.end()){
        return got->second.tax_;
    }else{
        return NO_VALUE;
    }
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> allTowns;

    // Käydään mapin kaupungit läpi
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        allTowns.push_back(it->first);
    }
    return allTowns;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    std::vector<TownID> same_name_towns;

    // Käydään mapin kaupungit läpi ja etsitään samannimistä kaupunkia
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        if (it->second.name_==name){
            same_name_towns.push_back(it->first);
        }
    }
    return same_name_towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    // Etsitään id mapista
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
    std::vector<TownID> sorted_towns;
    std::vector<std::pair<TownID,Name>> towns_info;

    // Käydään mapin kaupungit läpi ja lisätään tarvittavat tiedot info vektoriin
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        std::pair info(it->first,it->second.name_);
        towns_info.push_back(info);
    }
    // sortataan info vektori
    std::sort(towns_info.begin(),towns_info.end(),[](auto a, auto b)
    {return a.second<b.second;});

    // Käydään info vektori läpi ja lisätään järjestyksessä sorted vektoriin
    for (auto it=towns_info.begin();it!=towns_info.end();it++){
        sorted_towns.push_back(it->first);
    }

    return sorted_towns;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    std::vector<TownID> sorted_towns;
    std::vector<std::pair<TownID, std::pair<int,int>>> towns_info;

    // Käydään mapin kaupungit läpi ja lisätään tarvittavat tiedot info vektoriin
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        // Lasketaan etäisyys origosta
        double d=sqrt(it->second.coord_.x*it->second.coord_.x+
                        it->second.coord_.y*it->second.coord_.y);
        Distance dist=std::floor(d);
        // Tarvitaan koordinaatin y arvo vertailua varten
        std::pair dist_and_y(dist,it->second.coord_.y);
        std::pair id_and_dist(it->first,dist_and_y);
        towns_info.push_back(id_and_dist);
    }
    // sortataan info vektori
    std::sort(towns_info.begin(),towns_info.end(),[](auto a, auto b){
        if (a.second.first==b.second.first)
            // Mikäli etäisyydet ovat samat, vertaillaan y arvoja
            return a.second.second<b.second.second;
        else
            return a.second<b.second;
    });

    // Käydään info vektori läpi ja lisätään järjestyksessä sorted vektoriin
    for (auto it=towns_info.begin();it!=towns_info.end();it++){
        sorted_towns.push_back(it->first);
    }

    return sorted_towns;
}

TownID Datastructures::min_distance()
{
    if (towns_.size()!=0){
        // Kutsutaan edellistä funktiota ja palautetaan pienin alkio
        std::vector<TownID> sorted_towns=towns_distance_increasing();
        return sorted_towns.at(0);
    }else{
        return NO_TOWNID;
    }
}

TownID Datastructures::max_distance()
{
    auto amount=towns_.size();
    if (amount!=0){
        // Kutsutaan edellistä funktiota ja palautetaan suurin alkio
        std::vector<TownID> sorted_towns=towns_distance_increasing();
        return sorted_towns.at(amount-1);
    }else{
        return NO_TOWNID;
    }
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    // Etsitään id:t mapista
    std::unordered_map<TownID,Node>::const_iterator gotvassal=towns_.find(vassalid);
    std::unordered_map<TownID,Node>::const_iterator gotmaster=towns_.find(masterid);

    if (gotvassal==towns_.end() or gotmaster==towns_.end()){
        return false;
    }else{
        if(gotvassal->second.master_!=nullptr){
            return false;
        }else{
            // Lisätään vassalin master osoitin´
            towns_.at(vassalid).master_=&towns_.at(masterid);
            // Lisätään masterin vassals vektoriin
            towns_.at(masterid).vassals_.push_back(vassalid);
            return true;
        }
    }
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    std::vector<TownID> town_vassals;

    if(got!=towns_.end()){
        // Käydään id:n vassalit läpi ja lisätään vektoriin
        for(auto& vassal : got->second.vassals_){
            town_vassals.push_back(vassal);
        }
    }else{
        town_vassals.push_back(NO_TOWNID);
    }
    return town_vassals;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    std::vector<TownID> town_masters;

    if(got!=towns_.end()){
        // Aloitetaan id:n masterista ja edetään while loopilla kunnes uutta masteria
        // ei enää löydy
        town_masters.push_back(got->first);
        auto current=got->second.master_;
        while(current!=nullptr){
            town_masters.push_back(current->id_);
            // Vaihdetaan tarkasteltava kaupunki
            current=current->master_;
        }
        // Poistetaan osoitin
        current=nullptr;
        delete current;
    }else{
        town_masters.push_back(NO_TOWNID);
    }
    return town_masters;
}

bool Datastructures::remove_town(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);

    if(got==towns_.end()){
        return false;
    }else if(got->second.master_==nullptr){
        // Kaupungilla ei ole masteria
        if(got->second.vassals_.size()>0){
            // Käydään poistettavan kaupungin vassalit läpi ja poistetaan niiden master
            for(auto& town_vassals:towns_.at(id).vassals_){
                towns_.at(town_vassals).master_=nullptr;
            }
        }
    }else{
       // Kaupungilla on master
       if(got->second.vassals_.size()>0){
           // Käydään poistettavan kaupungin vassalit läpi ja vaihdetaan niiden
           // masteriksi poistettavan kaupungin master. Lisätään vassalit uuden
           // masterin vassals vektoriin
           for(auto& town_vassals:towns_.at(id).vassals_){
               towns_.at(town_vassals).master_=towns_.at(id).master_;
               towns_.at(got->second.master_->id_).vassals_.push_back(town_vassals);
           }
       }
       // Etsitään poistettavan kaupungin masterin vassals vektorista
       // poistettava kaupunki ja poistetaan se
       auto find_id=std::find(begin(towns_.at(got->second.master_->id_).vassals_),
                              end(towns_.at(got->second.master_->id_).vassals_),id);
       towns_.at(got->second.master_->id_).vassals_.erase(find_id);
       // Poistetaan poistettavan kaupungin master
       towns_.at(id).master_=nullptr;
       delete towns_.at(id).master_;
    }
    // Poistetaan kaupunki mapista
    towns_.erase(id);
    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    std::vector<TownID> sorted_towns;
    std::vector<std::pair<TownID, std::pair<int,int>>> towns_info;

    // Käydään mapin kaupungit läpi ja lisätään tarvittavat tiedot info vektoriin
    for (auto it=towns_.begin(); it!=towns_.end(); it++){
        // Lasketaan etäisyys pisteestä
        double d=sqrt((it->second.coord_.x-coord.x)*(it->second.coord_.x-coord.x)+
                        (it->second.coord_.y-coord.y)*(it->second.coord_.y-coord.y));
        Distance dist=std::floor(d);
        // Tarvitaan koordinaatin y arvo vertailua varten
        std::pair dist_and_y(dist,it->second.coord_.y);
        std::pair id_and_dist(it->first,dist_and_y);
        towns_info.push_back(id_and_dist);
    }
    // sortataan info vektori
    std::sort(towns_info.begin(),towns_info.end(),[](auto a, auto b){
        if (a.second.first==b.second.first)
            // Mikäli etäisyydet ovat samat, vertaillaan y arvoja
            return a.second.second<b.second.second;
        else
            return a.second<b.second;
    });
    // Käydään info vektori läpi ja lisätään järjestyksessä sorted vektoriin
    for (auto it=towns_info.begin();it!=towns_info.end();it++){
        sorted_towns.push_back(it->first);
    }
    return sorted_towns;
}
// Funktio palauttaa syvimmällä olevan vassalin ja sen syvyystason.
// Parametrina annetaan id, jonka vassaleja tarkastellaan. Lisäksi annetaan
// Apumuuttujina annetaan current_level, deepest_level ja deepestid, joilla on
// oletusarvot
std::pair<TownID,int> Datastructures::deepest_vassal(TownID id,int current_level=0,
                                                     int deepest_level=0,
                                                     TownID deepestid="")
{
    if (towns_.at(id).vassals_.size()!=0){
        // Mikäli id:llä on vassaleja niin käydään vassalit läpi
        // Taso myös kasvaa yhdellä
        current_level+=1;
        for (auto &vassal:towns_.at(id).vassals_){
            // Kutsutaan rekursiivisesti tätä funktiota
            std::pair<TownID,int> next_vassal=deepest_vassal(vassal,current_level,
                                                             deepest_level,deepestid);
            deepest_level=next_vassal.second;
            deepestid=next_vassal.first;
        }
    }
    if (current_level>deepest_level){
        deepest_level=current_level;
        deepestid=id;
    }else if (deepest_level==0 and current_level==0){
        // Mikäli id:llä ei ole lapsia
        deepestid=id;
    }
    // Muodostetaan pari syvimmästä alkiosta ja sen tasosta
    std::pair deepest(deepestid,deepest_level);
    return deepest;
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID,Node>::const_iterator got=towns_.find(id);
    std::vector<TownID> vassals;

    if (got!=towns_.end()){
        // Kutsutaan deepest_vassal apufunktiota, josta saadaan syvimmällä oleva
        // vassali
        std::pair<TownID,int> deepest=deepest_vassal(id);
        vassals.push_back(deepest.first);
        // Käydään läpi suurin vassali reitti aloittamalla syvimmällä olevan
        // vassalin masterista kunnes saavutaan tarkasteltavaan kaupunkiin.

        // Luodaan osoittimet joilla tiedetään mitä alkiota tarkastellaan
        // ja milloin lopetetaan tarkastelu
        Node* current_master=towns_.at(deepest.first).master_;
        Node* id_master=towns_.at(id).master_;
        while (current_master!=id_master){
            // Lisätään vektoriin kaupungin id
            vassals.push_back(current_master->id_);
            // Vaihdetaan tarkasteltavaa kaupunkia eteenpäi
            current_master=current_master->master_;
        }
        // poistetaan osoittimet
        current_master=nullptr;
        id_master=nullptr;
        delete current_master;
        delete id_master;

        // Vektori on järjestyksessä jossa on syvin alkio ensin, joten täytyy
        // kääntää järjestys
        std::reverse(vassals.begin(),vassals.end());
    }else{
        vassals.push_back(NO_TOWNID);
    }
    return vassals;
}

// Funktio laskee id:n vassaleilta tulevat verot. Paramterina id ja totuusarvo
// onko id se, jolle tätä funktiota kutsutaan total_net_tax funktiossa
int Datastructures::vassals_tax(TownID id, bool first_id)
{
    int total_tax=0;
    if (towns_.at(id).vassals_.size()!=0){
        // Käydään läpi id:n vassalit
        for (auto &vassal:towns_.at(id).vassals_){
            // Kutsutaan rekursiivisesti tätä funktiota. Nyt totuusarvo on false
            // koska tässä kohtaa tämä ei ole se alkuperäinen id
            int vassal_tax=vassals_tax(vassal,false);
            total_tax+=vassal_tax;
        }
    }
    if (first_id==false){
        // Mikäli totuusarvo on false niin palautetaan vain kymmenys nettoverosta
        return floor(total_tax+towns_.at(id).tax_)*0.1;
    }
    // Muuten palautetaan koko verosumma
    return total_tax;
}

int Datastructures::total_net_tax(TownID id)
{
    // Etsitään id mapista
    std::unordered_map<TownID,Node>::const_iterator got=towns_.find(id);
    int town_net_tax=0;

    if (got!=towns_.end()){
        // Lisätään nettoveroon kaupungin oma vero
        town_net_tax+=towns_.at(id).tax_;
        // Lisätään nettoveroon vassalien verot kutsumalla apufunktiota vassals_tax
        town_net_tax+=vassals_tax(id,true);

        if (towns_.at(id).master_!=nullptr){
            // Mikäli kaupungilla on master niin vähennetään nettoverosta
            // masterille menevä vero
            town_net_tax-=floor(town_net_tax*0.1);
        }
        return town_net_tax;
    }else{
        return NO_VALUE;
    }
}

//
// Phase 2 operations
//


void Datastructures::clear_roads()
{
    // Replace the line below with your implementation
    for (auto &town : towns_){
        if (town.second.town_roads_.size()>0){
            town.second.town_roads_.clear();
        }
    }
}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    // Replace the line below with your implementation
    // throw NotImplemented("all_roads()");
    std::unordered_set<std::pair<TownID,TownID>, boost::hash<std::pair
            <TownID,TownID>>> set_of_roads;
    std::vector<std::pair<TownID, TownID>> result_roads;
    for (auto &town : towns_){
        for (auto &town_road : town.second.town_roads_){
            if (town.first<town_road.first->id_){
                std::pair road(town.first,town_road.first->id_);
                set_of_roads.insert(road);
            }else{
                std::pair road(town_road.first->id_,town.first);
                set_of_roads.insert(road);
            }
        }
    }
    for (auto &road: set_of_roads){
        // Tähän tarkistus onko tietä ennestään
        result_roads.push_back(road);
    }
    return result_roads;
}

bool Datastructures::add_road(TownID town1, TownID town2)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("add_road()");
    std::unordered_map<TownID, Node>::const_iterator gotTown1=towns_.find(town1);
    std::unordered_map<TownID, Node>::const_iterator gotTown2=towns_.find(town2);

    if(gotTown1==towns_.end() or gotTown2==towns_.end()){
        return false;
    }else{
        for (auto town1_road: gotTown1->second.town_roads_){
            if (town1_road.first->id_==town2){
                return false;
            }
        }
        Node* Town1_ptr=&towns_.at(town1);
        Node* Town2_ptr=&towns_.at(town2);
        Coord town1_coord=gotTown1->second.coord_;
        Coord town2_coord=gotTown2->second.coord_;
        double d=sqrt((town1_coord.x-town2_coord.x)*(town1_coord.x-town2_coord.x)+
                        (town1_coord.y-town2_coord.y)*(town1_coord.y-town2_coord.y));
        Distance dist=std::floor(d);
        std::pair town1_road(Town2_ptr,dist);
        std::pair town2_road(Town1_ptr,dist);
        towns_.at(town1).town_roads_.push_back(town1_road);
        towns_.at(town2).town_roads_.push_back(town2_road);
        return true;
    }
}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_roads_from()");
    std::unordered_map<TownID, Node>::const_iterator got=towns_.find(id);
    std::vector<TownID> roads_from_town;

    if (got==towns_.end()){
        roads_from_town.push_back(NO_TOWNID);
    }else{
        for (auto& town: got->second.town_roads_){
            roads_from_town.push_back(town.first->id_);
        }
    }
    return roads_from_town;
}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("any_route()");
    std::unordered_map<TownID, Node>::const_iterator gotfromid=towns_.find(fromid);
    std::unordered_map<TownID, Node>::const_iterator gottoid=towns_.find(toid);
    std::vector<TownID> route;

    if (gotfromid==towns_.end() or gottoid==towns_.end()){
        route.push_back(NO_TOWNID);
    }else{
        for (auto &town: towns_){
            town.second.colour_=WHITE;
        }
        std::stack<Node*> stack;
        stack.push(&towns_.at(fromid));
        while (!stack.empty()){
            Node* top_element=stack.top();
            stack.pop();
            if (top_element->colour_==WHITE){
                top_element->colour_=GRAY;
                stack.push(top_element);
                if(top_element->id_==toid){
                    break;
                }
                for (auto road: top_element->town_roads_){
                    if (road.first->colour_==WHITE){
                        stack.push(road.first);
                    }
                }
            }else{
                top_element->colour_=BLACK;
            }
        }
        while(!stack.empty()){
            Node* top=stack.top();
            if (top->colour_==GRAY){
                route.push_back(top->id_);
                top->colour_=BLACK;
            }
            stack.pop();
        }
        std::reverse(route.begin(),route.end());
    }
    return route;

}

bool Datastructures::remove_road(TownID town1, TownID town2)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("remove_road()");
    std::unordered_map<TownID, Node>::const_iterator gotTown1=towns_.find(town1);
    std::unordered_map<TownID, Node>::const_iterator gotTown2=towns_.find(town2);

    if(gotTown1==towns_.end() or gotTown2==towns_.end()){
        return false;
    }else{
        Node* town1_ptr=&towns_.at(town1);
        Node* town2_ptr=&towns_.at(town2);
        bool find_road=false;
        unsigned long int index=0;
        while(index < town1_ptr->town_roads_.size()){
            if(town1_ptr->town_roads_.at(index).first==town2_ptr){
                town1_ptr->town_roads_.erase(town1_ptr->town_roads_.begin()+index);
                find_road=true;
                break;
            }
            index++;
        }
        if (find_road==false){
            return false;
        }else{
            index=0;
            while (index < town2_ptr->town_roads_.size()) {
                if (town2_ptr->town_roads_.at(index).first==town1_ptr){
                    town2_ptr->town_roads_.erase(town2_ptr->town_roads_.begin()+index);
                    break;
                }
                index++;
            }
            return true;
        }
    }
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("least_towns_route()");
    std::unordered_map<TownID, Node>::const_iterator gotfromid=towns_.find(fromid);
    std::unordered_map<TownID, Node>::const_iterator gottoid=towns_.find(toid);
    std::vector<TownID> route;

    if (gotfromid==towns_.end() or gottoid==towns_.end()){
        route.push_back(NO_TOWNID);
    }else{
        for (auto &town : towns_){
            town.second.colour_=WHITE;
            town.second.d_=INFINITY;
            town.second.path_back_=nullptr;
        }
        std::list<Node*> queue;
        Node* fromtown=&towns_.at(fromid);
        fromtown->colour_=GRAY;
        fromtown->d_=0;
        queue.push_back(fromtown);
        while(!queue.empty()){
            Node* front_element=queue.front();
            if (front_element->id_==toid){
                break;
            }
            queue.pop_front();
            for (auto& road: front_element->town_roads_){
                if (road.first->colour_==WHITE){
                    road.first->colour_=GRAY;
                    road.first->d_=front_element->d_+1;
                    road.first->path_back_=front_element;
                    queue.push_back(road.first);
                }
            }
            front_element->colour_=BLACK;
        }
        Node* current=queue.front();
        while(current!=nullptr){
            route.push_back(current->id_);
            current=current->path_back_;
        }
        std::reverse(route.begin(),route.end());
    }
    return route;

}

std::vector<TownID> Datastructures::road_cycle_route(TownID /*startid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("road_cycle_route()");
}

std::vector<TownID> Datastructures::shortest_route(TownID /*fromid*/, TownID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("shortest_route()");
}

Distance Datastructures::trim_road_network()
{
    // Replace the line below with your implementation
    throw NotImplemented("trim_road_network()");
}
