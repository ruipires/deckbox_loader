#include "DeckboxLoad.h"
#include <string>

#define FUSION_MAX_VECTOR_SIZE 20
#define BOOST_SPIRIT_UNICODE

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/qi_match_auto.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#undef FUSION_MAX_VECTOR_SIZE

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include <iostream>

BOOST_FUSION_ADAPT_STRUCT(
	deckbox::CardEntry,
	(uint32_t, inventoryCount)
	(uint32_t, tradelistCount)
	(std::string, name)
	(std::string, edition)
	(uint16_t, cardNumber)
	(std::string, condition)
	(std::string, language)
	(bool, isFoil)
	(bool, isSigned)
	(bool, isArtistProof)
	(bool, isAltered)
	(bool, isMisprint)
	(bool, isPromo)
	(bool, isTextless)
	(std::string, myPrice)
	(std::string, type)
	(std::string, cost)
	(std::string, rarity)
	(std::string, price)
	(std::string, imageUrl)
)

namespace deckbox
{
	void dump_int(int attr)
	{
		std::cout << "Parsed: " << attr << std::endl;
	}
	void dump_str(std::string const& attr)
	{
		std::cout << "Parsed: " << attr << std::endl;
	}
	void dump_bool(bool attr)
	{
		std::cout << "Parsed: " << attr << std::endl;
	}
	void dump_char(char attr)
	{
//		std::cout << "Parsed: " << attr << std::endl;
	}

	CardEntry loadCard(std::string const& in)
	{
		typedef std::string::const_iterator Iterator;
		CardEntry result;

		using qi::int_;
		using qi::lit;
		using qi::lexeme;
		using qi::attr;
		using qi::omit;
		using ascii::char_;

		qi::rule<Iterator, std::string()> character = qi::blank | qi::graph | char_("é");
		qi::rule<Iterator, std::string()> unquoted_string = lexeme[*(character - ',')];
		qi::rule<Iterator, std::string()> quoted_string = lexeme['"' >> *((qi::blank | (qi::graph - '"')) | ( lit('"')>>'"'>>attr('"') )) >> '"'];
		qi::rule<Iterator, std::string()> csv_string = quoted_string | unquoted_string;

		qi::rule<Iterator, bool()> signed_flag = ( (lit("signed") >> attr(true)) | attr(false) );
		qi::rule<Iterator, bool()> foil_flag = ( (lit("foil") >> attr(true)) | attr(false) );

		qi::rule<Iterator, std::string()> non_empty_string = lexeme[+(char_ - ',')];
		qi::rule<Iterator, bool()> flag = ( omit[non_empty_string] >> attr(true)) | attr(false);

		qi::rule<Iterator, CardEntry()/*, ascii::space_type*/> card =
			    int_       /*[&dump_int]  */>> ',' //inventory count
			>>  int_       /*[&dump_int]  */>> ',' //tradelist count
			>>  csv_string /*[&dump_str]  */>> ',' // name
			>>  csv_string /*[&dump_str]  */>> ',' // edition
			>>  int_       /*[&dump_int]  */>> ',' //card number
			>>  csv_string /*[&dump_str]  */>> ',' // condition
			>>  csv_string /*[&dump_str]  */>> ',' // language
			>>  foil_flag  /*[&dump_bool] */>> ',' // is foil
			>>  signed_flag/*[&dump_bool] */>> ',' // is signed
			>>  flag       /*[&dump_bool] */>> ',' // is artist proof
			>>  flag       /*[&dump_bool] */>> ',' // is altered
			>>  flag       /*[&dump_bool] */>> ',' // is misprint
			>>  flag       /*[&dump_bool] */>> ',' // is promo
			>>  flag       /*[&dump_bool] */>> ',' // is textless
			>>  csv_string /*[&dump_str]  */>> ',' // my price
			>>  csv_string /*[&dump_str]  */>> ',' // type
			>>  csv_string /*[&dump_str]  */>> ',' // cost
			>>  csv_string /*[&dump_str]  */>> ',' // rarity
			>>  csv_string /*[&dump_str]  */>> ',' // price
			>>  csv_string /*[&dump_str]  */      // image url
			;
		std::string::const_iterator iter = in.begin();
		std::string::const_iterator const end = in.end();

		bool r = qi::parse(iter, end, card, result);

		return result;
	}

	std::vector<CardEntry> load(std::istream &input)
	{
		std::vector<CardEntry> result;

		std::string line;
		std::getline(input, line); // skip header

		for(std::getline(input, line); bool(input); std::getline(input, line))
		{
			if(line.empty())
				continue;
			result.push_back(loadCard(line));
		}

		//input >> match(
		//		( (+(graph - char_(','))) % char_(',') ) % eol
		//		);

		//if(!input)
		//	throw 5;
		return result;
	}
}

