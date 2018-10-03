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

   
   shaderBlurOnePass.allocate(screenwidth,screenheight,GL_RGBA);
   shaderBlurTwoPass.allocate(screenwidth,screenheight,GL_RGBA);
    
    fboShader.allocate(screenwidth,screenheight,GL_RGBA);
    fboShader.begin();
    ofClear(255,255);
    fboShader.end();
    
    
    
    colorangle=0;
  
   backgroundcolor=ofColor(0);

    blendMode = 0;

    maske.load("maske.png");
    
  
    
    
    minAmplitude=screenheight/2;
    maxAmplitude=screenheight*4;
    
    minPeriod=200;
    maxPeriod=900;
    
    //wavecolor=ofColor(255,0,0);
    wavecolor.setHsb(0, 200, 200);
    waveHueAngle=0;
    
    maxPlayers=50;//15;
    
    amplitudeDuration=0.5;
    periodDuration=0.5;
    
    ofParamAmplitudeDuration.set("amplitude T",0.5,0.5,50);
    ofParamPeriodDuration.set("period T",0.5,0.5,50);

    ofParamMinWidth.set("minwidth",4,1,10);
    ofParamMaxWidth.set("maxwidth",45,10,70);
    ofParamMapShaper.set("mapShaper",8,1,15);
    
    ofParameterBlending.set("Additive Blend", true);
    
    gui = new ofxDatGui();
    gui->addLabel("gui from of_parameters");
    gui->addSlider(ofParamMinWidth);
    gui->addSlider(ofParamMaxWidth);
    gui->addSlider(ofParamMapShaper);
    gui->addLabel("Speed");
    gui->addSlider(ofParamPeriodDuration);
    gui->addSlider(ofParamAmplitudeDuration);
    gui->addLabel("Settings");
    
    gui->addToggle("Screen Simulation",true);
    gui->addToggle("Blur",true);
    gui->addToggle("Second Blur",true);

    gui->addToggle("Alphablending",false);
    


    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);

    addWave();
    addWave();
    
}

//--------------------------------------------------------------
void ofApp::update(){
  
  
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
    
    for(int i=0;i<wavesToRemove.size();i++){
        wavesToRemove[i]->setBackgroundcolor(backgroundcolor);
        wavesToRemove[i]->update();

    }
    
    
    
    ofRemove(wavesToRemove,shouldRemove);

    
    ofRemove(waves,shouldRemove);
    numPlayerBefore=numPlayer;

   // minWidthslider->update();
 
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
    if(bUseBlending){
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    }
   glBlendEquation(GL_FUNC_ADD);
    
    for(int i=0;i<wavesToRemove.size();i++){
        wavesToRemove[i]->draw();
    }
    
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
   // fbo.draw(0,0);
    //blur.draw();
  if(bUseShader){
        shader.end();
    }
    
    fboShader.end();

    
   // fboShader.getTextureReference().getTextureData().bFlipTexture = true;

    
   // fboShader.draw(ofGetWidth()/2-fboShader.getWidth()/2,ofGetHeight()/2-fboShader.getHeight()/2);
    

    
    blur=6;
    
    shaderBlurOnePass.begin();
    ofClear(0,0);
    // ofSetColor(255);
    ofSetColor(backgroundcolor);
    ofDrawRectangle(0,0,screenwidth,screenheight);
    
    if(bUseSecondBlur){
        shaderBlurX.begin();
        shaderBlurX.setUniform1f("blurAmnt", blur);
    }
    
   
    
    ofSetColor(255);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    fboShader.draw(0,0);
    //  ofEnableAlphaBlending();
    
    if(bUseSecondBlur){
        shaderBlurX.end();
    }
    shaderBlurOnePass.end();
    
    
    shaderBlurTwoPass.begin();
    ofClear(0,0);
    
    if(bUseSecondBlur){
        shaderBlurY.begin();
        shaderBlurY.setUniform1f("blurAmnt", blur);
    }
    ofSetColor(255);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    shaderBlurOnePass.draw(0, 0);
    if(bUseSecondBlur){
        shaderBlurY.end();
    }
    shaderBlurTwoPass.end();
    
    
    if(bUseSecondBlur){
        shaderBlurTwoPass.draw(ofGetWidth()/2-fboShader.getWidth()/2,ofGetHeight()/2-fboShader.getHeight()/2);

    }else{
        fboShader.draw(ofGetWidth()/2-fboShader.getWidth()/2,ofGetHeight()/2-fboShader.getHeight()/2);
    }

    
    
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

    ofSetColor(255);
    ofDrawBitmapString(info, 10, 350);
    
   
}

