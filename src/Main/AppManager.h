/*
 *  AppManager.h
 *  ProtoPixel Syphon
 *
 *  Created by Imanol Gomez on 05/02/17.
 *
 */


#pragma once

#include "ofMain.h"

#include "Manager.h"

#include "SettingsManager.h"
#include "ResourceManager.h"
#include "ViewManager.h"
#include "VisualEffectsManager.h"
#include "LayoutManager.h"
#include "KeyboardManager.h"
#include "GuiManager.h"
#include "NoiseManager.h"
#include "VideoManager.h"
#include "AudioVisualsManager.h"
#include "VideoOutputManager.h"
#include "AudioManager.h"


//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //==========================================================================

    //! Returns the settings manager
    SettingsManager& getSettingsManager() { return m_settingsManager; }
    
    //! Returns the layout manager
    LayoutManager& getLayoutManager() { return m_layoutManager; }
    
    //! Returns the resource manager
    ResourceManager& getResourceManager() { return m_resourceManager; }
    
    //! Returns the view manager
    ViewManager&  getViewManager() { return m_viewManager; }
    
    //! Returns the visual effects manager
    VisualEffectsManager&  getVisualEffectsManager() { return m_visualEffectsManager; }
    
    //! Returns the GUI manager
    GuiManager&   getGuiManager() { return m_guiManager; }
    
    //! Returns the Noise manager
    NoiseManager&   getNoiseManager() { return m_noiseManager; }
    
    //! Returns the video manager
    VideoManager&   getVideoManager() { return m_videoManager; }
    
    //! Returns the audio visuals manager
    AudioVisualsManager&   getAudioVisualsManager() { return m_audioVisualsManager; }
    
    //! Returns the video output manager
    VideoOutputManager&   getVideoOutputManager() { return m_videoOutputManager; }
    
    //! Returns the audio  manager
    AudioManager&  getAudioManager() { return m_audioManager; }
    
    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    

private:

     //! Constructor
     AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();

private:


    SettingsManager          m_settingsManager;          ///< Manages the application's settings
    ResourceManager          m_resourceManager;          ///< Manages the application's resources
    ViewManager              m_viewManager;              ///< Manages visuals
    VisualEffectsManager     m_visualEffectsManager;     ///< Manages visual effects
    LayoutManager            m_layoutManager;            ///< Manages the layout
    KeyboardManager          m_keyboardManager;          ///< Manages the keyboard
    GuiManager               m_guiManager;               ///< Manages the graphical user interface
    NoiseManager             m_noiseManager;             ///< Manages the noise visuals
    VideoManager             m_videoManager;             ///< Manages the video  visuals
    AudioVisualsManager      m_audioVisualsManager;      ///< Manages the audio reactive visuals
    VideoOutputManager       m_videoOutputManager;       ///< Manages the video output
    AudioManager             m_audioManager;             ///< Manages the audio manager

    bool                     m_debugMode;
};

//==========================================================================


