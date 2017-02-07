/*
 *  AudioVisualsManager.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "Manager.h"

#include "AudioParticles.h"
#include "AudioRings.h"
#include "AudioStrobe.h"


//========================== class AudioVisualsManager ==============================
//============================================================================
/** \class AudioVisualsManager AudioVisualsManager.h
 *	\brief Class managing the audio reactive visuals
 *	\details it creates and updates the audio reactive visuals
 */


class AudioVisualsManager: public Manager
{
    
    static const int NUMBER_VISUALS;
    
    public:

        //! Constructor
        AudioVisualsManager();

        //! Destructor
        ~AudioVisualsManager();

        //! Setup the Video Manager
        void setup();

        //! Update the Video Manager
        void update();
    
        //! Draw the Video Manager
        void draw();
    
        void  onPlayAudioVisualsChange(bool value);
    
        void  onInputLevelChange(float& value) {m_inputLevel = value;}
    
        void  onNextAudiohange();
    
        void resetPosition();
    
    
        void onHueChange(float& value) {m_color.setHue(value);}
    
        void onBrightnessChange(float& value) {m_color.setBrightness(value);}
    
        void onSaturationChange(float& value) {m_color.setSaturation(value);}

    
    private:
    
        void setupBoundingBox();
    
        void setupFbo();
    
        void setupStrobe();
    
        void setupShader();
    
        void setupRings();
    
        void setupParticles();
    
        void updateFbo();
    
        void updateRings();
    
        void updateParticles();
    
        void updateStrobe();
    
        void drawRings();
    
        void drawParticles();
    
        void drawStrobe();
    
    public:
    
        static const int FBO_WIDTH;
        static const int FBO_HEIGHT;
    
    private:
    
        bool            m_playAudioVisuals;
        ofRectangle     m_boundingBox;
        int             m_mode;
    
        float           m_inputLevel;
    
        AudioParticles  m_particles;
        AudioRings      m_rings;
        AudioStrobe     m_strobe;

        ofFbo               m_fbo;
        ofShader            m_shader;
    
        ofColor             m_color;
    
};




