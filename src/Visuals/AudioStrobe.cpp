/*
 *  AudioStrobe.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#include "ofMain.h"

#include "AudioStrobe.h"
#include "AppManager.h"


AudioStrobe::AudioStrobe(): m_brightness(0)
{
    //Intentionally left empty
}



AudioStrobe::~AudioStrobe()
{
    ofLogNotice() <<"AudioStrobe::Destructor" ;
}


void AudioStrobe::setup()
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
}


void AudioStrobe::update()
{
   
}

void AudioStrobe::draw()
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
 
    ofPushStyle();
    ofSetColor(m_brightness);
    ofDrawRectangle(0, 0, width, height);
    ofPopStyle();
    
}

void AudioStrobe::setParameters(float audioMax)
{
    m_brightness = (int) 255*audioMax;
}





