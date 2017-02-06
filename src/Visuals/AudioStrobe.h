/*
 *  AudioStrobe.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "Manager.h"


//========================== class AudioStrobe ==============================
//============================================================================
/** \class AudioStrobe AudioStrobe.h
 *	\brief Class representing audio particle visuals
 *	\details it creates and updates the audio particles
 */


class AudioStrobe
{
    public:

        //! Constructor
        AudioStrobe();

        //! Destructor
        ~AudioStrobe();

        //! Setup the Audio Particles
        void setup();

        //! Update the Audio Particles
        void update();
    
        //! Draw the Audio Particles
        void draw();

        void setParameters(float audioMax);
    
    
    private:
    
        int   m_brightness;
};




