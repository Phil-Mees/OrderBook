//
//  OrdBook.cpp
//  OrderBook
//
//  Created by Phil Mees on 28/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//
#include <iostream>
#include "OrdObject.hpp"
#include "OrdBook.hpp"
using namespace std;


OrdBook::OrdBook( const double tickSize )
  : m_tickSize( tickSize )
{
}

// insert an order.
void OrdBook::insert( const OrdObject& order )
{
    //  check the tick price
    // TDB
    
    ObjMap::iterator ordIt = m_ordMap.find( order.getOrderId() );
    if ( ordIt!= m_ordMap.end() )
    {
        cout << "OrdBook::insert: orderId " << order.getOrderId()
             << " already exists." << endl;
        return;
    }
    
    //  create the order and insert into the map and list
    OrdObject* ord( new OrdObject( order ));
    m_ordMap.insert( order.getOrderId(), ord );
    
    //  Match the order and insert into the appropriate list
    //  if not fully matched.
    if ( ord->isBuy() )
    {
        if ( !match( *ord, m_sellList ) )
            m_buyList.push_back( ord );
    }
    else
    {
        if ( !match( *ord, m_buyList ) )
            m_sellList.push_back( ord );
    }
}

// cancel an order
void OrdBook::cancel( int orderId )
{
    ObjMap::iterator ordIt = m_ordMap.find( orderId );
    if ( ordIt != m_ordMap.end() )
    {
        ordIt->second->cancel();
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
    ObjMap::iterator ordIt = m_ordMap.find( orderId );
    if ( ordIt != m_ordMap.end() )
    {
        double quantity( ordIt->second->getQuantity() );
        ordIt->second->setQuantity( newQuantity );
        if ( quantity < newQuantity )
        {
            if ( ordIt->second->isBuy() )
                moveToBack( ordIt->second, m_buyList );
            else
                moveToBack( ordIt->second, m_sellList );
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

void OrdBook::printOrder( int orderId ) const
{
    ObjMap::iterator ordIt = m_ordMap.find( orderId );
    if ( ordIt != m_ordMap.end() )
        cout << *ordIt->second;
    else
        cout << "OrdBook::printOrder: orderId " << orderId
             << " not found " << endl;

}

void OrdBook::printBuy() const
{
    ObjList::iterator it;
    for ( it = m_buyList.begin(); it != m_buyList.end(); it++ )
    {
        cout << *it << endl;
    }
}

void OrdBook::printSell() const
{
    ObjList::iterator it;
    for ( it = m_sellList.begin(); it != m_sellList.end(); it++ )
    {
        cout << *it << endl;
    }
}

void OrdBook::printAll() const
{
    ObjMap::iterator it;
    for ( it = m_ordMap.begin(); it != m_ordMap.end(); it++ )
    {
        cout << *it << endl;
    }
}

bool OrdBook::match( OrdObject& order,
                     ObjList&   list )
{
    ObjList::iterator it;
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

void OrdBook::moveToBack( OrdObject* order,
                          ObjList&  list )
{
    list.remove( order );
    list.push_back( order );
}
