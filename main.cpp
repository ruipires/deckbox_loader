#include <google/gtest/gtest.h>
#include "DeckboxLoad.h"
#include <sstream>
#include <fstream>

using namespace std;

TEST(Load, EmptyStream)
{
	stringstream in;
	ASSERT_ANY_THROW(deckbox::load(in));
}

TEST(Load, IncompleteHeader)
{
	stringstream in("Count,Tradelist Count,Name,Edition,Card Number,Condition,Language,Foil,Signed,Artist Proof,Altered Art,Misprint,Promo,Textless,Type,Cost,Rarity");
	ASSERT_ANY_THROW(deckbox::load(in));
}

TEST(Load, CorrectHeader)
{
	stringstream in("Count,Tradelist Count,Name,Edition,Card Number,Condition,Language,Foil,Signed,Artist Proof,Altered Art,Misprint,Promo,Textless,My Price,Type,Cost,Rarity,Price,Image URL");
	EXPECT_EQ(0, deckbox::load(in).size());
}

TEST(Load, LoadOneCard)
{
	stringstream in("Count,Tradelist Count,Name,Edition,Card Number,Condition,Language,Foil,Signed,Artist Proof,Altered Art,Misprint,Promo,Textless,My Price,Type,Cost,Rarity,Price,Image URL\n"
			"1,0,Nevinyrral's Disk,Revised Edition,267,Near Mint,English,,signed,,,,,,,Artifact,{4},Rare,$2.36,https://deckbox.org/system/images/mtg/cards/1128.jpg");

	auto a = deckbox::load(in);

	for(auto i : a)
		cout << i << endl;

	EXPECT_EQ(1, a.size());

	auto card = a[0];

	EXPECT_EQ(1, card.inventoryCount);
	EXPECT_EQ(0, card.tradelistCount);
	EXPECT_EQ("Nevinyrral's Disk", card.name);
	EXPECT_EQ("Revised Edition", card.edition);
	EXPECT_EQ(267, card.cardNumber);
	EXPECT_EQ("Near Mint", card.condition);
	EXPECT_EQ("English", card.language);
	EXPECT_EQ(false, card.isFoil);
	EXPECT_EQ(true, card.isSigned);
	EXPECT_EQ(false, card.isArtistProof);
	EXPECT_EQ(false, card.isAltered);
	EXPECT_EQ(false, card.isMisprint);
	EXPECT_EQ(false, card.isPromo);
	EXPECT_EQ(false, card.isTextless);
	EXPECT_EQ("", card.myPrice);
	EXPECT_EQ("Artifact", card.type);
	EXPECT_EQ("{4}", card.cost);
	EXPECT_EQ("Rare", card.rarity);
	EXPECT_EQ("$2.36", card.price);
	EXPECT_EQ("https://deckbox.org/system/images/mtg/cards/1128.jpg", card.imageUrl);
}

TEST(Load, LoadOneCardWithQuotes)
{
	stringstream in("Count,Tradelist Count,Name,Edition,Card Number,Condition,Language,Foil,Signed,Artist Proof,Altered Art,Misprint,Promo,Textless,My Price,Type,Cost,Rarity,Price,Image URL\n"
			"1,0,Flying Men,\"Time Spiral \"\"Timeshifted\"\"\",20,Near Mint,Portuguese,,,,,,,,,Creature  - Human,{U},Special,$0.39,https://deckbox.org/system/images/mtg/cards/107291.jpg");

	auto a = deckbox::load(in);

	for(auto i : a)
		cout << i << endl;

	EXPECT_EQ(1, a.size());

	auto card = a[0];

	EXPECT_EQ(1, card.inventoryCount);
	EXPECT_EQ(0, card.tradelistCount);
	EXPECT_EQ("Flying Men", card.name);
	EXPECT_EQ("Time Spiral \"Timeshifted\"", card.edition);
	EXPECT_EQ(20, card.cardNumber);
	EXPECT_EQ("Near Mint", card.condition);
	EXPECT_EQ("Portuguese", card.language);
	EXPECT_EQ(false, card.isFoil);
	EXPECT_EQ(false, card.isSigned);
	EXPECT_EQ(false, card.isArtistProof);
	EXPECT_EQ(false, card.isAltered);
	EXPECT_EQ(false, card.isMisprint);
	EXPECT_EQ(false, card.isPromo);
	EXPECT_EQ(false, card.isTextless);
	EXPECT_EQ("", card.myPrice);
	EXPECT_EQ("Creature  - Human", card.type);
	EXPECT_EQ("{U}", card.cost);
	EXPECT_EQ("Special", card.rarity);
	EXPECT_EQ("$0.39", card.price);
	EXPECT_EQ("https://deckbox.org/system/images/mtg/cards/107291.jpg", card.imageUrl);
}


TEST(Load, LoadAll)
{
	ifstream in("inventory.csv");
	auto a = deckbox::load(in);

	uint32_t count = 0;

	for(auto i : a)
	{
		cout << i << endl;
		count += i.inventoryCount;
		EXPECT_FALSE(i.name.empty());
		EXPECT_FALSE(i.edition.empty());
		EXPECT_FALSE(i.type.empty());
		EXPECT_NE(0, i.inventoryCount);
	}

	cout << "Loaded " << a.size() << " unique cards and a total of " << count << " cards." << endl;

	//EXPECT_EQ(1, deckbox::load(in).size());
	EXPECT_TRUE(!a.empty());
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
