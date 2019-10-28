//
//  OrdBook.cpp
//  OrderBook
//
//  Created by Phil Mees on 28/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#include "OrdBook.hpp"

OrdBook::OrdBook( double tickSize )
  : m_tickSize( tickSize )
{
}

// insert an order.
void OrdBook::insert( const OrdObject& order )
{
    //  check the tick price
    TDB
    
    auto ordIt = s_ordMap.find( order.getOrderId() );
    if ( ordIt!= s_ordMap.end() )
    {
        cout << "OrdBook::insert: orderId " << order.getOrderId()
             << " already exists." << endl;
        return;
    }
    
    //  create the order and insert into the map and list
    OrdOrder* ord( new OrdObject( order ));
    m_ordMap.insert( order.getOrderId(), ord );
    
    //  Match the order and insert into the appropriate list
    //  if not fully matched.
    if ( ord->isBuy() )
    {
        if ( !match( *ord, m_sellList ) )
            m_buyList.push_back()
    }
    else
    {
        if ( !match( *ord, m_buyList ) )
            m_sellList.push_back()
    }
}

// cancel an order
void OrdBook::cancel( int orderId )
{
    auto ordIt = s_ordMap.find( orderId );
    if ( ordIt != s_ordMap.end() )
    {
        ordIt.second->cancel();
    }
    else
    {
        cout << "OrdBook::cancel: orderId " << orderId
             << " not found " << endl;
    }
}

// ammend an order's quantity
void OrdBook::ammend( int    orderId,
                      double newQuantity )
{
    auto ordIt = s_ordMap.find( orderId );
    if ( ordIt != s_ordMap.end() )
    {
        double quantity( ordIt.second->getQuantity() );
        ordIt.second->ammend( newQuantity );
        if ( quantity < newQuantity )
        {
            if ( ordIt.second->isBuy )
                moveToBack( ordIt.second, m_buyList );
            else
                moveToBack( rdIt.second, m_sellList );
        }
    }
    else
    {
        cout << "OrdBook::ammend: orderId " << orderId
             << " not found " << endl;
    }
}

//  print an order/orders
void OrdBook::printLevel( const std::string& orderType,
                          int                level ) const
{
    if (orderType == "buy")
    {
        if ( m_buyList.size() < level )
            cout << m_buyList[level];
        else
            cout << "OrdBook::printLevel: has " << m_buyList.size()
                 << " entries" << endl;
    }
    else
    {
        if ( m_sellList.size() < level )
            cout << m_sellList[level];
        else
            cout << "OrdBook::printLevel: has " << m_sellList.size()
                 << " entries" << endl;
    }
}

void printOrder( int orderId ) const
{
    auto ordIt = s_ordMap.find( orderId );
    if ( ordIt != s_ordMap.end() )
        cout << *ordIt->second;
    else
        cout << "OrdBook::printOrder: orderId " << orderId
             << " not found " << endl;

}

void OrdBook::printBuy() const
{
    OrdList::iterator it;
    for ( it = m_buyList.begin(); it != m_buyList.end(); it++ )
    {
        cout << *it << endl;
    }
}

void OrdBook::printSell() const
{
    OrdList::iterator it;
    for ( it = m_sellList.begin(); it != m_sellList.end(); it++ )
    {
        cout << *it << endl;
    }
}

void OrdBook::printAll() const
{
    OrdMap::iterator it;
    for ( it = m_ordMap.begin(); it != m_ordMap.end(); it++ )
    {
        cout << *it << endl;
    }
}

bool OrdBook::match( OrdObject& order,
                     OrdList&   list )
{
    OrdList::iterator it;
    for ( it = list.begin(); it != list.end() && order.getQuantity() > 0.0; it++ )
    {
        if ( order.match( *it ))
        {
            order.execute( *it );
            if ( it->getQuantity() == 0.0 )
                list.erase( it );
        }
    }
}

void OrdBook::moveToBack( OrdOrder* order,
                          OrdList&  list )
{
    list.remove( order );
    list.push_back( order );
}
