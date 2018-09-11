#include "ofApp.h"


// write our boolean remove function
bool shouldRemove(shared_ptr<Wave> w){
    if(w->bShouldRemove)return true;
    else return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
    exclude.load("shaders_gl3/exclude.vert", "shaders_gl3/exclude.frag");
    
    shaderBlurX.load("shaders_gl3/shaderBlurX");
    shaderBlurY.load("shaders_gl3/shaderBlurY");
    
    
    fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
    fbo.begin();
    ofClear(255,255);
    fbo.end();
    
    fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
    fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
    
    colorangle=0;
  
   backgroundcolor=ofColor(222,184,135);
   // backgroundcolor=ofColor(222,184,135);

    blendMode = 0;

    maske.load("maske.png");
    
 //   blur.setup(ofGetWidth(), ofGetHeight(), 10, .2, 4);

    
   // ofBackground(255);
}

//--------------------------------------------------------------
void ofApp::update(){
  
  
   // blur.setScale(ofMap(mouseX, 0, ofGetWidth(), 0, 10));
    //blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
    
    for(int i=0;i<waves.size();i++){
        waves[i]->setBackgroundcolor(backgroundcolor);
        if(numPlayer!=numPlayerBefore){
            waves[i]->setPeriodTarget(ofMap(numPlayer, 0, 10, 800, 50));
            waves[i]->setPeriodDuration(5);
            waves[i]->setInitTime();
        }
        waves[i]->update();
    }
    
  
    
    ofRemove(waves,shouldRemove);
    numPlayerBefore=numPlayer;

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
 //   ofScale(0.072,0.072);
    ofBackground(backgroundcolor);
        float blur = 2;
  

        ofSetColor(255);
   
        
    //    vector <ofFbo> fbos;
        
      /*  for(int i=0;i<waves.size();i++){
            //ofFbo f=waves[i]->getFbo();
            fbos.push_back(waves[i]->getFbo());
        }*/
        
    
        ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fbo.begin();
    ofClear(0,0);
    for(int i=0;i<waves.size();i++){
        waves[i]->draw();
    }
      fbo.end();
   // ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

   /* fbo.draw(0,0);
    ofSetColor(255);
    maske.draw(0,0);
*/
    
/*
        fbo.begin();
        ofClear(255,0);
    
       ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            for(int i=0;i<waves.size();i++){
                waves[i]->draw();
            }
        fbo.end();

    */

    

    
    
    
    fboBlurOnePass.begin();
    ofClear(0,0);
    ofSetColor(255);
    
    ofSetColor(backgroundcolor);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    if(bUseBlur){
        shaderBlurX.begin();
        shaderBlurX.setUniform1f("blurAmnt", blur);
    }
 
    ofSetColor(255);
    fbo.draw(0, 0);
    if(bUseBlur){
        shaderBlurX.end();
    }
    fboBlurOnePass.end();

    
    fboBlurTwoPass.begin();
    ofClear(255,255);

    if(bUseBlur){
        shaderBlurY.begin();
        shaderBlurY.setUniform1f("blurAmnt", blur);
    }
    fboBlurOnePass.draw(0, 0);
    if(bUseBlur){
        shaderBlurY.end();
    }
        fboBlurTwoPass.end();
  

  

    

    
    

    
   if(bUseShader){
        shader.begin();
        shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
       // shader.setUniformTexture("tex0", fbo.getTextureReference(), 1);
       shader.setUniformTexture("tex1", fboBlurTwoPass.getTextureReference(), 1);

        shader.setUniform1f("time", ofGetElapsedTimef());
        float mousePosition = ofGetMouseX();
        shader.setUniform1f("mouseX", mousePosition);
        shader.setUniform1f("u_numDots", numDots);

    }
       ofSetColor(ofColor::white);
   // fboBlurTwoPass.draw(0, 0);
 
    
    ofSetColor(backgroundcolor);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(255);
   // ofEnableBlendMode(OF_BLENDMODE_ADD);

    fboBlurTwoPass.draw(0,0);
    //blur.draw();
  if(bUseShader){
        shader.end();
    }
    
    
    //fbo.draw(0,0);
    
   // ofEnableAlphaBlending();
    maske.draw(0,0);
    

//    blur.draw();
    ofPopMatrix();
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='a'){
        bUseAlpha=!bUseAlpha;
    }
    
    if(key=='s'){
        bUseShader=!bUseShader;
    }

    if(key=='b'){
        bUseBlur=!bUseBlur;
    }
    if(key=='c'){
        bUseBlending=!bUseBlending;
    }
    
    if(key=='C'){
        for(int i=0;i<waves.size();i++){
            waves[i]->bUseBlending=!waves[i]->bUseBlending;
        }
    }
    
    if(key=='w'){
        angle=(angle+45)%360;
        hueAngle+=10;
        backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);

    }
    
    if(key=='W'){
        angle=(angle+45)%360;
        
        colorangle=(colorangle+80)%255;
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,colorangle);
    }
    
    
    if(key=='n'){
        bUseSingleBlend=!bUseSingleBlend;
    }
    
    if(key=='e'){
        bUseExclude=!bUseExclude;
    }
    
    if(key=='r' && waves.size()>0){
        waves[0]->bShouldRemove=true;
        
     //   waves.erase( waves.begin()+1 );
        
    }
    
    
    if(key=='1'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setPeriod(100);
        }
    }
    
    if(key=='2'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setPeriod(200);
        }
    }
    
    if(key=='3'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setPeriod(1000);
        }
    }
    
    
    if(key=='7'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setXSpacing(3);
        }
    }
    
    if(key=='8'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setXSpacing(10);
        }
    }
    
    if(key=='9'){
        for(int i=0;i<waves.size();i++){
            waves[i]->setXSpacing(100);
        }
    }
    
    if (key == OF_KEY_UP)
    {
        numPlayer++;
    }
    if (key == OF_KEY_DOWN)
    {
        numPlayer--;
        if(numPlayer<0)numPlayer=0;

    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
