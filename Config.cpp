//
//  Config.cpp
//  OrderBook
//
//  Created by Phil Mees on 27/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//
#include <stdlib.h>
#include <string>
#include <map>
#include "Config.hpp"

typedef std::map< std::string, std::string > ConfigMap;

namespace
{
    ConfigMap   s_cfgMap;
}

//---------- init ----------
void Config::init( int   argc,
                  char*  argv[] )
{
    for ( int i = 0; i < argc; i++ )
    {
        std::string param( argv[i] );
        std::string value;
        if ( param[0] == '-' && i < argc+1 )
        {
            value = argv[i+1];
            if ( value[0] == '-' )
                value = "true";
            else
                i++;
        }
        s_cfgMap.insert( param, value );
    }
}

//---------- getString ----------
const std::string& Config::getString( const std::string& param,
                                      const std::string& defValue )
{
    ConfigMap::iterator value = s_cfgMap.find( param );
    if ( value != s_cfgMap.end() )
        return value->second;
    else
        return defValue;
}

//---------- getLong ----------
int Config::getInt( const std::string& param,
                    int                defValue )
{
    ConfigMap::iterator value = s_cfgMap.find( param );
    if ( value != s_cfgMap.end() )
        return atoi( value->second.c_str() );
    else
        return defValue;
}

//---------- getBool ----------
bool Config::getBool( const std::string& param,
                      bool               defValue )
{
    ConfigMap::iterator value = s_cfgMap.find( param );
    if ( value != s_cfgMap.end() )
        return value->second == "true" || value->second == "1";
    else
        return defValue;
}
