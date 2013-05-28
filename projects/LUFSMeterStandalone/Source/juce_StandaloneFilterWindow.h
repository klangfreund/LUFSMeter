/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_STANDALONEFILTERWINDOW_JUCEHEADER__
#define __JUCE_STANDALONEFILTERWINDOW_JUCEHEADER__

extern AudioProcessor* JUCE_CALLTYPE createPluginFilter ();

//==============================================================================
/**
    A class that can be used to run a simple standalone application containing 
    your filter.

    Just create one of these objects in your JUCEApplication::initialise()
    method, and let it do its work. It will create your filter object using the
    same createFilter() function that the other plugin wrappers use.
*/
class StandaloneFilterWindow    : public DocumentWindow,
                                  public ApplicationCommandTarget,
                                    // This will be registered at the
                                    // globalCommandManager.
                                  public MenuBarModel
{
public:
    //==============================================================================
    /** Creates a window with a given title and colour.
        The settings object can be a PropertySet that the class should use to
        store its settings - the object that is passed-in will be owned by this
        class and deleted automatically when no longer needed. (It can also be null)
    */
    StandaloneFilterWindow (const String& title,
                            const Colour& backgroundColour,
                            PropertySet* settingsToUse)
        : DocumentWindow (title, backgroundColour, DocumentWindow::minimiseButton | DocumentWindow::closeButton),
          settings (settingsToUse)
    {
        // Register the StandaloneFilterWindow as ApplicationCommandTarget.
        globalCommandManager.registerAllCommandsForTarget (this);
        //globalCommandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());
        
        // This lets the command manager use keypresses that arrive in our
        // window to send out commands.
        addKeyListener (globalCommandManager.getKeyMappings());

#if JUCE_MAC
        setMenuBar (nullptr); // Disable the main menu below the window title bar.
        MenuBarModel::setMacMainMenu (this); // Enable
#else
        setMenuBar (this);
#endif
        
        // Tells our menu bar model that it should watch the
        // globalCommandManager for changes, and send change messages
        // accordingly.
        // Without this, the entries in the menu bar are greyed out.
        // (For example, they are greyed out as soon as the Audio Settings
        // Dialog is open an has the focus.)
        setApplicationCommandManagerToWatch (&globalCommandManager);
        
        setUsingNativeTitleBar (true);
        //setTitleBarButtonsRequired (DocumentWindow::minimiseButton | DocumentWindow::closeButton, false);

        createFilter();

        if (filter == nullptr)
        {
            jassertfalse    // Your filter didn't create correctly! In a standalone app that's not too great.
            JUCEApplication::quit();
        }

        filter->setPlayConfigDetails (JucePlugin_MaxNumInputChannels,
                                      JucePlugin_MaxNumOutputChannels,
                                      44100, 512);

        deviceManager = new AudioDeviceManager();
        deviceManager->addAudioCallback (&player);
        deviceManager->addMidiInputCallback (String::empty, &player);

        player.setProcessor (filter);

        ScopedPointer<XmlElement> savedState;

        if (settings != nullptr)
            savedState = settings->getXmlValue ("audioSetup");

        deviceManager->initialise (filter->getNumInputChannels(),
                                   filter->getNumOutputChannels(),
                                   savedState,
                                   true);

        if (settings != nullptr)
        {
            MemoryBlock data;

            if (data.fromBase64Encoding (settings->getValue ("filterState"))
                 && data.getSize() > 0)
            {
                filter->setStateInformation (data.getData(), data.getSize());
            }
        }

        setContentOwned (filter->createEditorIfNeeded(), true);

        if (settings != nullptr)
        {
            const int x = settings->getIntValue ("windowX", -100);
            const int y = settings->getIntValue ("windowY", -100);

            if (x != -100 && y != -100)
                setBoundsConstrained (Rectangle<int> (x, y, getWidth(), getHeight()));
            else
                centreWithSize (getWidth(), getHeight());
        }
        else
        {
            centreWithSize (getWidth(), getHeight());
        }
    }

    ~StandaloneFilterWindow()
    {
        if (settings != nullptr)
        {
            settings->setValue ("windowX", getX());
            settings->setValue ("windowY", getY());

            if (deviceManager != nullptr)
            {
                ScopedPointer<XmlElement> xml (deviceManager->createStateXml());
                settings->setValue ("audioSetup", xml);
            }
        }

        deviceManager->removeMidiInputCallback (String::empty, &player);
        deviceManager->removeAudioCallback (&player);
        deviceManager = nullptr;

        if (settings != nullptr && filter != nullptr)
        {
            MemoryBlock data;
            filter->getStateInformation (data);

            settings->setValue ("filterState", data.toBase64Encoding());
        }

        deleteFilter();
        
        // because we've set the StandaloneFilterWindow to be used as our menu
        // bar model, we have to switch this off before deleting the
        // StandaloneFilterWindow.
        setMenuBar (nullptr);
        
#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
        MenuBarModel::setMacMainMenu (nullptr);
#endif
    }

    //==========================================================================
    AudioProcessor* getAudioProcessor() const noexcept      { return filter; }
    AudioDeviceManager* getDeviceManager() const noexcept   { return deviceManager; }
    
    //==========================================================================
    // ApplicationCommandTarget methods:
    ApplicationCommandTarget* getNextCommandTarget()
    {
        // Source: Juce Demo.
        // This will return the next parent component that is an ApplicationCommandTarget (in this
        // case, there probably isn't one, but it's best to use this method in your own apps).
        return findFirstTargetParentComponent();
    }
    
    void getAllCommands (Array <CommandID>& commands)
    {
        // this returns the set of all commands that this target can perform..
        const CommandID ids[] = {   showAudioSettings,
                                    saveCurrentState,
                                    loadASavedState,
                                    resetToDefaultState
                                };
        
        commands.addArray (ids, numElementsInArray (ids));
    }
    
    // This method is used when something needs to find out the details about one of the commands
    // that this object can perform..
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
    {
        const String optionsCategory ("Options");
        
        switch (commandID)
        {
            case showAudioSettings:
                result.setInfo ("Audio Settings...",
                                "Shows the audio settings dialog",
                                optionsCategory,
                                0);
                result.addDefaultKeypress (',', ModifierKeys::commandModifier);
                break;
                
            case saveCurrentState:
                result.setInfo ("Save current state...",
                                "Saves the current state",
                                optionsCategory,
                                0);
                result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
                break;
                
            case loadASavedState:
                result.setInfo ("Load a saved state...",
                                "Loads a saved state",
                                optionsCategory,
                                0);
                result.addDefaultKeypress ('o', ModifierKeys::commandModifier);
                break;
                
            case resetToDefaultState:
                result.setInfo ("Reset to the default state",
                                "Reset to the default state",
                                optionsCategory,
                                0);
                result.addDefaultKeypress ('r', ModifierKeys::commandModifier);
                break;
                
            default:
                break;
        };
    }
    
    // This is the ApplicationCommandTarget method that is used to actually
    // perform one of our commands..
    bool perform (const InvocationInfo& info)
    {
        switch (info.commandID)
        {
            case showAudioSettings:
                showAudioSettingsDialog();
                break;
            
            case saveCurrentState:
                saveState();
                break;
                
            case loadASavedState:
                loadState();
                break;
                
            case resetToDefaultState:
                resetFilter();
                break;
                
            default:
                return false;
        };
        
        return true;
    }
    
    
    //==========================================================================
    // MenuBarModel methods
    
    StringArray getMenuBarNames()
    {
        const char* const names[] = { "Options", nullptr };
        
        return StringArray (names);
    }

    PopupMenu getMenuForIndex (int menuIndex, const String& /*menuName*/)
    {
        PopupMenu menu;

        if (menuIndex == 0)
        {
            menu.addCommandItem (&globalCommandManager, showAudioSettings);
            menu.addCommandItem (&globalCommandManager, saveCurrentState);
            menu.addCommandItem (&globalCommandManager, loadASavedState);
            menu.addCommandItem (&globalCommandManager, resetToDefaultState);
        }
        return menu;
    }
    
    void menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/)
    {
        // most of our menu items are invoked automatically as commands, but we
        // could handle the other special cases here..
    }
    
    //==========================================================================
    

    void createFilter()
    {
        AudioProcessor::setTypeOfNextNewPlugin (AudioProcessor::wrapperType_Standalone);
        filter = createPluginFilter();
        AudioProcessor::setTypeOfNextNewPlugin (AudioProcessor::wrapperType_Undefined);
    }

    /** Deletes and re-creates the filter and its UI. */
    void resetFilter()
    {
        deleteFilter();
        createFilter();

        if (filter != nullptr)
        {
            if (deviceManager != nullptr)
                player.setProcessor (filter);

            setContentOwned (filter->createEditorIfNeeded(), true);
        }

        if (settings != nullptr)
            settings->removeValue ("filterState");
    }

    /** Pops up a dialog letting the user save the filter's state to a file. */
    void saveState()
    {
        FileChooser fc (TRANS("Save current state"),
                        settings != nullptr ? File (settings->getValue ("lastStateFile"))
                                            : File::nonexistent);

        if (fc.browseForFileToSave (true))
        {
            MemoryBlock data;
            filter->getStateInformation (data);

            if (! fc.getResult().replaceWithData (data.getData(), data.getSize()))
            {
                AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                             TRANS("Error whilst saving"),
                                             TRANS("Couldn't write to the specified file!"));
            }
        }
    }

    /** Pops up a dialog letting the user re-load the filter's state from a file. */
    void loadState()
    {
        FileChooser fc (TRANS("Load a saved state"),
                        settings != nullptr ? File (settings->getValue ("lastStateFile"))
                                            : File::nonexistent);

        if (fc.browseForFileToOpen())
        {
            MemoryBlock data;

            if (fc.getResult().loadFileAsData (data))
            {
                filter->setStateInformation (data.getData(), data.getSize());
            }
            else
            {
                AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                             TRANS("Error whilst loading"),
                                             TRANS("Couldn't read from the specified file!"));
            }
        }
    }

    /** Shows the audio properties dialog box modally. */
    virtual void showAudioSettingsDialog()
    {
        DialogWindow::LaunchOptions o;
        o.content.setOwned (new AudioDeviceSelectorComponent (*deviceManager,
                                                              filter->getNumInputChannels(),
                                                              filter->getNumInputChannels(),
                                                              filter->getNumOutputChannels(),
                                                              filter->getNumOutputChannels(),
                                                              true, false, true, false));
        o.content->setSize (500, 450);

        o.dialogTitle                   = TRANS("Audio Settings");
        o.dialogBackgroundColour        = Colours::lightgrey;
        o.escapeKeyTriggersCloseButton  = true;
        o.useNativeTitleBar             = true;
        o.resizable                     = false;

        o.launchAsync();
    }

    //==============================================================================
    /** @internal */
    void closeButtonPressed()
    {
        JUCEApplication::quit();
    }

    /** @internal */
    void resized()
    {
        DocumentWindow::resized();
    }

private:
    //==============================================================================
    ScopedPointer<PropertySet> settings;
    ScopedPointer<AudioProcessor> filter;
    ScopedPointer<AudioDeviceManager> deviceManager;
    AudioProcessorPlayer player;
    
    // The global command manager object used to dispatch command events
    ApplicationCommandManager globalCommandManager;

    void deleteFilter()
    {
        player.setProcessor (nullptr);

        if (filter != nullptr && getContentComponent() != nullptr)
        {
            filter->editorBeingDeleted (dynamic_cast <AudioProcessorEditor*> (getContentComponent()));
            clearContentComponent();
        }

        filter = nullptr;
    }
    
    enum CommandIDs
    {
        showAudioSettings           = 0x2000,
        saveCurrentState            = 0x2001,
        loadASavedState             = 0x2002,
        resetToDefaultState         = 0x2003
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StandaloneFilterWindow)
};

#endif   // __JUCE_STANDALONEFILTERWINDOW_JUCEHEADER__
