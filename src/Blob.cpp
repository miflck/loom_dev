//
//  Blob.cpp
//  shaderTests
//
//  Created by Flückiger Michael on 04.07.18.
//

#include "Blob.hpp"
void Blob::setup(){
    initRadius=200;
    bSeekTarget=true;
    setTarget(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
    
    for(int i=0;i<360;i+=10){
        ofVec2f p(200,0);
        p.rotate(i);
        positions.push_back(p);
        positions2.push_back(p);

        initPositions.push_back(p);
    }
    
    

    Blobfbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA);
Blobfbo.getTextureReference().getTextureData().bFlipTexture = true;
    Blobfbo.begin();
    ofClear(0, 0, 0,255);
    Blobfbo.end();
    
    
    
}

void Blob::update(){
    move();
    
}

void Blob::draw(){
    
    


    for(int j=1;j<5;j++){
        noisestep=stepper;
        ofPolyline p;

        
        float s=ofMap(j,1,5,1.6,0.5);
        
    for(int i=0;i<positions.size();i++){
        positions[i]=(initPositions[i]*s)+(100*ofSignedNoise( noisestep +j));
        p.addVertex(positions[i]);

        noisestep+=0.1;
    }
    p.close();
    p.getResampledBySpacing(100).getSmoothed(20);
    
    ofPath path;
    for( int i = 0; i < p.getVertices().size(); i++) {
        if(i == 0) {
            path.newSubPath();
            path.moveTo(p.getVertices()[i] );
        } else {
            path.lineTo( p.getVertices()[i] );
        }
    }
    path.close();
    path.simplify();
    
    ofPushMatrix();
    ofTranslate(getPosition());
    path.setColor(ofColor(j*50,0,  255-j*50) );
    path.draw();
    ofPopMatrix();
    
    }
    
    stepper+=0.01;

    
    /*
    for(int i=0;i<positions.size();i++){
        positions[i]=initPositions[i]+(100*ofSignedNoise( noisestep ));
        positions2[i]=(initPositions[i]*1.3)+(120*ofSignedNoise( noisestep+0.5));

        noisestep+=0.1;
    }
    
    ofPolyline p;
    for(int i=0;i<positions.size();i++){
        p.addVertex(positions[i]);
      }
    
    p.close();
    p.getResampledBySpacing(100).getSmoothed(20);
    
    ofPolyline p2;
    for(int i=0;i<positions2.size();i++){
        p2.addVertex(positions2[i]);
    }
    
    p2.close();
    p2.getResampledBySpacing(100).getSmoothed(20);
    
    
    ofPushMatrix();
    ofTranslate(getPosition());
    ofDrawCircle(0,0,5);
       // p.draw();
   // p2.draw();

    ofPopMatrix();
    stepper+=0.01;
    
    
    
    ofPath path;
    
    for( int i = 0; i < p.getVertices().size(); i++) {
        if(i == 0) {
            path.newSubPath();
            path.moveTo(p.getVertices()[i] );
        } else {
            path.lineTo( p.getVertices()[i] );
        }
    }
    path.close();
    path.simplify();
    
    
    ofPath path2;
    
    for( int i = 0; i < p2.getVertices().size(); i++) {
        if(i == 0) {
            path2.newSubPath();
            path2.moveTo(p2.getVertices()[i] );
        } else {
            path2.lineTo( p2.getVertices()[i] );
        }
    }
    path2.close();
    path2.simplify();
    
    ofPushMatrix();
    ofTranslate(getPosition());
    path2.setColor(ofColor(255, 120, 0) );

    path2.draw();
  //  ofSetColor(255, 0, 0 );
    path.setColor(ofColor(255, 50, 0) );
    path.draw();
    ofPopMatrix();
    */
    
 //   radius=(100*ofSignedNoise( noisestep ))+initRadius;
 //   ofDrawEllipse(getPosition(), radius, radius);
 //   noisestep+=0.01;
}


ofFbo Blob::getFbo(){
    
  
    
    Blobfbo.begin();
    ofClear(0,0,0,255);
    for(int j=1;j<5;j++){
        noisestep=stepper;
        ofPolyline p;
        
        
        float s=ofMap(j,1,5,1.6,0.5);
        
        for(int i=0;i<positions.size();i++){
            positions[i]=(initPositions[i]*s)+(100*ofSignedNoise( noisestep +j));
            p.addVertex(positions[i]);
            
            noisestep+=0.1;
        }
        p.close();
        p.getResampledBySpacing(100).getSmoothed(20);
        
        ofPath path;
        for( int i = 0; i < p.getVertices().size(); i++) {
            if(i == 0) {
                path.newSubPath();
                path.moveTo(p.getVertices()[i] );
            } else {
                path.lineTo( p.getVertices()[i] );
            }
        }
        path.close();
        path.simplify();
        
        ofPushMatrix();
        ofTranslate(getPosition());
        path.setColor(ofColor(j*50,0,  255-j*50) );
        path.draw();
        ofPopMatrix();
        
    }
  
    Blobfbo.end();
    stepper+=0.01;
    

    
    return Blobfbo;
    
}

