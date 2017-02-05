/*
 *  AudioRings.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */

#pragma once

#include "Manager.h"


//========================== class AudioRing ==============================
//============================================================================
/** \class AudioRing AudioRings.h
 *	\brief Class representing a single audio ring
 */


class AudioRing
{
    
public:
    
    //! Constructor
    AudioRing();
    
    //! Destructor
    ~AudioRing(){}
    
    //! Draw the Audio Ring
    void draw();
    
    
public:
    
    ofColor m_color;
    ofPoint m_position;
    ofPoint m_offset;
    float   m_radius;
    
};

//========================== class AudioRings ==============================
//============================================================================
/** \class AudioRings AudioRings.h
 *	\brief Class representing audio ring visuals
 *	\details it creates and updates the audio rings
 */


class AudioRings
{

    public:

        //! Constructor
        AudioRings();

        //! Destructor
        ~AudioRings();

        //! Setup the Audio Rings
        void setup();

        //! Update the Audio Rings
        void update();
    
        //! Draw the Audio Rings
        void draw();

        void setParameters(float radius, float velocity);
    
    
    private:
    
        typedef vector< ofPtr<AudioRing> > Rings;
    
        Rings   m_rings;
    
        float   m_radius;
        float   m_velocity;

};




