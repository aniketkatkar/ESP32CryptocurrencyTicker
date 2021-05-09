

# ESP32 Cryptocurreny Ticker

![](https://github.com/aniketkatkar/ESP32CryptocurrencyTicker/img/1.JPG)



**Introduction**

This project shows how to interface Nokia 5110 LCD with Esp32 module to show current prices of any cryptocurrency like Bitcoin, Dogecoin, etc

### Coingecko API
The Coingecko API gives data such as live pricing, trading volume, tickers, exchanges, historical data, coin info & images, developer & community stats, events, global markets, and CoinGecko Beam coins & exchanges status updates directly. Refer the below link for more information on its use.


###Links

`<Website>` : <https://www.coingecko.com/en/api>


####Usage
I have used two APIs for Bitcoin and Dogecoin in this project that gives the `current_price`, `market_cap`, `total_volume`,`price_change_24h`,
    `price_change_percentage_24h`, `last_updated`, along with other attributes.

`<Bitcoin API>` : <https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=bitcoin>

`<Dogecoin API>` : <https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=dogecoin>

You can replace the `ids=` with the coin name of your choice along with the `vs_currency=` with the currency of your country as given in the docs. The current prices are in INR(₹).

####Connections

![](https://github.com/aniketkatkar/ESP32CryptocurrencyTicker/img/connections.jpg)

####The Code

I have used an ESP32 with Nokia 5110 display which gives the current price of the specified cryptocurrency and keeps updating in about 6 seconds. 

Enter your Wifi credentials over here:

    const char* ssid = "yourSSID";
	const char* password = "yourPASSWORD";

Replace the links with API for your coins:

    //Dogecoin API from coingecko
	const char* api1 = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=dogecoin";
	//Bitcoin API from coingecko
	const char* api2 = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=inr&ids=bitcoin";
	


####Materials

- ESP32
- Nokia 5110 LCD
- Wires
     
For additional information about our API visit : https://www.coingecko.com/api

Rate Limit: **100 requests/minute**

**Powered by CoinGecko API**

Do you like this ? Please ⭐ this project!

License
[MIT](https://github.com/aniketkatkar/ESP32CryptocurrencyTicker/LICENSE.txt)