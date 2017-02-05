/*
 *  AudioParticles.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "Manager.h"


//========================== class AudioParticle ==============================
//============================================================================
/** \class AudioParticle AudioParticles.h
 *	\brief Class representing a single audio particle
 */


class AudioParticle
{
    
public:
    
    //! Constructor
    AudioParticle(){}
    
    //! Destructor
    ~AudioParticle(){}
    
    //! Draw the Audio Particles
    void draw();
    
    
public:
    
    ofPoint m_position;
    ofPoint m_offset;
    
};

//========================== class AudioParticles ==============================
//============================================================================
/** \class AudioParticles AudioParticles.h
 *	\brief Class representing audio particle visuals
 *	\details it creates and updates the audio particles
 */


class AudioParticles
{
    static const int NUM_PARTICLES;
    static const float DISTANCE_THRESHOLD;
    
    public:

        //! Constructor
        AudioParticles();

        //! Destructor
        ~AudioParticles();

        //! Setup the Audio Particles
        void setup();

        //! Update the Audio Particles
        void update();
    
        //! Draw the Audio Particles
        void draw();

        void setParameters(float radius, float velocity);
    
    
    private:
    
        typedef vector< ofPtr<AudioParticle> > Particles;
    
        Particles   m_particles;
    
        float   m_radius;
        float   m_velocity;

};




