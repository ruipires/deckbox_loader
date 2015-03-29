# Deckbox Loader
This is a simple library whose sole purpose is to parse a csv file containing an exported collection from the website http://deckbox.org
It is a simplistic implementation (at least for now), since it was written as a way to test drive biicode.

# License
See the accompanying LICENSE.txt
Spoiler alert: it is the Boost Software License 1.0

# Dependencies
This currently depends on the STL, Boost (Spirit and Fusion) and in GTest for the unit tests.

# Usage
Assuming you are using biicode, just add an include for it in your source code
	#include "sennin/deckbox_loader/DeckboxLoader.h"
And run
	bii find

# In biicode
You can find it in [biicode here](https://www.biicode.com/sennin/deckbox_loader).

[![Build Status](https://webapi.biicode.com/v1/badges/sennin/sennin/deckbox_loader/master)](https://www.biicode.com/sennin/deckbox_loader) 
