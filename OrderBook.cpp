//
//  OrderBook.cpp
//  OrderBook
//
//  Created by Phil Mees on 27/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "OrdObject.hpp"
#include "OrdBook.hpp"
#include "Config.hpp"

using namespace std;

OrdBook     s_orderBook( 0.5 );

//---------- help ----------
void help()
{
    cout << "  <command> <command-parameters>"
         << "  order <orderId> <buy|sell> <orderSize> <orderPrice>" << endl
         << "  cancel <orderId>" << endl
         << "  ammend <orderId> <new-orderSize>" << endl
         << "  q level <ask|bid> <position: 0..n>" << endl
         << "  q order <orderId>" << endl
         << "  print <buy|sell|all>" << endl;
}


//---------- getCommands ----------
void getCommands()
{
    char line[256];
    std::string command;

   
    while( command != "quit" || command != "q")
    {
        int         orderId(0);
        std::string orderType;
        double      quantity(0.0);
        double      price(0.0);
        
        cout << "> ";
        cin.getline( line, 256 );

        std::istringstream ss (line);
        ss >> command;
        if ( command == "order" )
        {
            ss >> orderId;
            ss >> orderType;
            ss >> quantity;
            ss >> price;
            OrdObject order( orderId, orderType, quantity, price );
            s_orderBook.insert( order );
        }
        else if ( command == "cancel" )
        {
            ss >> orderId;
            s_orderBook.cancel( orderId );
        }
        else if ( command == "amend" )
        {
            ss >> orderId;
            ss >> quantity;
            s_orderBook.amend( orderId, quantity );
        }
        else if ( command == "q" )
        {
            std::string queryType;
            int level;
            ss >> queryType;
            if ( queryType == "level" )
            {
                ss >> orderType;
                ss >> level;
                s_orderBook.printLevel( orderType, level );
            }
            else if ( queryType == "order" )
            {
                ss >> orderId;
                s_orderBook.printOrder( orderId );
            }
        }
        else if ( command == "print" )
        {
            std::string what;
            ss >> what;
            if ( what == "buy" )
                s_orderBook.printBuy();
            else if ( what == "sell" )
                s_orderBook.printSell();
            else
                s_orderBook.printAll();
        }
        else if ( command == "help" )
        {
            help();
        }
    }
}

//----------- main ----------
int main( int   argc,
          char* argv[] )
{
    getCommands();
    return 1;
}
