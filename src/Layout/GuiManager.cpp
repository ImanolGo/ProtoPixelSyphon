/*
 *  GuiManager.cpp
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */
#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "HeroDress";
const int GuiManager::GUI_WIDTH = 200;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
	//Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;
    
    Manager::setup();


    this->setupGuiParameters();
    this->setupModesGui();
    this->setupLayoutGui();
    this->setupVideoGui();
    this->setupAudioGui();
    this->setupNoiseGui();
    this->loadGuiValues();
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(ofGetWidth() - GUI_WIDTH - 20, 40);
    //m_gui.setPosition(20, 20);
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    ofxGuiSetFont( "fonts/open-sans/OpenSans-Semibold.ttf", 9 );

}


void GuiManager::setupModesGui()
{

    m_parametersModes.setName("Modes");
    
    m_videoMode.set("Video",  false );
    m_videoMode.addListener(this, &GuiManager::onSetVideoMode);
    m_parametersModes.add(m_videoMode);
    
    m_noiseMode.set("Noise",  false );
    m_noiseMode.addListener(this, &GuiManager::onSetNoiseMode);
    m_parametersModes.add(m_noiseMode);
    
    m_audioMode.set("Audio",  false );
    m_audioMode.addListener(this, &GuiManager::onSetAudioMode);
    m_parametersModes.add(m_audioMode);
    
    m_gui.add(m_parametersModes);
}

void GuiManager::setupLayoutGui()
{
    auto layoutManager = &AppManager::getInstance().getLayoutManager();
    auto videoOutputManager = &AppManager::getInstance().getVideoOutputManager();
    
    m_parametersLayout.setName("Color");
    
    m_hue.set("Hue", 0.0, 0.0, 255.0);
    m_hue.addListener(layoutManager, &LayoutManager::onHueChange);
    m_parametersLayout.add(m_hue);
    
    m_saturation.set("Saturation", 0.0, 0.0, 255.0);
    m_saturation.addListener(layoutManager, &LayoutManager::onSaturationChange);
    m_parametersLayout.add(m_saturation);
    
    m_brightness.set("Brightness", 0.0, 0.0, 255.0);
    m_brightness.addListener(layoutManager, &LayoutManager::onBrightnessChange);
    m_parametersLayout.add(m_brightness);
    
    m_blurRadius.set("Blur", 0.0, 0.0, 10.0);
    m_blurRadius.addListener(videoOutputManager, &VideoOutputManager::onBlurScaleChange);
    m_parametersLayout.add(m_blurRadius);
    
    m_gui.add(m_parametersLayout);
}

void GuiManager::setupVideoGui()
{
    auto videoManager = &AppManager::getInstance().getVideoManager();
    
    m_parametersVideo.setName("Video");
    
    m_videoSpeed.set("Speed", 1.0, 0.0, 2.0);
    m_videoSpeed.addListener(videoManager, &VideoManager::onVideoSpeedChange);
    m_parametersVideo.add(m_videoSpeed);
    
    m_nextVideo.setup("Next Video");
    m_nextVideo.addListener(videoManager, &VideoManager::onNextVideoChange);
    
    m_videoTrail.set("Video Trail", false);
    m_videoTrail.addListener(videoManager, &VideoManager::onVideoTrailChange);
    m_parametersVideo.add(m_videoTrail);

    
    m_gui.add(m_parametersVideo);
    m_gui.add(&m_nextVideo);
    
}

void GuiManager::setupAudioGui()
{
    auto audioVisualManager = &AppManager::getInstance().getAudioVisualsManager();
    auto audioManager = &AppManager::getInstance().getAudioManager();
    
    m_parametersAudio.setName("Audio");
    
    m_audioLevel.set("Audio Level",  0.5, 0.0, 1.0 );
    m_audioLevel.addListener(audioVisualManager, &AudioVisualsManager::onInputLevelChange);
    m_parametersAudio.add(m_audioLevel);
    
    m_audioOn.set("Audio On", false);
    m_audioOn.addListener(audioManager, &AudioManager::onChangeAudioOn);
    m_parametersAudio.add(m_audioOn);
    
    m_nextAudio.setup("Next Visual");
    m_nextAudio.addListener(audioVisualManager, &AudioVisualsManager::onNextAudiohange);
    
    m_gui.add(m_parametersAudio);
    m_gui.add(&m_nextAudio);
}

void GuiManager::setupNoiseGui()
{
    auto noiseManager = &AppManager::getInstance().getNoiseManager();
    
    m_parametersNoise.setName("Noise");

    m_noiseResolution.set("Noise Resolution",  64, 2, 256 );
    m_noiseResolution.addListener(noiseManager, &NoiseManager::onNoiseResolutionChange);
    m_parametersNoise.add(m_noiseResolution);
        
    m_noiseFrequency.set("Noise Frequency",  0.4, 0.0, 4.0);
    m_noiseFrequency.addListener(noiseManager, &NoiseManager::onNoiseFrequencyChange);
    m_parametersNoise.add(m_noiseFrequency);
    
    m_noiseSpeed.set("Noise Speed",  1.0, 0.001, 3);
    m_noiseSpeed.addListener(noiseManager, &NoiseManager::onNoiseSpeedChange);
    m_parametersNoise.add(m_noiseSpeed);

    
    m_gui.add(m_parametersNoise);
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    
    m_guiFPS = ofGetFrameRate();
    m_gui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofDrawRectangle( m_gui.getPosition().x - 20, 0, GUI_WIDTH + 60, ofGetHeight());
    ofPopStyle();
}



void GuiManager::onSetVideoMode(bool& value)
{
    if(value == true)
    {
        m_noiseMode = false;
        m_audioMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(true);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(false);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(false);
    }

}

void GuiManager::onSetNoiseMode(bool& value)
{
    if(value == true)
    {
        m_videoMode = false;
        m_audioMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(false);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(true);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(false);
    }
}

void GuiManager::onSetAudioMode(bool& value)
{
    if(value == true)
    {
        m_videoMode = false;
        m_noiseMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(false);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(false);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(true);
    }
    
}
