//
//  RTTrPParser.hpp
//  TestBlacktraxx
//
//  Created by Matteo on 28/11/2018.
//

#ifndef RTTrPManager_hpp
#define RTTrPManager_hpp

#include "RTTrP.h"
//https://rttrp.github.io/RTTrP-Wiki/RTTrPM.html

class RTTrPManager{
    public:
        RTTrPManager();
        ~RTTrPManager();
        vector<RTTrPM *> parseData(vector<unsigned char> &data);
    
    protected:
};
#endif /* RTTrPParser_hpp */
