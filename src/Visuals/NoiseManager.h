/*
 *  NoiseManager.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "Manager.h"


//========================== class NoiseManager ==============================
//============================================================================
/** \class NoiseManager NoiseManager.h
 *	\brief Class managing the noise visuals
 *	\details it creates and updates noise visuals, as well it provides methods to change it in real time
 */


class NoiseManager: public Manager
{
    
    public:

        //! Constructor
        NoiseManager();

        //! Destructor
        ~NoiseManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();
    
        //! Draw the Halo Manager
        void draw();
    
        //bool readToPixels(ofPixelsRef pix) {return m_fboReader.readToPixels(m_fbo, pix);}
    
        void readToPixels(ofPixelsRef pix) {pix = m_noiseImage.getPixels();}
    
        float getWidth()  {return m_noiseImage.getWidth();}
    
        float getHeight()  {return m_noiseImage.getHeight();}
    
        void onNoiseResolutionChange( int& value);
    
        void onNoiseFrequencyChange(float& value) {m_noiseFrequency = value;}
    
        void onNoiseSpeedChange(float& value) {m_noiseSpeed = value;}
    
        void onHueChange(float& value) {m_color.setHue(value);}
    
        void onBrightnessChange(float& value) {m_color.setBrightness(value);}
    
        void onSaturationChange(float& value) {m_color.setSaturation(value);}
    
        void  onPlayNoiseChange(bool value) {m_playNoise = value;}
    
        void resetPosition();

    
    private:
    
        void setupBoundingBox();
    
        void setupFbo();
    
        void setupNoise();
    
        void updateNoise();
    
    
    private:
  
        ofFbo               m_fbo;

        ofRectangle         m_boundingBox;
    
        float       m_noiseFrequency;
        float       m_noiseSpeed;
        int         m_noiseResolution;
    
        ofColor     m_color;
        bool        m_playNoise;
        ofImage     m_noiseImage;
};




