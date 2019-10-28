//
//  Config.hpp
//  OrderBook
//
//  Created by Phil Mees on 27/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#include <string>

class Config
{
public:
    // initialise the configuration from args and files
    static void init( int   argc,
                      char* argv[] );
    
    // getters
    static const std::string& getString(const std::string& param,
                                        const std::string& defValue = "");
    
    static int getInt(const std::string& param,
                      int                defValue = 0);
    
    static bool getBool(const std::string& param,
                        bool               defValue = false);
    
private:
    //  Not implemented.
    Config();
    ~Config();
};

#endif /* Config_hpp */
