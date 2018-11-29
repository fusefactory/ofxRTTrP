//
//  RTTrPParser.cpp
//  TestBlacktraxx
//
//  Created by Matteo on 28/11/2018.
//

#include "RTTrPManager.h"

RTTrPManager::RTTrPManager(){
    
}

vector<RTTrPM *> RTTrPManager::parseData(vector<unsigned char> &data){
    vector<RTTrPM *> rTTrPMs;
    
    RTTrP rTTrP(data);
//    rTTrP.printHeader();
    
    //RTTrPM Big Endian: 0x4434 Little Endian: 0x3443 (RTTrPM)
    if (rTTrP.fltHeader == 0x4434 || rTTrP.fltHeader == 0x3443){
        for (int i = 0; i < rTTrP.numMods; i++){
            Trackable trackable(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
            
            RTTrPM *rTTrPM = new RTTrPM();
            rTTrPM->header = &rTTrP;
            rTTrPM->trackable = &trackable;
            rTTrPM->ledMod = new vector<LEDModule *>;
            rTTrPM->lavMod = new vector<LEDAccVelMod *>;
            rTTrPMs.push_back(rTTrPM);
            
            for (int t = 0; t <  trackable.numMods; t++){
                if (rTTrP.data[0] == 0x02){
                    CentroidMod centroidMod(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->centroidMod = &centroidMod;
                }
                else if (rTTrP.data[0] == 0x03){
                    QuatModule quatModule(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->quatMod = &quatModule;
                }
                else if (rTTrP.data[0] == 0x04){
                    EulerModule eulerModule(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->eulerMod = &eulerModule;
                }
                else if (rTTrP.data[0] == 0x06){
                    LEDModule ledModule(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->ledMod->push_back(&ledModule);
                }
                else if (rTTrP.data[0] == 0x20){
                    CentroidAccVelMod centroidAccVelMod(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->cavMod = &centroidAccVelMod;
                }
                else if (rTTrP.data[0] == 0x21){
                    LEDAccVelMod ledAccVelMod(&rTTrP.data, rTTrP.intHeader, rTTrP.fltHeader);
                    rTTrPM->lavMod->push_back(&ledAccVelMod);
                }
            }
        }
    }
    else if(rTTrP.fltHeader == 0x4434 || rTTrP.fltHeader == 0x3444){
        cout << "RTTrPL not parsed " << endl;
    }
    
    return rTTrPMs;
}

RTTrPManager::~RTTrPManager(){
 
}

