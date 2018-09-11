//
//  Blob.hpp
//  shaderTests
//
//  Created by Flückiger Michael on 04.07.18.
//

#ifndef Blob_hpp
#define Blob_hpp
#include "ofMain.h"
#include <stdio.h>
#include "MovingObject.hpp"

class Blob:public MovingObject {
    public:
        void setup();
        void update();
        void draw();
    
    float initRadius;
    float noisestep;
    float radius;
    
    vector <ofVec2f> positions;
    vector <ofVec2f> positions2;

    vector <ofVec2f> initPositions;
    vector <float> noises;

    
    
    
    float stepper;

    ofFbo Blobfbo;
    ofFbo getFbo();
};

#endif /* Blob_hpp */
