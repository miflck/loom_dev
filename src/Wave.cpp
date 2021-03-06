//
//  Wave.cpp
//  shaderTests
//
//  Created by Flückiger Michael on 04.07.18.
//

#include "Wave.hpp"
#include "ofxPoly.h"
#include "ofxEasing.h"


void Wave::setup(int _angle,int _colorangle){
    w = screenwidth+500;
    dx = (TWO_PI / period) * xspacing;
   // yvalues = new Array(p.floor(w/xspacing));
    for (int i=0;i<floor(w/xspacing);i++){
        yvalues.push_back(0.0);
    }
    /*
    // random angle
    float rand=int(ofRandom(360/45));
    angle=45*rand;
    */
    
    angle=_angle;
    
    speed=ofRandom(-0.005,-0.01);
    
    
    colorangle= _colorangle;
    //myColor=ofColor( ofColor::fromHsb(ofRandom(150,220),ofRandom(200,255),ofRandom(150,255),150));
   // myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(100,150),ofRandom(150,180),250));
   // myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(200,255),ofRandom(200,255),255));
    //myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(100,180),ofRandom(150,200),255));

    
    myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(200,255),ofRandom(200,255),255));

    
    state=INIT;
    setState(START);
    numActors=yvalues.size();
    
    
    
    waveFbo.allocate(screenwidth, screenheight,GL_RGBA);
    waveFbo.getTextureReference().getTextureData().bFlipTexture = false;

    
    fadeInitTime=ofGetElapsedTimef();
    
     amplitude = screenheight/2; // Height of wave

    
    
    
    float t=10;
    
    
     startAlpha=255;
     actualAlpha=255;
     alphaTarget=0;
     fadeInitTime=ofGetElapsedTimef();
     fadeDuration=t*1.5;
    
    startAmplitude=amplitude*2;
     actualAmplitude=amplitude*2;
     amplitudeTarget=amplitude*10;
     amplitudeInitTime=ofGetElapsedTimef();
     amplitudeDuration=t;
    
    
     actualPeriod=period;
    periodStart=period;
     periodTarget=50;
     periodInitTime=ofGetElapsedTimef();
     periodDuration=t;
    
    
    
}


void Wave::setup(int _angle,ofColor color){
  //  w = ofGetWidth()+5;
    w = screenwidth+500;

    dx = (TWO_PI / period) * xspacing;
    // yvalues = new Array(p.floor(w/xspacing));
    for (int i=0;i<floor(w/xspacing);i++){
        yvalues.push_back(0.0);
    }
    /*
     // random angle
     float rand=int(ofRandom(360/45));
     angle=45*rand;
     */
    
    angle=_angle;
    
   // speed=ofRandom(-0.005,-0.01);
    speed=ofRandom(-0.01,-0.005);

    colorangle=(color.getHueAngle()+180);
    colorangle=colorangle%255;
   // myColor=ofColor( ofColor::fromHsb(ofRandom(150,220),ofRandom(200,255),ofRandom(150,255),150));
    // myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(100,150),ofRandom(150,180),250));
    // myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(200,255),ofRandom(200,255),255));
//myColor=ofColor( ofColor::fromHsb(colorangle,ofRandom(100,180),ofRandom(150,200),255));
  //  myColor=ofColor( ofColor::fromHsb(colorangle,200,200,255));
    
 //  myColor=ofColor(222,184,135);
    myColor=ofColor(255,0,0);

    
    initBackgroundcolor=color;
    
    
    state=INIT;
    setState(START);
    numActors=yvalues.size();
    
    
    
    waveFbo.allocate(screenwidth,screenheight,GL_RGBA);
  //  waveFbo.getTextureReference().getTextureData().bFlipTexture = false;
    /*waveFbo.begin();
    ofClear(0,0,0,0);
    waveFbo.end();
    */
    fadeInitTime=ofGetElapsedTimef();
    
    amplitude = screenheight/2; // Height of wave
    
    
    
    
    float t=30;    
    startAlpha=1;
    actualAlpha=1;
    alphaTarget=1;
    fadeInitTime=ofGetElapsedTimef();
    fadeDuration=1;
    
    startAmplitude=0;
    actualAmplitude=0;
    amplitudeTarget=100;//amplitude*10;
    amplitudeInitTime=ofGetElapsedTimef();
    amplitudeDuration=t;
    
    
    actualPeriod=period;
    periodStart=period;
    periodTarget=200;
    periodInitTime=ofGetElapsedTimef();
    periodDuration=t;
    
    
     startLerp=0;
     actualLerp=0;
     lerpTarget=1;
     lerpInitTime=ofGetElapsedTimef();
     lerpDuration=t;
    
    
    
}


