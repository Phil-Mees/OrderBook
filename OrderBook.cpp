//
//  OrderBook.cpp
//  OrderBook
//
//  Created by Phil Mees on 27/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#include <iostream>
#include "Config.hpp"

using namespace std;


//---------- getCommands ----------
void getCommands()
{
    cout << "> ";
}

//---------- help ----------
void help()
{
    cout << "OrderBook" << endl
         << "  <command> <command-parameters>"
         << "  order <orderId> <buy|sell> <orderSize> <orderPrice>" << endl
         << "  cancel <orderId>" << endl
         << "  ammend <orderId> <new-orderSize>" << endl
         << "  q level <ask|bid> <position: 0..n>" << endl
         << "  q order <orderId>" << endl;
}

//----------- main ----------
int main( int   argc,
          char* argv[] )
{
    Config::init( argc, argv );
    
    if ( Config::getBool( "help" ) )
    {
        help();
        return 1;
    }
    getCommands();
 
    return 1;
}
