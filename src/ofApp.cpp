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
    
    
    fbo.allocate(screenwidth,screenheight,GL_RGBA);
    fbo.begin();
    ofClear(255,255);
    fbo.end();
    
    fboBlurOnePass.allocate(screenwidth,screenheight,GL_RGBA);
    fboBlurTwoPass.allocate(screenwidth,screenheight,GL_RGBA);

    fboBlurOnePass_end.allocate(screenwidth,screenheight,GL_RGBA);
    fboBlurTwoPass_end.allocate(screenwidth,screenheight,GL_RGBA);
    
    
    
    fboShader.allocate(screenwidth,screenheight,GL_RGBA);
    fboShader.begin();
    ofClear(255,255);
    fboShader.end();
    
    
    
    colorangle=0;
  
   backgroundcolor=ofColor(0);
   // backgroundcolor=ofColor(222,184,135);

    blendMode = 0;

    maske.load("maske.png");
    
 //   blur.setup(ofGetWidth(), ofGetHeight(), 10, .2, 4);

    
   // ofBackground(255);
    
    
    
   /* backgroundcolor.setHueAngle(hueAngle%360);
    waves.push_back(shared_ptr<Wave>(new Wave));
    waves.back().get()->setup(angle,backgroundcolor);
    
    
    angle=(angle+90)%360;
    hueAngle+=10;
    backgroundcolor.setHueAngle(hueAngle%360);
    waves.push_back(shared_ptr<Wave>(new Wave));
    waves.back().get()->setup(angle,backgroundcolor);
    */
    
    
    
    minAmplitude=screenheight/2;
    maxAmplitude=screenheight*4;
    
    minPeriod=200;
    maxPeriod=900;
    
    //wavecolor=ofColor(255,0,0);
    wavecolor.setHsb(0, 200, 200);
    waveHueAngle=0;
    
    maxPlayers=15;
    
    amplitudeDuration=0.5;
    periodDuration=0.5;
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
  
   // blur.setScale(ofMap(mouseX, 0, ofGetWidth(), 0, 10));
    //blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
   /* if(numPlayer!=numPlayerBefore){
    waveHueAngle+=10;
    wavecolor.setHueAngle(waveHueAngle%360);
    }*/
    
    for(int i=0;i<waves.size();i++){
        waves[i]->setBackgroundcolor(backgroundcolor);
        if(numPlayer!=numPlayerBefore){
            
            
            
            
         //  waves[i]->setPeriodTarget(ofMap(numPlayer, 0, 10, maxPeriod, minPeriod));
         //   waves[i]->setPeriodDuration(5);
         //   waves[i]->setInitTime();
            
        // waves[i]->setAmplitudeTarget(ofMap(numPlayer, 0, 10, minAmplitude, maxAmplitude));
          //  waves[i]->setAmplitudeDuration(5);
            
           // waves[i]->myColor=wavecolor;
            
            //waves[i]->setSpeed(ofMap(numPlayer, 0, 10, 0.05, 0.005));
           
        }
      //  waves[i]->setSpeed(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.005, 1));

        waves[i]->update();
    }
    
  
    
    ofRemove(waves,shouldRemove);
    numPlayerBefore=numPlayer;

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    //ofScale(0.072,0.072);
    ofBackground(backgroundcolor);
        float blur = 2;
  

        ofSetColor(255);
 /*
    vector <ofFbo> fbos;
    
    for(int i=0;i<waves.size();i++){
        fbos.push_back(waves[i]->getFbo());
    }
   */
    
   // ofSetColor(backgroundcolor);
   // ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    
    



    
    
    ofSetColor(255);
    
    fbo.begin();

    ofClear(0,0);
   // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   glBlendEquation(GL_FUNC_ADD);
    for(int i=0;i<waves.size();i++){
        waves[i]->draw();
    }
    fbo.end();
   
  
    
    
    

    
 
    
    fboBlurOnePass.begin();
    ofClear(0,0);
   // ofSetColor(255);
    ofSetColor(backgroundcolor);
   ofDrawRectangle(0,0,screenwidth,screenheight);
    
    if(bUseBlur){
        shaderBlurX.begin();
        shaderBlurX.setUniform1f("blurAmnt", blur);
    }
 
    ofSetColor(255);
    fbo.draw(0, 0);
    
    ofSetColor(255);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    fbo.draw(0,0);
  //  ofEnableAlphaBlending();
    
    if(bUseBlur){
        shaderBlurX.end();
    }
    fboBlurOnePass.end();

    
    fboBlurTwoPass.begin();
    ofClear(0,0);

    if(bUseBlur){
        shaderBlurY.begin();
        shaderBlurY.setUniform1f("blurAmnt", blur);
    }
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    fboBlurOnePass.draw(0, 0);
    if(bUseBlur){
        shaderBlurY.end();
    }
        fboBlurTwoPass.end();
  

  

    
    
    
    fboShader.begin();
    ofClear(0,0);
