#include "network.h"
#include "random.h"
#include <iostream>
#include <map>


bool is_neigbour(Network net,const size_t& a, const size_t& b);


size_t Network::random_connect(const double& mean)
{
	double tries(0);
	if(mean>=std::sqrt(values.size())){
		throw std::invalid_argument("too big degree for node number, dmax=sqrt(n)");
	}
	int nbr_liens(0);
	links.clear();
	for(size_t i(0);i<values.size();++i){
		size_t deg_i(RNG.poisson(mean));
		size_t deg_init(degree(i));
		//for(size_t j(0);j<deg_i;++j){
		while(degree(i)<deg_i+deg_init){
					
		
				if(tries>100000){
					throw std::invalid_argument("generating infinite boucle ");
				}
				++tries;
				if(add_link(i,RNG.uniform_int(0,values.size()-1))){
					++nbr_liens;
					
				}
				
		}
		
	}

	return nbr_liens;
	
	
}

void Network::resize(const size_t& taille)
{
	
	values.clear();
	for(size_t i(0);i<taille;++i){
		values.push_back(RNG.normal());
	}
	
}

bool Network::add_link(const size_t& a, const size_t& b)
{
	
	
	if((b!=a)and(!is_neigbour(*this,a,b))and (a<values.size()) and (b<values.size() and a>=0 and b>=0)){

		links.insert(std::make_pair(a,b));
		links.insert(std::make_pair(b,a));
		return true;
	}else {
		return false;}
	
}



size_t Network::set_values(const std::vector<double>& val_)
{
	
	values.clear();
	values=val_;
	return values.size();
			
}

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t& n) const
{
	if(values.size()>n){
		return links.count(n);
	}throw std::invalid_argument("degree(n)-> node n doesn't exist");
	
}

double Network::value(const size_t& n) const
{
	if(values.size()>n){
		return values[n];
	}else throw std::invalid_argument("value(n)-> node n doesn't exist");
	
}

std::vector<double> Network::sorted_values() const
{
	std::vector<double> ordered_values(values);
	std::sort(ordered_values.begin(), ordered_values.end()); 
	std::reverse(ordered_values.begin(), ordered_values.end());
	return ordered_values;
}

std::vector<size_t> Network::neighbors(const size_t& n) const
{
	std::vector<size_t> voisins;
	if(values.size()>n){	
		
		auto range = links.equal_range(n);
	 
		for (auto i = range.first; i != range.second; ++i){
				voisins.push_back(i->second);
		}
		return voisins;
	}else throw std::invalid_argument("neighbors(n)-> node n doesn't exist");
	
}



bool is_neigbour(Network net,const size_t& a, const size_t& b)
{
	for(size_t i(0);i<net.neighbors(a).size();++i){
		if(net.neighbors(a)[i]==b){
			return true;
		}
	}
	return false;
}



