/*
 *  AppManager.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false)
{
   //Intentionally left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;

    //ofSetDataPathRoot("../Resources/data/");
    
    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    
    //setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
    ofSetLogLevel(OF_LOG_NOTICE);
    //ofSetFrameRate(25);
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(true);
}


void AppManager::setupManagers()
{
    m_settingsManager.setup();
    m_resourceManager.setup();
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_layoutManager.setup();
    m_videoOutputManager.setup();
    m_keyboardManager.setup();
    m_noiseManager.setup();
    m_videoManager.setup();
    m_audioVisualsManager.setup();
    m_guiManager.setup();
    m_noiseManager.resetPosition();
    m_videoManager.resetPosition();
    m_audioVisualsManager.resetPosition();
    
}

void AppManager::update()
{
    m_visualEffectsManager.update();
    m_viewManager.update();
    m_noiseManager.update();
    m_videoManager.update();
    m_audioVisualsManager.update();
}


void AppManager::draw()
{
    
    //ofBackgroundGradient( ofColor(80), ofColor(55), OF_GRADIENT_CIRCULAR );
    ofBackground(55,55,55);
    m_viewManager.draw();
    m_guiManager.draw();
    
    m_videoOutputManager.begin();
        m_noiseManager.draw();
        m_videoManager.draw();
        m_audioVisualsManager.draw();
    m_videoOutputManager.end();
    
    m_videoOutputManager.draw();
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}



