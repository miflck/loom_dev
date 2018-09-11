//
//  Wave.hpp
//  shaderTests
//
//  Created by Flückiger Michael on 04.07.18.
//

#ifndef Wave_hpp
#define Wave_hpp
#include "ofMain.h"
#include <stdio.h>

#define INIT 0
#define START 1
#define WAVE 2
#define FADEOUT 3

class Wave {
    public:
        void setup(int _angle, int _colorangle);
    
    void setup(int _angle, ofColor color);

    
        void update();
        void draw();
    
    
    int xspacing = 3;    // Distance between each horizontal location
    int w;                // Width of entire wave
    float theta = 0.0;      // Start angle at 0
    float amplitude = ofGetHeight()/2; // Height of wave
    float period = ofRandom(800.0,1000);   // How many pixels before the wave repeats
    float dx;               // Value for incrementing x
    //float yvalues;  // Using an array to store height values for the wave
    vector <float> yvalues;

    
    float angle=0;
    ofColor myColor;
    
    float radius=20;
    
    float speed;
    
    float numActors=0;
    
    bool bIsGrowing=true;
    
    
    int state;
    int stateBefore;
    void setState(int _state);
    int getState();
    
    int colorangle;
    
    bool bUseBlending=true;
    
    
    ofFbo waveFbo;
    ofFbo getFbo();
    bool bShouldRemove=false;
    
    
    
    float startAlpha=255;
    float actualAlpha=255;
    float alphaTarget=0;
    float fadeInitTime;
    float fadeDuration=50000;
    
    
    float startAmplitude;
    float actualAmplitude;
    float amplitudeTarget;
    float amplitudeInitTime;
    float amplitudeDuration=5;
    
    
    
    int actualPeriod;
    int periodTarget=0;
    float periodInitTime;
    float periodDuration=50000;
    float periodStart;
    
    
    
    float startLerp=0;
    float actualLerp=0;
    float lerpTarget=1;
    float lerpInitTime;
    float lerpDuration=50000;
    
    
    void startFadeOut();
    void setPeriod(int _p);
    void setXSpacing(int _x);
    
    
    float getAlpha();
    
    int minWidth=5;
    int maxWidth=25;
    
    ofColor backgroundcolor;
    ofColor initBackgroundcolor;
    void setBackgroundcolor(ofColor _col);
    
    void setPeriodTarget(int t);
    void setPeriodDuration(float t);
    void setInitTime();
    
    float map(float in, float inMin, float inMax, float outMin, float outMax, float shaper);
   
    
};




#endif /* Wave_hpp */
