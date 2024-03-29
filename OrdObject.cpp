//
//  OrdObject.cpp
//  OrderBook
//
//  Created by Phil Mees on 28/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#include <iostream>
#include "OrdObject.hpp"
#include "OrdBook.hpp"
using namespace std;

#include "OrdObject.hpp"

using namespace std;

namespace
{
const std::string   s_ordOpen( "Open" );
const std::string   s_ordPartFilled( "Partially-Filled" );
const std::string   s_ordFilled( "Filled" );
const std::string   s_ordCancelled( "Cancelled" );
const std::string   s_ordUnknown( "Unknown" );

const std::string   s_buy( "buy" );
const std::string   s_sell( "sell" );
const std::string   s_ask( "ask" );
const std::string   s_bid( "bid" );
}

//---------- OrdObject  ----------
OrdObject::OrdObject( int          orderId,
                      std::string& orderType,
                      double       quantity,
                      double       price )
  : m_orderId( orderId ),
    m_orderType( orderType ),
    m_quantity( quantity ),
    m_price( price ),
    m_status( ORD_OPEN )
{
}

//---------- OrdObject( copy )  ----------
OrdObject::OrdObject( const OrdObject&  obj )
  : m_orderId( obj.m_orderId ),
    m_orderType( obj.m_orderType ),
    m_quantity( obj.m_quantity ),
    m_price( obj.m_price ),
    m_status( obj.m_status )
{
}

std::ostream& operator<<( std::ostream& os,
                          const OrdObject& obj )
{
    os << obj.m_orderId << " "
       << obj.m_orderType << " "
       << obj.m_quantity << " "
       << obj.m_price << " ["
       << obj.getStatusStr() << "]" ;
    return os;
}

//--------- getStatusStr ---------
const std::string& OrdObject::getStatusStr() const
{
    switch (m_status) {
        case ORD_OPEN:
            return s_ordOpen;
            break;
    
        case ORD_PART_FILLED:
            return s_ordPartFilled;
            break;
            
        case ORD_FILLED:
            return s_ordFilled;
            break;
        
        case ORD_CANCELLED:
            return s_ordCancelled;
            break;
            
        default:
            return s_ordUnknown;
            break;
    }
}

//---------- match  ----------
bool OrdObject::match( const OrdObject& obj ) const
{
    //  can't match equal types
    if ( m_orderType == obj.m_orderType )
        return false;
    
    if ( m_orderType == s_buy && m_price >= obj.m_price )
        return true;
    else if ( m_orderType == s_sell && m_price <= obj.m_price )
        return true;
    else
        return false;
}

//---------- execute  -----------
double OrdObject::execute( OrdObject* obj )
{
    if ( m_quantity == obj->m_quantity )
    {
        cout << "OrdObject::execute: filled order " << m_orderId
             << " with " << obj->m_orderId << ": "
             << m_quantity << " @ " << m_price << endl;
        m_quantity = 0.0;
        m_status = ORD_FILLED;
        obj->m_quantity = 0.0;
        obj->m_status = ORD_FILLED;
    }
    else if ( m_quantity < obj->m_quantity )
    {
        cout << "OrdObject::execute: filled order " << m_orderId
             << " with " << obj->m_orderId << ": "
             << m_quantity << " @ " << m_price << endl;
        m_quantity = 0.0;
        m_status = ORD_FILLED;
        obj->m_quantity -= m_quantity;
        obj->m_status = ORD_PART_FILLED;
    }
    else
    {
        cout << "OrdObject::execute: partially filled order " << m_orderId
             << " with " << obj->m_orderId << ": "
             << obj->m_quantity << " @ " << obj->m_price << endl;
        m_quantity -= obj->m_quantity;
        m_status = ORD_PART_FILLED;
        obj->m_quantity = 0.0;
        obj->m_status = ORD_FILLED;
    }
    return m_quantity;
}

//--------- cancel ----------
void OrdObject::cancel()
{
    m_status = ORD_CANCELLED;
}

//---------- isBuy ----------
bool OrdObject::isBuy() const
{
    return m_orderType == s_buy;
}

//---------- isSell ----------
bool OrdObject::isSell() const
{
    return m_orderType == s_sell;
}
