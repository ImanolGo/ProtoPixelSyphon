/*
 *  VideoOutputManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxSyphon.h"
#include "ofxBlur.h"

//========================== class VideoOutputManager ==============================
//============================================================================
/** \class VideoOutputManager VideoOutputManager.h
 *	\brief Class managing the preview of the application
 *	\details It reads the render visuals in the other windows and previews them in the main window
 */

class VideoOutputManager: public Manager
{
public:

    //! Constructor
    VideoOutputManager();

    //! Destructor
    ~VideoOutputManager();

    //! Set-up the layout
    void setup();
    
    //! Draw Layer
    void draw();
    
    //! Draw a specific fbo
    void draw(int windowIndex);
    
    //! Begin fbo for a specific window
    void begin();
    
    //! End fbo for a specific window
    void end();
    
    const ofFbo& getVideoFbo() {return m_fboVideoOutput;}
    
    void onBlurScaleChange(float& value);

private:

    //! Set-up the fbo
    void setupFbo();
    
    //! Set-up the syphon server
    void setupSyphon();
    
    //! Set-up the blur filter
    void setupBlur();

private:
    
    ofFbo               m_fboVideoOutput;
    ofxSyphonServer     m_syphonServer;
    ofxBlur             m_blur;
    float               m_blurScale;

};

//==========================================================================


