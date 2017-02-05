/*
 *  VideoOutputManager.cpp
 *  Murmur
 *
 *  Created by Imanol Gomez on 29/09/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "VideoOutputManager.h"



VideoOutputManager::VideoOutputManager(): Manager()
{
	//Intentionally left empty
}


VideoOutputManager::~VideoOutputManager()
{
    ofLogNotice() <<"VideoOutputManager::Destructor";
}


void VideoOutputManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupFbo();
    this->setupSyphon();
    
    ofLogNotice() <<"VideoOutputManager::initialized";

}

void VideoOutputManager::setupFbo()
{
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth() - AppManager::getInstance().getGuiManager().getWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fboVideoOutput.allocate(width, height);
    m_fboVideoOutput.begin(); ofClear(0); m_fboVideoOutput.end();
}

void VideoOutputManager::setupSyphon()
{
    string name = AppManager::getInstance().getSettingsManager().getSyphonName();
    m_syphonServer.setName(name);
    
    ofLogNotice() <<"VideoOutputManager::setupSyphon << Setting up Syphon server: " << name;
}

void VideoOutputManager::draw()
{
    m_fboVideoOutput.draw(0,0);
    
    m_syphonServer.publishTexture(&m_fboVideoOutput.getTexture());
}


void VideoOutputManager::begin()
{
    m_fboVideoOutput.begin();
    ofClear(0);
}

void VideoOutputManager::end()
{
     m_fboVideoOutput.end();
}





