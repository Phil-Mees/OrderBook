//
//  OrdBook.hpp
//  OrderBook
//
//  Created by Phil Mees on 28/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#ifndef OrdBook_hpp
#define OrdBook_hpp

#include <stdio.h>
#include <map>
#include <list>
#include <string>
#include "OrdObject.hpp"

typedef std::map< int, OrdObject* > ObjMap;
typedef std::pair< int, OrdObject* > ObjPair;
typedef std::list< OrdObject* > ObjList;

class OrdBook
{
protected:
    ObjMap      m_ordMap;
    ObjList     m_buyList;
    ObjList     m_sellList;
    double      m_tickSize;
    
public:
    OrdBook( const double tickSize );
    ~OrdBook() {}
    
    // insert an order.
    void insert( const OrdObject& order );
    
    // cancel an order
    void cancel( int orderId );
    
    // ammend an order's quantity
    void ammend( int    orderId,
                double newQuantity );
    
    //  print an order/orders
    void printLevel( const std::string& orderType,
                     int                level ) const;
    void printOrder( int orderId ) const;
    void printBuy() const;
    void printSell() const;
    void printAll() const;
    
protected:
    void moveToBack( OrdObject* order,
                     ObjList&  list );
    
    bool match( OrdObject& order,
                ObjList&   list );
};

#endif /* OrdBook_hpp */
