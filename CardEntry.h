#ifndef DECKBOX_CARD_ENTRY
#define DECKBOX_CARD_ENTRY
#include <string>
#include <iosfwd>
#include <stdint.h>

namespace deckbox
{
	struct CardEntry
	{
		uint32_t inventoryCount;
		uint32_t tradelistCount;
		std::string name;
		std::string edition;
		uint16_t cardNumber; // collector number
		std::string condition;
		std::string language;
		bool isFoil;
		bool isSigned;
		bool isArtistProof;
		bool isAltered;
		bool isMisprint;
		bool isPromo;
		bool isTextless;
		std::string myPrice;
		std::string type;
		std::string cost;
		std::string rarity;
		std::string price;
		std::string imageUrl;
	};

	std::ostream& operator<<(std::ostream &out, CardEntry const& card);

}

#endif