void Wave::setPeriod(int _p){
    period=_p;
    dx = (TWO_PI / period) * xspacing;
    // yvalues = new Array(p.floor(w/xspacing));
    yvalues.clear();
    
    for (int i=0;i<floor(w/xspacing);i++){
        yvalues.push_back(0.0);
    }
}

void Wave::setXSpacing(int _x){
    xspacing=_x;
    dx = (TWO_PI / period) * xspacing;
    // yvalues = new Array(p.floor(w/xspacing));
    yvalues.clear();
    
    for (int i=0;i<floor(w/xspacing);i++){
        yvalues.push_back(0.0);
    }
}


void Wave::startFadeOut(){
    alphaTarget=0;
    fadeInitTime=ofGetElapsedTimef();
    
    cout<<"----------START FADE OUT------------------"<<endl;

}

void Wave::update(){
    //setPeriod(period-1);
    auto now = ofGetElapsedTimef();
    auto endTime = fadeInitTime + fadeDuration;
    
    actualAlpha = ofxeasing::map_clamp(now, fadeInitTime, endTime, startAlpha, alphaTarget, &ofxeasing::linear::easeNone);
    
    
    
    if(actualAlpha<=0){
        bShouldRemove=true;
        cout<<"Remove"<<endl;
    }
    
    auto lerpEndTime = lerpInitTime + lerpDuration;

    actualLerp = ofxeasing::map_clamp(now, lerpInitTime, lerpEndTime, startLerp, lerpTarget, &ofxeasing::linear::easeOut);

    auto amplitudeEndTime = amplitudeInitTime + amplitudeDuration;
    actualAmplitude = ofxeasing::map_clamp(now, amplitudeInitTime, amplitudeEndTime, startAmplitude, amplitudeTarget, &ofxeasing::linear::easeNone);
    
    auto periodEndTime = periodInitTime + periodDuration;
    
    actualPeriod = int(ofxeasing::map_clamp(now, periodInitTime, periodEndTime, periodStart, periodTarget, &ofxeasing::linear::easeNone));
   
    setPeriod(actualPeriod);
    
   
    theta -= speed;
    
    // For every x value, calculate a y value with sine function
    float x = -250+theta;
    for (int i = 0; i < numActors; i++) {
        yvalues[i] = sin(x)*actualAmplitude;
        x+=dx;
    }
    

    
    //if(numActors<yvalues.size())numActors++;
    
    
    switch (state) {
        case START:
            if(numActors<yvalues.size()){
                numActors+=0.5;
            }else if(numActors>=yvalues.size()){
                setState(WAVE);
            }
            break;
            
        case WAVE:
            break;
            
        case FADEOUT:
          
            break;
            
        default:
            break;
    }
}

void Wave::draw(){
    
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofTranslate(500,500);

    ofRotate(angle);
   // ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
    ofTranslate(-500,-500);

   
    
    ofPolyline rough;
    ofMesh smooth;
    rough.clear();
    smooth.clear();
    //for (int x = 1; x < yvalues.size(); x++) {
    for (int x = 0; x < numActors-1; x++) {
        rough.addVertex(x*xspacing, screenheight/2+yvalues[x]);
    }

    
    int anz=10;
    
   //  minWidth=4;
   //  maxWidth=45;

    for(int i=anz-1;i>=0;i--){
        
        //float alpha=ofMap(i,0,anz-1,255,60);
        float alpha=ofMap(i,0,anz-1,255,10);

       // ofSetColor(255,alpha);
        ofSetColor(myColor,alpha*actualAlpha);

       // float r=map(i,0,anz-1,minWidth,maxWidth,3);
        float r=map(i,0,anz-1,minWidth,maxWidth,mapShaper);

        ofxPolyToMesh(smooth, rough, r);
        smooth.draw();
        //ofSetLineWidth(5);
       // rough.draw();
        
    }
    
    ofPopMatrix();

    
}



