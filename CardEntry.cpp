#include "CardEntry.h"
#include <iostream>

using namespace std;

namespace deckbox
{

	ostream& operator<<(ostream& out, CardEntry const& card)
	{
		const std::string separator = "\t";
		return out << "{" << card.inventoryCount << "x "
			<< card.edition << separator << card.name << separator << card.cost << separator
			<< card.type << separator
			<< card.cardNumber << "}";
	}

}