void ofApp::addWave(){
    
    numPlayer++;
    if(numPlayer>maxPlayers)numPlayer=maxPlayers;
    
    if(waves.size()<numPlayer){
        angle=(angle+45)%360;
        hueAngle+=10;
        
        
        waveHueAngle+=5;
        wavecolor.setHueAngle(waveHueAngle%360);
        
        
    //    ofParamMapShaper=ofMap(numPlayer, 2, 20, 1, 10,true);
        
        
        // backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);
        
        
        
        waves.back().get()->setPeriodTarget(ofMap(numPlayer, 0, maxPlayers, maxPeriod, minPeriod));
        waves.back().get()->setPeriodDuration(ofParamPeriodDuration);
        waves.back().get()->setInitTime();
        
        waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, maxPlayers, minAmplitude, maxAmplitude));
        waves.back().get()->setAmplitudeDuration(ofParamAmplitudeDuration);
        
        waves.back().get()->myColor=wavecolor;
        
        
        waves.back().get()->minWidth=ofParamMinWidth;
        waves.back().get()->maxWidth=ofParamMaxWidth;
        waves.back().get()->mapShaper=ofParamMapShaper;
        
        
        // waves.back()->setSpeed(ofMap(numPlayer, 0, 10, 0.01, 0.005));
        // waves.back()->setSpeed(0.99);
        
     /*   for(int i=0;i<waves.size();i++){
            waves[i]->mapShaper=ofParamMapShaper;
        }*/
        
        
    }
    
}


void ofApp::addWaveClockwise(){
    
    numPlayer++;
    if(numPlayer>maxPlayers)numPlayer=maxPlayers;
    
    if(waves.size()<numPlayer){
        angle=(angle-45)%360;
        hueAngle+=10;
        
        
        waveHueAngle+=5;
        wavecolor.setHueAngle(waveHueAngle%360);
        
        
       // ofParamMapShaper=ofMap(numPlayer, 2, 20, 1, 10,true);

        
        // backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);
        
        
        
        waves.back().get()->setPeriodTarget(ofMap(numPlayer, 0, maxPlayers, maxPeriod, minPeriod));
        waves.back().get()->setPeriodDuration(ofParamPeriodDuration);
        waves.back().get()->setInitTime();
        
        waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, maxPlayers, minAmplitude, maxAmplitude));
        waves.back().get()->setAmplitudeDuration(ofParamAmplitudeDuration);
        
        waves.back().get()->myColor=wavecolor;
        
        
        waves.back().get()->minWidth=ofParamMinWidth;
        waves.back().get()->maxWidth=ofParamMaxWidth;
        waves.back().get()->mapShaper=ofParamMapShaper;
        
        
        // waves.back()->setSpeed(ofMap(numPlayer, 0, 10, 0.01, 0.005));
        // waves.back()->setSpeed(0.99);
        
       /* for(int i=0;i<waves.size();i++){
            waves[i]->mapShaper=ofParamMapShaper;
        }*/
        
    }
    
}



void ofApp::addWaveAntiClockwise(){
    
    numPlayer++;
    if(numPlayer>maxPlayers)numPlayer=maxPlayers;
    
    if(waves.size()<numPlayer){
        angle=(angle+45)%360;
        hueAngle+=10;
        
        
        waveHueAngle+=5;
        wavecolor.setHueAngle(waveHueAngle%360);
        
       // ofParamMapShaper=ofMap(numPlayer, 2, 20, 1, 10,true);

        
        
        // backgroundcolor.setHueAngle(hueAngle%360);
        waves.push_back(shared_ptr<Wave>(new Wave));
        waves.back().get()->setup(angle,backgroundcolor);
        
        
        
        waves.back().get()->setPeriodTarget(ofMap(numPlayer, 0, maxPlayers, maxPeriod, minPeriod));
        waves.back().get()->setPeriodDuration(ofParamPeriodDuration);
        waves.back().get()->setInitTime();
        
        waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, maxPlayers, minAmplitude, maxAmplitude));
        waves.back().get()->setAmplitudeDuration(ofParamAmplitudeDuration);
        
        waves.back().get()->myColor=wavecolor;
        
        
        waves.back().get()->minWidth=ofParamMinWidth;
        waves.back().get()->maxWidth=ofParamMaxWidth;
        waves.back().get()->mapShaper=ofParamMapShaper;
        
        
        // waves.back()->setSpeed(ofMap(numPlayer, 0, 10, 0.01, 0.005));
        // waves.back()->setSpeed(0.99);
        
     /*   for(int i=0;i<waves.size();i++){
            waves[i]->mapShaper=ofParamMapShaper;
        }*/
        
    }
    
}

