//
//  MovingObject.cpp
//  moving object
//
//  Created by Flückiger Michael on 08.05.18.
//

#include "MovingObject.hpp"
#include "ofxEasing.h"


MovingObject:: MovingObject(){
    
}
MovingObject:: ~ MovingObject(){
}

void MovingObject::setup(){
    scaleDuration=ofRandom(1,100);
    actualRadius=0;
    easingInitTime = ofGetElapsedTimef();
    radiusTarget=ofRandom(10,200);

}

void MovingObject::update(){
    auto endTime = easingInitTime + scaleDuration;
    auto now = ofGetElapsedTimef();
    move();
    actualRadius = ofxEasing::map_clamp(now, easingInitTime, endTime, actualRadius, radiusTarget, &ofxEasing::linear::easeIn);
}



void MovingObject::scaleTo(float _value){
    easingInitTime = ofGetElapsedTimef();
    radiusTarget=_value;
}

void MovingObject::scaleTo(float _value, float _duration){
    easingInitTime = ofGetElapsedTimef();
    radiusTarget=_value;
    scaleDuration=_duration;
}

void MovingObject::move(){
   /* ofVec2f d;
    d.set(target);
    d-=position;
    if(d.length()>0.5){
    d.normalize();
    d*=maxspeed;
    speed.set(d);
    }else{
        speed.set(0,0);
    }

    */
    
    if(bSeekTarget) applyForce(seek(target,seekforce));
    
    
    velocity+=acceleration;
    velocity*=0.99;
    position+= velocity;
    acceleration.set(0,0);
    

}





void MovingObject::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    //ofSetColor(255);
    ofDrawEllipse(position.x, position.y, actualRadius, actualRadius);
    ofPopStyle();
    ofPopMatrix();
    
    
    
}


void MovingObject::setPosition(int _x, int _y){
    position.set(_x, _y);


}


void MovingObject::setRadius(int _radius){
    radiusTarget=_radius;
}

int MovingObject::getRadius(){
    return actualRadius;

}

void MovingObject::setSpeed(int _x, int _y){
    velocity.set(_x,_y);
}

ofVec2f MovingObject::getSpeed(){
    return velocity;
}


void MovingObject::setTarget(ofVec2f _target){
    target.set(_target);
}

void MovingObject::applyForce(ofVec2f _force){
    acceleration+= _force;
}


void MovingObject::applyForce(ofVec2f _force, float _strength){
    _force.limit(_strength);
    acceleration+= _force;
}


ofVec2f MovingObject::getPosition(){
    return position;
}

void MovingObject::setSeekForce(float _f){
    seekforce=_f;
}


ofVec2f MovingObject::getDistance(ofVec2f _t){
    ofVec2f p(position);
    ofVec2f desired=_t-p;
    return desired;
}

void MovingObject::setSlowDown(bool _b){
    bSlowDown=_b;
}

void MovingObject::setSlowDownDistance(int _d){
    slowdowndistance=_d;
}


bool MovingObject::shouldRemoveOffScreen(shared_ptr<MovingObject> shape) {
    return !ofRectangle(0, 0, ofGetWidth(), ofGetHeight()).inside(shape.get()->getPosition());
}



bool MovingObject::isOnScreen(){
    bool isInside=false;
    ofRectangle r;
    r.set(0,0,ofGetWidth(),ofGetHeight());
    if(r.inside(position))isInside=true;
    return isInside;
}

void MovingObject::setMaxSpeed(float _m){
    maxspeed=_m;
}


ofVec2f MovingObject::seek(ofVec2f t, float f){
    ofVec2f p(position);
    ofVec2f desired=t-p;
    float d = desired.length();
    desired.normalize();
    if(d<slowdowndistance && bSlowDown){
        float m=ofMap(d,0,slowdowndistance,0,maxspeed);
        desired*=m;
    }else{
        desired*=maxspeed;
    }
    ofVec2f steer=desired-velocity;
    steer.limit(f);
    return steer;
}