ofFbo Wave::getFbo(){
    waveFbo.begin();
    ofClear(0, 0, 0,0);

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotate(angle);
    ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
    
    float h=myColor.getHue();
    float s=myColor.getSaturation();
    float b=myColor.getBrightness();
    
    ofColor c1,c2;
    c1.setHsb(h,s,b,255);
    c2.set(0,255);
    
   ofColor c3=ofColor(255,255);
    ofColor bkg=backgroundcolor;
    
    ofColor bkg_mix=initBackgroundcolor.lerp(bkg,actualLerp);
    ofColor white_bkg_mix=c3.lerp(bkg_mix,actualLerp);
    ofColor black_bkg_mix=c2.lerp(bkg_mix,actualLerp);

    
    ofSetColor(255);
    ofPolyline rough;
    ofMesh smooth;
    rough.clear();
    smooth.clear();
    for (int x = 0; x < numActors-1; x++) {
        rough.addVertex(x*xspacing, ofGetHeight()/2+yvalues[x]);
    }
    
    int anz=10;
    ofPushMatrix();
    for(int i=anz-1;i>=0;i--){
        s=ofMap(i,0,anz-1,0,255);
        c2.setSaturation(s);
        
        float ratio=ofMap(i, anz-1,0, 0, 1);
        ofColor inBetween = black_bkg_mix.lerp(white_bkg_mix,ratio) ;

        ofSetColor(inBetween);
        
        float alpha=ofMap(i,0,anz-1,255,0);
        ofSetColor(255,alpha);

       float r=ofMap(i,0,anz-1,minWidth,maxWidth);
        ofxPolyToMesh(smooth, rough, r);
        smooth.draw();
    }
    ofPopMatrix();
    

    
    ofPopMatrix();
    waveFbo.end();

    return waveFbo;
    
}

float Wave::getAlpha(){
    return actualAlpha;
}


void Wave::setBackgroundcolor(ofColor _col){
    backgroundcolor=_col;
}

void Wave::setState(int _state){
    stateBefore=state;
    state=_state;
    switch (state) {
        case START:
            break;
            
        case WAVE:
            break;
            
        case FADEOUT:
            startFadeOut();
            break;
            
        default:
            break;
    }
}

int Wave::getState(){
    return state;
}

void Wave::setPeriodTarget(int t){
    periodTarget=t;
    periodStart=actualPeriod;
    cout<<"target "<<periodTarget<<" start "<<periodStart<<endl;
}

void Wave::setPeriodDuration(float t){
    periodDuration=t;
}
void Wave::setInitTime(){
    periodInitTime=ofGetElapsedTimef();
}




void Wave::setAmplitudeTarget(int t){
    amplitudeTarget=t;
    startAmplitude=actualAmplitude;
    cout<<"amp "<<amplitudeTarget<<" start "<<startAmplitude<<endl;
}

void Wave::setAmplitudeDuration(float t){
    amplitudeDuration=t;
    amplitudeInitTime=ofGetElapsedTimef();

}

void Wave::setSpeed(float s){
    speed=s;
}


float Wave::map(float in, float inMin, float inMax, float outMin, float outMax, float shaper){
        // (1) convert to pct (0-1)
        float pct = ofMap (in, inMin, inMax, 0, 1, true);
        // raise this number to a power
        pct = powf(pct, shaper);
        float out = ofMap(pct, 0,1, outMin, outMax, true);
        return out;
    }
    

