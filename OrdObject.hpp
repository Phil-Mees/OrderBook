//
//  OrdObject.hpp
//  OrderBook
//
//  Created by Phil Mees on 28/10/19.
//  Copyright © 2019 com.philmees. All rights reserved.
//

#ifndef OrdObject_hpp
#define OrdObject_hpp

#include <string>

class OrdObject
{
public:
    enum OrdStatus { ORD_OPEN,
                     ORD_PART_FILLED,
                     ORD_FILLED,
                     ORD_CANCELLED
    };
    
protected:
    int             m_orderId;
    std::string     m_orderType;
    double          m_quantity;
    double          m_price;
    OrdStatus       m_status;
    
public:
    OrdObject( int          orderId,
               std::string& orderType,
               double       quantity,
               double       price );
    
    OrdObject( const OrdObject&  obj );
    
    ~OrdObject() {}
    
    friend std::ostream & operator<<( std::ostream& os,
                                      const OrdObject& obj);
    
    //  getters
    int getOrderId() const { return m_orderId; }
    const std::string& getOrderType() const { return m_orderType; }
    double getQuantity() const { return m_quantity; }
    double getPrice() const { return m_price; }
    OrdStatus getStatus() const { return m_status; }
    const std::string& getStatusStr() const;
    
    bool isBuy() const;
    bool isSell() const;
    
    //  Ammend the quantity
    void setQuantity( double newQuantity )
    {
        m_quantity = newQuantity;
    }
    
    //  Cancel the order
    void cancel();
    
    //  match against another object
    //  returns true when the orders match
    bool match( const OrdObject& obj ) const;
    
    //  execute and update the order accordingly
    //  returns the quantity executed
    double execute( const OrdObject& obj );
};

#endif /* OrdObject_hpp */
