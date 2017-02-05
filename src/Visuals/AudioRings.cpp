/*
 *  AudioRings.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#include "ofMain.h"

#include "AudioRings.h"
#include "AppManager.h"


AudioRing::AudioRing(): m_radius(0)
{
    
}

void AudioRing::draw()
{
    ofPushStyle();
        ofSetColor(m_color);
        ofNoFill();
        ofCircle(m_position, m_radius);
    ofPopStyle();
}


AudioRings::AudioRings()
{
	//Intentionally left empty
}


AudioRings::~AudioRings()
{
    ofLogNotice() <<"AudioRings::Destructor" ;
}


void AudioRings::setup()
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
    ofPtr<AudioRing> ringLeft = ofPtr<AudioRing>(new AudioRing());
    ringLeft->m_offset.x = width*0.2;  ringLeft->m_offset.y = height*0.5;
    ringLeft->m_position = ringLeft->m_offset;
    ringLeft->m_color = ofColor(255, 0, 0);
    m_rings.push_back(ringLeft);
    
    ofPtr<AudioRing> ringRight = ofPtr<AudioRing>(new AudioRing());
    ringRight->m_offset.x = width*0.8;  ringRight->m_offset.y = height*0.5;
    ringRight->m_position = ringRight->m_offset;
    ringRight->m_color = ofColor(0, 0, 255);
    m_rings.push_back(ringRight);
}


void AudioRings::update()
{
    double dt = ofGetLastFrameTime();
    
    //Update particles positions
    int i = 0;
    for (auto ring : m_rings )
    {
        ring->m_offset.x += m_velocity * dt;	//move offset
        ring->m_offset.y += m_velocity * dt;	//move offset
      
        //Calculate Perlin's noise in [-1, 1] and
        //multiply on Rad
        ring->m_position.x = ring->m_offset.x + ofSignedNoise( i*1000 + ring->m_offset.x ) * m_radius;
        ring->m_position.y = ring->m_offset.y + ofSignedNoise( i*1000 + ring->m_offset.y ) * m_radius;
        
        i++;
    }
    
    m_rings[0]->m_radius = m_radius;
    m_rings[1]->m_radius = m_radius;
}

void AudioRings::draw()
{
    
    for (auto ring : m_rings )
    {
        ring->draw();
    }
}

void AudioRings::setParameters(float radius, float velocity)
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
    m_radius = ofMap( radius, 0.0, 1.0, 10, width/2, true );
    m_velocity = ofMap( velocity, 0.0, 1.0, 0.2, 3.5 );//
}