void ofApp::removeWave(){
    numPlayer--;
    if(numPlayer<2)numPlayer=2;
    
   // ofParamMapShaper=ofMap(numPlayer, 2, 20, 1, 10,true);

    
    if( waves.size()>2 ){
        for(int i=0;i<waves.size();i++){
            cout<<i<<" "<<waves[i]->getState()<<endl;
            
            if(waves[i]->getState()!=FADEOUT){
                waves[i]->setState(FADEOUT);
                wavesToRemove.push_back(waves[i]);
                waves.erase(waves.begin() + i);
                break;
                
            }
        }
        
        
    /*    for(int i=0;i<waves.size();i++){
                 waves[i]->mapShaper=ofParamMapShaper;
        }*/
        
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
  /*  if(key=='a'){
        bUseAlpha=!bUseAlpha;
    }*/
    
    if(key=='s'){
        bUseShader=!bUseShader;
    }

    if(key=='b'){
        bUseBlur=!bUseBlur;
   }
  
    if(key=='c'){
        bUseBlending=!bUseBlending;
    }
    if(key=='g'){
        gui->setVisible(!gui->getVisible());
    }
 
    if(key=='q'){
        addWaveClockwise();
    }
    if(key=='w'){
        addWaveAntiClockwise();
    }
    
    
    /*
    if(key=='C'){
        for(int i=0;i<waves.size();i++){
            waves[i]->bUseBlending=!waves[i]->bUseBlending;
        }
    }
 */
    
 /*   if(key=='w'){
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
    }*/
    
    

    

    
    
    if(key=='1'){
       ofParamMinWidth=2;
       ofParamMaxWidth=45;
        ofParamMapShaper=8;
        for(int i=0;i<waves.size();i++){
            waves[i]->minWidth=ofParamMinWidth;
            waves[i]->maxWidth=ofParamMaxWidth;
            waves[i]->mapShaper=ofParamMapShaper;
        }
    }
    
    if(key=='2'){
        ofParamMinWidth=4;
        ofParamMaxWidth=45;
        ofParamMapShaper=8;
        for(int i=0;i<waves.size();i++){
            waves[i]->minWidth=ofParamMinWidth;
            waves[i]->maxWidth=ofParamMaxWidth;
            waves[i]->mapShaper=ofParamMapShaper;
        }
    }
    
    
    
    if(key=='3'){
        ofParamMinWidth=4;
        ofParamMaxWidth=65;
        ofParamMapShaper=6;
        for(int i=0;i<waves.size();i++){
            waves[i]->minWidth=ofParamMinWidth;
            waves[i]->maxWidth=ofParamMaxWidth;
            waves[i]->mapShaper=ofParamMapShaper;
        }
    }
    
   
  
    
    if (key == OF_KEY_UP)
    {
       /* numPlayer++;
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
        waves.back().get()->setPeriodDuration(ofParamPeriodDuration);
        waves.back().get()->setInitTime();
        
        waves.back().get()->setAmplitudeTarget(ofMap(numPlayer, 0, maxPlayers, minAmplitude, maxAmplitude));
        waves.back().get()->setAmplitudeDuration(ofParamAmplitudeDuration);
            
        waves.back().get()->myColor=wavecolor;

            
           waves.back().get()->minWidth=ofParamMinWidth;
          waves.back().get()->maxWidth=ofParamMaxWidth;
          waves.back().get()->mapShaper=ofParamMapShaper;
           
            
           // waves.back()->setSpeed(ofMap(numPlayer, 0, 10, 0.01, 0.005));
           // waves.back()->setSpeed(0.99);

        }
        */
        addWave();
        

    }
    if (key == OF_KEY_DOWN)
    {
       /* numPlayer--;
        if(numPlayer<2)numPlayer=2;
        if( waves.size()>2 ){
            for(int i=0;i<waves.size();i++){
                cout<<i<<" "<<waves[i]->getState()<<endl;

                if(waves[i]->getState()!=FADEOUT){
                    waves[i]->setState(FADEOUT);
                    wavesToRemove.push_back(waves[i]);
                    waves.erase(waves.begin() + i);
                    break;

                }
            }
            
        }
*/
        removeWave();
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

void ofApp::onParamIntChanged(int & n)
{
    // cout << "onParamIntChanged "<< n << endl;
}

void ofApp::onParamFloatChanged(float & f)
{
    // cout << "onParamFloatChanged "<< f << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
  /*  if(e.target == minWidthSlider){
       // ofSetBackgroundColor(ofColor::white*e.scale);
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == sliderInt){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }   else if (e.target == sliderFloat){
        cout << e.target->getLabel() << " value = "; e.target->printValue();
    }*/
    
    for(int i=0;i<waves.size();i++){
        waves[i]->minWidth=ofParamMinWidth;
        waves[i]->maxWidth=ofParamMaxWidth;
        waves[i]->mapShaper=ofParamMapShaper;
    }
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e){
    
        // or we can check against the label of the event target //
if(e.target->getLabel() == "Alphablending"){
   // cout<<e.target->getChecked()<<endl;
    bUseBlending=e.target->getChecked();
    }
if(e.target->getLabel() == "Screen Simulation"){
    bUseShader=e.target->getChecked();
    
}
    
    if(e.target->getLabel() == "Blur"){
        bUseBlur=e.target->getChecked();
    }
    
    
    if(e.target->getLabel() == "Second Blur"){
        bUseSecondBlur=e.target->getChecked();
    }
    
    
}