fboShader.getTextureReference().getTextureData().bFlipTexture = true;
    
   if(bUseShader){
        shader.begin();
        shader.setUniform2f("u_resolution", screenwidth,screenheight);
       // shader.setUniformTexture("tex0", fbo.getTextureReference(), 1);
       shader.setUniformTexture("tex1", fboBlurTwoPass.getTextureReference(), 1);

        shader.setUniform1f("time", ofGetElapsedTimef());
        float mousePosition = ofGetMouseX();
        shader.setUniform1f("mouseX", mousePosition);
        shader.setUniform1f("u_numDots", numDots);

    }
       ofSetColor(ofColor::white);
   // fboBlurTwoPass.draw(0, 0);
 
    
  
    ofSetColor(255);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    fboBlurTwoPass.draw(0,0);
    //blur.draw();
  if(bUseShader){
        shader.end();
    }
    
    fboShader.end();

    
   // fboShader.getTextureReference().getTextureData().bFlipTexture = true;

    
    fboShader.draw(ofGetWidth()/2-fboShader.getWidth()/2,ofGetHeight()/2-fboShader.getHeight()/2);
    

    
    
    
    
    
    
   // ofSetColor(255);
  // glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
   // fbo.draw(0,0);
    //glDisable(GL_BLEND);

   ofEnableAlphaBlending();
    ofSetColor(0);

    maske.draw(ofGetWidth()/2-500,ofGetHeight()/2-500);
    

//    blur.draw();
    ofPopMatrix();
    
    
    string info = "";
    info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
    info += "num Player: "+ofToString(numPlayer)+"\n";
    info += "Speed: "+ofToString(ofMap(ofGetMouseX(), 0,screenwidth, 0.005, 1))+"\n";

    
    ofSetColor(255);
   ofDrawBitmapString(info, 10, 10);
   
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
      //  backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);
        
        
        
         waves.back().get()->setPeriodTarget(ofMap(numPlayer, 0, 10, 800, 100));
         waves.back().get()->setPeriodDuration(periodDuration);
         waves.back().get()->setInitTime();
        
         waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, 10, 100, screenheight*3));
        waves.back().get()->setAmplitudeDuration(amplitudeDuration);
        

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
        if(numPlayer>maxPlayers)numPlayer=maxPlayers;
        
        if(waves.size()<numPlayer){
        angle=(angle+45)%360;
        hueAngle+=10;
  
            
        waveHueAngle+=5;
        wavecolor.setHueAngle(waveHueAngle%360);
            
            
       // backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);
        
        
        
        waves.back().get()->setPeriodTarget(ofMap(numPlayer, 0, maxPlayers, maxPeriod, minPeriod));
        waves.back().get()->setPeriodDuration(periodDuration);
        waves.back().get()->setInitTime();
        
        waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, maxPlayers, minAmplitude, maxAmplitude));
        waves.back().get()->setAmplitudeDuration(amplitudeDuration);
            
        waves.back().get()->myColor=wavecolor;

            
            
           
            
           // waves.back()->setSpeed(ofMap(numPlayer, 0, 10, 0.01, 0.005));
           // waves.back()->setSpeed(0.99);

        }
        
        

    }
    if (key == OF_KEY_DOWN)
    {
        numPlayer--;
        if(numPlayer<0)numPlayer=0;
        if(numPlayer>=0)
            for(int i=0;i<waves.size();i++){
                cout<<i<<" "<<waves[i]->getState()<<endl;

                if(waves[i]->getState()!=FADEOUT){
                    waves[i]->setState(FADEOUT);
                    break;

                }
            }
            
        

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
