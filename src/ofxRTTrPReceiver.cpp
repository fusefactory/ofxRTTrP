//
//  RTTrPParser.cpp
//  TestBlacktraxx
//
//  Created by Matteo on 28/11/2018.
//

#include "ofxRTTrPReceiver.h"

ofxRTTrPReceiver::ofxRTTrPReceiver(){
    
}

ofxRTTrPReceiver::~ofxRTTrPReceiver(){

}

void ofxRTTrPReceiver::setup(int listen_port, bool non_blocking){
    udpConnectionRx.Create();
    udpConnectionRx.Bind(listen_port);
    udpConnectionRx.SetNonBlocking(non_blocking);
}

bool ofxRTTrPReceiver::update(){
    bool newMessage = false;

    std::fill_n(udpMessage, messageSize, 0);   //clear array
    dataReceived.clear();

    string message = "";
    
    do{
        udpConnectionRx.Receive(udpMessage, messageSize);
        message = udpMessage;
        if (message.size() > 1){
            newMessage = true;
            
            dataReceived.clear();
            dataReceived.assign(udpMessage, udpMessage + sizeof(udpMessage) / sizeof(udpMessage[0]));
            processData(dataReceived);
        }
        
    }while (message.size() > 1);
    
    

    return newMessage;
}

void ofxRTTrPReceiver::processData(vector<unsigned char> &data){
    if (rTTrPMs.size() > 0){
        for (std::vector< RTTrPM *>::iterator pm = rTTrPMs.begin() ; pm != rTTrPMs.end(); ++pm)
        {
            delete (*pm);
        }
        rTTrPMs.clear();
    }

    RTTrP *rTTrP = new RTTrP(data);
//    rTTrP->printHeader();
    // RTTrPM Big Endian: 0x4434 Little Endian: 0x3443 (RTTrPM)
    if (rTTrP->fltHeader == 0x4434 || rTTrP->fltHeader == 0x3443){
        for (int i = 0; i < rTTrP->numMods; i++){
            Trackable *trackable = new Trackable(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
            
            RTTrPM *rTTrPM = new RTTrPM();
            rTTrPM->header = rTTrP;
            rTTrPM->trackable = trackable;
            rTTrPM->ledMod = new vector<LEDModule *>;
            rTTrPM->lavMod = new vector<LEDAccVelMod *>;
            rTTrPMs.push_back(rTTrPM);
            
            for (int t = 0; t <  trackable->numMods; t++){
                if (rTTrP->data[0] == 0x02){
                    CentroidMod *centroidMod = new CentroidMod(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->centroidMod = centroidMod;
                }
                else if (rTTrP->data[0] == 0x03){
                    QuatModule *quatModule = new QuatModule(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->quatMod = quatModule;
                }
                else if (rTTrP->data[0] == 0x04){
                    EulerModule *eulerModule = new EulerModule(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->eulerMod = eulerModule;
                }
                else if (rTTrP->data[0] == 0x06){
                    LEDModule *ledModule = new LEDModule(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->ledMod->push_back(ledModule);
                }
                else if (rTTrP->data[0] == 0x20){
                    CentroidAccVelMod *centroidAccVelMod = new CentroidAccVelMod(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->cavMod = centroidAccVelMod;
                }
                else if (rTTrP->data[0] == 0x21){
                    LEDAccVelMod *ledAccVelMod = new LEDAccVelMod(&rTTrP->data, rTTrP->intHeader, rTTrP->fltHeader);
                    rTTrPM->lavMod->push_back(ledAccVelMod);
                }
            }
        }
    }
    else if(rTTrP->fltHeader == 0x4434 || rTTrP->fltHeader == 0x3444){
        cout << "RTTrPL not parsed " << endl;
    }
    
    delete (rTTrP);
}
