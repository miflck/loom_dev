#pragma once

#include "ofMain.h"
#include "Wave.hpp"
//#include "ofxBlur.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font;
    ofShader shader;
    bool doShader;
    
    
    ofShader exclude;

    
    
    ofShader shaderBlurX;
    ofShader shaderBlurY;
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    
    
    ofFbo fbo;

    bool bUseShader=true;
    bool bUseBlur=true;
    
    bool bUseAlpha=true;
    
    int numDots=72;
    
    Wave wave;
    int angle=0;
    
    vector      <shared_ptr<Wave> > waves;

    


    ofColor backgroundcolor;
    int colorangle=0;
    
    bool bUseBlending=false;
    bool bUseSingleBlend=false;
    bool bUseExclude=false;
    
    int blendMode;

    ofImage maske;
    
    int hueAngle=0;
    int waveHueAngle=0;
    ofColor wavecolor;
    
    
    int numPlayer=0;
    int numPlayerBefore=0;
    
    
    
    int minAmplitude;
    int maxAmplitude;
    
    //ofxBlur blur;


    
};
