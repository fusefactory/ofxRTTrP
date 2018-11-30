//
//  RTTrPParser.hpp
//  TestBlacktraxx
//
//  Created by Matteo on 28/11/2018.
//

#ifndef ofxRTTrPReceiver_hpp
#define ofxRTTrPReceiver_hpp

#include "RTTrP.h" //https://rttrp.github.io/RTTrP-Wiki/RTTrPM.html
#include "ofxNetwork.h"

class ofxRTTrPReceiver{
    public:
        ofxRTTrPReceiver();
        ~ofxRTTrPReceiver();

	    void setup( int listen_port, bool non_blocking = true);
        bool update();          //TODO: implement thread
        vector<RTTrPM *>& getRTTrPMs(){return rTTrPMs;}
    
    protected:
        void processData(vector<unsigned char> &data);

        ofxUDPManager udpConnectionRx;
        const int messageSize = 65535;
        char udpMessage[65535];
        vector<unsigned char> dataReceived;

        vector<RTTrPM *> rTTrPMs;
    private:
  
};
#endif /* RTTrPParser_hpp */
