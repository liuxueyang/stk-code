#ifndef GET_PUBLIC_ADDRESS_HPP
#define GET_PUBLIC_ADDRESS_HPP

#include "../protocol.hpp"

class GetPublicAddress : public Protocol
{
    public:
        GetPublicAddress(CallbackObject* callbackObject);
        virtual ~GetPublicAddress();
        
        virtual void notifyEvent(Event* event);
         
        virtual void setup();
        virtual void update();
        
    protected:
        enum STATE
        {
            NOTHING_DONE,
            TEST_SENT,
            ADDRESS_KNOWN
        };
        STATE m_state;
        uint32_t m_stunTransactionID[3];
        static const uint32_t m_stunMagicCookie = 0x2112A442;
};

#endif // GET_PUBLIC_ADDRESS_HPP