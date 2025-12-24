this project currently sends a request to two apis https://api.hypixel.net/v2/skyblock/auctions and https://api.hypixel.net/v2/skyblock/bazaar.

The auctions api usually consists out of around 70.000 active auctions. most of the items being auctioned can be crafted with materials on the bazaar and/or with other items which can drop ingame on rare occurances but can not be crafted.
For example, to craft item A, you might require materials B, C aswell as item D which is a drop by a specific hostile mob. item D is usually sold as a auction.

Item details (eg enchantments that can be bought on the bazaar) are decoded as base64 encoded strings. 

my goal is to figgure out in live time, which auctions are (heavily) underpriced aswell as if there are any items that are selling for
way more money than their crafting price by buying the required items on the bazaar.

i want to do this to learn to use boost::beast for https requests aswell as boost asio for asynchronous web regests. (the auctions api consists out of 60-70 (depending on the amount of active players) pages which each have a unique url (eg /skyblock/auctions?page=0, /skyblock/auctions?page=1, .....)
