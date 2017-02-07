/*
 *  AudioParticles.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#include "ofMain.h"

#include "AudioParticles.h"
#include "AppManager.h"

const int  AudioParticles::NUM_PARTICLES = 50;
const float  AudioParticles::DISTANCE_THRESHOLD = 200;

void AudioParticle::draw()
{
    ofPushStyle();
        ofSetColor(ofColor::white);
        ofFill();
        ofCircle(m_position, 4);
    ofPopStyle();
}


AudioParticles::AudioParticles()
{
	//Intentionally left empty
}


AudioParticles::~AudioParticles()
{
    ofLogNotice() <<"AudioParticles::Destructor" ;
}


void AudioParticles::setup()
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
    for (int i = 0; i < NUM_PARTICLES; i++) {
        ofPtr<AudioParticle> particle = ofPtr<AudioParticle>(new AudioParticle());
        particle->m_offset = ofPoint(ofRandom( -width, width ), ofRandom( -height, height ));
        m_particles.push_back(particle);
    }
}


void AudioParticles::update()
{
    double dt = ofGetLastFrameTime();
    
    //Update particles positions
    for (auto particle : m_particles )
    {
        particle->m_offset.x += m_velocity * dt;	//move offset
        particle->m_offset.y += m_velocity * dt;	//move offset
      
        //Calculate Perlin's noise in [-1, 1] and
        //multiply on Rad
        particle->m_position.x = ofSignedNoise(  particle->m_offset.x ) * m_radius;
        particle->m_position.y = ofSignedNoise(  particle->m_offset.y ) * m_radius;
    }
}

void AudioParticles::draw()
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
    //Move center of coordinate system to the screen center
    ofPushMatrix();
    ofTranslate( width / 2, height/ 2 );
    
    for (auto particle : m_particles )
    {
        //particle->draw();
    }
    
   
    
    ofPushStyle();
    ofSetColor(ofColor::white);
    
    for (int j=0; j < m_particles.size(); j++)
    {
        for (int k= j + 1; k < m_particles.size(); k++)
        {
            if (m_particles[j]->m_position.distance(m_particles[k]->m_position) < DISTANCE_THRESHOLD)
            {
                ofDrawLine( m_particles[j]->m_position, m_particles[k]->m_position );
            }
        }
    }
    
    ofPopStyle();
    ofPopMatrix();
}

void AudioParticles::setParameters(float radius, float velocity)
{
    float width = AudioVisualsManager::FBO_WIDTH;
    float height = AudioVisualsManager::FBO_HEIGHT;
    
    m_radius = ofMap( radius, 0.0, 1.0, width, width*2, true );
    m_velocity = ofMap( velocity, 0.0, 1.0, 0.05, 0.5 );
}





