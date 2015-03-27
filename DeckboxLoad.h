#ifndef DECKBOX_LOAD_H
#define DECKBOX_LOAD_H
#include <vector>
#include <iosfwd>
#include "CardEntry.h"

namespace deckbox
{
	std::vector<CardEntry> load(std::istream &input);
}

#endif
